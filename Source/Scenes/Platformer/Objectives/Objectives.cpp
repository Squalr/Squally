#include "Objectives.h"

#include "base/CCValue.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Save/SaveManager.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
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

	// Absense of a key should return nullptr so the caller knows not to create a UI element
	if (objectiveKey == "")
	{
		return nullptr;
	}

	// Default to the missing key so that we know to add it
	return ConstantString::create(objectiveKey);
}

std::string Objectives::GetCurrentObjective()
{
	return SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyCurrentObjective, Value("")).asString();
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

	const std::string& currentObjectiveKey = Objectives::GetCurrentObjective();

	if (Objectives::ObjectiveMap.find(currentObjectiveKey) != Objectives::ObjectiveMap.end())
	{
		int currentPriority = Objectives::ObjectiveMap[currentObjectiveKey].priority;
		int newPriority = Objectives::ObjectiveMap[objectiveKey].priority;

		// Fail safe unlocks for testing / backwards compatibility
		if (newPriority >= 100)
		{
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyQuickPotionUnlocked, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGuanoFound, Value(true));
		}
		if (newPriority >= 300)
		{
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGeckyFound, Value(true));
		}
		if (newPriority >= 400)
		{
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGrimFound, Value(true));
		}

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
	Objectives::ObjectiveMap[ObjectiveKeys::EFHeadNorth] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_HeadNorth::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFAmbush] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_Ambush::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFRepairRam] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_RepairRam::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFConfrontCommander] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_ConfrontCommander::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFReturnToQueenAgain] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_ReturnToQueenAgain::create()->setStringReplacementVariables(Strings::Platformer_MapNames_EndianForest_Elbridge::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::EFSailForUR] = Objective([](){ return Strings::Platformer_Objectives_EndianForest_EF_SailForUR::create()->setStringReplacementVariables(Strings::Platformer_MapNames_EndianForest_Elbridge::create()); }, priority++);

	priority = 100;

	// UR
	Objectives::ObjectiveMap[ObjectiveKeys::URHeadToTown] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_HeadToTown::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URLookForSurvivors] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_LookForSurvivors::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URExploreFountain] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_ExploreFountain::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URSearchCistern] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_SearchCistern::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URSolvePuzzle] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_SolvePuzzle::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URSlayMedusa] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_SlayMedusa::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URCureTownspeople] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_CureTownspeople::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Hera::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URReturnToHera] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_ReturnToHera::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Hera::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URCrossBridge] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_CrossBridge::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URFindMineEntrance] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_FindMineEntrance::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::URLightTorches] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_LightTorches::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::UREnterTheMines] = Objective([](){ return Strings::Platformer_Objectives_UnderflowRuins_UR_EnterTheMines::create(); }, priority++);

	priority = 200;

	// DM
	Objectives::ObjectiveMap[ObjectiveKeys::DMDeliverLetter] = Objective([](){ return Strings::Platformer_Objectives_DataMines_DM_DeliverLetter::create()->setStringReplacementVariables({ Strings::Platformer_Entities_Names_Npcs_DataMines_PrincessDawn::create(), Strings::Platformer_MapNames_DataMines_Drammol::create() }); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::DMInvestigatePowerOutage] = Objective([](){ return Strings::Platformer_Objectives_DataMines_DM_InvestigatePowerOutage::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::DMSailToDrammol] = Objective([](){ return Strings::Platformer_Objectives_DataMines_DM_SailToDrammol::create()->setStringReplacementVariables(Strings::Platformer_MapNames_DataMines_Drammol::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::DMRestorePower] = Objective([](){ return Strings::Platformer_Objectives_DataMines_DM_RestorePower::create()->setStringReplacementVariables(Strings::Platformer_MapNames_DataMines_Drammol::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::DMReturnToPrincessDawn] = Objective([](){ return Strings::Platformer_Objectives_DataMines_DM_ReturnToPrincessDawn::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_DataMines_PrincessDawn::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::DMObtainTrainTicket] = Objective([](){ return Strings::Platformer_Objectives_DataMines_DM_ObtainTrainTicket::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_DataMines_PrincessDawn::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::DMRideTrainToCastleValgrind] = Objective([](){ return Strings::Platformer_Objectives_DataMines_DM_RideTrainToCastleValgrind::create()->setStringReplacementVariables(Strings::Platformer_MapNames_CastleValgrind_CastleValgrind::create()); }, priority++);

	priority = 300;

	// CV
	Objectives::ObjectiveMap[ObjectiveKeys::CVEnterCastle] = Objective([](){ return Strings::Platformer_Objectives_CastleValgrind_CV_EnterCastle::create()->setStringReplacementVariables(Strings::Platformer_MapNames_CastleValgrind_CastleValgrind::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::CVInvestigateCastle] = Objective([](){ return Strings::Platformer_Objectives_CastleValgrind_CV_InvestigateCastle::create()->setStringReplacementVariables(Strings::Platformer_MapNames_CastleValgrind_CastleValgrind::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::CVExamineArcaneEnergy] = Objective([](){ return Strings::Platformer_Objectives_CastleValgrind_CV_ExamineArcaneEnergy::create()->setStringReplacementVariables(Strings::Platformer_MapNames_CastleValgrind_CastleValgrind::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::CVRepairClock] = Objective([](){ return Strings::Platformer_Objectives_CastleValgrind_CV_RepairClock::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::CVEnterClock] =  Objective([](){ return Strings::Platformer_Objectives_CastleValgrind_CV_EnterClock::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::CVExploreDarkSide] =  Objective([](){ return Strings::Platformer_Objectives_CastleValgrind_CV_ExploreDarkSide::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::CVDefeatSpirits] =  Objective([](){ return Strings::Platformer_Objectives_CastleValgrind_CV_DefeatSpirits::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Helpers_CastleValgrind_Grim::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::CVReturnToMabel] =  Objective([](){ return Strings::Platformer_Objectives_CastleValgrind_CV_ReturnToMabel::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Mabel::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::CVTakeArcaneBook] =  Objective([](){ return Strings::Platformer_Objectives_CastleValgrind_CV_TakeArcaneBook::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::CVExploreSecretTunnel] =  Objective([](){ return Strings::Platformer_Objectives_CastleValgrind_CV_ExploreSecretTunnel::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::CVDefeatAgnes] =  Objective([](){ return Strings::Platformer_Objectives_CastleValgrind_CV_DefeatAgnes::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Agnes::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::CVEnterLambdaCrypts] =  Objective([](){ return Strings::Platformer_Objectives_CastleValgrind_CV_EnterLambdaCrypts::create()->setStringReplacementVariables(Strings::Platformer_MapNames_LambdaCrypts_LambdaCrypts::create()); }, priority++);

	priority = 400;

	// LC
	Objectives::ObjectiveMap[ObjectiveKeys::LCSeekAmelia] =  Objective([](){ return Strings::Platformer_Objectives_LambdaCrypts_LC_SeekAmelia::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Amelia::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::LCTalkToNebea] =  Objective([](){ return Strings::Platformer_Objectives_LambdaCrypts_LC_TalkToNebea::create()->setStringReplacementVariables({ Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_PrincessNebea::create(), Strings::Platformer_MapNames_LambdaCrypts_GraveFlower::create(), Strings::Platformer_MapNames_LambdaCrypts_LambdaCrypts::create() }); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::LCReturnToElric] =  Objective([](){ return Strings::Platformer_Objectives_LambdaCrypts_LC_ReturnToElric::create()->setStringReplacementVariables(Strings::Platformer_Entities_Names_Npcs_LambdaCrypts_Elric::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::LCEnterLesserCrypt] =  Objective([](){ return Strings::Platformer_Objectives_LambdaCrypts_LC_EnterLesserCrypt::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::LCExploreLesserCrypt] =  Objective([](){ return Strings::Platformer_Objectives_LambdaCrypts_LC_ExploreLesserCrypt::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::LCFindGems] =  Objective([](){ return Strings::Platformer_Objectives_LambdaCrypts_LC_FindGems::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::LCEnterGreaterCrypt] =  Objective([](){ return Strings::Platformer_Objectives_LambdaCrypts_LC_EnterGreaterCrypt::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::LCExploreGreaterCrypt] =  Objective([](){ return Strings::Platformer_Objectives_LambdaCrypts_LC_ExploreGreaterCrypt::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::LCCraftDemonHeart] =  Objective([](){ return Strings::Platformer_Objectives_LambdaCrypts_LC_CraftDemonHeart::create()->setStringReplacementVariables({ Strings::Platformer_MapNames_DataMines_Drammol::create(), Strings::Platformer_MapNames_DataMines_DataMines::create(), Strings::Items_Misc_Keys_DemonHeart::create() }); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::LCOpenDemonPortal] =  Objective([](){ return Strings::Platformer_Objectives_LambdaCrypts_LC_OpenDemonPortal::create()->setStringReplacementVariables(Strings::Platformer_MapNames_DataMines_DataMines::create()); }, priority++);

	priority = 500;

	// FF
	Objectives::ObjectiveMap[ObjectiveKeys::FFExploreFirewallFissure] =  Objective([](){ return Strings::Platformer_Objectives_FirewallFissure_FF_Explore::create()->setStringReplacementVariables(Strings::Platformer_MapNames_FirewallFissure_FirewallFissure::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::FFEnterTown] =  Objective([](){ return Strings::Platformer_Objectives_FirewallFissure_FF_EnterTown::create()->setStringReplacementVariables({ Strings::Platformer_MapNames_FirewallFissure_Brimstone::create(), Strings::Platformer_MapNames_FirewallFissure_FirewallFissure::create()}); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::FFCraftBomb] =  Objective([](){ return Strings::Platformer_Objectives_FirewallFissure_FF_CraftBomb::create()->setStringReplacementVariables({ Strings::Items_Misc_Keys_HeliumBomb::create(), Strings::Platformer_MapNames_FirewallFissure_Brimstone::create() }); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::FFDeliverBomb] =  Objective([](){ return Strings::Platformer_Objectives_FirewallFissure_FF_DeliverBomb::create()->setStringReplacementVariables(Strings::Platformer_MapNames_FirewallFissure_Brimstone::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::FFLaunchBomb] =  Objective([](){ return Strings::Platformer_Objectives_FirewallFissure_FF_LaunchBomb::create()->setStringReplacementVariables(Strings::Platformer_MapNames_FirewallFissure_FirewallFissure::create()); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::FFFindAsmodeus] =  Objective([](){ return Strings::Platformer_Objectives_FirewallFissure_FF_FindAsmodeus::create()->setStringReplacementVariables({ Strings::Platformer_Entities_Names_Enemies_FirewallFissure_Asmodeus::create(), Strings::Platformer_MapNames_FirewallFissure_FirewallFissure::create()}); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::FFAscendVolcano] =  Objective([](){ return Strings::Platformer_Objectives_FirewallFissure_FF_AscendVolcano::create(); }, priority++);
	
	priority = 600;

	// BP
	// Objectives::ObjectiveMap[ObjectiveKeys::TODO] =  Objective([](){ return Strings::TODO::create(); }, priority++);
	
	priority = 700;

	// VS
	Objectives::ObjectiveMap[ObjectiveKeys::VSExplore] =  Objective([](){ return Strings::Platformer_Objectives_VoidStar_VS_Explore::create()->setStringReplacementVariables({ Strings::Platformer_MapNames_VoidStar_VoidStar::create() }); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::VSExploreLab] =  Objective([](){ return Strings::Platformer_Objectives_VoidStar_VS_ExploreTheLab::create(); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::VSDestroyPerceptron] =  Objective([](){ return Strings::Platformer_Objectives_VoidStar_VS_DestroyPerceptron::create()->setStringReplacementVariables({ Strings::Platformer_Entities_Names_Enemies_VoidStar_Perceptron::create() }); }, priority++);
	Objectives::ObjectiveMap[ObjectiveKeys::VSDestroyReactorCore] =  Objective([](){ return Strings::Platformer_Objectives_VoidStar_VS_DestroyReactor::create(); }, priority++);
	
}
