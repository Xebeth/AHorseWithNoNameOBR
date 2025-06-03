#include <Unreal/BPMacros.hpp>
#include <Unreal/FString.hpp>
#include <Unreal/UClass.hpp>
#include <Unreal/FProperty.hpp>

#include "PropertyMacro.h"
#include "TESForm.h"
#include "TESActorBase.h"

namespace RC::Unreal
{
    IMPLEMENT_EXTERNAL_OBJECT_CLASS(TESActorBase)

    auto TESActorBase::GetActorName() -> StringType
    {
        const FProperty* property = GetPropertyByNameInChain(STR("FullName"));
        const auto subPathString = property->ContainerPtrToValuePtr<FString>(this);

        return subPathString->GetCharArray();
    }
}
