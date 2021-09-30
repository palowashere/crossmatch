#pragma once

#include <memory>
#include <string>

#include "Program.hpp"

namespace crossmatch 
{
    class Crossmatch {
    public:
        Crossmatch();

        void LoadProgram(const std::string &path);

    private:
        std::unique_ptr<Program> m_program{nullptr};
    };
}