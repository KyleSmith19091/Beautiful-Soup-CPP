#ifndef TAG_NODE_HPP 
#define TAG_NODE_HPP

#include "Node.hpp"

#include <exception>
#include <map>
#include <Logging/Logger.hpp>

// TagNode => A specialised node for representing html tags
class TagNode : public Node {
    private:
        // Map of html tag attributes to their values
        std::map<std::string,std::string> attrsMap;

    public:
        TagNode(TSNode& n, std::map<std::string,std::string> attrsM) noexcept : Node(n) {
            this->attrsMap = attrsM;
        };

        TagNode(Node& n, std::map<std::string,std::string> attrsM) noexcept : Node(n.getNode()) {
            this->attrsMap = attrsM;
        };

        std::map<std::string,std::string> attrs() const noexcept {
            return attrsMap;
        }

        std::string operator[](const std::string& attrib) const noexcept {
            try {
                return this->attrsMap.at(attrib);
            }catch(const std::exception& e) {
                return "";
            }
        }
};	
#endif
