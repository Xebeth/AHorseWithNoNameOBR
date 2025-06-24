#pragma once

namespace RC::Unreal
{
    class UVCharacterStatePairingComponent: public UObject
    {
        DECLARE_EXTERNAL_OBJECT_CLASS(UVCharacterStatePairingComponent, Altar)
        DEFINE_PROPERTY(bool, bIsSwimming, IsSwimming)
        DEFINE_PROPERTY(bool, bIsSneaking, IsSneaking)
        DEFINE_PROPERTY(bool, bIsBlocking, IsBlocking)
        DEFINE_PROPERTY(bool, bIsFalling, IsFalling)
        DEFINE_PROPERTY(bool, bIsJumping, IsJumping)
        DEFINE_PROPERTY(bool, bIsRunning, IsRunning)
    };
}
