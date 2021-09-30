#pragma once

#include <map>
#include <string>
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

    private:
        std::string m_program_path{""};
        std::map<std::string, Function> m_functions;
    };
}