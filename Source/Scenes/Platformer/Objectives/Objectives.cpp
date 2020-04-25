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

void Objectives::ClearObjective()
{
	Objectives::SetCurrentObjective("");
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

	Objectives::ObjectiveMap[ObjectiveKeys::EFHeadToTown] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_HeadToTown::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFExploreMagesGuild] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_ExploreMagesGuild::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFTalkToSarude] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_TalkToSarude::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFBeatGauntlet] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_BeatGauntlet::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFBeatSarude] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_BeatSarude::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFExplorePrison] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_ExplorePrison::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFRescueGuano] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_RescueGuano::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFSneakIntoTown] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_SneakIntoTown::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFFindAShip] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_FindAShip::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFVisitQueen] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_VisitQueen::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFFindElriel] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_FindElriel::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFSearchTemple] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_SearchTemple::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFReturnToQueen] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_ReturnToQueen::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFVisitMarcel] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_VisitMarcel::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFHeadNorth] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_HeadNorth::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFAmbush] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_Ambush::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFRepairRam] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_RepairRam::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFConfrontCommander] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_ConfrontCommander::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFReturnToQueenAgain] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_ReturnToQueenAgain::create(); };
	Objectives::ObjectiveMap[ObjectiveKeys::EFSailForUR] = [](){ return Strings::Platformer_Objectives_EndianForest_EF_SailForUR::create(); };

	hasInit = true;
}
