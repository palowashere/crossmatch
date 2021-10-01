#pragma once

#include <optional>
#include <string>

namespace crossmatch::utility
{
    std::optional<std::string> ReadFileContent(const std::string &path);
}