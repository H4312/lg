#include <CppUTest/CommandLineTestRunner.h>
#include <Automate.h>
#include <algorithm>
#include <string.h>
#include <strings.h>
#include <iostream>
#include <sstream>

TEST_GROUP(Lexer) {
};

TEST(Lexer, OpenFile)
{
    Lexer lexer;
    lexer.openFile((char *) "res/programme_ok.txt");
    CHECK(lexer.isFileOpen());
}

TEST(Lexer, SplitFile)
{

    Lexer lexer;
    lexer.openFile((char *) "res/test_split.txt");
    vector<string> * v = lexer.splitFileBySym();
    CHECK_EQUAL("var", v->at(0));
    CHECK_EQUAL("x", v->at(1));
    CHECK_EQUAL(";", v->at(2));
    CHECK_EQUAL("const", v->at(3));
    CHECK_EQUAL("n", v->at(4));
    CHECK_EQUAL("=", v->at(5));
    CHECK_EQUAL("10", v->at(6));
    CHECK_EQUAL(",", v->at(7));
    CHECK_EQUAL("n2", v->at(8));
    CHECK_EQUAL("=", v->at(9));
    CHECK_EQUAL("100", v->at(10));
    CHECK_EQUAL(";", v->at(11));
    CHECK_EQUAL("ecrire", v->at(12));
    CHECK_EQUAL("n", v->at(13));
    CHECK_EQUAL("+", v->at(14));
    CHECK_EQUAL("n2", v->at(15));
    CHECK_EQUAL(";", v->at(16));
    CHECK_EQUAL("x", v->at(17));
    CHECK_EQUAL(":=", v->at(18));
    CHECK_EQUAL("n", v->at(19));
    CHECK_EQUAL("+", v->at(20));
    CHECK_EQUAL("n2", v->at(21));
    CHECK_EQUAL(";", v->at(22));
    CHECK_EQUAL("x", v->at(23));
    CHECK_EQUAL(":=", v->at(24));
    CHECK_EQUAL("n", v->at(25));
    CHECK_EQUAL("+", v->at(26));
    CHECK_EQUAL("2", v->at(27));
    CHECK_EQUAL(";", v->at(28));
    CHECK_EQUAL("lire", v->at(29));
    CHECK_EQUAL("x", v->at(30));
    CHECK_EQUAL(";", v->at(31));


    //lexer.DisplaySplittedFile();
    //FAIL("Not finished")
};

TEST(Lexer, isDouble)
{
    Lexer lexer;
    CHECK(lexer.isOnlyDouble("6"));
    CHECK(lexer.isOnlyDouble("0"));
    CHECK(lexer.isOnlyDouble("134567"));
    CHECK(lexer.isOnlyDouble("0.5"));
    CHECK(lexer.isOnlyDouble("1.5"));
    CHECK_FALSE(lexer.isOnlyDouble("1.2f"));
    CHECK_FALSE(lexer.isOnlyDouble(".2"));
    CHECK_FALSE(lexer.isOnlyDouble("fd"));
    CHECK_FALSE(lexer.isOnlyDouble("f.54"));
}

TEST(Lexer, isIdentifer) {
    Lexer lexer;
    CHECK(lexer.isIdentifier("hello"));
    CHECK(lexer.isIdentifier("n2"));
    CHECK(lexer.isIdentifier("n2t3"));
    CHECK_FALSE(lexer.isIdentifier("3t3"));
    CHECK_FALSE(lexer.isIdentifier("33"));
}

TEST(Lexer, getSymbole) {
    Lexer lexer;
    Symbole *sym;
    CHECK((sym = lexer.getSymbole("2"))->getType() == Symbole::val);
    delete sym;
    CHECK((sym = lexer.getSymbole("hello"))->getType() == Symbole::id);
    delete sym;
    CHECK((sym = lexer.getSymbole("const"))->getType() == Symbole::cons);
    delete sym;
    CHECK((sym = lexer.getSymbole("var"))->getType() == Symbole::var);
    delete sym;
    CHECK((sym = lexer.getSymbole("="))->getType() == Symbole::eq);
    delete sym;
    CHECK((sym = lexer.getSymbole(":="))->getType() == Symbole::aff);
    delete sym;
    CHECK((sym = lexer.getSymbole("jds76"))->getType() == Symbole::id);
    delete sym;
    CHECK((sym = lexer.getSymbole("+"))->getType() == Symbole::pl);
    delete sym;
    CHECK((sym = lexer.getSymbole("-"))->getType() == Symbole::mn);
    delete sym;
    CHECK((sym = lexer.getSymbole("2"))->getType() == Symbole::val);
    delete sym;
}

TEST(Lexer, readNext) {
    Lexer lexer;
    lexer.openFile((char *) "res/programme_ok.txt");
    lexer.splitFileBySym();
    Symbole * sym;
    int index = 0;


    CHECK((sym = lexer.readNext())->getType() == Symbole::var);
    delete sym;
    CHECK((sym = lexer.readNext())->getType() == Symbole::id);
    delete sym;
    CHECK((sym = lexer.readNext())->getType() == Symbole::pv);
    delete sym;
    CHECK((sym = lexer.readNext())->getType() == Symbole::cons);
    delete sym;

}

TEST(Lexer, fakeChar) {
    std::stringstream buffer;
    std::streambuf * old = std::cerr.rdbuf(buffer.rdbuf());
    Lexer lexer;
    lexer.openFile((char *) "res/programme_char_faux.txt");
    lexer.splitFileBySym();
    string str = "Symbole invalide ligne 3 position 1\n"
    "Symbole invalide ligne 3 position 3\n"
    "Symbole invalide ligne 3 position 5\n"
    "Symbole invalide ligne 4 position 1\n"
    "Symbole invalide ligne 4 position 2\n"
    "Symbole invalide ligne 4 position 3\n";
    CHECK_EQUAL(str, buffer.str());
}

TEST_GROUP(Symbole) {
};

TEST(Symbole, afficher) {
    Symbole s(Symbole::id);
    s.setName("id");
    Symbole s1(Symbole::aff);
    Symbole s2(Symbole::val);
    s2.setValue(2.0);
    Symbole s3(Symbole::pv);
    Symbole s4(Symbole::I);
    s4.ajouterFils(&s);
    s4.ajouterFils(&s1);
    s4.ajouterFils(&s2);
    s4.ajouterFils(&s3);
    CHECK_EQUAL("id:= 2.000000;\n", s4.toString());

}

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
