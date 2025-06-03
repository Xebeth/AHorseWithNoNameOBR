#include <Unreal/BPMacros.hpp>
#include <Unreal/UClass.hpp>

#include "PropertyMacro.h"
#include "TESForm.h"
#include "VTESObjectRefComponent.h"

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UVTESObjectRefComponent)

    FString UVTESObjectRefComponent::GetHexFormRefID()
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Altar.VTESObjectRefComponent:GetHexFormRefID")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(FString)
    }
}
