#include "TestRunner.h"
#include "Assertions.h"
#include <algorithm>
#include <iostream>

namespace nkentseu {
    namespace test {

        // Définition du pointeur statique pour TestAssert
        TestCase* TestAssert::current_test = nullptr;

        TestRunner& TestRunner::GetInstance() {
            static TestRunner instance;
            return instance;
        }

        void TestRunner::RegisterTest(std::unique_ptr<TestCase> test_case) {
            test_cases_.push_back(std::move(test_case));
        }

        int TestRunner::RunAllTests() {
            return RunTests({});
        }

        int TestRunner::RunTests(const std::vector<std::string>& test_names) {
            ConsoleReporter::PrintHeader("🧪 Nken Test Suite");
            
            // Récupérer les tests à exécuter
            std::vector<TestCase*> tests_to_run;
            if (test_names.empty()) {
                for (auto& test_case : test_cases_) {
                    tests_to_run.push_back(test_case.get());
                }
            } else {
                for (const auto& test_name : test_names) {
                    auto it = std::find_if(test_cases_.begin(), test_cases_.end(),
                        [&](const std::unique_ptr<TestCase>& tc) {
                            return tc->GetName() == test_name;
                        });
                    if (it != test_cases_.end()) {
                        tests_to_run.push_back(it->get());
                    } else {
                        std::cout << "❌ Test not found: " << test_name << "\n";
                    }
                }
            }
            
            // Exécuter les tests
            for (auto test_case : tests_to_run) {
                RunTest(*test_case);
            }
            
            // Afficher le résumé dans le style nova
            ConsoleReporter::PrintSummary(tests_to_run);
            
            // Compter les échecs pour le code de retour
            int failed_tests = 0;
            for (auto& test_case : test_cases_) {
                if (test_case->GetResult() == TestResult::FAILED) {
                    failed_tests++;
                }
            }
            
            return failed_tests > 0 ? 1 : 0;
        }

        void TestRunner::RunTest(TestCase& test_case) {
            TestAssert::current_test = &test_case;
            
            try {
                test_case.Run();
            } 
            catch (const std::exception& e) {
                test_case.AddFailure("UNCAUGHT EXCEPTION in " + test_case.GetName() + 
                                    ": " + std::string(e.what()), __FILE__, __LINE__);
            } 
            catch (...) {
                test_case.AddFailure("UNKNOWN EXCEPTION in " + test_case.GetName(), 
                                __FILE__, __LINE__);
            }
            
            // Afficher le résultat avec le nouveau style
            ConsoleReporter::PrintTestResult(test_case);
            TestAssert::current_test = nullptr;
        }

    } // namespace test
} // namespace nkentseu