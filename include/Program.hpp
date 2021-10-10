#pragma once

#include <map>
#include <string>
#include <set>
#include <llvm/Analysis/CallGraph.h>
#include <llvm/IR/Module.h>

#include "Function.hpp"

namespace crossmatch
{
    class Program {
    public:
        Program(const std::string &path);

    private:
        void Load(const std::string &path);

        void StructuralPass(const llvm::Module::FunctionListType &functions, llvm::CallGraph &callgraph);
        void SemanticPass(const llvm::Module::FunctionListType &functions);

    private:
        std::string m_program_path{""};
        std::map<std::string, Function> m_functions;
    };
}