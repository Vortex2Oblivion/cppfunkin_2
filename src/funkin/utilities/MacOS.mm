#include "MacOS.hpp"

#include "raylib.h"
#include <Cocoa/Cocoa.h>


namespace funkin::utilities::MacOS{
    void fixWindowColorSpace() {
       auto nativeWindow = (NSWindow*)GetWindowHandle();

       if (nativeWindow == nullptr) {
           return;
       }

       [nativeWindow setColorSpace: [NSColorSpace sRGBColorSpace]];
    }
}
