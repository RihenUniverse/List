#pragma once
#include "TestRunner.h"
#include "Assertions.h"

// Macros pour définir des tests
#define TEST_CASE(name) \
    class TestCase_##name : public nkentseu::test::TestCase { \
    public: \
        TestCase_##name() : TestCase(#name, [this]() { RunTest(); }) {} \
        void RunTest(); \
    }; \
    static struct TestRegistrar_##name { \
        TestRegistrar_##name() { \
            nkentseu::test::TestRunner::GetInstance().RegisterTest( \
                std::make_unique<TestCase_##name>() \
            ); \
        } \
    } test_registrar_##name; \
    void TestCase_##name::RunTest()

// Helper macro pour convertir l'expression en string
#define EXPR_TO_STRING(expr) #expr

#define ASSERT_FAIL(message) nkentseu::test::TestAssert::Fail(message, __FILE__, __LINE__)

#define ASSERT_SUCCESS(message) nkentseu::test::TestAssert::Success(message, __FILE__, __LINE__)

// Macros d'assertion avec messages optionnels - VERSION SIMPLIFIÉE
#define ASSERT_EQUAL(expected, actual, ...) \
    nkentseu::test::TestAssert::Equal(expected, actual, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(expected == actual))

#define ASSERT_TRUE(condition, ...) \
    nkentseu::test::TestAssert::True(condition, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(condition))

#define ASSERT_FALSE(condition, ...) \
    nkentseu::test::TestAssert::False(condition, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(condition))

#define ASSERT_NOT_NULL(ptr, ...) \
    nkentseu::test::TestAssert::True(ptr != nullptr, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(ptr != nullptr))

#define ASSERT_NULL(ptr, ...) \
    nkentseu::test::TestAssert::True(ptr == nullptr, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(ptr == nullptr))

#define ASSERT_NOT_EQUAL(expected, actual, ...) \
    nkentseu::test::TestAssert::NotEqual(expected, actual, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(expected != actual))

// Assertions de pointeurs
#define ASSERT_NULL_SHARED(ptr, ...) \
    nkentseu::test::TestAssert::Null(ptr, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(ptr == nullptr))

#define ASSERT_NOT_NULL_SHARED(ptr, ...) \
    nkentseu::test::TestAssert::NotNull(ptr, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(ptr != nullptr))

// Assertions de comparaison
#define ASSERT_LESS(left, right, ...) \
    nkentseu::test::TestAssert::Less(left, right, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(left < right))

#define ASSERT_LESS_EQUAL(left, right, ...) \
    nkentseu::test::TestAssert::LessEqual(left, right, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(left <= right))

#define ASSERT_GREATER(left, right, ...) \
    nkentseu::test::TestAssert::Greater(left, right, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(left > right))

#define ASSERT_GREATER_EQUAL(left, right, ...) \
    nkentseu::test::TestAssert::GreaterEqual(left, right, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(left >= right))

// Assertions avec tolérance (pour les nombres à virgule)
#define ASSERT_EQUAL_TOLERANCE(expected, actual, tolerance, ...) \
    nkentseu::test::TestAssert::EqualWithTolerance(expected, actual, tolerance, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(std::abs(expected - actual) <= tolerance))

// Assertions d'exceptions
#define ASSERT_THROWS(exception_type, expression, ...) \
    nkentseu::test::TestAssert::Throws<exception_type>([&]() { expression; }, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(expression))

#define ASSERT_NO_THROW(expression, ...) \
    nkentseu::test::TestAssert::NoThrow([&]() { expression; }, "" __VA_ARGS__, __FILE__, __LINE__, \
        EXPR_TO_STRING(expression))