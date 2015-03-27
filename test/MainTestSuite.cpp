#include <CppUTest/CommandLineTestRunner.h>
#include <Automate.h>
#include <algorithm>

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
    lexer.openFile((char *) "res/programme_ok.txt");
    lexer.splitFileBySym();
    //lexer.DisplaySplittedFile();
    FAIL("Not finished")
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

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
