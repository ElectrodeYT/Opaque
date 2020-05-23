#pragma once

/// Opaque Engine
// log.h
// Contains Logging macros

#include <iostream>


#define LOG_MSG(a) std::cout << "[" << __FUNCTION__  << "] [MSG] " << a << "\n"
#ifdef _DEBUG
#define LOG_DBG(a) std::cout << "[" << __FUNCTION__  << "] [DBG] " << a << "\n"
#else
// Do fuckall
#define LOG_DBG(a)
#endif
#define LOG_WRN(a) std::cout << "[" << __FUNCTION__  << "] [WRN] " << a << "\n"
#define LOG_ERR(a) std::cout << "[" << __FUNCTION__  << "] [ERR] " << a << "\n"