#include "git3/branch_tree.hh"
#include "git3/exceptions/exceptions.hh"

#include "absl/base/macros.h"

#include <iostream>
#include <stdexcept>

namespace g3 {

// Each time we add a branch, we add it to the map of
// oid -> downstream oid's
void BranchTreeBuilder::addBranch(Branch&& b) {
  const auto upstream = b.upstream();

  if (upstream) {
    _state._edges[upstream.oid()].push_back(b.oid());
  }

  _state._branches.emplace(b.oid(), std::move(b));
}

namespace {
bool all_contained(const std::vector<Oid> ids,
                   const absl::flat_hash_map<Oid, BranchTreeNode>& nodes) {
  return std::all_of(ids.begin(), ids.end(), [&nodes](const Oid& downstream) {
    return nodes.count(downstream);
  });
}
}  // namespace

BranchTree BranchTreeBuilder::buildTree() {
  return BranchTreeBuilder::buildTree(std::move(this->_state));
}

BranchTree BranchTreeBuilder::buildTree(State&& state) {
  absl::flat_hash_map<Oid, BranchTreeNode> nodes;
  nodes.reserve(state._branches.size());

  std::cout << "Above loop, branches.size() == " << state._branches.size()
            << std::endl;

  if (state._branches.empty()) {
    throw NoBranches();
  }

  // While there are still branches to process
  while (state._branches.size()) {
    std::cout << "Outer loop, branches.size() == " << state._branches.size()
              << std::endl;

    auto it = state._branches.begin();
    const auto end = state._branches.end();

    bool no_branches_were_processed = true;

    // For each branch
    while (it != end) {
      std::cout << "Inner Loop" << std::endl;
      // If that branch has no downstream _or_ we have already created
      // nodes for all of its downstreams, then we can create a node for
      // it, and delete it.
      //
      // /usr/include/c++/8/bits/stl_pair.h: In instantiation of
      //     'struct std::pair<const g3::Oid, g3::Branch>':
      // git3/branch_tree.cc:77:35:   required from here
      // /usr/include/c++/8/bits/stl_pair.h:303:17: error:
      //      'constexpr std::pair<_T1, _T2>::pair(const std::pair<_T1, _T2>&)
      //         [with _T1 = const g3::Oid; _T2 = g3::Branch]'
      //      declared to take const reference, but implicit declaration would
      //      take non-const
      //        constexpr pair(const pair&) = default;
      //                         ^~~~
      //

      // std::pair<const Oid, Branch>& pair_result = *it;
      const Oid oid = it->first;  // pair_result.first;

      auto edge_it = state._edges.find(oid);

      if (edge_it == state._edges.end() ||
          all_contained(edge_it->second, nodes)) {
        no_branches_were_processed = false;
        std::cout << "No edges, or all already have nodes" << std::endl;
        // If there are no edges out of the branch (no downstreams)
        // _OR_ nodes have been created for all downstreams, then
        // we create a node for this branch, and delete it from the map
        auto newNode = nodes.emplace(it->first, std::move(it->second));
        state._branches.erase(it++);

        // We create the vector of downstream branches, by moving-out and then
        // deleting the entries in the `node` map. This is the correct thing to
        // do, because we know that each branch will only have a single
        // upstream, so it is fine for the upstream to own all of its downstream
        // branches.
        if (edge_it != state._edges.end()) {
          std::cout << "there are some edges, adding children" << std::endl;
          std::transform(
              edge_it->second.begin(), edge_it->second.end(),
              std::back_inserter(newNode.first->second._downstreamBranches),
              [&nodes](const Oid& oid) {
                auto node_it = nodes.find(oid);
                BranchTreeNode output{std::move(node_it->second)};
                nodes.erase(node_it);
                return output;
              });
        }
      } else {
        std::cout << "Some edges with children that are not yet processed, "
                     "skipping for now"
                  << std::endl;
        // Otherwise we will process this branch in a subsequent iteration
        ++it;
      }
    }

    if (no_branches_were_processed) {
      throw CycleDetected(std::move(state));
    }
  }

  ABSL_ASSERT(nodes.size() == 1);

  return BranchTree(std::move(nodes.begin()->second));
}

}  // namespace g3
