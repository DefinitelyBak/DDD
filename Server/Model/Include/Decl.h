/////////////////////////////////////////////////////////////////////////////
// Содержание файла: Декларация импорта/эскпорта классов и функций
/////////////////////////////////////////////////////////////////////////////
#pragma once

//DOM-IGNORE-BEGIN

#ifdef _MSC_VER // Visual Studio specific macro

#ifdef DLL_EXPORTS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif
#ifdef DLL_EXPORTS_INTERNAL
#define DLL_LOCAL DLL_EXPORT
#else
#define DLL_LOCAL
#endif
#elif defined(__GNUC__)
#define DLL_EXPORT __attribute__ ((visibility("default")))
#ifdef DLL_EXPORTS_INTERNAL
#define DLL_LOCAL __attribute__ ((visibility("default")))
#else
#define DLL_LOCAL __attribute__ ((visibility("hidden")))
#endif
#else
#error Unknown platform
#endif

//DOM-IGNORE-END