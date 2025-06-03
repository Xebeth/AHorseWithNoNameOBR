#pragma once

namespace RC::Unreal
{
    class TESActorBase: public TESForm
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(TESActorBase, Altar)

        auto GetActorName() -> StringType;
    };
}
