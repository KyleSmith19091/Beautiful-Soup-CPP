#ifndef TREE_SITTER_PARSER_HPP 
#define TREE_SITTER_PARSER_HPP

#include "Tree.hpp"

#include <tree-sitter/lib/include/tree_sitter/api.h>
#include <string>

class TreeSitterParser {
    private:
        TSParser* parser;

    public:
        TreeSitterParser();
        ~TreeSitterParser();
        Tree parse(const std::string&);
};	

#endif
