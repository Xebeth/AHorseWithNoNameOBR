#pragma once

namespace RC::Unreal
{
    class UTESForm: public UObject
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UTESForm, Altar)

        auto GetFormEditorID() -> FString;
        auto GetHexFormID() -> FString;
    };
}
