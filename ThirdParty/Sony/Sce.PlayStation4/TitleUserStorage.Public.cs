using System;
using System.Runtime.InteropServices;


namespace Sce.PlayStation4.Network
{
    public partial class TitleUserStorage
    {
        public TitleUserStorage(int userId, uint serviceLabel = 0)
            : this()
        {
            var result = this.CreateContext(userId, serviceLabel);
            if (result != TitleUserStorageResult.Ok)
                throw new Exception(result.ToString());
        }

        public unsafe TitleUserStorageResult GetData(ulong targetAccountId, int slotId, byte[] buffer, out ulong recvdSize)
        {
            var bufferHandle = GCHandle.Alloc(buffer, GCHandleType.Pinned);
            var bufferPtr = (IntPtr)(bufferHandle.AddrOfPinnedObject().ToInt64());

            TitleUserStorageResult result;
            try
            {
                result = GetData(targetAccountId, slotId, (void*) bufferPtr, (ulong) buffer.Length, out recvdSize);
            }
            finally
            {
                bufferHandle.Free();
            }

            return result;
        }

        public TitleUserStorageResult SetData(ulong targetAccountId, int slotId, byte[] buffer)
        {
            return SetData(targetAccountId, slotId, buffer, buffer.Length);
        }

        public unsafe TitleUserStorageResult SetData(ulong targetAccountId, int slotId, byte[] buffer, int bufferSize)
        {
            var bufferHandle = GCHandle.Alloc(buffer, GCHandleType.Pinned);
            var bufferPtr = (IntPtr)(bufferHandle.AddrOfPinnedObject().ToInt64());

            TitleUserStorageResult result;
            try
            {
                result = SetData(targetAccountId, slotId, (void*) bufferPtr, (ulong) bufferSize);
            }
            finally
            {
                bufferHandle.Free();                
            }

            return result;
        }
    }
}
