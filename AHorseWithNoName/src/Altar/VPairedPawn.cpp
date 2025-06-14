#include <Unreal/BPMacros.hpp>
#include <Unreal/UClass.hpp>

#include "PropertyMacro.h"
#include "TESForm.h"
#include "VTESObjectRefComponent.h"
#include "VCharacterStatePairingComponent.h"
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
        if (const auto pRefComponent = GetTESRef(); pRefComponent != nullptr)
        {
            return pRefComponent->GetTESForm();
        }

        return nullptr;
    }

    auto AVPairedPawn::IsFalling() -> bool
    {
        if (const auto pActorStateComponent = GetActorState(); pActorStateComponent != nullptr)
        {
            return pActorStateComponent->GetIsFalling();
        }

        return false;
    }

    auto AVPairedPawn::IsJumping() -> bool
    {
        if (const auto pActorStateComponent = GetActorState(); pActorStateComponent != nullptr)
        {
            return pActorStateComponent->GetIsJumping();
        }

        return false;
    }

    auto AVPairedPawn::IsSneaking() -> bool
    {
        if (const auto pActorStateComponent = GetActorState(); pActorStateComponent != nullptr)
        {
            return pActorStateComponent->GetIsSneaking();
        }

        return false;
    }

    auto AVPairedPawn::IsRunning() -> bool
    {
        if (const auto pActorStateComponent = GetActorState(); pActorStateComponent != nullptr)
        {
            return pActorStateComponent->GetIsRunning();
        }

        return false;
    }

    auto AVPairedPawn::IsSwimming() -> bool
    {
        if (const auto pActorStateComponent = GetActorState(); pActorStateComponent != nullptr)
        {
            return pActorStateComponent->GetIsSwimming();
        }

        return false;
    }

    auto AVPairedPawn::SetActorName(const FString& Name) -> bool
    {
        if (const auto pTESForm = GetTESForm(); pTESForm != nullptr)
        {
            const auto pActorBase = reinterpret_cast<TESActorBase*>(pTESForm);

            return pActorBase->SetActorName(Name);
        }

        return false;
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

    auto AVPairedPawn::GetRefFormID() -> StringType
    {
        if (const auto pRefComponent = GetTESRef(); pRefComponent != nullptr)
        {
            return StringType { pRefComponent->GetHexFormRefID().GetCharArray() };
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
