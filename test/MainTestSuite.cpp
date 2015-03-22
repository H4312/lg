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
    lexer.DisplaySplittedFile();
    FAIL("Not finished")
};

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}
