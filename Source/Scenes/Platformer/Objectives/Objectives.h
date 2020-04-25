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
	static void SetCurrentObjective(std::string objectiveKey);

private:
	static void InitMap();

	static std::map<std::string, std::function<LocalizedString*()>> ObjectiveMap;
};
