#pragma once

#include <string>

#include "StructuralInfo.hpp"

namespace crossmatch
{
    class Function {
    public:
        Function(const std::string &function_name);

        std::string GetName() const;
        
        void SetStructuralInfo(const StructuralInfo &si);

    private:
        std::string m_function_name{""};
        StructuralInfo m_structural_info;
    };
}