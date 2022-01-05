# ifndef PAL_UNIFIED_SDK_HIJACK_H
# define PAL_UNIFIED_SDK_HIJACK_H

# include <string>

namespace PAL
{
    namespace Internal
    {

        void SetCurrentUnitPath(std::string path);

        std::string GetCurrentUnitPath();
    }


    namespace Hijack
    {

        void SetHijackUnitPath(std::string path);

        std::string GetHijackUnitPath();

    }
}

# endif //PAL_UNIFIED_SDK_HIJACK_H
