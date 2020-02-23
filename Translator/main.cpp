#include "LexicalAnalyzer.h"
#include "SyntacticalAnalyzer.h"
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
    LexicalAnalyzer la;
    la.StartAnalyze("C:\\Users\\Ivan\\Desktop\\KPI\\3 curs\\6-semestr\\TranslatorVS\\TranslatorVS\\TestData\\1.txt");
    la.PrintResult();
    SyntacticalAnalyzer sa{la.GetContext(), la.GetTokensInfoVector()};
    sa.StartAnalyze();
    /*
    for (fs::directory_iterator it(dir), end; it != end; ++it)
    {
        if (it->path().extension() == ".txt")
        {
            std::cout << "\n======" << it->path() << "=======\n";

//            la.StartAnalyze(it->path().c_str());
            la.StartAnalyze("C:\\Users\\Ivan\\Desktop\\KPI\\3 curs\\6-semestr\\Translator\\Translator\\TestData\\1.txt");

            std::cout << "\n=============\n";
        }
    }
*/
}

int main()
{
    TestLexicalAnalyzer();
    return 0;
}