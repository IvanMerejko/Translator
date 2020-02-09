#include "LexicalAnalyzer.h"
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

void TestLexicalAnalyzer()
{
    fs::path dir = "C:\\Users\\Ivan\\Desktop\\KPI\\3 curs\\6-semestr\\Translator\\Translator\\TestData";
    if (!fs::exists(dir))
    {
        std::cout << "UUPPS";
        return;
    }
    for (fs::directory_iterator it(dir), end; it != end; ++it)
    {
        if (it->path().extension() == ".txt")
        {
            std::cout << "\n======" << it->path() << "=======\n";
            LexicalAnalyzer la;
            la.StartAnalyze(it->path().c_str());
            la.PrintResult();
            std::cout << "\n=============\n";
        }
    }
}

int main()
{
    TestLexicalAnalyzer();
    return 0;
}