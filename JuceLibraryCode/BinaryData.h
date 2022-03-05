/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   pause_png;
    const int            pause_pngSize = 4248;

    extern const char*   fx4_wav;
    const int            fx4_wavSize = 638998;

    extern const char*   fx3_wav;
    const int            fx3_wavSize = 1060132;

    extern const char*   fx5_wav;
    const int            fx5_wavSize = 226396;

    extern const char*   fx6_wav;
    const int            fx6_wavSize = 257030;

    extern const char*   fx1_wav;
    const int            fx1_wavSize = 813028;

    extern const char*   fx_png;
    const int            fx_pngSize = 20257;

    extern const char*   upload_png;
    const int            upload_pngSize = 6074;

    extern const char*   fx2_wav;
    const int            fx2_wavSize = 294730;

    extern const char*   play_png;
    const int            play_pngSize = 4747;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 10;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
