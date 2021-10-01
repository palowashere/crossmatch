#include "Config.hpp"
#include "Utility.hpp"
#include "Log.hpp"

namespace crossmatch
{
    std::unique_ptr<Config> config{nullptr};

    Config::Config(const std::string &path)
    {
        Parse(path);
    }

    void Config::Parse(const std::string &path)
    {
        if(auto data = utility::ReadFileContent(path); data.has_value())
        {
            rapidjson::Document json;
            json.Parse(data.value().c_str());

            ParseStructuralWeights(json);
        }
    }
    
    std::size_t Config::GetValue(const rapidjson::Value &element, const std::string &name) const
    {
        if(auto element_name = name.c_str(); element.HasMember(element_name) && element[element_name].IsNumber())
        {
            return element[element_name].GetUint();
        }
        else
        {
            log->error("[Config::GetValue] No element named: '%s'", name.c_str());
            return 0;
        }
    }

    void Config::ParseStructuralWeights(const rapidjson::Document &document)
    {
        if(document.HasMember("structural_weights"))
        {
            auto &sw = document["structural_weights"];

            structural_weights.bb_count = GetValue(sw, "bb_count");
            structural_weights.entry_points = GetValue(sw, "entry_points");
            structural_weights.exit_points = GetValue(sw, "exit_points");
            structural_weights.inlinks = GetValue(sw, "inlinks");
            structural_weights.unique_inlinks = GetValue(sw, "unique_inlinks");
            structural_weights.outlinks = GetValue(sw, "outlinks");
            structural_weights.unique_outlinks = GetValue(sw, "unique_outlinks");
            structural_weights.loops = GetValue(sw, "loops");
            structural_weights.forward_edges = GetValue(sw, "forward_edges");
            structural_weights.cross_edges = GetValue(sw, "cross_edges");
            structural_weights.back_edges = GetValue(sw, "back_edges");
            structural_weights.basis_edges = GetValue(sw, "basis_edges");
            structural_weights.cfg_bitsig = GetValue(sw, "cfg_bitsig");
            structural_weights.folded_cfg_bitsig = GetValue(sw, "folded_cfg_bitsig");
            structural_weights.dom_bitsig = GetValue(sw, "dom_bitsig");
            structural_weights.folded_dom_bitsig = GetValue(sw, "folded_dom_bitsig");
            structural_weights.cyc_complexity = GetValue(sw, "cyc_complexity");
            structural_weights.callgraph_depth = GetValue(sw, "callgraph_depth");
            structural_weights.callgraph_dom_depth = GetValue(sw, "callgraph_dom_depth");
        }
        else
        {
            log->error("[Config::ParseStructuralWeights] No 'structural_weights' in configuration file");
        }
    }
}