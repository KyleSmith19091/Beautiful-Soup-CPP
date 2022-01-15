# ⚡️ HTML Document Data Extractor

This project was inspired by the BeautifulSoup python library and was used as an opportunity to learn the tree sitter parser api. 

## Project Components

The project can be broken into two main components:
1. Tree-sitter API
2. CPP Interface

The Tree-sitter api does did not have a C++ language binding as it is written in C so I wrote a C++ layer on top of this api. The Tree-sitter library does not have native HTML parsing capabilities as
it is meant to be parser generator tool, but does provide a query language interface which will be discussed later. This project uses a HTML grammar which can be found here: <a href="https://github.com/tree-sitter/tree-sitter-html">Tree-sitter-html</a>

## Usage
The BeautifulSoup object is the only interface that is required to use the library.

```c++
BeautifulSoup soup("url");
```
Upon creating the BeautifulSoup object given a valid URL it will perform a cURL request using the cURL library and parse the html document at that location. We now have an AST(Abstract Syntax Tree) which we can now explore.

The BeautifulSoup object provides two methods:
1. find_all
2. find

### Find_all
The find_all can be used to find all occurences of a specific tag in the html document. This is done by first extracting all instances of tags with the same 'tag name' as given in the parameter of the function call. We do this by performing
a query on the AST which Tree-sitter allows us to do through its very own query language which is very 'scheme' like.

The query for finding the tag names loooks something like this:
```scheme
(start_tag (tag_name) @name)
```

#### std::vector\<TagNode> BeautifulSoup::find_all(const std::string& tagName)

```c++
BeautifulSoup soup("url");
auto docSpans = soup.find_all("span");
```
The above example will extract all nodes from the AST, starting from the root node, with the span tag name. We can further filter the search results(See next example).

#### std::vector\<TagNode> BeautifulSoup::find_all(const std::string& tagName, std::map\<std::string,std::string\> attrs)
```c++
BeautifulSoup soup("url");
auto docSpans = soup.find_all("span", {{"class", "social"}});
```
The above example will extract all nodes from the AST, starting from the root node, with the span tag name and which have the social class.

#### std::vector\<TagNode> BeautifulSoup::find_all(const Node& startNode, const std::string& tagName, std::map\<std::string,std::string\> attrs)
```c++
BeautifulSoup soup("url");
auto articles = soup.find_all("article", {{"class", "featured"}, {"data-value", "2"}});

for(auto& article : articles) {
    auto articleTitle = soup.find(article, "h1", {{"class", "title"}});
    std::cout << soup.getNodeText(articleTitle) << "\n";
}
```
The above example finds all articles in the html document and then proceeds to print the titles of those articles by finding the first h1 tag within that tag with the title class and using the getNodeText helper function to
extract text data from the source document.

#### TagNode BeautifulSoup::find(const std::string& tagName)
```c++
BeautifulSoup soup("url");
auto docSpans = soup.find("span");
```
The above example will extract the first node from the AST, starting from the root node, with the span tag name. We can further filter the search results(See next example).

#### TagNode BeautifulSoup::find(const std::string& tagName, std::map\<std::string,std::string\> attrs)
```c++
BeautifulSoup soup("url");
auto docSpans = soup.find_all("span", {{"class", "social"}});
```
The above example will extract the first node from the AST, starting from the root node, with the span tag name and includes the social class.

#### TagNode BeautifulSoup::find(const Node& startNode, const std::string& tagName, std::map\<std::string,std::string\> attrs)
```c++
BeautifulSoup soup("url");
auto articles = soup.find_all("article", {{"class", "featured"}, {"data-value", "2"}});

for(auto& article : articles) {
    auto articleTitle = soup.find(article, "h1", {{"class", "title"}});
    std::cout << soup.getNodeText(articleTitle) << "\n";
}
```
The above example finds the first article in the html document and then proceeds to print the title of that title by finding the first h1 tag within that tag with the title class and using the getNodeText helper function to
extract text data from the source document.

