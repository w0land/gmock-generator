#ifndef CLANGPARSER_HPP_EI7CPHU1
#define CLANGPARSER_HPP_EI7CPHU1

#include <clang-c/CXCompilationDatabase.h>
#include <clang-c/Index.h>

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "clangparseroptions.hpp"
#include "types.hpp"

struct ClangParser {
    ClangParser(const std::string& filename,
                ClangParserOptions options = ClangParserOptions{});
    ~ClangParser();

    CXXFile parse();

   private:
    using NamespaceCb = std::function<void(CXCursor)>;
    static CXChildVisitResult visit(CXCursor cursor, CXCursor parent,
                                    CXClientData thiz);

    const std::string _filename;
    ClangParserOptions _options;
    CXIndex _index;
    CXTranslationUnit _unit;
    CXCompilationDatabase _compilationDatabase{nullptr};
    CXCompileCommands _compileCommands{nullptr};

    std::unordered_map<CXCursorKind, NamespaceCb> _cbs;
    CXXFile _file;
};

#endif /* end of include guard: CLANGPARSER_HPP_EI7CPHU1 */
