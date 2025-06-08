#include <Unreal/BPMacros.hpp>
#include <Unreal/UClass.hpp>

#include "PropertyMacro.h"
#include "TESForm.h"

namespace RC::Unreal
{
    using namespace std;

    IMPLEMENT_EXTERNAL_OBJECT_CLASS(TESForm)

    auto TESForm::GetFormEditorID() -> FString
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Altar.TESForm:GetFormEditorID")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(FString)
    }

    auto TESForm::GetHexFormID() -> FString
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Altar.TESForm:GetHexFormID")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(FString)
    }
}
