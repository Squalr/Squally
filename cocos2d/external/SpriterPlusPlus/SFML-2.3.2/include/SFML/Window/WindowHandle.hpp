////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2015 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_WINDOWHANDLE_HPP
#define SFML_WINDOWHANDLE_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML-2.3.2/include/SFML/Config.hpp>

// Windows' HWND is a typedef on struct HWND__*
#if defined(SFML_SYSTEM_WINDOWS)
    struct HWND__;
#endif

namespace sf
{
////////////////////////////////////////////////////////////
/// Define a low-level window handle type, specific to
/// each platform
////////////////////////////////////////////////////////////
#if defined(SFML_SYSTEM_WINDOWS)

    // Window handle is HWND (HWND__*) on Windows
    typedef HWND__* WindowHandle;

#elif defined(SFML_SYSTEM_LINUX) || defined(SFML_SYSTEM_FREEBSD)

    // Window handle is Window (unsigned long) on Unix - X11
    typedef unsigned long WindowHandle;

#elif defined(SFML_SYSTEM_MACOS)

    // Window handle is NSWindow (void*) on Mac OS X - Cocoa
    typedef void* WindowHandle;

#elif defined(SFML_SYSTEM_IOS)

    // Window handle is UIWindow (void*) on iOS - UIKit
    typedef void* WindowHandle;

#elif defined(SFML_SYSTEM_ANDROID)

    // Window handle is ANativeWindow (void*) on Android
    typedef void* WindowHandle;

#endif

} // namespace sf


#endif // SFML_WINDOWHANDLE_HPP
