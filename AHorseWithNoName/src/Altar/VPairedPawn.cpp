#include <Unreal/BPMacros.hpp>
#include <Unreal/UClass.hpp>

#include "PropertyMacro.h"
#include "TESForm.h"
#include "VTESObjectRefComponent.h"
#include "VPairedPawn.h"
#include "TESActorBase.h"

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(AVPairedPawn)

    auto AVPairedPawn::IsPlayerCharacter() -> bool
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Altar.VPairedPawn:IsPlayerCharacter")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(bool)
    }

    UTESForm* AVPairedPawn::GetTESForm()
    {
        if (const auto pRefComponent = GetTESRefComponent(); pRefComponent != nullptr)
        {
            return pRefComponent->GetTESForm();
        }

        return nullptr;
    }


    auto AVPairedPawn::GetActorName() -> StringType
    {
        if (const auto pTESForm = GetTESForm(); pTESForm != nullptr)
        {
            const auto pActorBase = reinterpret_cast<TESActorBase*>(pTESForm);

            return StringType { pActorBase->GetActorName().GetCharArray() };
        }

        return StringType {};
    }

    auto AVPairedPawn::GetFormID() -> StringType
    {
        if (const auto pTESForm = GetTESForm(); pTESForm != nullptr)
        {
            return StringType { pTESForm->GetHexFormID().GetCharArray() };
        }

        return StringType {};
    }

    auto AVPairedPawn::GetEditorID() -> StringType
    {
        if (const auto pTESForm = GetTESForm(); pTESForm != nullptr)
        {
            return StringType { pTESForm->GetFormEditorID().GetCharArray() };
        }

        return StringType {};
    }
}
