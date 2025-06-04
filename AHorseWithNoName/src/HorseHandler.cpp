#include <Unreal/UClass.hpp>
#include <AActor.hpp>

#include "PropertyMacro.h"
#include "TESForm.h"
#include "TESActorBase.h"
#include "UCheatManager.h"
#include "PlayerController.h"
#include "UAltarCheatManager.h"
#include "VAltarPlayerController.h"
#include "VTESObjectRefComponent.h"
#include "VPairedPawn.h"
#include "VPairedCharacter.h"
#include "HorseHandler.h"

namespace RC::Mod::HorseName
{
	using namespace Unreal::UObjectGlobals;

	HorseHandler::HorseHandler(const fnSetSelectedActor setSelectedActorFunc)
	{
		SetSelectedActorFunc = setSelectedActorFunc;
	}

	auto HorseHandler::PostOnStartDockingToHorse(const UnrealScriptFunctionCallableContext& context, void *) -> void
	{
		if (const auto pPlayer = reinterpret_cast<AVPairedCharacter*>(context.Context); pPlayer != nullptr)
		{
			pPlayer->GetHorse();
		}
	}

	auto HorseHandler::PostGetHorse(const UnrealScriptFunctionCallableContext& context, void*) -> void
	{
		const auto ppHorse = static_cast<UObject**>(context.RESULT_DECL);

		if (ppHorse == nullptr)
		{
			Output::send<LogLevel::Warning>(MODSTR("No return value"));

			return;
		}

		const auto pHorse = reinterpret_cast<AVPairedPawn*>(*ppHorse);

		if (pHorse == nullptr)
		{
			Output::send<LogLevel::Warning>(MODSTR("Invalid horse"));

			return;
		}

		Output::send(MODSTR("Found the horse: {}"), pHorse->GetName());

		const auto pRider = reinterpret_cast<AVPairedPawn*>(context.Context);

		if (pRider == nullptr)
		{
			Output::send<LogLevel::Warning>(MODSTR("Invalid rider"));

			return;
		}

		if (pRider->IsPlayerCharacter())
		{
			this->UpdateHorseName(pHorse);
		}
		else
		{
			Output::send<LogLevel::Warning>(MODSTR("{} is not the player"), pRider->GetFullName());
		}
	}

	auto HorseHandler::UpdateHorseName(AVPairedPawn *pHorse) -> void
	{
		const auto pPlayerController = reinterpret_cast<AVAltarPlayerController*>(FindFirstOf(STR("BP_AltarPlayerController_C")));

		if (pPlayerController == nullptr)
		{
			Output::send<LogLevel::Warning>(MODSTR("Invalid player controller"));

			return;
		}

		auto mounted = pPlayerController->IsHorseRiding() && pHorse != nullptr;
		auto pCheatManager = pPlayerController->GetAltarCheatManager();

		Output::send(MODSTR("UpdateHorseName: {}"), mounted ? STR("Mounted") : STR("Dismounted"));
		Output::send(MODSTR("CheatManager: {}"), pCheatManager->GetName());

		if (mounted == false)
		{
			if (LastRiddenHorse != nullptr)
			{
				if (const auto formID = StringType(LastRiddenHorse->GetTESRefComponent()->GetHexFormRefID().GetCharArray()); HorseNames.contains(formID))
				{
					const auto horseName = HorseNames[formID];

					Output::send(MODSTR("Restore horse {} {} [{}]"), horseName, formID, LastRiddenHorse->GetName());

					RenameHorse(pCheatManager, LastRiddenHorse, horseName);
				}
				else
				{
					Output::send<LogLevel::Warning>(MODSTR("Horse name not found for FormID {}"), formID);
				}
			}
		}
		else if (LastRiddenHorse == nullptr || pHorse->GetName() != LastRiddenHorse->GetName())
		{
			const auto pTESForm = reinterpret_cast<TESActorBase*>(pHorse->GetTESRefComponent()->GetTESForm());

			if (pTESForm != nullptr)
			{
				const auto horseName = pTESForm->GetActorName();
				const auto formID = StringType(pHorse->GetTESRefComponent()->GetHexFormRefID().GetCharArray());

				Output::send(MODSTR("Rename horse {} {} [{}]"), horseName, formID, pHorse->GetName());
				RenameHorse(pCheatManager, pHorse, STR(" "));
				HorseNames[formID] = horseName;
			}
			else
			{
				Output::send(MODSTR("Horse TESForm is not of type TESActorBase"));
			}
		}
	}

	auto HorseHandler::RenameHorse(UAltarCheatManager *pCheatManager, AActor* pHorse, const StringType &horseName) -> void
	{
		if (SetSelectedActorFunc != nullptr)
		{
			SetSelectedActorFunc(pCheatManager, pHorse);
		}
	}

	void HorseHandler::ResetLastCalledHorse(UnrealScriptFunctionCallableContext&, void*)
	{
		this->LastRiddenHorse = nullptr;
	}

	void HorseHandler::RegisterHooks()
	{
		RegisterHook(OnFadeToBlackEvent, bind_front(&HorseHandler::ResetLastCalledHorse, this), NoCallback, nullptr);
		RegisterHook(OnStartDockingEvent, NoCallback, &HorseHandler::PostOnStartDockingToHorse, nullptr);
		RegisterHook(GetHorseFunc, NoCallback, bind_front(&HorseHandler::PostGetHorse, this), nullptr);
	}
}
