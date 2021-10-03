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

        StructuralAnalysis sa;
        for(const auto &f : functions)
        {
            sa.Analyze(*this, f);
        }
    }
    
    void Program::SemanticPass(const retdec::common::FunctionSet &functions)
    {
        log->info("[Program::SemanticPass] Start");       
        (void)functions;
    }

    void Program::AddCallGraphRoot(Addr root)
    {
        m_callgraph_roots.insert(root);
    }

    void Program::AddFunctionBBStart(Addr function, Addr bb)
    {
        m_function_bb_starts[function].insert(bb);
    }
}