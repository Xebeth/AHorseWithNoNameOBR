#include <Unreal/BPMacros.hpp>
#include <Unreal/UClass.hpp>

#include "PropertyMacro.h"
#include "UCheatManager.h"
#include "PlayerController.h"
#include "UAltarCheatManager.h"
#include "TESForm.h"
#include "VTESObjectRefComponent.h"
#include "VPairedPawn.h"
#include "VPairedCreature.h"
#include "VPairedCharacter.h"
#include "VOblivionPlayerCharacter.h"
#include "VAltarPlayerController.h"

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(AVAltarPlayerController)

    auto AVAltarPlayerController::GetAltarCheatManager() -> UAltarCheatManager*
    {
        return static_cast<UAltarCheatManager*>(GetCheatManager());
    }

    auto AVAltarPlayerController::GetPlayerCharacter() -> AVOblivionPlayerCharacter*
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Altar.VAltarPlayerController:GetPlayerCharacter")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(AVOblivionPlayerCharacter*)
    }

    auto AVAltarPlayerController::IsHorseRiding() -> bool
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Altar.VAltarPlayerController:IsHorseRiding")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(bool)
    }
}
