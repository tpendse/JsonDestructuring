#pragma once

#ifdef BUILDBACKEND
	#define DLL __declspec(dllexport)
#else
	#define DLL __declspec(dllimport)
#endif