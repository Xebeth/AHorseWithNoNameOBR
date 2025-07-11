#include <Unreal/BPMacros.hpp>
#include <Unreal/UClass.hpp>

#include "PropertyMacro.h"
#include "TESForm.h"
#include "VTESObjectRefComponent.h"
#include "VCharacterStatePairingComponent.h"
#include "VPairedPawn.h"
#include "VPairedCreature.h"
#include "VPairedCharacter.h"

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(AVPairedCharacter)

    auto AVPairedCharacter::GetHorse() -> AVPairedCreature*
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Altar.VPairedCharacter:GetHorse")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(AVPairedCreature*)
    }
}
