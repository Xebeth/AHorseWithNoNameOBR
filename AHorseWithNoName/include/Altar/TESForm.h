#pragma once

namespace RC::Unreal
{
    class TESForm: public UObject
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(TESForm, Altar)

        auto GetFormEditorID() -> FString;
        auto GetHexFormID() -> FString;
    };
}
