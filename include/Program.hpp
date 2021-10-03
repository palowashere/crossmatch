#pragma once

#include <map>
#include <string>
#include <set>
#include <retdec/retdec/retdec.h>

#include "Function.hpp"

namespace crossmatch
{
    class Program {
    public:
        Program(const std::string &path);

    private:
        void Load(const std::string &path);

        void StructuralPass(const retdec::common::FunctionSet &functions);
        void SemanticPass(const retdec::common::FunctionSet &functions);

        void AddCallGraphRoot(Addr root);
        void AddFunctionBBStart(Addr function, Addr bb);

    private:
        std::string m_program_path{""};
        std::map<std::string, Function> m_functions;
        std::set<Addr> m_callgraph_roots;
        std::map<Addr, std::set<Addr>> m_function_bb_starts;
    };
}