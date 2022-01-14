#ifndef NODE_HPP
#define NODE_HPP

#include <tree-sitter/lib/include/tree_sitter/api.h>
#include <utility>
#include <string> 

class Node {
    private:
        TSNode node;

    public:
        Node() noexcept {};
        Node(TSNode&) noexcept;
        Node(TSNode&&) noexcept;
        Node(const TSNode&) noexcept;

        std::pair<int,int> getNodeTextIndices() const noexcept;

        // AST Tree navigation methods
        TSNode getNode() const noexcept { return this->node; };
        Node getParent() const noexcept { return ts_node_parent(this->node); };
        Node getNextSibling() const noexcept { return ts_node_next_sibling(this->node); };
        Node getPreviousSibling() const noexcept { return ts_node_prev_sibling(this->node); };

        // Node data methods
        std::string getSString() const noexcept { return ts_node_string(this->node); };
        int getChildCount() const noexcept { return ts_node_child_count(this->node); };
        Node getChildAtIndex(const uint32_t& index) const noexcept { return ts_node_child(this->node, index); };
};

#endif
