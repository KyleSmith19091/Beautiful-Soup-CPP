#include "../include/TreeSitterParser.hpp"

TreeSitterParser::TreeSitterParser() {
    parser = ts_parser_new();
    ts_parser_set_language(parser, tree_sitter_html());
}

TreeSitterParser::~TreeSitterParser() {
    ts_parser_delete(parser);
}

Tree TreeSitterParser::parse(const std::string& source_code) {
    return Tree(this->parser,source_code);
}

