#include "TestRunner.h"
#include "ConsoleReporter.h"
#include "TestMacros.h"
#include "TestCase.h"
#include "Assertions.h"

#include <iostream>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#endif

class ConsoleSetup {
public:
    ConsoleSetup() {
        setupConsole();
    }
    
private:
    void setupConsole() {
        setupEncoding();
        setupLocale();
    }
    
    void setupEncoding() {
#ifdef _WIN32
        // Configuration Windows pour UTF-8
        SetConsoleOutputCP(65001);
        SetConsoleCP(65001);
#else
        // Sur Linux/macOS, UTF-8 est généralement le défaut
        // On peut forcer le flush pour assurer l'affichage
        std::cout.setf(std::ios::unitbuf);
#endif
    }
    
    void setupLocale() {
        // Configuration portable des locales
        try {
            // Essayer la locale UTF-8
            std::locale::global(std::locale("C.UTF-8"));
        } catch (const std::exception&) {
            try {
                // Essayer la locale système
                std::locale::global(std::locale(""));
            } catch (const std::exception&) {
                // Fallback vers la locale C standard
                std::locale::global(std::locale::classic());
            }
        }
        
        // Appliquer la locale aux flux
        std::cout.imbue(std::locale());
        std::wcout.imbue(std::locale());
    }
};

// Initialiseur global
ConsoleSetup consoleSetup;

int main(int argc, char* argv[]) {
    std::cout << "Testing Nken Compiler Components...\n\n";
    nkentseu::test::ConsoleReporter::PrintHeader("🧪 Nken Test Suite");
    std::cout << "Testing Nken Compiler Components...\n\n";
    
    nkentseu::test::TestRunner& runner = nkentseu::test::TestRunner::GetInstance();
    
    if (argc > 1) {
        std::vector<std::string> test_names;
        for (int i = 1; i < argc; i++) {
            test_names.push_back(argv[i]);
        }
        return runner.RunTests(test_names);
    } else {
        return runner.RunAllTests();
    }
}