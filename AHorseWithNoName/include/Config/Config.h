#pragma once

namespace RC::UserMod::HorseName
{
    #define MODSTR(_in_mod_str) STR("[AHorseWithNoName] " _in_mod_str "\n")

    class Config
    {
        typedef struct ConfigData_t
        {
            int Offset = DefaultOffset;
            std::string Signature = DefaultSignature;

            struct glaze_json_schema
            {
                glz::schema Signature {.description = "Signature used to find the address of the UAltarCheatManager::SetSelectedActor function -- DO NOT MODIFY"};
                glz::schema Offset {.description = "Offset to apply to the result of the memory scan -- DO NOT MODIFY"};
            };
        } ConfigData;

        std::map<std::string, std::string> m_HorseNames;
        std::filesystem::path m_ConfigPath;
        std::string m_Signature;
        int m_Offset;
    public:
        explicit Config(std::filesystem::path path);

        StringType GetHorseName(const std::string &editorID);
        void SaveConfig(std::string configFile) const;

        std::map<std::string, std::string> HorseNames() const;
        const std::string& Signature() const;
        int Offset() const;

        static const char* DefaultSignature;
        static const int DefaultOffset;
    };

}
