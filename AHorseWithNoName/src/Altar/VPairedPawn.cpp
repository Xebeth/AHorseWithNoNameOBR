#include <Unreal/BPMacros.hpp>
#include <Unreal/UClass.hpp>

#include "PropertyMacro.h"
#include "TESForm.h"
#include "VTESObjectRefComponent.h"
#include "VPairedPawn.h"

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(AVPairedPawn)

    auto AVPairedPawn::IsPlayerCharacter() -> bool
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Altar.VPairedPawn:IsPlayerCharacter")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(bool)
    }
}
