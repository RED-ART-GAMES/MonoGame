using System;
using System.Runtime.InteropServices;
using System.Security;

namespace Sce.PlayStation4.Input
{
    // NOTE: This exactly matches the struct defined in the C++ code.
    [StructLayout(LayoutKind.Explicit, Size = 104)]
    public struct GamePadState
    {
        [FieldOffset(0)]
        public bool IsConnected;

        [FieldOffset(4)]
        public int PacketNumber;

        [FieldOffset(8)]
        public float LeftStickX;

        [FieldOffset(12)]
        public float LeftStickY;

        [FieldOffset(16)]
        public float RightStickX;

        [FieldOffset(20)]
        public float RightStickY;

        [FieldOffset(24)]
        public float LeftTrigger;

        [FieldOffset(28)]
        public float RightTrigger;

        [FieldOffset(32)]
        public uint Buttons;

        [FieldOffset(36)]
        public float OrientationX;

        [FieldOffset(40)]
        public float OrientationY;

        [FieldOffset(44)]
        public float OrientationZ;

        [FieldOffset(48)]
        public float OrientationW;

        [FieldOffset(52)]
        public float AccelerationX;

        [FieldOffset(56)]
        public float AccelerationY;

        [FieldOffset(60)]
        public float AccelerationZ;

        [FieldOffset(64)]
        public float AngularVelocityX;

        [FieldOffset(68)]
        public float AngularVelocityY;

        [FieldOffset(72)]
        public float AngularVelocityZ;

        [FieldOffset(76)]
        public byte TouchCount;

        [FieldOffset(80)]
        public float Touch1X;

        [FieldOffset(84)]
        public float Touch1Y;

        [FieldOffset(88)]
        public byte Touch1Id;

        [FieldOffset(92)]
        public float Touch2X;

        [FieldOffset(96)]
        public float Touch2Y;

        [FieldOffset(100)]
        public byte Touch2Id;
    }

    public static partial class GamePad
    {
        public static unsafe GamePadState GetState(int playerIndex)
        {
            var state = new GamePadState();
            GetState(playerIndex, &state);
            return state;
        }
    }
}
