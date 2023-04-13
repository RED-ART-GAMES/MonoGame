using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Sce.PlayStation4.Audio
{
    public partial class SoundSystem
    {
        static private readonly SoundSystem _instance = new SoundSystem();

        static public SoundSystem Instance
        {
            get { return _instance; }
        }
    }

}
