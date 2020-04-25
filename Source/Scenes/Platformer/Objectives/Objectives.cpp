#include "Objectives.h"

#include "base/CCValue.h"

#include "Engine/Save/SaveManager.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Strings/Strings.h"

using namespace cocos2d;

std::map<std::string, std::function<LocalizedString*()>> Objectives::ObjectiveMap = std::map<std::string, std::function<LocalizedString*()>>();

LocalizedString* Objectives::GetObjectiveString()
{
	Objectives::InitMap();

	std::string objectiveKey = Objectives::GetCurrentObjective();

	if (Objectives::ObjectiveMap.find(objectiveKey) != Objectives::ObjectiveMap.end())
	{
		return Objectives::ObjectiveMap[objectiveKey]();
	}

	return nullptr;
}

std::string Objectives::GetCurrentObjective()
{
	return SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyCurrentObjective, Value("")).asString();
}

void Objectives::SetCurrentObjective(std::string objectiveKey)
{
	SaveManager::SaveProfileData(SaveKeys::SaveKeyCurrentObjective, Value(objectiveKey));

	PlatformerEvents::TriggerObjectiveChanged();
}

void Objectives::InitMap()
{
	static bool hasInit = false;

	if (hasInit)
	{
		return;
	}

	Objectives::ObjectiveMap[ObjectiveKeys::EFHeadToTown] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFExploreMagesGuild] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFBeatGauntlet] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFBeatSarude] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFExplorePrison] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFRescueGuano] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFSneakIntoTown] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFFindABoat] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFVisitQueen] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFFindElriel] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFReturnToQueen] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFVisitMarcel] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFHeadNorth] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFReturnToQueenAgain] = [](){ return Strings::Common_Triconcat::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFSailForUR] = [](){ return Strings::Common_Triconcat::create(); };

	hasInit = true;
}
