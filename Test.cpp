#include "FamilyTree.hpp"
#include "doctest.h"
using namespace family;

TEST_CASE("Test for relation method") {
    Tree T("Yosef");
	CHECK(T.relation("Yosef") == string("me"));
	CHECK(T.relation("Yaakov") == string("unrelated"));
	T.addFather("Yosef", "Yaakov");
	CHECK(T.relation("Yaakov") == string("father"));
	CHECK(T.find("father") == string("Yaakov"));
	CHECK(T.relation("Rachel") == string("unrelated"));
	T.addMother("Yosef", "Rachel");
	CHECK(T.relation("Rachel") == string("mother"));
	CHECK(T.find("mother") == string("Rachel"));
	CHECK(T.relation("Isaac") == string("unrelated"));
	T.addFather("Yaakov", "Isaac");
	CHECK(T.relation("Isaac") == string("grandfather"));
	CHECK(T.find("grandfather") == string("Isaac"));
	CHECK(T.relation("Rivka") == string("unrelated"));
	T.addMother("Yaakov", "Rivka");
	CHECK(T.relation("Rivka") == string("grandmother"));
	CHECK(T.find("grandmother") == string("Rivka"));
	CHECK(T.relation("Shimon") == string("unrelated"));
	T.addFather("Rachel", "Shimon");
	CHECK(T.relation("Shimon") == string("grandfather"));
	CHECK(T.find("grandfather") == string("Shimon")); // According to BFS
	T.remove("Shimon");
	CHECK(T.find("grandfather") == string("Isaac")); // According to BFS
	CHECK(T.relation("Oshrit") == string("unrelated"));
	T.addMother("Rachel", "Oshrit");
	CHECK(T.relation("Oshrit") == string("grandmother"));
	CHECK(T.find("grandmother") == string("Oshrit")); // According to BFS
	T.remove("Oshrit");
	CHECK(T.find("grandmother") == string("Rivka")); // According to BFS
	CHECK(T.relation("Avraham") == string("unrelated"));
	T.addFather("Isaac", "Avraham");
	CHECK(T.relation("Avraham") == string("great-grandfather"));
	CHECK(T.relation("Terah") == string("unrelated"));
	T.addFather("Avraham", "Terah");
	CHECK(T.relation("Terah") == string("great-great-grandfather"));
	CHECK(T.relation("Shlomit") == string("unrelated"));
	T.addMother("Isaac", "Shlomit");
	CHECK(T.relation("Shlomit") == string("great-grandmother"));
	CHECK(T.relation("Baruch") == string("unrelated"));
	T.addFather("Shlomit", "Baruch");
	CHECK(T.relation("Baruch") == string("great-great-grandfather")); // According to BFS
	CHECK(T.find("great-great-grandfather") == string("Baruch")); // According to BFS
	T.remove("Baruch");
	CHECK(T.find("great-great-grandfather") == string("Terah")); // According to BFS

}

TEST_CASE("Test for find method") {
    Tree T("Yosef");
	CHECK_THROWS_AS(T.find("father"), std::exception);
	T.addFather("Yosef", "Yaakov");
	CHECK_THROWS_AS(T.find("mother"), std::exception);
	T.addMother("Yosef", "Rachel");
	CHECK_THROWS_AS(T.find("grandfather"), std::exception);
	T.addFather("Yaakov", "Isaac");
	CHECK_THROWS_AS(T.find("grandmother"), std::exception);
	T.addMother("Yaakov", "Rivka");
	CHECK_THROWS_AS(T.find("great-grandfather"), std::exception);
	T.addFather("Rachel", "Shimon");
	CHECK_THROWS_AS(T.find("great-grandmother"), std::exception);
	T.addMother("Rachel", "Oshrit");
	CHECK_THROWS_AS(T.find("great-grandfather"), std::exception);
	T.addFather("Isaac", "Avraham");
	CHECK_THROWS_AS(T.find("great-grandmother"), std::exception);
	T.addMother("Isaac", "Shlomit");
	CHECK_THROWS_AS(T.find("great-great-grandfather"), std::exception);
	T.addFather("Avraham", "Terah");
	CHECK(T.find("me") == string("Yosef"));
	CHECK(T.find("father") == string("Yaakov"));
	CHECK(T.find("mother") == string("Rachel"));
	CHECK(T.find("grandfather") == string("Shimon")); // According to BFS
	CHECK(T.find("grandmother") == string("Oshrit")); // According to BFS
	CHECK(T.find("great-grandfather") == string("Avraham")); // According to BFS
	CHECK(T.find("great-grandmother") == string("Shlomit")); // According to BFS
	T.addFather("Shlomit", "Avner");
	CHECK(T.find("great-great-grandfather") == string("Avner")); // According to BFS
	T.remove("Avner");
	CHECK(T.find("great-great-grandfather") == string("Terah")); // According to BFS
}

