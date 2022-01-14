#include "../include/Tree.hpp"
#include <tree-sitter/lib/include/tree_sitter/api.h>

std::vector<Node> Tree::execQuery(const std::string& queryString, const Node& n) const {
    Query q(queryString);
    TSQueryCursor* cursor = ts_query_cursor_new();    
    ts_query_cursor_exec(cursor, q.getQuery(), n.getNode());    

    TSQueryMatch* match = (TSQueryMatch*)malloc(sizeof(TSQueryMatch));
    std::string* dest = nullptr;
    std::vector<Node> matchedNodes;
    while(ts_query_cursor_next_match(cursor, match)) {
        for (uint16_t i = 0; i < match->capture_count; ++i) {
                matchedNodes.push_back(Node(match->captures[i].node));
          }
      }

    ts_query_cursor_delete(cursor);
    delete(dest);
    delete(match);
    return matchedNodes;
}

Tree::Tree(TSParser*& parser, const std::string& str) {
    source_code = str;
    tree = ts_parser_parse_string(parser, NULL, str.c_str(),str.length());
    TSNode n = ts_tree_root_node(tree);
    root_node = Node(n);
}

Tree::~Tree() {
    ts_tree_delete(tree);
}

std::string Tree::getNodeText(const Node& n) const noexcept {
    auto nodes = this->execQuery("(text) @text", n);
    return nodes.size() == 0 ? "" : this->source_code.substr(nodes[0].getNodeTextIndices().first,nodes[0].getNodeTextIndices().second - nodes[0].getNodeTextIndices().first); 
}
