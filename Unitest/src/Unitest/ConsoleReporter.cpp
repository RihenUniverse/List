#include "ConsoleReporter.h"
#include <iostream>
#include <iomanip>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace nkentseu {
    namespace test {

        ConsoleReporter::Config ConsoleReporter::currentConfig_;

        void ConsoleReporter::SetColor(Color color) {
        #ifdef _WIN32
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            WORD winColor;
            switch (color) {
                case Color::GREEN:    winColor = FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
                case Color::RED:      winColor = FOREGROUND_RED | FOREGROUND_INTENSITY; break;
                case Color::YELLOW:   winColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
                case Color::BLUE:     winColor = FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
                case Color::CYAN:     winColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY; break;
                case Color::MAGENTA:  winColor = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY; break;
                default:              winColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE; break;
            }
            SetConsoleTextAttribute(hConsole, winColor);
        #else
            const char* ansiColor;
            switch (color) {
                case Color::GREEN:    ansiColor = "\033[1;32m"; break;
                case Color::RED:      ansiColor = "\033[1;31m"; break;
                case Color::YELLOW:   ansiColor = "\033[1;33m"; break;
                case Color::BLUE:     ansiColor = "\033[1;34m"; break;
                case Color::CYAN:     ansiColor = "\033[1;36m"; break;
                case Color::MAGENTA:  ansiColor = "\033[1;35m"; break;
                default:              ansiColor = "\033[0m"; break;
            }
            std::cout << ansiColor;
        #endif
        }

        void ConsoleReporter::ResetColor() {
            SetColor(Color::RESET);
        }

        void ConsoleReporter::PrintColored(const std::string& text, Color color) {
            SetColor(color);
            std::cout << text;
            ResetColor();
        }

        std::string ConsoleReporter::FormatDuration(double ms) {
            if (ms < 1.0) {
                return std::to_string(static_cast<int>(ms * 1000)) + "µs";
            } else if (ms < 1000.0) {
                return std::to_string(static_cast<int>(ms)) + "ms";
            } else {
                return std::to_string(static_cast<int>(ms / 1000)) + "s";
            }
        }

        // Nouvelle fonction pour formater les pourcentages avec couleur
        std::string ConsoleReporter::FormatPercentage(double value, double total) {
            if (total == 0) return "0%";
            
            double percentage = (value / total) * 100.0;
            std::stringstream ss;
            ss << std::fixed << std::setprecision(1) << percentage << "%";
            
            return ss.str();
        }

        // Nouvelle fonction pour obtenir la couleur basée sur le pourcentage
        ConsoleReporter::Color ConsoleReporter::GetPercentageColor(double percentage) {
            return percentage >= 50.0 ? Color::GREEN : Color::RED;
        }

        void ConsoleReporter::PrintHeader(const std::string& title) {
            SetColor(Color::CYAN);
            std::cout << "\n\033[1;36m" << std::string(60, '=') << "\033[0m\n";
            std::cout << "\033[1;36m  " << title << "\033[0m\n";
            std::cout << "\033[1;36m" << std::string(60, '=') << "\033[0m\n\n";
            ResetColor();
        }

        void ConsoleReporter::PrintTestResult(const TestCase& test_case) {
            // Ligne principale du test
            SetColor(GetTestStatusColor(test_case.GetResult()));
            std::cout << GetTestStatusSymbol(test_case.GetResult()) << " ";
            ResetColor();
            
            std::cout << test_case.GetName();
            
            // Durée colorée
            SetColor(Color::BLUE);
            std::cout << " (\033[2m" << FormatDuration(test_case.GetDurationMs()) << "\033[0m";
            
            // Compteurs d'assertions
            nkentseu::usize passed = test_case.GetAssertionsPassed();
            nkentseu::usize failed = test_case.GetAssertionsFailed();
            nkentseu::usize totalAssertions = passed + failed;
            
            if (passed > 0) {
                std::cout << " | ";
                SetColor(Color::GREEN);
                std::cout << "✓" << passed;
                ResetColor();
            }
            
            if (failed > 0) {
                std::cout << " | ";
                SetColor(Color::RED);
                std::cout << "✗" << failed;
                ResetColor();
            }
            
            // Pourcentage d'assertions réussies pour ce test
            if (totalAssertions > 0) {
                double assertionPercentage = (static_cast<double>(passed) / totalAssertions) * 100.0;
                Color percentageColor = GetPercentageColor(assertionPercentage);
                
                std::cout << " | ";
                SetColor(percentageColor);
                std::cout << std::fixed << std::setprecision(1) << assertionPercentage << "%";
                ResetColor();
            }
            
            std::cout << ")\n";
            
            // Détails des assertions si configuré
            if (currentConfig_.showAssertionDetails && 
                (test_case.GetResult() == TestResult::FAILED || currentConfig_.showPassedTests)) {
                PrintAssertionDetails(test_case);
            }
        }

        void ConsoleReporter::PrintSummary(const std::vector<TestCase*>& test_cases) {
            nkentseu::usize totalTests = test_cases.size();
            nkentseu::usize passedTests = 0;
            nkentseu::usize failedTests = 0;
            nkentseu::usize skippedTests = 0;
            nkentseu::usize totalAssertions = 0;
            nkentseu::usize passedAssertions = 0;
            nkentseu::usize failedAssertions = 0;
            double totalDuration = 0.0;
            
            // Calcul des statistiques
            for (const auto& test_case : test_cases) {
                totalDuration += test_case->GetDurationMs();
                totalAssertions += test_case->GetAssertionsPassed() + test_case->GetAssertionsFailed();
                passedAssertions += test_case->GetAssertionsPassed();
                failedAssertions += test_case->GetAssertionsFailed();
                
                switch (test_case->GetResult()) {
                    case TestResult::PASSED: passedTests++; break;
                    case TestResult::FAILED: failedTests++; break;
                    case TestResult::SKIPPED: skippedTests++; break;
                }
            }
            
            // Calcul des pourcentages
            double testSuccessPercentage = totalTests > 0 ? 
                (static_cast<double>(passedTests) / totalTests) * 100.0 : 0.0;
            double assertionSuccessPercentage = totalAssertions > 0 ? 
                (static_cast<double>(passedAssertions) / totalAssertions) * 100.0 : 0.0;
            
            Color testPercentageColor = GetPercentageColor(testSuccessPercentage);
            Color assertionPercentageColor = GetPercentageColor(assertionSuccessPercentage);
            
            // Affichage du résumé dans le style nova
            std::cout << "\n\033[1;36m" << std::string(50, '=') << "\033[0m\n";
            std::cout << "\033[1;36m📊 Test Summary\033[0m\n";
            std::cout << "\033[1;36m" << std::string(50, '-') << "\033[0m\n";
            
            // Ligne des tests avec pourcentage
            std::cout << "Tests:      ";
            if (passedTests > 0) {
                PrintColored("✓ " + std::to_string(passedTests) + " passed", Color::GREEN);
                std::cout << " | ";
            }
            if (failedTests > 0) {
                PrintColored("✗ " + std::to_string(failedTests) + " failed", Color::RED);
                std::cout << " | ";
            }
            if (skippedTests > 0) {
                PrintColored("⏭ " + std::to_string(skippedTests) + " skipped", Color::YELLOW);
                std::cout << " | ";
            }
            
            // Pourcentage de tests réussis
            PrintColored("🎯 " + FormatPercentage(passedTests, totalTests), testPercentageColor);
            std::cout << "\n";
            
            // Ligne des assertions avec pourcentage
            std::cout << "Assertions: ";
            if (passedAssertions > 0) {
                PrintColored("✓ " + std::to_string(passedAssertions) + " passed", Color::GREEN);
                std::cout << " | ";
            }
            if (failedAssertions > 0) {
                PrintColored("✗ " + std::to_string(failedAssertions) + " failed", Color::RED);
                std::cout << " | ";
            }
            
            // Pourcentage d'assertions réussies
            PrintColored("🎯 " + FormatPercentage(passedAssertions, totalAssertions), assertionPercentageColor);
            std::cout << "\n";
            
            // Ligne durée totale
            std::cout << "Duration:   ";
            SetColor(Color::BLUE);
            std::cout << "⏱ " << FormatDuration(totalDuration);
            ResetColor();
            std::cout << "\n";
            
            std::cout << "\033[1;36m" << std::string(50, '-') << "\033[0m\n";
            
            // Message final coloré avec pourcentages
            if (failedTests == 0 && failedAssertions == 0) {
                SetColor(Color::GREEN);
                std::cout << "🎉 All tests passed! ";
                ResetColor();
                std::cout << passedTests << "/" << totalTests << " tests succeeded. ";
                PrintColored("(" + FormatPercentage(passedTests, totalTests) + ")", Color::GREEN);
                std::cout << "\n";
            } else {
                SetColor(Color::RED);
                std::cout << "💥 Test failures! ";
                ResetColor();
                std::cout << failedTests << " test(s) and " << failedAssertions << " assertion(s) failed. ";
                
                // Afficher le pourcentage global de réussite
                double overallSuccess = (testSuccessPercentage + assertionSuccessPercentage) / 2.0;
                Color overallColor = GetPercentageColor(overallSuccess);
                PrintColored("(Overall: " + FormatPercentage(overallSuccess, 100.0) + ")", overallColor);
                std::cout << "\n";
            }
            
            SetColor(Color::CYAN);
            std::cout << std::string(50, '=') << "\n";
            ResetColor();
        }

        void ConsoleReporter::PrintAssertionDetails(const TestCase& test_case) {
            const auto& failures = test_case.GetFailures();
            const auto& successes = test_case.GetSuccesses();
            
            // Afficher les échecs d'abord
            for (const auto& failure : failures) {
                std::cout << "    \033[31m✗\033[0m " << failure.condition;
                std::cout << " \033[2m(" << FormatDuration(failure.durationMs) << ")\033[0m";
                std::cout << " \033[2m(" << failure.file << ":" << failure.line << ")\033[0m\n";
                
                if (!failure.message.empty()) {
                    std::cout << "      → " << failure.message << "\n";
                }
            }
            
            // Afficher les succès si configuré
            if (currentConfig_.showPassedAssertions) {
                for (const auto& success : successes) {
                    std::cout << "    \033[32m✓\033[0m " << success.condition;
                    std::cout << " \033[2m(" << FormatDuration(success.durationMs) << ")\033[0m";
                    if (!success.file.empty()) {
                        std::cout << " \033[2m(" << success.file << ":" << success.line << ")\033[0m";
                    }
                    std::cout << "\n";
                }
            }
            
            if (!failures.empty() || (currentConfig_.showPassedAssertions && !successes.empty())) {
                std::cout << "\n";
            }
        }

        void ConsoleReporter::PrintFailureDetails(const TestCase& test_case) {
            if (test_case.GetResult() != TestResult::FAILED) return;
            
            SetColor(Color::RED);
            std::cout << "\n❌ " << test_case.GetName() << ":\n";
            ResetColor();
            
            for (const auto& failure : test_case.GetFailures()) {
                std::cout << "   └─ ";
                SetColor(Color::RED);
                std::cout << failure.message;
                ResetColor();
                
                if (!failure.file.empty() && failure.line > 0) {
                    std::cout << " \033[2m(at " << failure.file << ":" << failure.line << ")\033[0m";
                }
                std::cout << "\n";
            }
        }

        std::string ConsoleReporter::GetTestStatusSymbol(TestResult result) {
            switch (result) {
                case TestResult::PASSED:  return "✅";
                case TestResult::FAILED:  return "❌";
                case TestResult::SKIPPED: return "⏭️";
                default: return "?";
            }
        }

        ConsoleReporter::Color ConsoleReporter::GetTestStatusColor(TestResult result) {
            switch (result) {
                case TestResult::PASSED:  return Color::GREEN;
                case TestResult::FAILED:  return Color::RED;
                case TestResult::SKIPPED: return Color::YELLOW;
                default: return Color::RESET;
            }
        }

    } // namespace test
} // namespace nkentseu