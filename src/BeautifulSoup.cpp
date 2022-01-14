#include "../include/BeautifulSoup.hpp"
#include <tree-sitter/lib/include/tree_sitter/api.h>
#include <utility>
#include <iostream>

BeautifulSoup::BeautifulSoup(const std::string& URL) : tree(this->parser.parse(performCURLGetRequest(URL))){
}

BeautifulSoup::~BeautifulSoup() {
    curl_easy_cleanup(curl);
    curl = NULL;
}

size_t BeautifulSoup::writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

std::string BeautifulSoup::performCURLGetRequest(const std::string& URL) {
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.42.0");
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
        curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
        
        std::string response_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        curl_easy_perform(curl);

        // Clean the html
        std::replace(response_string.begin(), response_string.end(), '\n',' '); 

        return response_string;
    } else {
        throw "cURL could not start!";
    }
}

std::map<std::string,std::string> BeautifulSoup::createAttribsMap(const std::string& source, const std::vector<Node>& attribs) noexcept {
    std::string value("");
    std::string attrib("");
    std::string val("");
    std::map<std::string,std::string> attribValues;

    for(auto& a : attribs) {
        std::pair<uint32_t,uint32_t> idxsValue = a.getNodeTextIndices(); 
        value = source.substr(idxsValue.first,idxsValue.second - idxsValue.first);
        value.erase(std::remove_if(value.begin(), value.end(), [](char c) {
            return c == '"';
        }), value.end());

        int equalIdx = value.find_first_of("=");
        attrib = value.substr(0,equalIdx);
        val = value.substr(equalIdx+1);
        attribValues.insert({attrib,val});
    }

    return attribValues;
}

bool BeautifulSoup::findMapIntersection(std::map<std::string,std::string>& cmpMap, std::map<std::string,std::string>& givenMap) {
    const unsigned int numKeys = givenMap.size();
    unsigned int numKeysFound = 0;

    for(auto attrib : givenMap) {
        const auto key = attrib.first;
        const auto value = attrib.second;
        if(cmpMap.find(key) != cmpMap.end() && cmpMap[key].find(value) != std::string::npos) {
            numKeysFound++;
        }
    } 

    return numKeys == numKeysFound;
}

std::vector<Node> BeautifulSoup::getTagNameNodes(const Node& nodeToSearchFrom) const noexcept {
    return tree.execQuery("(start_tag (tag_name) @name)", nodeToSearchFrom);
}

std::vector<Node> BeautifulSoup::getTagAttributeNodes(const Node& nodeToSearchFrom) const noexcept {
    return tree.execQuery("(start_tag (attribute) @attribs)", nodeToSearchFrom);
}

std::vector<TagNode> BeautifulSoup::filterOutTagNames(const std::string& tagName, std::vector<Node>& tagNameNodes) noexcept {
    std::vector<TagNode> tagNodes;
    std::string matchTextValue("");
    std::string source(tree.getSourceCode());
    Node tag;

    for(auto& n : tagNameNodes) {
        // Get Tag source code indices
        const std::pair<uint32_t,uint32_t> idxsValue = n.getNodeTextIndices(); 

        // Grab tag name substring from source
        matchTextValue = source.substr(idxsValue.first,idxsValue.second - idxsValue.first);

        // Check if the tag name is the same
        if(isStringsEqual(tagName, matchTextValue)) {
            tag = n.getParent().getParent(); // Extract whole tag by traversing up tree
            const auto attribsString = getTagAttributeNodes(tag);
            auto attribs = createAttribsMap(source, attribsString);
            tagNodes.push_back(TagNode(tag,attribs));
        }
    }

    return tagNodes;
}

std::vector<TagNode> BeautifulSoup::filterByTagNameUsingAttribs(const Node& startNode, const std::string& tagName, std::map<std::string,std::string>& attrs, const bool& returnFirstValue) noexcept {
    // Nodes to return
    std::vector<TagNode> nodes;

    // Read source code once
    std::string source(tree.getSourceCode());

    // Text from source
    std::string matchTextValue("");

    // Entire tag element node
    Node tag;

    // Grab tag names from ast
    auto matchedTagNameNodes = getTagNameNodes(startNode);

    // Filter out tag names that do not match given tag name
    auto filteredTagNames = filterOutTagNames(tagName, matchedTagNameNodes);

    // No attributes provided
    if(attrs.size() == 0) {
        return filteredTagNames;
    }

    if(!returnFirstValue) {
        for(auto& n : filteredTagNames) {
            auto attribs = n.attrs();
            if(findMapIntersection(attribs,attrs)) {
                nodes.push_back(n);
            }
        }
    } else {
        for(auto& n : filteredTagNames) {
            auto attribs = n.attrs();
            if(findMapIntersection(attribs,attrs)) {
                nodes.push_back(n);
                return nodes;
            }
        }
    }

    return nodes;
}

std::vector<TagNode> BeautifulSoup::find_all(const std::string& tag_name, std::map<std::string,std::string> attrs) {
    return filterByTagNameUsingAttribs(tree.root_node, tag_name, attrs, false);
}

std::vector<TagNode> BeautifulSoup::find_all(const Node& node, const std::string& tag_name, std::map<std::string,std::string> attrs) {
    return filterByTagNameUsingAttribs(node, tag_name, attrs, false);
}

std::vector<TagNode> BeautifulSoup::find_all(const std::string& tag_name) {
    std::map<std::string,std::string> emptyMap;
    return filterByTagNameUsingAttribs(tree.root_node, tag_name, emptyMap, false);
}

std::vector<TagNode> BeautifulSoup::find_all(const Node& node, const std::string& tag_name) {
    std::map<std::string,std::string> emptyMap;
    return filterByTagNameUsingAttribs(node, tag_name, emptyMap, false);
}

TagNode BeautifulSoup::find(const std::string& tag_name, std::map<std::string,std::string> attrs) {
    return filterByTagNameUsingAttribs(tree.root_node, tag_name, attrs, true)[0];
}

TagNode BeautifulSoup::find(const std::string& tag_name) {
    std::map<std::string,std::string> emptyMap;
    return filterByTagNameUsingAttribs(tree.root_node, tag_name, emptyMap, true)[0];
}

TagNode BeautifulSoup::find(const Node& n, const std::string& tag_name, std::map<std::string,std::string> attrs) {
    return filterByTagNameUsingAttribs(n, tag_name, attrs, true)[0];
}

TagNode BeautifulSoup::find(const Node& n, const std::string& tag_name) {
    std::map<std::string,std::string> emptyMap;
    return filterByTagNameUsingAttribs(n, tag_name, emptyMap, true)[0];
}

std::string BeautifulSoup::getNodeText(const Node &n) {
    return this->tree.getNodeText(n);
}

std::string BeautifulSoup::getNodeData(const Node &n) {
    auto nodePosition = n.getNodeTextIndices();
    return this->tree.getSourceCode().substr(nodePosition.first, nodePosition.second - nodePosition.first);
}

Node BeautifulSoup::getRootNode() const {
    return this->tree.root_node;
}

