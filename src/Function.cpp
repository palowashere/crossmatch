#include "Function.hpp"

namespace crossmatch
{
    Function::Function(const std::string &function_name)
        : m_function_name{function_name}
    {

    }

    void Function::SetStructuralInfo(const StructuralInfo &si)
    {
        m_structural_info = si;
    }

    std::string Function::GetName() const
    {
        return m_function_name;
    }
}