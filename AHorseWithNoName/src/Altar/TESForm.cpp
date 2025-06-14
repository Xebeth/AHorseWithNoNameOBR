#include <Unreal/BPMacros.hpp>
#include <Unreal/UClass.hpp>

#include "PropertyMacro.h"
#include "TESForm.h"

namespace RC::Unreal
{
    using namespace std;

    IMPLEMENT_EXTERNAL_OBJECT_CLASS(UTESForm)

    auto UTESForm::GetFormEditorID() -> FString
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Altar.TESForm:GetFormEditorID")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(FString)
    }

    auto UTESForm::GetHexFormID() -> FString
    {
        UE_BEGIN_NATIVE_FUNCTION_BODY("/Script/Altar.TESForm:GetHexFormID")

        UE_CALL_FUNCTION()

        UE_RETURN_PROPERTY(FString)
    }
}
