#include <gtest/gtest.h>
#include "clangparser.hpp"
#include "fs.hpp"

const std::string rootTestData = TEST_DIR;

TEST(Generator, non_existent_file_throws) {
    EXPECT_ANY_THROW(ClangParser gen{""});
}

TEST(Generator, reading_file_ok) {
    fs::path testFilePath = fs::path{rootTestData} / "C1.hpp";
    EXPECT_NO_THROW(ClangParser gen{testFilePath.string()});
}

TEST(Generator, c1_hpp) {
    fs::path testFilePath = fs::path{rootTestData} / "C1.hpp";
    ClangParser gen{testFilePath.string()};

    auto parsed = gen.parse();

    ASSERT_EQ(parsed._namespaces.size(), 1);
    ASSERT_EQ(parsed._namespaces.at(0)._classes.size(), 1);

    auto& _classes = parsed._namespaces.at(0)._classes;
    auto& _class = _classes.at(0);

    EXPECT_EQ(_class._name, "C1");

    ASSERT_EQ(_class._ctors.size(), 1);
    ASSERT_EQ(_class._ctors.at(0)._arguments.size(), 1);
    EXPECT_EQ(_class._ctors.at(0)._arguments.at(0)._type, "int");

    EXPECT_EQ(_class._methods.size(), 3);
    EXPECT_EQ(_class._methods.at(0)._name, "f0");
    EXPECT_EQ(_class._methods.at(0)._const, true);
    EXPECT_EQ(_class._methods.at(0)._returnType, "void");

    ASSERT_EQ(_class._ctors.size(), 1);
    EXPECT_EQ(_class._ctors.at(0)._returnType, "");
    ASSERT_EQ(_class._ctors.at(0)._arguments.size(), 1);
    EXPECT_EQ(_class._ctors.at(0)._arguments.at(0)._type, "int");
}

TEST(Generator, NotificationBackendInterface_hpp) {
    fs::path testFilePath =
        fs::path{rootTestData} / "NotificationBackendInterface.hpp";
    ClangParser gen{testFilePath.string()};

    auto parsed = gen.parse();
    ASSERT_EQ(parsed._namespaces.size(), 1);
    ASSERT_EQ(parsed._namespaces.at(0)._classes.size(), 1);

    auto& _classes = parsed._namespaces.at(0)._classes;
    auto& _class = _classes.at(0);

    EXPECT_EQ(_class._name, "NotificationBackendInterface");
    ASSERT_EQ(_class._methods.size(), 1);
    EXPECT_EQ(_class._methods.at(0)._returnType, "void");
    EXPECT_EQ(_class._methods.at(0)._const, false);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(Generator, missing_include_file) {
    const fs::path testFilePath = fs::path{rootTestData} / "MissingInclude.hpp";

    auto fn = [&]() {
        ClangParser{testFilePath.string(), ClangParserOptions::StrictMode};
    };
    EXPECT_THROW(fn(), std::runtime_error);
}
