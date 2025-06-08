#include <Microsoft/AllowMicrosoftPlatformTypes.hpp>
#include <SigScanner/SinglePassSigScanner.hpp>
#include <Mod/CppUserModBase.hpp>
#include <String/StringType.hpp>
#include <Unreal/UClass.hpp>
#include <UE4SSProgram.hpp>
#include <AActor.hpp>

#include <glaze/json/schema.hpp>
#include <string>
#include <map>

#include <algorithm>

#include "Config.h"
#include "PropertyMacro.h"
#include "TESForm.h"
#include "TESActorBase.h"
#include "UCheatManager.h"
#include "PlayerController.h"
#include "VTESObjectRefComponent.h"
#include "VPairedPawn.h"
#include "VPairedCreature.h"
#include "VPairedCharacter.h"
#include "UAltarCheatManager.h"
#include "VOblivionPlayerCharacter.h"
#include "VAltarPlayerController.h"
#include "HorseHandler.h"

namespace RC::UserMod::HorseName
{
    class AHorseWithNoName final : public CppUserModBase
    {
        using SignatureContainerMap = std::unordered_map<ScanTarget, std::vector<SignatureContainer>>;

        HorseHandler *m_pHorseHandler = nullptr;
        void FindSetSelectedActor();
    public:
        AHorseWithNoName()
        {
            ModDescription = STR("Hides your horse name while riding");
            ModAuthors = STR("Beorn Blackclaw");
            ModName = STR("A Horse With No Name");
            ModVersion = STR("1.0");
        }

        ~AHorseWithNoName() override
        {
            if (m_pHorseHandler != nullptr)
            {
                m_pHorseHandler->UnregisterHooks();

                delete m_pHorseHandler;
                m_pHorseHandler = nullptr;
            }
        }

        auto on_unreal_init() -> void override
        {
            if (m_pHorseHandler == nullptr)
            {
                FindSetSelectedActor();

                if (m_pHorseHandler != nullptr)
                {
                    m_pHorseHandler->RegisterHooks();
                }
            }
        }
    };

    void AHorseWithNoName::FindSetSelectedActor()
    {
        auto configPath = StringType{UE4SSProgram::get_program().get_mods_directory()} + fmt::format(STR("\\AHorseWithNoName\\"));
        auto *pConfig = new Config(configPath);

        if (pConfig == nullptr)
        {
            Output::send<LogLevel::Error>(STR("Failed to create the configuration from {}"), configPath);

            return;
        }

        SignatureData signature { .signature = pConfig->Signature() };

        std::vector signatures = { SignatureContainer({ signature }, [&](SignatureContainer &match) {
            const StringType pattern { signature.signature.begin(), signature.signature.end() };
            const auto matchedAddress = match.get_match_address();
            const bool success = matchedAddress != nullptr;

            Output::send(MODSTR("Match found @ {} for SetSelectedActor using signature {}"),
                                fmt::ptr(reinterpret_cast<const void*>(match.get_match_address())), pattern);
            match.get_did_succeed() = success;

            return success;
        }, [&](SignatureContainer& match){
            if (match.get_did_succeed() == false)
            {
                StringType pattern;

                pattern.assign(signature.signature.begin(), signature.signature.end());
                Output::send<LogLevel::Error>(MODSTR("Scan for SetSelectedActor failed using signature {}"), pattern);
            }
            else
            {
                auto setSelectedActorFunc = reinterpret_cast<fnSetSelectedActor>(match.get_match_address() + pConfig->Offset());
                Output::send(MODSTR("SetSelectedActor found at {}"), fmt::ptr(setSelectedActorFunc));

                m_pHorseHandler = new HorseHandler(setSelectedActorFunc, pConfig);
            }
        })};
        SignatureContainerMap map;

        map.emplace(ScanTarget::MainExe, signatures);

        uint32_t old_threads = SinglePassScanner::m_num_threads;
        SinglePassScanner::m_num_threads = 1;
        SinglePassScanner::start_scan(map);
        SinglePassScanner::m_num_threads = old_threads;
    }
}

using namespace RC::UserMod::HorseName;

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
