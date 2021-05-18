#pragma once

#ifdef SFTPLIBSSHADAPTER_API_DEFINE
#define SFTPLIBSSHADAPTER_API __declspec(dllexport)
#else
#define SFTPLIBSSHADAPTER_API __declspec(dllimport)
#endif
