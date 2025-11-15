#include "TestCase.h"
#include <iostream>

namespace nkentseu {
    namespace test {

        TestCase::TestCase(const std::string& name, std::function<void()> test_func)
            : name_(name), test_func_(test_func), result_(TestResult::SKIPPED) {}

        void TestCase::Run() {
            failures_.clear();
            successes_.clear();
            
            auto start = std::chrono::high_resolution_clock::now();
            
            try {
                test_func_();
                // Le résultat est déterminé par la présence ou non d'échecs
                result_ = failures_.empty() ? TestResult::PASSED : TestResult::FAILED;
            } catch (const std::exception& e) {
                AddFailure("Uncaught exception: " + std::string(e.what()), "", 0);
                result_ = TestResult::FAILED;
            } catch (...) {
                AddFailure("Uncaught unknown exception", "", 0);
                result_ = TestResult::FAILED;
            }
            
            auto end = std::chrono::high_resolution_clock::now();
            durationMs_ = std::chrono::duration<double, std::milli>(end - start).count();
        }

        void TestCase::AddFailure(const std::string& message, const std::string& file, int line, 
                                const std::string& condition, double durationMs) {
            TestFailure failure;
            failure.message = message;
            failure.file = file;
            failure.line = line;
            failure.condition = condition;
            failure.durationMs = durationMs;
            failures_.push_back(failure);
        }

        void TestCase::AddSuccess(const std::string& condition, double durationMs, 
                                const std::string& file, int line) {
            TestSuccess success;
            success.condition = condition;
            success.durationMs = durationMs;
            success.file = file;
            success.line = line;
            successes_.push_back(success);
        }

    } // namespace test
} // namespace nkentseu::Test