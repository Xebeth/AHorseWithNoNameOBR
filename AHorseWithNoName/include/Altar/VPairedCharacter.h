#pragma once

namespace RC::Unreal
{
    class AVPairedCharacter: public AVPairedPawn
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(AVPairedCharacter, Altar)

        auto GetHorse() -> AVPairedPawn*;
    };
}
