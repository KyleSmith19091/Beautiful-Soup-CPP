#ifndef SOUP_RESULT_HPP 
#define SOUP_RESULT_HPP

#include "TagNode.hpp"

#include <vector>

class SoupResult {
    private:
        std::vector<TagNode> resultNodes;

    public:
        SoupResult(const std::vector<TagNode>&);
        ~SoupResult();
};	

#endif
