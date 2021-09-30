#include "Program.hpp"
#include "Log.hpp"
#include "StructuralAnalysis.hpp"

namespace crossmatch
{
    Program::Program(const std::string &path)
        : m_program_path{path}
    {
        this->Load(path);
    }

    void Program::Load(const std::string &path)
    {
        log->info("[Program::Load] Loading program: %s", path.c_str());

        retdec::common::FunctionSet fs;
        auto llvm = retdec::disassemble(path, &fs);

        log->info("[Program::Load] Functions found by retdec: %d", fs.size());

        StructuralPass(fs);
        SemanticPass(fs);
    }

    void Program::StructuralPass(const retdec::common::FunctionSet &functions)
    {
        log->info("[Program::StructuralPass] Start");       

        for(const auto &f : functions)
        {
            Function new_function(f.getName());
            StructuralAnalysis sa;

            if(sa.Analyze(new_function, f))
            {
                m_functions.insert({new_function.GetName(), new_function});
            }
        }
    }
    
    void Program::SemanticPass(const retdec::common::FunctionSet &functions)
    {
        log->info("[Program::SemanticPass] Start");       
        (void)functions;
    }
}