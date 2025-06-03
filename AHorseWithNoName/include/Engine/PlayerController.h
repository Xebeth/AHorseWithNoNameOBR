#pragma once

namespace RC::Unreal
{
    class APlayerController: public UObject
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(APlayerController, Engine)
        DEFINE_PROPERTY(TObjectPtr<UCheatManager>, CheatManager)
    };
}
