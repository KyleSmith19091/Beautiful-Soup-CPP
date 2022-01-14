#ifndef BEAUTIFUL_SOUP_HPP 
#define BEAUTIFUL_SOUP_HPP

#include "TreeSitterParser.hpp"
#include "Tree.hpp"
#include "TagNode.hpp"
#include "Node.hpp"
#include "Query.hpp"

#include <curl/curl.h>

#include <vector>
#include <string>
#include <utility>

class BeautifulSoup {
    private:
        // For creating handling HTML parse tree
        TreeSitterParser parser;
        Tree tree;

        // For performing GET requests
        CURL* curl;

        // Functions for performing GET requests
        static size_t writeFunction(void*, size_t, size_t, std::string*);
        std::string performCURLGetRequest(const std::string&);

        // Get list of Tag Name Nodes from Tree
        std::vector<Node> getTagNameNodes(const Node&) const noexcept;

        // Get list of tag attributes from the given node
        std::vector<Node> getTagAttributeNodes(const Node&) const noexcept;
        
        // Check if given node has same attributes
        void checkIfNodeAttribsAreSame(const Node&, std::vector<Node>&, std::vector<TagNode>&) noexcept;

        std::vector<TagNode> filterOutTagNames(const std::string&, std::vector<Node>&) noexcept;

        // Helper function for getting tags assiciated with a specific attribte value pair
        std::vector<TagNode> filterByTagNameUsingAttribs(const Node&, const std::string&, std::map<std::string,std::string>&, const bool&) noexcept;
        
        // Create a map of attribute value pairs given their syntax tree nodes
        std::map<std::string,std::string> createAttribsMap(const std::string&, const std::vector<Node>&) noexcept;

        // Find values from one map in another
        bool findMapIntersection(std::map<std::string,std::string>&, std::map<std::string,std::string>&);

        constexpr static bool strings_equal(char const * a, char const * b) noexcept {
            return *a == *b && (*a == '\0' || strings_equal(a + 1, b + 1));
        }

        constexpr static bool isStringsEqual(const std::string& a, const std::string& b) noexcept {
            return strings_equal(a.c_str(), b.c_str());
        }


    public:
        /**
         * @brief Construct a new Beautiful Soup object
         * @param URL URL of HTML document  
         */
        BeautifulSoup(const std::string&);

        /**
         * @brief Destroy the Beautiful Soup object
         */
        ~BeautifulSoup();

        /**
         * @brief Find all occurences of the given tag name using the given map as a filter 
         * @param tagName The name of the tag   
         * @param attrs The attributes to search for in the given tag name
         * @return std::vector<TagNode> 
         */
        std::vector<TagNode> find_all(const std::string&, std::map<std::string,std::string>);
        std::vector<TagNode> find_all(const std::string&);
        std::vector<TagNode> find_all(const Node&, const std::string&, std::map<std::string,std::string>);
        std::vector<TagNode> find_all(const Node&, const std::string&);

        /**
         * @brief Find first occurence of given tag using the given map as a filter 
         * @param tagName The name of the tag  
         * @param attrs The attributes to search for in the given tag name
         * @return TagNode 
         */
        TagNode find(const std::string&, std::map<std::string,std::string>);
        TagNode find(const std::string&);
        TagNode find(const Node&, const std::string&, std::map<std::string,std::string>);
        TagNode find(const Node&, const std::string&);

        std::string getNodeText(const Node& n);
        std::string getNodeData(const Node& n);

        Node getRootNode() const;
};	
#endif
