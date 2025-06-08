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

    auto TESActorBase::GetActorName() -> FString
    {
        const FProperty* property = GetPropertyByNameInChain(STR("FullName"));

        if (property != nullptr)
        {
            if (const auto fullName = property->ContainerPtrToValuePtr<FString>(this); fullName != nullptr)
            {
                return *fullName;
            }
        }

        return FString {};
    }
}
