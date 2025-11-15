#pragma once
#include <string>
#include <functional>
#include <vector>
#include <chrono>

namespace nkentseu {
    using uint64 = unsigned long long;
    using usize = uint64;
    
    namespace test
    {
        enum class TestResult {
            PASSED,
            FAILED,
            SKIPPED
        };

        struct TestFailure {
            std::string message;
            std::string file;
            int line;
            std::string condition;
            double durationMs;
        };

        struct TestSuccess {
            std::string condition;
            double durationMs;
            std::string file;
            int line;
        };

        class TestCase {
            public:
                TestCase(const std::string& name, std::function<void()> test_func);
                
                void Run();
                const std::string& GetName() const { return name_; }
                TestResult GetResult() const { return result_; }
                const std::vector<TestFailure>& GetFailures() const { return failures_; }
                const std::vector<TestSuccess>& GetSuccesses() const { return successes_; }
                nkentseu::usize GetAssertionsPassed() const { return successes_.size(); }
                nkentseu::usize GetAssertionsFailed() const { return failures_.size(); }
                double GetDurationMs() const { return durationMs_; }
                
                // Méthodes publiques pour ajouter des résultats
                void AddFailure(const std::string& message, const std::string& file = "", int line = 0, 
                              const std::string& condition = "", double durationMs = 0.0);
                void AddSuccess(const std::string& condition = "", double durationMs = 0.0, 
                              const std::string& file = "", int line = 0);
                
            private:
                std::string name_;
                std::function<void()> test_func_;
                TestResult result_;
                std::vector<TestFailure> failures_;
                std::vector<TestSuccess> successes_;
                double durationMs_ = 0.0;
                
                friend class TestAssert;
                friend class TestRunner;
        };
    }
} // namespace nkentseu::Test