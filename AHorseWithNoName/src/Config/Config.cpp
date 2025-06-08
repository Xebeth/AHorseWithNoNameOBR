#include <DynamicOutput/Output.hpp>
#include <String/StringType.hpp>
#include <Helpers/String.hpp>

#include <glaze/json/schema.hpp>
#include <glaze/json/write.hpp>
#include <glaze/json/read.hpp>
#include <string>
#include <map>

#include "Config.h"

namespace RC::UserMod::HorseName
{
    const char* Config::DefaultSignature = "41 56 48 83 EC 30 33 ED 48 8B FA 48 8B F1";
    const int Config::DefaultOffset = -0x14;

    Config::Config(std::filesystem::path path): m_ConfigPath(std::move(path)),
                                                m_Signature(DefaultSignature),
                                                m_Offset(DefaultOffset)
    {
        const auto horseNamesFile = (m_ConfigPath / "horses.json").string();
        const auto configFile = (m_ConfigPath / "config.json").string();
        ConfigData data {};

        Output::send(MODSTR("Reading configuration from {}"), to_wstring(configFile));

        if (const auto ec = glz::read_file_json(data, m_ConfigPath.string(), std::string{}); ec)
        {
            Output::send<LogLevel::Warning>(MODSTR("No configuration file found. Creating default."));
            SaveConfig(configFile);
        }

        Output::send(MODSTR("Reading horse names from {}"), to_wstring(horseNamesFile));

        if (const auto ec = glz::read_file_json(m_HorseNames, horseNamesFile, std::string{}); ec)
        {
            Output::send<LogLevel::Warning>(MODSTR("No horse names file found"));
        }

        m_Signature = data.Signature;
        m_Offset = data.Offset;
    }

    std::map<std::string, std::string> Config::HorseNames() const
    {
        return m_HorseNames;
    }

    auto Config::GetHorseName(const std::string& editorID) -> StringType
    {
        for (const auto& [id, name] : m_HorseNames)
        {
            if (id == editorID)
            {
                return to_wstring(name);
            }
        }

        return std::format(STR("LOC_FN_{}"), to_wstring(editorID));
    }

    void Config::SaveConfig(std::string configFile) const
    {
        ConfigData data {
            .Offset = m_Offset,
            .Signature = m_Signature
        };

        if (auto ec = glz::write_file_json<glz::opts{.prettify = true}>(data, configFile, std::string{}))
        {
            Output::send<LogLevel::Error>(MODSTR("Failed to write configuration {}: {}"),
                                          to_wstring(configFile), to_wstring(ec.includer_error));
        }
    }

    const std::string&Config::Signature() const
    {
        return m_Signature;
    }

    int Config::Offset() const
    {
        return m_Offset;
    }
}
