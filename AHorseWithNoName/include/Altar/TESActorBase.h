#pragma once

namespace RC::Unreal
{
    class TESActorBase: public UTESForm
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(TESActorBase, Altar)

        auto GetActorName() -> FString;
    };
}
