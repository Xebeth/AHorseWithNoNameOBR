#pragma once

namespace RC::Unreal
{
    class AVAltarPlayerController: public APlayerController
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(AVAltarPlayerController, Altar)

        auto GetPlayerCharacter() -> AVOblivionPlayerCharacter*;
        auto GetAltarCheatManager() -> UAltarCheatManager*;

        auto IsHorseRiding() -> bool;
    };
}
