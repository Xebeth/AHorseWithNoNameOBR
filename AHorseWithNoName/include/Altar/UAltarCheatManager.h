#pragma once

namespace RC::Unreal
{
    class UAltarCheatManager : public UCheatManager
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UAltarCheatManager, Altar)

        auto SendMultipleOblivionCommand(const TArray<FString>& CommandeLists) -> void;
        void ObvConselect(FString& Arg);
        void ObvConsole(FString& Arg);
    };
}
