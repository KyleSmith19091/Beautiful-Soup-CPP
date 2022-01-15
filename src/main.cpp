#include <cassert>
#include <iostream>
#include <map>

#include "../include/BeautifulSoup.hpp"

using namespace std;

#define soup_map std::map<std::string,std::string>

void test1() {
    // Connect to site & parse HTML to an AST
    BeautifulSoup soup("https://sacoronavirus.co.za/");

    auto case_data = soup.find_all("span", soup_map{{"class" , "display-counter"}});
    std::cout << case_data.size() << "\n";
    for(auto& a : case_data) {
        std::cout << a.attrs()["data-value"] << "\n";
    }
    
    auto case_text = soup.find_all("div", soup_map{{"class", "counter-box-content"}});
    std::cout << case_data.size() << "\n";

    for(auto& a : case_text) {
        std::cout << soup.getNodeText(a) << "\n";
    }

    std::cout << "TEST1 Done\n";
}

void test2() {
    BeautifulSoup soup("https://dev.to");
    auto article = soup.find("div", {{"class", "crayons-story--featured"}});
    auto a_tag = soup.find(article, "a", {{"class", "crayons-story__hidden-navigation-link"}});
    std::cout << a_tag.attrs()["href"] << "\n";
    std::cout << "TEST2 Done\n";
}

void test3() {
    BeautifulSoup soup("https://www.tradingview.com/markets/stocks-usa/market-movers-gainers/");
    auto page_content = soup.find("div", {{"class", "tv-content"}});
    auto table_object = soup.find(page_content, "table", {{"class", "tv-data-table tv-screener-table"}});
    auto table_rows = soup.find_all(table_object, "tr");
    std::cout << table_rows.size() << "\n";
}

int main() {

    BeautifulSoup soup("https://www.tradingview.com/markets/stocks-usa/market-movers-gainers/");
    auto page_content = soup.find("div", {{"class", "tv-content"}});
    auto table_object = soup.find(page_content, "table", {{"class", "tv-data-table tv-screener-table"}});
    auto table_rows = soup.find_all(table_object, "tr");
    std::cout << table_rows.size() << "\n";

    return 0;
}
