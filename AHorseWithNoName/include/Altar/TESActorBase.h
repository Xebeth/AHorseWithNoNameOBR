#pragma once

namespace RC::Unreal
{
    class TESActorBase: public UTESForm
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(TESActorBase, Altar)
        DEFINE_PROPERTY(FString, FullName)

        auto GetActorName() -> FString;
        auto SetActorName(const FString& Name) -> bool;
    };
}
