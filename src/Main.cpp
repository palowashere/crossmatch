#include <iostream>
#include <retdec/retdec/retdec.h>
#include <retdec/llvm/Support/raw_ostream.h>

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "Hello from CrossaMatch!" << std::endl;
    retdec::common::FunctionSet fs;
    auto llvm = retdec::disassemble("./samples/test", &fs);

    llvm::outs() << *llvm.module;

    return 0;
}