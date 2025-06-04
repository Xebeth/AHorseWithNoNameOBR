#include <Microsoft/AllowMicrosoftPlatformTypes.hpp>
#include <SigScanner/SinglePassSigScanner.hpp>
#include <Mod/CppUserModBase.hpp>
#include <Unreal/UClass.hpp>
#include <AActor.hpp>

#include "AActor.hpp"
#include <algorithm>
#include "PropertyMacro.h"
#include "TESForm.h"
#include "TESActorBase.h"
#include "UCheatManager.h"
#include "PlayerController.h"
#include "UAltarCheatManager.h"
#include "VAltarPlayerController.h"
#include "VTESObjectRefComponent.h"
#include "VPairedPawn.h"
#include "VPairedCharacter.h"
#include "HorseHandler.h"

using namespace RC::Mod::HorseName;

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
        ModName = STR("AHorseWithNoName");
        ModVersion = STR("1.0");
    }

    ~AHorseWithNoName() override
    {
        if (m_pHorseHandler != nullptr)
        {
            delete m_pHorseHandler;
            m_pHorseHandler = nullptr;
        }
    }

    auto on_unreal_init() -> void override
    {
        FindSetSelectedActor();

        if (m_pHorseHandler != nullptr)
        {
            m_pHorseHandler->RegisterHooks();
        }
    }
};

void AHorseWithNoName::FindSetSelectedActor()
{
    SignatureData signature;
    signature.signature = "41 56 48 83 EC 30 33 ED 48 8B FA 48 8B F1";
    std::vector setSelectedActor = { SignatureContainer({ signature }, [&](SignatureContainer &match) {
        auto matchedAddress = match.get_match_address();
        bool success = matchedAddress != nullptr;
        StringType pattern;

        match.get_did_succeed() = success;
        pattern.assign(signature.signature.begin(), signature.signature.end());
        Output::send(MODSTR("Match found @ {} for SetSelectedActor using signature {}"),
                            fmt::ptr(reinterpret_cast<const void*>(match.get_match_address())), pattern);

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
            auto setSelectedActorFunc = reinterpret_cast<fnSetSelectedActor>(match.get_match_address() - 0x14);
            Output::send(MODSTR("SetSelectedActor found at {}"), fmt::ptr(setSelectedActorFunc));

            m_pHorseHandler = new HorseHandler(setSelectedActorFunc);
        }
    }) };
    SignatureContainerMap map;

    map.emplace(ScanTarget::MainExe, setSelectedActor);

    uint32_t old_threads = SinglePassScanner::m_num_threads;
    SinglePassScanner::m_num_threads = 1;
    SinglePassScanner::start_scan(map);
    SinglePassScanner::m_num_threads = old_threads;
}

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
