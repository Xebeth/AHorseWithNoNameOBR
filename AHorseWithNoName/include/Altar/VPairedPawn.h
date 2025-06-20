#pragma once

namespace RC::Unreal
{
    class AVPairedPawn: public AActor
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(AVPairedPawn, Engine)
        DEFINE_PROPERTY(UVTESObjectRefComponent*, TESRefComponent)

        auto IsPlayerCharacter() -> bool;
        TESForm*GetTESForm();

        auto GetActorName() -> StringType;
        auto GetEditorID() -> StringType;
        auto GetFormID() -> StringType;
    };
}
