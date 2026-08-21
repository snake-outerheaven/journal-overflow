#ifndef UTILS_H
#define UTILS_H

#if defined(UTILS_BUILD_DLL)
#define UTILS_API __declspec (dllexport)
#elif defined(_WIN32)
#define UTILS_API __declspec (dllimport)
#else
#define UTILS_API
#endif

UTILS_API void utils_inicializar_aleatorio (void);

UTILS_API int utils_natural_aleatorio (int limite);

#endif
