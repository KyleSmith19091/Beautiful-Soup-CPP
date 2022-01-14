#include <gtest/gtest.h>

#include "../include/BeautifulSoup.hpp"

using namespace std;

TEST(findAllFromRoot, rootNode) {
    BeautifulSoup soup("https://sacoronavirus.co.za/");
    auto case_data = soup.find_all("span", {{"class", "display-counter"}});
    EXPECT_EQ(case_data.size(), 5);
}

TEST(findAllFromReturnNode, returnedNode) {
    BeautifulSoup soup("https://dev.to");
    auto article = soup.find_all("div", {{"class", "crayons-story--featured"}});
    auto a_tag = soup.find_all(article[0], "a", {{"class", "crayons-story__hidden-navigation-link"}});
    EXPECT_EQ(a_tag.size(),1);
}

TEST(findFromRootNode, rootNode) {
    BeautifulSoup soup("https://dev.to");
    auto article = soup.find("div", {{"class", "crayons-story--featured"}});
    auto a_tag = soup.find(article, "a", {{"class", "crayons-story__hidden-navigation-link"}});
    EXPECT_EQ(a_tag.attrs()["class"], "crayons-story__hidden-navigation-link");
}

TEST(findFromReturnNode, returnedNode) {
}

int main(){
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
