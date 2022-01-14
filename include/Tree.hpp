#ifndef TREE_HPP 
#define TREE_HPP

#include "Node.hpp" 
#include "Query.hpp"

#include <tree-sitter/lib/include/tree_sitter/api.h>
#include <string>
#include <vector>

class Tree{
    private:
        TSTree* tree;
        std::string source_code;

    public:
        Node root_node;
        Tree(TSParser*& parser,const std::string&);
        ~Tree();
        std::vector<Node> execQuery(const std::string&, const Node&) const;
        std::string getSourceCode() const noexcept { return source_code; };
        std::string getNodeText(const Node&) const noexcept;
};	
#endif
