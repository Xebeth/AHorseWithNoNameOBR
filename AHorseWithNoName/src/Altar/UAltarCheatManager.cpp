#include <Unreal/BPMacros.hpp>
#include <Unreal/UClass.hpp>

#include "UCheatManager.h"
#include "UAltarCheatManager.h"

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UAltarCheatManager)

    auto UAltarCheatManager::SendMultipleOblivionCommand(const TArray<FString>& CommandeLists) -> void
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Altar.AltarCheatManager:SendMultipleOblivionCommand")

        UE_COPY_PROPERTY(CommandeLists, TArray<FString>)
        UE_CALL_FUNCTION()

        UE_END_VOID_FUNCTION()
    }
}
