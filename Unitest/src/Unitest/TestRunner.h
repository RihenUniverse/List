#pragma once
#include <vector>
#include <memory>
#include "TestCase.h"
#include "ConsoleReporter.h"

namespace nkentseu {

    namespace test
    {
        class TestRunner {
            public:
                static TestRunner& GetInstance();
                
                void RegisterTest(std::unique_ptr<TestCase> test_case);
                int RunAllTests();
                int RunTests(const std::vector<std::string>& test_names);
                
            private:
                TestRunner() = default;
                
                std::vector<std::unique_ptr<TestCase>> test_cases_;
                
                void RunTest(TestCase& test_case);
        };
    }
} // namespace nkentseu::Test