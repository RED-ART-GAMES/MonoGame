﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace Sce.PlayStation4
{
    namespace Network
    {
        public unsafe partial class NpScoreRankings : IDisposable
        {
            public void GetGameInfo(byte[] data)
            {
                var temp = BinaryGameInfoIndex;
                for (int i = 0; i < data.Length && i < 189; ++i)
                {
                    data[i] = temp[i];
                }
            }
        }

        public unsafe partial class NpScoreRequest : IDisposable
        {
            public NpCommunityError RecordScore(uint boardId, long score, string scoreComment, byte[] gameInfo, ulong compareDate, out uint tmpRank)
            {
                fixed (byte* pGameInfo = gameInfo)
                    return RecordScore(boardId, score, scoreComment, pGameInfo, gameInfo == null ? 0 : gameInfo.Length, compareDate, out tmpRank);
            }

            public NpCommunityError RecordScore(uint boardId, long score, string scoreComment, byte[] gameInfo)
            {
                fixed (byte* pGameInfo = gameInfo)
                    return RecordScore(boardId, score, scoreComment, pGameInfo, gameInfo == null ? 0 : gameInfo.Length);
            }

            public byte[] GetGameData(uint boardId, ulong accountId, out NpCommunityError error)
            {
                ulong totalSize;
                void* pointer = GetGameData(boardId, accountId, out totalSize, out error);
                int length = (int)totalSize;

                byte[] data = new byte[length];
                try
                {
                    Marshal.Copy((IntPtr)pointer, data, 0, length);
                }
                catch
                {
                    return new byte[0];
                }

                return data;
            }
        }
    }
}