TEST_CASE("Test for remove method") {
	Tree T("Yosef");
	T.addFather("Yosef", "Yaakov");
	T.addMother("Yosef", "Rachel");
	T.addFather("Yaakov", "Isaac");
	T.addMother("Yaakov", "Rivka");
	T.addFather("Isaac", "Avraham");
	T.addFather("Avraham", "Terah");
	T.addMother("Isaac", "Dana");
	T.addFather("Rachel", "Nissim");
	T.addMother("Rachel", "Efrat");
	CHECK(T.relation("Avraham") == string("great-grandfather"));
	CHECK(T.relation("Terah") == string("great-great-grandfather"));
	T.remove("Avraham");
	CHECK(T.relation("Avraham") == string("unrelated"));
	CHECK(T.relation("Terah") == string("unrelated"));
	CHECK(T.relation("Yaakov") == string("father"));
	CHECK(T.relation("Isaac") == string("grandfather"));
	CHECK(T.relation("Rivka") == string("grandmother"));
	CHECK(T.relation("Efrat") == string("grandmother")); // According to BFS
	CHECK(T.find("grandmother") == string("Efrat")); // According to BFS
	CHECK(T.find("grandfather") == string("Nissim")); // According to BFS
	CHECK(T.relation("Rachel") == string("mother"));
	T.remove("Rachel");
	CHECK(T.relation("Nissim") == string("unrelated"));
	CHECK(T.relation("Efrat") == string("unrelated"));
	CHECK(T.relation("Rachel") == string("unrelated"));
	CHECK(T.find("grandmother") == string("Rivka")); // According to BFS
	CHECK(T.find("grandfather") == string("Isaac")); // According to BFS
	T.remove("Yaakov");
	CHECK(T.relation("Rivka") == string("unrelated"));
	CHECK(T.relation("Isaac") == string("unrelated"));
	CHECK(T.relation("Yaakov") == string("unrelated"));
}

TEST_CASE("Test for exceptions") {
	Tree T("Yosef");
	T.addFather("Yosef", "Yaakov");
	T.addMother("Yosef", "Rachel");
	T.addFather("Yaakov", "Isaac");
	T.addMother("Yaakov", "Rivka");
	T.addFather("Isaac", "Avraham");
	T.addFather("Avraham", "Terah");
	CHECK_THROWS_AS(T.addFather("Yosef", "Avner"), std::exception);
	CHECK_THROWS_AS(T.addMother("Yosef", "Bella"), std::exception);
	CHECK_THROWS_AS(T.addFather("Yaakov", ""), std::exception);
	CHECK_THROWS_AS(T.addMother("", "Dana"), std::exception);
	CHECK_THROWS_AS(T.addFather("", ""), std::exception);
	CHECK_THROWS_AS(T.addMother("", ""), std::exception);
	CHECK_THROWS_AS(T.addFather("Moshe", "David"), std::exception);
	CHECK_THROWS_AS(T.addMother("Dan", "Dana"), std::exception);
	CHECK_THROWS_AS(T.find(""), std::exception);
	CHECK_THROWS_AS(T.find("great-grandmother"), std::exception);
	CHECK_THROWS_AS(T.find("great-great-grandmother"), std::exception);
	CHECK_THROWS_AS(T.remove(""), std::exception);
	CHECK_THROWS_AS(T.remove("David"), std::exception);
	CHECK_THROWS_AS(T.remove("Shlomo"), std::exception);
	CHECK_THROWS_AS(T.remove("Isaschar"), std::exception);
	CHECK_THROWS_AS(T.remove("Ezra"), std::exception);
	CHECK_THROWS_AS(T.remove("Ted"), std::exception);
	T.remove("Isaac");
	CHECK_THROWS_AS(T.find("grandfather"), std::exception);
	CHECK_THROWS_AS(T.find("great-grandfather"), std::exception);
	CHECK_THROWS_AS(T.find("uncle"), std::exception);
	CHECK_THROWS_AS(T.find("grand-grandfather"), std::exception);
	CHECK_THROWS_AS(T.find("great-greatfather"), std::exception);
	CHECK_THROWS_AS(T.find("great greatfather"), std::exception);
	CHECK_THROWS_AS(T.find("great greatmother"), std::exception);
	CHECK_THROWS_AS(T.find("dad"), std::exception);
	CHECK_THROWS_AS(T.find("daddy"), std::exception);
	CHECK_THROWS_AS(T.find("mom"), std::exception);
	CHECK_THROWS_AS(T.find("mommy"), std::exception);
	CHECK_THROWS_AS(T.find("grandpa"), std::exception);
	CHECK_THROWS_AS(T.find("grandma"), std::exception);
	CHECK_THROWS_AS(T.relation(""), std::exception);
	CHECK_THROWS_AS(Tree T2(""), std::exception);
	CHECK_THROWS_AS(T.remove("Isaac"), std::exception); // Already done
}