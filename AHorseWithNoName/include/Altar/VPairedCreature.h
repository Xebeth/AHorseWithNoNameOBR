#pragma once

namespace RC::Unreal
{
    class AVPairedCharacter;

    class AVPairedCreature: public AVPairedPawn
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(AVPairedCreature, Altar)
        DEFINE_PROPERTY(AVPairedCharacter*, Rider)
    };
}
