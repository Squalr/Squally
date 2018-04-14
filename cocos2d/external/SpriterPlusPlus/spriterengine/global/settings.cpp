#include "settings.h"

#include <iostream>

namespace SpriterEngine
{
	// set your program initial settings here:
	
	bool Settings::renderDebugBoxes = false;
	bool Settings::renderDebugPoints = false;
	bool Settings::renderDebugBones = false;

	// enableDebugBones must be true while creating a new instance in order for renderDebugBones to have an effect
	bool Settings::enableDebugBones = false;

	// set to &simpleError to use std::cerr to output errors, or use your own callback function
	// to output to your authoring tool's or custom engine's debug
	ErrorFunctionPointer Settings::errFunction = &nullError; 
	
	// loading options - set these if your engine requires the y, pivotY, or angle to be reversed to display properly
	bool Settings::reverseYOnLoad = true;
	bool Settings::reversePivotYOnLoad = true;
	bool Settings::reverseAngleOnLoad = true;

	// end of program initial settings






	void Settings::simpleError(const std::string &errorMessage)
	{
		std::cerr << "SpriterEngine Error: " << errorMessage.c_str() << std::endl;
	}

	void Settings::nullError(const std::string &errorMessage)
	{
		// do nothing
	}

	void Settings::error(const std::string & errorMessage)
	{
		errFunction(errorMessage);
	}

	void Settings::setErrorFunction(ErrorFunctionPointer errorFunction)
	{
		if (errorFunction)
		{
			errFunction = errorFunction;
		}
		else
		{
			errFunction = &nullError;
		}
		previousErrorFunction = errFunction;
	}

	void Settings::suppressErrorOutput(bool suppress)
	{
		if (suppress)
		{
			errFunction = &nullError;
		}
		else
		{
			errFunction = previousErrorFunction;
		}
	}

	ErrorFunctionPointer Settings::previousErrorFunction = errFunction;

}
