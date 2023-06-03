/**
 * @file windows.hpp
 * @brief Macros specific to windows/linux
 */

#ifndef _WINDOWS_HPP
#define _WINDOWS_HPP

// https://stackoverflow.com/questions/3213037/determine-if-linux-or-windows-in-c
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <unistd.h>

/**
 * @brief Create "out" dir in Windows
 */
inline void create_dir()
{
    mkdir("out");
}

#else
#include <sys/stat.h>

/**
 * @brief Create "out" dir in Linux
 */
inline void create_dir()
{
    mkdir("out", 0777);
}
#endif

#endif // _WINDOWS_HPP