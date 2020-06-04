#include "Objectives.h"

#include "base/CCValue.h"

#include "Engine/Save/SaveManager.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Strings/Strings.h"

using namespace cocos2d;

std::map<std::string, Objectives::Objective> Objectives::ObjectiveMap = std::map<std::string, Objectives::Objective>();

LocalizedString* Objectives::GetObjectiveString()
{
	Objectives::InitMap();

	std::string objectiveKey = Objectives::GetCurrentObjective();

	if (Objectives::ObjectiveMap.find(objectiveKey) != Objectives::ObjectiveMap.end())
	{
		return Objectives::ObjectiveMap[objectiveKey].createFunc();
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
	if (Objectives::ObjectiveMap.find(objectiveKey) == Objectives::ObjectiveMap.end())
	{
		return;
	}

	std::string currentObjectiveKey = Objectives::GetCurrentObjective();

	if (Objectives::ObjectiveMap.find(currentObjectiveKey) != Objectives::ObjectiveMap.end())
	{
		int currentPriority = Objectives::ObjectiveMap[currentObjectiveKey].priority;
		int newPriority = Objectives::ObjectiveMap[objectiveKey].priority;

		// Prevent setting objective if the new objective has a lower prio
		if (newPriority < currentPriority)
		{
			return;
		}
	}

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

	hasInit = true;

	int priority = 0;

	// EF
	Objectives::ObjectiveMap[ObjectiveKeys::EFHeadToTown] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_HeadToTown::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFExploreMagesGuild] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_ExploreMagesGuild::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFTalkToSarude] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_TalkToSarude::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_DataMines_Sarude::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFBeatGauntlet] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_BeatGauntlet::create()->setStringReplacementVariables({ Strings::Platformer_Entities_Names_Npcs_DataMines_Sarude::create(), Strings::Hexus_Hexus::create() }); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFBeatSarude] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_BeatSarude::create()->setStringReplacementVariables({ Strings::Platformer_Entities_Names_Npcs_DataMines_Sarude::create(), Strings::Hexus_Hexus::create() }); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFExplorePrison] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_ExplorePrison::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFRescueGuano] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_RescueGuano::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Helpers_EndianForest_Guano::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFSneakIntoTown] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_SneakIntoTown::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFFindAShip] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_FindAShip::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFVisitQueen] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_VisitQueen::create()->setStringReplacementVariables(Strings::Platformer_MapNames_EndianForest_Elbridge::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFFindElriel] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_FindElriel::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_EndianForest_Elriel::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFSearchTemple] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_SearchTemple::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_EndianForest_Elriel::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFReturnToQueen] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_ReturnToQueen::create()->setStringReplacementVariables(Strings::Platformer_MapNames_EndianForest_Elbridge::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFVisitMarcel] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_VisitMarcel::create()->setStringReplacementVariables({ Strings::Platformer_Entities_Names_Npcs_EndianForest_Marcel::create(), Strings::Platformer_MapNames_EndianForest_Elbridge::create() }); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFHeadNorth] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_HeadNorth::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFAmbush] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_Ambush::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFRepairRam] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_RepairRam::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFConfrontCommander] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_ConfrontCommander::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFReturnToQueenAgain] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_ReturnToQueenAgain::create()->setStringReplacementVariables(Strings::Platformer_MapNames_EndianForest_Elbridge::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFSailForUR] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_SailForUR::create(); }, priority++);

	priority = 100;

	// UR
	Objectives::ObjectiveMap[ObjectiveKeys::URHeadToTown] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_HeadToTown::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URLookForSurvivors] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_LookForSurvivors::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URExploreFountain] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_ExploreFountain::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URExploreCistern] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_ExploreCistern::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URCureTownspeople] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_CureTownspeople::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Hera::create());; }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URReturnToHera] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_ReturnToHera::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Hera::create());; }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URCrossBridge] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_CrossBridge::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URFindMineEntrance] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_FindMineEntrance::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::UREnterTheMines] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_EnterTheMines::create(); }, priority++);

	priority = 200;
}
