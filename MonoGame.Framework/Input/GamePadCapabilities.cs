#region License
/*
Microsoft Public License (Ms-PL)
MonoGame - Copyright © 2009 The MonoGame Team

All rights reserved.

This license governs use of the accompanying software. If you use the software, you accept this license. If you do not
accept the license, do not use the software.

1. Definitions
The terms "reproduce," "reproduction," "derivative works," and "distribution" have the same meaning here as under 
U.S. copyright law.

A "contribution" is the original software, or any additions or changes to the software.
A "contributor" is any person that distributes its contribution under this license.
"Licensed patents" are a contributor's patent claims that read directly on its contribution.

2. Grant of Rights
(A) Copyright Grant- Subject to the terms of this license, including the license conditions and limitations in section 3, 
each contributor grants you a non-exclusive, worldwide, royalty-free copyright license to reproduce its contribution, prepare derivative works of its contribution, and distribute its contribution or any derivative works that you create.
(B) Patent Grant- Subject to the terms of this license, including the license conditions and limitations in section 3, 
each contributor grants you a non-exclusive, worldwide, royalty-free license under its licensed patents to make, have made, use, sell, offer for sale, import, and/or otherwise dispose of its contribution in the software or derivative works of the contribution in the software.

3. Conditions and Limitations
(A) No Trademark License- This license does not grant you rights to use any contributors' name, logo, or trademarks.
(B) If you bring a patent claim against any contributor over patents that you claim are infringed by the software, 
your patent license from such contributor to the software ends automatically.
(C) If you distribute any portion of the software, you must retain all copyright, patent, trademark, and attribution 
notices that are present in the software.
(D) If you distribute any portion of the software in source code form, you may do so only under this license by including 
a complete copy of this license with your distribution. If you distribute any portion of the software in compiled or object 
code form, you may only do so under a license that complies with this license.
(E) The software is licensed "as-is." You bear the risk of using it. The contributors give no express warranties, guarantees
or conditions. You may have additional consumer rights under your local laws which this license cannot change. To the extent
permitted under your local laws, the contributors exclude the implied warranties of merchantability, fitness for a particular
purpose and non-infringement.
*/
#endregion License

using System;

namespace Microsoft.Xna.Framework.Input
{
    public struct GamePadCapabilities
    {
        /// <summary>
        /// Gets the gamepad display name.
        /// 
        /// This property is not available in XNA.
        /// </summary>
        /// <value>String representing the display name of the gamepad.</value>
        public string DisplayName { get; internal set; }

        /// <summary>
        /// Gets the unique identifier of the gamepad.
        /// 
        /// This property is not available in XNA.
        /// </summary>
        /// <value>String representing the unique identifier of the gamepad.</value>
        public string Identifier { get; internal set; }

        public bool IsConnected { get; internal set; }

		public bool HasAButton { get; internal set; }

		public bool HasBackButton { get; internal set; }

		public bool HasBButton { get; internal set; }

		public bool HasDPadDownButton { get; internal set; }

		public bool HasDPadLeftButton { get; internal set; }

		public bool HasDPadRightButton { get; internal set; }

		public bool HasDPadUpButton { get; internal set; }

		public bool HasLeftShoulderButton { get; internal set; }

		public bool HasLeftStickButton { get; internal set; }

		public bool HasRightShoulderButton { get; internal set; }

		public bool HasRightStickButton { get; internal set; }

		public bool HasStartButton { get; internal set; }

		public bool HasXButton { get; internal set; }

		public bool HasYButton { get; internal set; }

		public bool HasBigButton { get; internal set; }

		public bool HasLeftXThumbStick { get; internal set; }

		public bool HasLeftYThumbStick { get; internal set; }

		public bool HasRightXThumbStick { get; internal set; }

		public bool HasRightYThumbStick { get; internal set; }

		public bool HasLeftTrigger { get; internal set; }

		public bool HasRightTrigger { get; internal set; }

		public bool HasLeftVibrationMotor { get; internal set; }

		public bool HasRightVibrationMotor { get; internal set; }

		public bool HasVoiceSupport { get; internal set; }

        public GamePadType GamePadType { get; internal set; }

