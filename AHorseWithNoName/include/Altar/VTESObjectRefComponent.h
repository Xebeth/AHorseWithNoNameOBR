#pragma once

namespace RC::Unreal
{
    class UVTESObjectRefComponent: public UObject
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UVTESObjectRefComponent, Altar)
        DEFINE_PROPERTY(UTESForm*, TESForm)

        auto GetHexFormRefID() -> FString;
    };
}
