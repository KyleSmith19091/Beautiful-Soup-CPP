#include "../include/Node.hpp"

Node::Node(TSNode& n) noexcept {
    this->node = n;
}

Node::Node(TSNode&& n) noexcept {
    this->node = n;
}

Node::Node(const TSNode& n) noexcept {
    this->node = n;
}

std::pair<int32_t,int32_t> Node::getNodeTextIndices() const noexcept {
    TSPoint start = ts_node_start_point(this->node);
    TSPoint end = ts_node_end_point(this->node);
    return std::make_pair(start.column,end.column);
}
