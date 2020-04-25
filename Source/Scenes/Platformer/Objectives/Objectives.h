#pragma once

#include <functional>
#include <map>
#include <string>

#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"

class LocalizedString;

class Objectives
{
public:
	static LocalizedString* GetObjectiveString();
	static std::string GetCurrentObjective();
	static void ClearObjective();
	static void SetCurrentObjective(std::string objectiveKey);

private:
	static void InitMap();

	struct Objective
	{
		std::function<LocalizedString*()> createFunc;
		int priority;

		Objective() : createFunc(nullptr), priority(-1) { }
		Objective(std::function<LocalizedString*()> createFunc, int priority) : createFunc(createFunc), priority(priority) { }
	};

	static std::map<std::string, Objective> ObjectiveMap;
};
