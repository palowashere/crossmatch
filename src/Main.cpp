#include "Crossmatch.hpp"
#include "Log.hpp"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    crossmatch::log->SetLevel(crossmatch::Level::DEBUG);

    crossmatch::Crossmatch cm;
    cm.LoadProgram("./samples/test");

    return 0;
}