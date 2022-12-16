﻿// MonoGame - Copyright (C) The MonoGame Team
// This file is subject to the terms and conditions defined in
// file 'LICENSE.txt', which is part of this source code package.

using System;
using MonoGame.Framework.Content.Pipeline.Builder;
using System.IO;

namespace Microsoft.Xna.Framework.Content.Pipeline.Processors
{
    [ContentProcessor(DisplayName = "Video - MonoGame")]
    public class VideoProcessor : ContentProcessor<VideoContent, VideoContent>
    {
        public override VideoContent Process(VideoContent input, ContentProcessorContext context)
        {
            var relative = Path.GetDirectoryName(PathHelper.GetRelativePath(context.OutputDirectory, context.OutputFilename));
            var relVideoPath = PathHelper.Normalize(Path.Combine(relative, Path.GetFileName(input.Filename)));
            var absVideoPath = PathHelper.Normalize(Path.Combine(context.OutputDirectory, relVideoPath));

            if (context.TargetPlatform == TargetPlatform.PlayStation4)
            {
                var ext = Path.GetExtension(relVideoPath);
                if (!ext.Equals(".mp4", StringComparison.InvariantCultureIgnoreCase))
                    throw new InvalidContentException("We only support H.264 MP4 videos on PS4.");
            }

            // Make sure the output folder for the video exists.
            Directory.CreateDirectory(Path.GetDirectoryName(absVideoPath));

            // Copy the already encoded video file over
            File.Copy(input.Filename, absVideoPath, true);
            context.AddOutputFile(absVideoPath);

            // Fixup relative path
            input.Filename = PathHelper.GetRelativePath(context.OutputFilename, absVideoPath);

            return input;
        }
    }
}
