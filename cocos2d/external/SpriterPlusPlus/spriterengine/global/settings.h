#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>

#include <string>

namespace SpriterEngine
{

	typedef void(*ErrorFunctionPointer)(const std::string &errorMessage);

	class Settings
	{
	public:
		static bool renderDebugBoxes;
		static bool renderDebugPoints;
		static bool renderDebugBones;

		static bool enableDebugBones;

		static void simpleError(const std::string &errorMessage);

		static void nullError(const std::string &errorMessage);
		
		static void error(const std::string &errorMessage);

		static void setErrorFunction(ErrorFunctionPointer errorFunction);

		static void suppressErrorOutput(bool suppress = true);

		static bool reverseYOnLoad;
		static bool reversePivotYOnLoad;
		static bool reverseAngleOnLoad;

	private:
		static ErrorFunctionPointer errFunction;
		static ErrorFunctionPointer previousErrorFunction;
	};

}
#endif // SETTINGS_H
