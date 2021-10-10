#include "Program.hpp"
#include "Log.hpp"
#include "StructuralAnalysis.hpp"

#include <retdec/retdec/retdec.h>

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
            
        auto llvm = retdec::disassemble(path, nullptr);

        auto &functions = llvm.module->getFunctionList();
        log->info("[Program::Load] Functions found: %d", functions.size());

        llvm::CallGraph callgraph = llvm::CallGraph(*llvm.module);

        StructuralPass(functions, callgraph);
        SemanticPass(functions);
    }

    void Program::StructuralPass(const llvm::Module::FunctionListType &functions, llvm::CallGraph &callgraph)
    {
        log->info("[Program::StructuralPass] Start");       

        StructuralAnalysis sa;
        for(const auto &f : functions)
        {
            sa.Analyze(*this, f, callgraph);
        }
    }
    
    void Program::SemanticPass(const llvm::Module::FunctionListType &functions)
    {
        log->info("[Program::SemanticPass] Start");       
        (void)functions;
    }
}