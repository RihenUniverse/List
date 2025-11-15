#pragma once
#include <string>
#include <type_traits>
#include <memory>
#include <chrono>
#include <cmath>
#include "TestCase.h"
#include "Utils.h"

namespace nkentseu {
    namespace test
    {
        // Forward declaration pour l'amitié
        class TestAssert;
        
        class TestAssert {
            public:
                static TestCase* current_test;
                
                // ==================== ASSERTIONS FONDAMENTALES ====================
                
                static void Fail(const std::string& message = "", const std::string& file = "", int line = 0) {
                    auto start = std::chrono::high_resolution_clock::now();
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    std::string failure_msg = "FAIL: " + message;
                    current_test->AddFailure(failure_msg, file, line, "", duration);
                }

                static void Success(const std::string& message = "", const std::string& file = "", int line = 0) {
                    auto start = std::chrono::high_resolution_clock::now();
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    current_test->AddSuccess(message, duration, file, line);
                }
                
                template<typename T>
                static void Equal(const T& expected, const T& actual, const std::string& message = "", 
                                const std::string& file = "", int line = 0, 
                                const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    bool success = (expected == actual);
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        std::string failure_msg = "Expected: " + ToString(expected) + " | Actual: " + ToString(actual);
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }
                
                template<typename T>
                static void NotEqual(const T& expected, const T& actual, const std::string& message = "", 
                                    const std::string& file = "", int line = 0,
                                    const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    bool success = (expected != actual);
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        std::string failure_msg = "Values should not be equal: " + ToString(expected);
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }
                
                static void True(bool condition, const std::string& message = "",
                                const std::string& file = "", int line = 0,
                                const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    bool success = condition;
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        std::string failure_msg = "Condition is false";
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }
                
                static void False(bool condition, const std::string& message = "",
                                const std::string& file = "", int line = 0,
                                const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    bool success = !condition;
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        std::string failure_msg = "Condition is true";
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }
                
                // ==================== ASSERTIONS DE POINTEURS ====================
                
                template<typename T>
                static void Null(T* ptr, const std::string& message = "",
                                const std::string& file = "", int line = 0,
                                const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    bool success = (ptr == nullptr);
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        std::string failure_msg = "Pointer is not null: " + ToString(ptr);
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }
                
                template<typename T>
                static void NotNull(T* ptr, const std::string& message = "",
                                const std::string& file = "", int line = 0,
                                const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    bool success = (ptr != nullptr);
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        std::string failure_msg = "Pointer is null";
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }
                
                // ==================== ASSERTIONS DE COMPARAISON ====================
                
                template<typename T>
                static void Less(const T& left, const T& right, const std::string& message = "",
                                const std::string& file = "", int line = 0,
                                const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    bool success = (left < right);
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        std::string failure_msg = ToString(left) + " >= " + ToString(right);
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }
                
                template<typename T>
                static void LessEqual(const T& left, const T& right, const std::string& message = "",
                                    const std::string& file = "", int line = 0,
                                    const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    bool success = (left <= right);
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        std::string failure_msg = ToString(left) + " > " + ToString(right);
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }
                
                template<typename T>
                static void Greater(const T& left, const T& right, const std::string& message = "",
                                const std::string& file = "", int line = 0,
                                const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    bool success = (left > right);
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        std::string failure_msg = ToString(left) + " <= " + ToString(right);
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }
                
                template<typename T>
                static void GreaterEqual(const T& left, const T& right, const std::string& message = "",
                                        const std::string& file = "", int line = 0,
                                        const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    bool success = (left >= right);
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        std::string failure_msg = ToString(left) + " < " + ToString(right);
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }
                
                // ==================== ASSERTIONS AVEC TOLÉRANCE ====================
                
                template<typename T>
                static void EqualWithTolerance(const T& expected, const T& actual, const T& tolerance,
                                            const std::string& message = "", 
                                            const std::string& file = "", int line = 0,
                                            const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    T difference = std::abs(expected - actual);
                    bool success = (difference <= tolerance);
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        std::string failure_msg = "Expected: " + ToString(expected) + " ± " + ToString(tolerance) + 
                                               " | Actual: " + ToString(actual) + 
                                               " | Difference: " + ToString(difference);
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }
                
                // ==================== ASSERTIONS D'EXCEPTIONS ====================
                
                template<typename ExceptionT, typename FunctionT>
                static void Throws(FunctionT func, const std::string& message = "",
                                const std::string& file = "", int line = 0,
                                const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    bool success = false;
                    std::string failure_msg;
                    
                    try {
                        func();
                        failure_msg = "Expected exception was not thrown";
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                    } catch (const ExceptionT&) {
                        // Succès - l'exception attendue a été attrapée
                        success = true;
                    } catch (...) {
                        failure_msg = "Wrong exception type thrown";
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                    }
                    
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }
                
                template<typename FunctionT>
                static void NoThrow(FunctionT func, const std::string& message = "",
                                const std::string& file = "", int line = 0,
                                const std::string& expression = "") {
                    auto start = std::chrono::high_resolution_clock::now();
                    bool success = true;
                    std::string failure_msg;
                    
                    try {
                        func();
                        // Succès - pas d'exception
                    } catch (const std::exception& e) {
                        success = false;
                        failure_msg = "Unexpected exception: " + std::string(e.what());
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                    } catch (...) {
                        success = false;
                        failure_msg = "Unexpected unknown exception";
                        if (!message.empty()) {
                            failure_msg += " | " + message;
                        }
                    }
                    
                    auto end = std::chrono::high_resolution_clock::now();
                    double duration = std::chrono::duration<double, std::milli>(end - start).count();
                    
                    if (!success) {
                        current_test->AddFailure(failure_msg, file, line, expression, duration);
                    } else {
                        current_test->AddSuccess(message.empty() ? expression : message, duration, file, line);
                    }
                }

                // Surcharges pour les types communs
                static void Equal(size_t expected, size_t actual, const std::string& message = "", 
                                const std::string& file = "", int line = 0,
                                const std::string& expression = "") {
                    Equal<size_t>(expected, actual, message, file, line, expression);
                }

                static void Equal(const char* expected, const std::string& actual, const std::string& message = "", 
                                const std::string& file = "", int line = 0,
                                const std::string& expression = "") {
                    Equal<std::string>(std::string(expected), actual, message, file, line, expression);
                }

                static void Equal(const std::string& expected, const char* actual, const std::string& message = "", 
                                const std::string& file = "", int line = 0,
                                const std::string& expression = "") {
                    Equal<std::string>(expected, std::string(actual), message, file, line, expression);
                }
        };

    } // namespace test
} // namespace nkentseu::test