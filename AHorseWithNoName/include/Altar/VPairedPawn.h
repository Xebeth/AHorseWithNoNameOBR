#pragma once

namespace RC::Unreal
{
    class AVPairedPawn: public AActor
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(AVPairedPawn, Engine)
        DEFINE_PROPERTY(UVTESObjectRefComponent*, TESRefComponent, TESRef)
        DEFINE_PROPERTY(UVCharacterStatePairingComponent*, OblivionActorStatePairingComponent, ActorState)

        auto IsPlayerCharacter() -> bool;
        UTESForm* GetTESForm();

        auto IsSneaking() -> bool;
        auto IsBlocking() -> bool;
        auto IsSwimming() -> bool;
        auto IsFalling() -> bool;
        auto IsJumping() -> bool;
        auto IsRunning() -> bool;

        auto SetActorName(const FString& Name) -> bool;
        auto GetActorName() -> StringType;
        auto GetRefFormID() -> StringType;
        auto GetEditorID() -> StringType;
        auto GetFormID() -> StringType;
    };
}
