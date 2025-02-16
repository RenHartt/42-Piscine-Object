#pragma once
#include <iostream>

#ifdef DEBUG
    #define LOG_DEBUG(msg) std::cout << "[DEBUG] " << msg << std::endl
#else
    #define LOG_DEBUG(msg)
#endif

#ifdef VERBOSE
    #define LOG_VERBOSE(msg) std::cout << "[VERBOSE] " << msg << std::endl
#else
    #define LOG_VERBOSE(msg)
#endif
