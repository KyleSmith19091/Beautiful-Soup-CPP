#ifndef QUERY_HPP 
#define QUERY_HPP

#include <tree-sitter/lib/include/tree_sitter/api.h>
#include <string>

extern "C" {
    TSLanguage *tree_sitter_html();
}

class Query{
    private:
        TSQuery* q;         
        TSQueryError* error;
        uint32_t* error_offset;

    public:
        Query(const std::string&) noexcept;
        ~Query();

        TSQuery* getQuery() const noexcept { return this->q; };
        TSQueryError* getError() const noexcept { return this->error; };
        uint32_t* getErrorOffset() const noexcept { return this->error_offset; };
};	
#endif
