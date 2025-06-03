#include <Mod/CppUserModBase.hpp>

#include "HorseHandler.h"

using namespace RC::Mod::HorseName;

class AHorseWithNoName final : public CppUserModBase
{
    HorseHandler HorseHandler;
public:
    AHorseWithNoName()
    {
        ModDescription = STR("Hides your horse name while riding");
        ModAuthors = STR("Beorn Blackclaw");
        ModName = STR("AHorseWithNoName");
        ModVersion = STR("1.0");
    }

    auto on_unreal_init() -> void override
    {
        HorseHandler.RegisterHooks();
    }
};

#define USER_DLL_MOD_API __declspec(dllexport)

extern "C"
{
    USER_DLL_MOD_API CppUserModBase* start_mod()
    {
        return new AHorseWithNoName();
    }

    USER_DLL_MOD_API void uninstall_mod(const CppUserModBase* pModInstance)
    {
        delete pModInstance;
    }
}
