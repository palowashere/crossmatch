#pragma once

#include <optional>
#include <string>
#include <retdec/retdec.h>

namespace crossmatch
{
    using Addr = retdec::common::Address;
}

namespace crossmatch::utility
{
    std::optional<std::string> ReadFileContent(const std::string &path);
}