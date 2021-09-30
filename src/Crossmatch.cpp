#include "Crossmatch.hpp"

namespace crossmatch
{
    Crossmatch::Crossmatch()
    {

    }

    void Crossmatch::LoadProgram(const std::string &path)
    {
        m_program = std::make_unique<Program>(path);
    }
}