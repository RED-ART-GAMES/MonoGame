using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace Sce.PlayStation4.Network
{
    public partial class TitleSmallStorage
    {
        public TitleSmallStorage(int userId, uint serviceLabel = 0)
            : this()
        {
            var result = this.CreateContext(userId, serviceLabel);
            if (result != TitleSmallStorageResult.Ok)
                throw new Exception(result.ToString());
        }

        public ulong GetData(int slotId, byte[] buffer)
        {
            var bufferHandle = GCHandle.Alloc(buffer, GCHandleType.Pinned);
            var bufferPtr = (IntPtr)(bufferHandle.AddrOfPinnedObject().ToInt64());
            TitleSmallStorageResult result;
            ulong recvdSize = 0;
            unsafe
            {
                result = GetData(slotId, (void*)bufferPtr, (uint)buffer.Length, out recvdSize);
            }
            bufferHandle.Free();

            if (result != TitleSmallStorageResult.Ok)
                throw new Exception(result.ToString());

            return recvdSize;
        }
    }
}