        /// <summary>
        /// Determines whether a specified instance of <see cref="Microsoft.Xna.Framework.Input.GamePadCapabilities"/>
        /// is equal to another specified <see cref="Microsoft.Xna.Framework.Input.GamePadCapabilities"/>.
        /// </summary>
        /// <param name="left">The first <see cref="Microsoft.Xna.Framework.Input.GamePadCapabilities"/> to compare.</param>
        /// <param name="right">The second <see cref="Microsoft.Xna.Framework.Input.GamePadCapabilities"/> to compare.</param>
        /// <returns><c>true</c> if <c>left</c> and <c>right</c> are equal; otherwise, <c>false</c>.</returns>
        public static bool operator ==(GamePadCapabilities left, GamePadCapabilities right)
        {
            return left.DisplayName == right.DisplayName
                && left.Identifier == right.Identifier
                && left.IsConnected == right.IsConnected
                && left.HasAButton == right.HasAButton
                && left.HasBackButton == right.HasBackButton
                && left.HasBButton == right.HasBButton
                && left.HasDPadDownButton == right.HasDPadDownButton
                && left.HasDPadLeftButton == right.HasDPadLeftButton
                && left.HasDPadRightButton == right.HasDPadRightButton
                && left.HasDPadUpButton == right.HasDPadUpButton
                && left.HasLeftShoulderButton == right.HasLeftShoulderButton
                && left.HasLeftStickButton == right.HasLeftStickButton
                && left.HasRightShoulderButton == right.HasRightShoulderButton
                && left.HasRightStickButton == right.HasRightStickButton
                && left.HasStartButton == right.HasStartButton
                && left.HasXButton == right.HasXButton
                && left.HasYButton == right.HasYButton
                && left.HasBigButton == right.HasBigButton
                && left.HasLeftXThumbStick == right.HasLeftXThumbStick
                && left.HasLeftYThumbStick == right.HasLeftYThumbStick
                && left.HasRightXThumbStick == right.HasRightXThumbStick
                && left.HasRightYThumbStick == right.HasRightYThumbStick
                && left.HasLeftTrigger == right.HasLeftTrigger
                && left.HasRightTrigger == right.HasRightTrigger
                && left.HasLeftVibrationMotor == right.HasLeftVibrationMotor
                && left.HasRightVibrationMotor == right.HasRightVibrationMotor
                && left.HasVoiceSupport == right.HasVoiceSupport
                && left.GamePadType == right.GamePadType;
        }

        public static bool operator !=(GamePadCapabilities left, GamePadCapabilities right)
        {
            return !(left == right);
        }

        public override bool Equals(object obj)
        {
            return (obj is GamePadCapabilities) && (this == (GamePadCapabilities)obj);
        }

        /// <summary>
        /// Serves as a hash function for a <see cref="T:Microsoft.Xna.Framework.Input.GamePadCapabilities"/> object.
        /// </summary>
        /// <returns>A hash code for this instance that is suitable for use in hashing algorithms and data structures such as a
        /// hash table.</returns>
        public override int GetHashCode()
        {
            return Identifier.GetHashCode();
        }

        /// <summary>
        /// Returns a <see cref="T:System.String"/> that represents the current <see cref="T:Microsoft.Xna.Framework.Input.GamePadCapabilities"/>.
        /// </summary>
        /// <returns>A <see cref="T:System.String"/> that represents the current <see cref="T:Microsoft.Xna.Framework.Input.GamePadCapabilities"/>.</returns>
        public override string ToString()
        {
            return "[GamePadCapabilities: IsConnected=" + IsConnected +
                ", DisplayName=" + DisplayName +
                ", Identifier=" + Identifier +
                ", HasAButton=" + HasAButton +
                ", HasBackButton=" + HasBackButton +
                ", HasBButton=" + HasBButton +
                ", HasDPadDownButton=" + HasDPadDownButton +
                ", HasDPadLeftButton=" + HasDPadLeftButton +
                ", HasDPadRightButton=" + HasDPadRightButton +
                ", HasDPadUpButton=" + HasDPadUpButton +
                ", HasLeftShoulderButton=" + HasLeftShoulderButton +
                ", HasLeftStickButton=" + HasLeftStickButton +
                ", HasRightShoulderButton=" + HasRightShoulderButton +
                ", HasRightStickButton=" + HasRightStickButton +
                ", HasStartButton=" + HasStartButton +
                ", HasXButton=" + HasXButton +
                ", HasYButton=" + HasYButton +
                ", HasBigButton=" + HasBigButton +
                ", HasLeftXThumbStick=" + HasLeftXThumbStick +
                ", HasLeftYThumbStick=" + HasLeftYThumbStick +
                ", HasRightXThumbStick=" + HasRightXThumbStick +
                ", HasRightYThumbStick=" + HasRightYThumbStick +
                ", HasLeftTrigger=" + HasLeftTrigger +
                ", HasRightTrigger=" + HasRightTrigger +
                ", HasLeftVibrationMotor=" + HasLeftVibrationMotor +
                ", HasRightVibrationMotor=" + HasRightVibrationMotor +
                ", HasVoiceSupport=" + HasVoiceSupport +
                ", GamePadType=" + GamePadType +
                "]";
        }
    }
}

