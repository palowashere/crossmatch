#include "Utility.hpp"

#include <fstream>
#include <sstream>

namespace crossmatch::utility
{
    std::optional<std::string> ReadFileContent(const std::string &path)
    {
        std::string data{""};

        if(std::ifstream file(path); file.is_open())
        {
            std::ostringstream oss;
            oss << file.rdbuf();
            data = oss.str();
            return data;
        }
        else
        {
            return std::nullopt;
        }
    }
}