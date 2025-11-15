#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include "TestCase.h"

namespace nkentseu {
    namespace test
    {
        class ConsoleReporter {
            public:
                enum class Color {
                    RESET,
                    GREEN,
                    RED,
                    YELLOW,
                    BLUE,
                    CYAN,
                    MAGENTA
                };
                
                struct Config {
                    bool showPassedTests = false;
                    bool showFailedTests = true;
                    bool showPassedAssertions = false;
                    bool showAssertionDetails = true;
                    unsigned verbosityLevel = 2; // 0=minimal, 1=normal, 2=verbose
                };
                
                static void SetColor(Color color);
                static void ResetColor();
                
                static void PrintHeader(const std::string& title);
                static void PrintTestResult(const TestCase& test_case);
                static void PrintSummary(const std::vector<TestCase*>& test_cases);
                static void PrintFailureDetails(const TestCase& test_case);
                static void PrintAssertionDetails(const TestCase& test_case);
                
                static void Configure(const Config& config) { currentConfig_ = config; }
                static Config& GetConfig() { return currentConfig_; }
                
            private:
                static Config currentConfig_;
                
                static std::string GetTestStatusSymbol(TestResult result);
                static Color GetTestStatusColor(TestResult result);
                static std::string FormatDuration(double ms);
                static std::string FormatPercentage(double value, double total);
                static Color GetPercentageColor(double percentage);
                static void PrintColored(const std::string& text, Color color);
        };
    }
} // namespace nkentseu::Test