#pragma once

#if defined(WIN32)
#ifdef LIB_EXPORTS
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif
#else
#ifdef LIB_EXPORTS
#define DLLAPI __attribute__((visibility("default")))
#else
#define DLLAPI
#endif
#endif
