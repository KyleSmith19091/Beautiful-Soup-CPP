#include "../include/Query.hpp"

Query::Query(const std::string& query) noexcept {
    error = (TSQueryError*)malloc(sizeof(TSQueryError));
    error_offset = (uint32_t*)malloc(sizeof(uint32_t));
    q = ts_query_new(tree_sitter_html(), query.c_str(), strlen(query.c_str()),error_offset,error);
}

Query::~Query() {
    ts_query_delete(q);
    delete(error);
    delete(error_offset);
}
