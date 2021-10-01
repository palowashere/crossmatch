#pragma once

#include <rapidjson/document.h>
#include <string>
#include <memory>

#include "StructuralInfo.hpp"

namespace crossmatch
{
    class Config;
    extern std::unique_ptr<Config> config;

    class Config {
    public:
        explicit Config(const std::string &path);

    public:
        StructuralWeights structural_weights;

    private:
        void Parse(const std::string &path);
        std::size_t GetValue(const rapidjson::Value &element, const std::string &name) const;
        void ParseStructuralWeights(const rapidjson::Document &document);
    };
}