#pragma once

namespace RC::Unreal
{
    class AVPairedPawn: public AActor
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(AVPairedPawn, Engine)
        DEFINE_PROPERTY(UVTESObjectRefComponent*, TESRefComponent)
        DEFINE_PROPERTY(UVCharacterStatePairingComponent*, OblivionActorStatePairingComponent, ActorState)

        auto IsPlayerCharacter() -> bool;
        UTESForm* GetTESForm();

        auto IsSneaking() -> bool;
        auto IsSwimming() -> bool;
        auto IsFalling() -> bool;
        auto IsJumping() -> bool;
        auto IsRunning() -> bool;

        auto GetActorName() -> StringType;
        auto GetEditorID() -> StringType;
        auto GetFormID() -> StringType;
    };
}
