#include "Crossmatch.hpp"
#include "Log.hpp"
#include "Config.hpp"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    crossmatch::log->SetLevel(crossmatch::Level::DEBUG);
    crossmatch::config = std::make_unique<crossmatch::Config>("./config.json");

    crossmatch::Crossmatch cm;
    cm.LoadProgram("./samples/test");

    return 0;
}