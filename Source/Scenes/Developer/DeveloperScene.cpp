#include "DeveloperScene.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Helpers/BallmerPeaks/Snowman.h"
#include "Entities/Platformer/Helpers/CastleValgrind/Grim.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Helpers/UnderflowRuins/GuanoPetrified.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/MapResources.h"
#include "Resources/MusicResources.h"
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

DeveloperScene* DeveloperScene::Instance = nullptr;

DeveloperScene* DeveloperScene::getInstance()
{
	if (DeveloperScene::Instance == nullptr)
	{
		DeveloperScene::Instance = new DeveloperScene();

		DeveloperScene::Instance->autorelease();
		DeveloperScene::Instance->initializeListeners();

		GlobalDirector::RegisterGlobalScene(DeveloperScene::getInstance());
	}

	return DeveloperScene::Instance;
}

DeveloperScene::DeveloperScene()
{
	// DEBUG MAPS
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Debug");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room", MapResources::MagesGuild_Mages_Warp));
		mapList.push_back(this->buildDebugButton("Museum", MapResources::MagesGuild_Museum));
		mapList.push_back(this->buildDebugButton("DBG Cages", MapResources::Dev_Cages));
		mapList.push_back(this->buildDebugButton("DBG Cutscenes", MapResources::Dev_Cracks));
		mapList.push_back(this->buildDebugButton("DBG Cipher", MapResources::Dev_Cipher));
		mapList.push_back(this->buildDebugButton("DBG Quests", MapResources::Dev_Quests));
		mapList.push_back(this->buildDebugButton("DBG Warp Depth", MapResources::Dev_WarpDepth));
		mapList.push_back(this->buildDebugButton("DBG Notifications", MapResources::Dev_Items));
		mapList.push_back(this->buildDebugButton("DBG Collision", MapResources::Dev_Collision));
		mapList.push_back(this->buildDebugButton("DBG Pickpocket", MapResources::Dev_Pickpocket));
		mapList.push_back(this->buildDebugButton("DBG Positions", MapResources::Dev_PositionBug));
		mapList.push_back(this->buildDebugButton("DBG Bounds", MapResources::Dev_Bounds));
		mapList.push_back(this->buildDebugButton("DBG Animation Sequences", MapResources::Dev_AnimSeq));
		mapList.push_back(this->buildDebugButton("DBG Combat", MapResources::Dev_Combat));
		mapList.push_back(this->buildDebugButton("DBG Terrain", MapResources::Dev_Terrain));

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	/*
	- 5x EE:
		- * Mayan Door (000/666)		=> Pirate Hat (Special: Bonus Drop Rates)
		- * Clock 069/420		 		=> Warlock's Headdress (Special: Longer Hack Durations -- ie swim)
		- * Perilous Sea (tri m/l/r)	=> The Golden Eagle (Special: Higher Jump)
		- * Sky Tower (tri l/r/m)		=> Tiger's Bane (Special: Faster Movement)
		- ** CV, throne room? or wat	=> Royal Crown (Special: Shop Discounts)

	- Easy wins:
		- v LC change dialogue for npc outside of crypts if has key
		- v FF enemy shadows wrong in 1st combat map

	- Medium wins:
		- v scrolling down passed end in script editor cycles back to top
		- v CV some indicator of remaining souls
		- v FF Asmodeus crowd should animate
		- v FF give demon grunt (scalding blade user) an add potion?
		- v FF/DM(?) overworld archer attack SetPosition doesn't actually do anything as far as I can tell (see Demon Archer)
		- v CV Mabel should look at Perceptron the entire patrol, or cower until he is gone
		- v CV smelting pot broken in haunted map? seems weird. Actually I think a bug on deactivated behavior.
		- v quick swap FX
		- v quick warp FX
		- v Pressing left on "select target" in combat should go back to prior menu, not base menu (inconsistent?)
		- v Auto leave potion menu if everyone is maxed (but only if maxed from healing, not initially maxed)
		- v LC terrain connectors in 3_x maps are offset baddly (which map?)
		- v Maybe HP pots in combat should self-target initally?
		- v Can probably use Silver for more craft recipes
		- v Wand energy bolt literally does an attack anim and nothing
		- v EF Quest to temporarily grant before EF boss? never made sense that we could refelct that fire-ball...

	- Hard wins:
		- v maybe stat deltas on equipment in craft menu
		- v Maybe interact with helper to revive after holy spellbook?
		- v Should add some sort of archery mini-game with jump shots or something in some town. Maybe FF.
			- v Ruby necklace as a reward
			- v Maybe horde against 3Q perspective:
				- v Skeletal Warrior / Archer / Necromancer
				- v Orc Grunt / Warrior / Swordsman 
				- v Earth Golem
		- v FF maybe move mage tower to 1_x area eh?
		- v LC blue gem map feels empty. Traps?
		- v LC Daze script too long / needs hint
		- v Make LC final 4_x maps less bad.
		- v CV 2_x maps feels unfinished
		- v DM show collision on ship map mini-map
		- v DM binary puzzle area is shitty imo
		- v UR Pyramid [still] fucking sucks. Circuit puzzle? Wind puzzles? Anything, please. Lightning?
		- v Could scrap hack button, and instead show [1] button keys (ideally with art), and sort them by distance to squally
			- v could click OR press the button to activate
		- v Something feels off about torch puzzles. Colors? Give control over top and bottom? Hard to say, but rework it.
			- v If we keep them -- EF no offscreen lantern for binary puzzle. Maybe put some lanterns in the BG across a bridge
		- v More transmutes (perhaps custom UI to show a transmute wheel)
			- v or just scrap transmutes, and add the ability to sell shit
		- * Lexicon is largely incomplete
			- * Fill out descriptions without samples first
		- v Lexicon add examples are half broken (highlighting)
		- v Lexicon push example doesn't refresh highlighting on click
		- * Arrow keys in large scripts should auto-scroll if cursor goes out of visible text range
		- * Multi-line comments in scripts can cause line counter to become disrupted
		- * Should really expand scripting text editor
			- * Support click-to-place cursor
		- v CodeWindow::NumberColor not applied to negatives (bad token splitting)
		
	- Asset updates:
		- v Enemy anims for getting hit
		- v Enemy death sounds
		- v Enemy anims for combat begin (temporarily pausing timeline)
		- v Enemy combat begin sounds
		- v SFX pass
			- v All defend variants
		- v Unique icons for all spells
		- v More passes on music. Probably need more overworld. Far and Away / Sunset once I get access.
	
	- Mini-games:
		- v Cipher:
			* Reinstate? What's the new play? Asm? Macro magic to avoid emulation (store state to a struct after each instruction).
				- Probably like Hexus puzzles, with preset C++ classes rather than map-property defined.
		- v P-Trace:
			- Reinstate? What's the new play? Can this be that circuit game I was thinking? Maybe can flip circuit switches to incentivize using brain
			- isometric squally, and some form of strategy element that isn't prone to trial-and-error.
				- Another play is to make these actual "maps" that you can pass through.
			- Could make a mini-game in towns? Inns? Where? Maybe just one machine in a zone of my choosing? (I kinda prefer DM or CV)
	
	- * BP Zone
		- * Vertical town (maybe two sections, one inaccessible at first to spread out NPCs)
		- * 1_x typical EF style outdoors leading to town (viking, penguin grunt, penguin warrior, frost fiend (technically in 3_x))
		- * 2_x for some frost caverns (ice golem, water elemental, yeti) => cryogen
		- * 3_x for blizzard environment? (goblin elf, toy soldier goblin, snow fiend) => santa => sky cannon
		- * Needs hexus battles
		- * Tune hexus battle special cards
		- * Needs animals
		- * Needs enemy scripting according to notes on which instructions this zone covers
		- * Frost SpellBook (?? / ??)
		- * BP, somewhere				=> Frost Axe unused item

	- Low prio:
		- v Fix terrain connectors
			- v Frost
			- v Marble [Dark too]
			- v Jungle [Dark too]
		- v Camera harsh leaving camera targets (see FF cinematic)
		- v (Maybe) Chapter transitions can be more special 
		- v Please god new anim system would be soo cool perf wise (especially on maps with a large number of entities, ie FF)
			- v Tiki anims still broken (bad Spriter implementation strikes again)
			- v Train anims broken (for same reason)
		- v Missing squally breath bubbles
		- v User-made script titles can go TOFU upon language change. Wontfix? Save original language, and reset to current if the user clears the title?
		- v If ever re-instating Arabic, Ctrl+F all "ar": "! and "ar": ". strings to find places where punctuation was messed up and fix them
		- v If ever re-instating Arabic, probably force English for scripting. Mixing RTL and LTR language is awful. Or use Arabic romanization.
	*/

	// CHAPTER 1 - Mov/add/sub/inc/dec/div/mul + AND Puzzle
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Endian Forest");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Boat EF => UR", MapResources::EndianForest_Ship_Main));
		mapList.push_back(this->buildDebugButton("Docks (EF)", MapResources::EndianForest_Town_Docks));
		mapList.push_back(this->buildDebugButton("Elbridge", MapResources::EndianForest_Town_Main));
		mapList.push_back(this->buildDebugButton("Inn (EF)", MapResources::EndianForest_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (EF)", MapResources::EndianForest_Town_Smith));
		mapList.push_back(this->buildDebugButton("Alch (EF)", MapResources::EndianForest_Town_Alch));
		mapList.push_back(this->buildDebugButton("Gramps (EF)", MapResources::EndianForest_Home_Gramps));
		mapList.push_back(this->buildDebugButton("Liana Back (EF)", MapResources::EndianForest_Town_Liana_Back));
		mapList.push_back(this->buildDebugButton("Liana (EF)", MapResources::EndianForest_Town_Liana));
		mapList.push_back(this->buildDebugButton("Ara (EF)", MapResources::EndianForest_Home_Ara));
		mapList.push_back(this->buildDebugButton("Zone 3_7 (EF)", MapResources::EndianForest_Zone_3_7));
		mapList.push_back(this->buildDebugButton("Zone 3_6 (EF)", MapResources::EndianForest_Zone_3_6));
		mapList.push_back(this->buildDebugButton("Zone 3_5 (EF)", MapResources::EndianForest_Zone_3_5));
		mapList.push_back(this->buildDebugButton("Zone 3_4 (EF)", MapResources::EndianForest_Zone_3_4));
		mapList.push_back(this->buildDebugButton("Zone 3_Dev (EF)", MapResources::EndianForest_Zone_3_Dev));
		mapList.push_back(this->buildDebugButton("Zone 3_3 (EF)", MapResources::EndianForest_Zone_3_3));
		mapList.push_back(this->buildDebugButton("Zone 3_2 (EF)", MapResources::EndianForest_Zone_3_2));
		mapList.push_back(this->buildDebugButton("Zone 3_1 (EF)", MapResources::EndianForest_Zone_3_1));
		mapList.push_back(this->buildDebugButton("Zone 3_0 experimental (EF)", MapResources::EndianForest_Zone_3_0_experimental));
		mapList.push_back(this->buildDebugButton("Zone 3_0 (EF)", MapResources::EndianForest_Zone_3_0));
		mapList.push_back(this->buildDebugButton("Zone 2_8 Temple (EF)", MapResources::EndianForest_Zone_2_8));
		mapList.push_back(this->buildDebugButton("Zone 2_7 Inner Sanctum Temple (EF)", MapResources::EndianForest_Zone_2_7));
		mapList.push_back(this->buildDebugButton("Zone 2_6 Temple (EF)", MapResources::EndianForest_Zone_2_6));
		mapList.push_back(this->buildDebugButton("Zone 2_5 Temple (EF)", MapResources::EndianForest_Zone_2_5));
		mapList.push_back(this->buildDebugButton("Zone 2_4_a Temple (EF)", MapResources::EndianForest_Zone_2_4_a));
		mapList.push_back(this->buildDebugButton("Zone 2_4 Temple (EF)", MapResources::EndianForest_Zone_2_4));
		mapList.push_back(this->buildDebugButton("Zone 2_3 (EF)", MapResources::EndianForest_Zone_2_3));
		mapList.push_back(this->buildDebugButton("Zone 2_2 (EF)", MapResources::EndianForest_Zone_2_2));
		mapList.push_back(this->buildDebugButton("Zone 2_1 (EF)", MapResources::EndianForest_Zone_2_1));
		mapList.push_back(this->buildDebugButton("Zone 2_0 (EF)", MapResources::EndianForest_Zone_2_0));
		mapList.push_back(this->buildDebugButton("Zone 1_3 (EF)", MapResources::EndianForest_Zone_1_3));
		mapList.push_back(this->buildDebugButton("Zone 1_2 (EF)", MapResources::EndianForest_Zone_1_2));
		mapList.push_back(this->buildDebugButton("Zone 1_1 (EF)", MapResources::EndianForest_Zone_1_1));
		mapList.push_back(this->buildDebugButton("Zone 1_0 (EF)", MapResources::EndianForest_Zone_1_0));
		mapList.push_back(this->buildDebugButton("Guano's Cell", MapResources::MagesGuild_Home_Guano));
		mapList.push_back(this->buildDebugButton("Mage's Prison", MapResources::MagesGuild_Mages_Prison));
		mapList.push_back(this->buildDebugButton("Mage's Guild",MapResources::MagesGuild_Mages_Guild));
		mapList.push_back(this->buildDebugButton("Mage's Gauntlet", MapResources::MagesGuild_Mages_Gauntlet_Entrance));
		mapList.push_back(this->buildDebugButton("Mage's Gauntlet #1", MapResources::MagesGuild_Mages_Gauntlet_1));
		mapList.push_back(this->buildDebugButton("Mage's Gauntlet #2", MapResources::MagesGuild_Mages_Gauntlet_2));
		mapList.push_back(this->buildDebugButton("Mage's Gauntlet #3", MapResources::MagesGuild_Mages_Gauntlet_3));
		mapList.push_back(this->buildDebugButton("Mage's Gauntlet #4", MapResources::MagesGuild_Mages_Gauntlet_4));

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 2 - Compare/CMOV/Neg/SHL/SHR + OR Puzzle
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Underflow Ruins");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Cleopatra (UR)", MapResources::UnderflowRuins_Home_Cleopatra));
		mapList.push_back(this->buildDebugButton("Zone_3_8 (UR) Pyramid Boss vv", MapResources::UnderflowRuins_Zone_3_8));
		mapList.push_back(this->buildDebugButton("Zone_3_7 (UR) Pyramid -->", MapResources::UnderflowRuins_Zone_3_7));
		mapList.push_back(this->buildDebugButton("Zone_3_6 (UR) Pyramid >>^^", MapResources::UnderflowRuins_Zone_3_6));
		mapList.push_back(this->buildDebugButton("Zone_3_5 (UR) Pyramid ^^^^", MapResources::UnderflowRuins_Zone_3_5));
		mapList.push_back(this->buildDebugButton("Zone_3_4 (UR) Pyramid <<^^", MapResources::UnderflowRuins_Zone_3_4));
		mapList.push_back(this->buildDebugButton("Zone_3_3 (UR) Pyramid <--", MapResources::UnderflowRuins_Zone_3_3));
		mapList.push_back(this->buildDebugButton("Zone_3_2 (UR) Pyramid Interior", MapResources::UnderflowRuins_Zone_3_2));
		mapList.push_back(this->buildDebugButton("Zone_3_1 (UR) Pyramid Top", MapResources::UnderflowRuins_Zone_3_1));
		mapList.push_back(this->buildDebugButton("Zone_3_0 (UR) Pyramid", MapResources::UnderflowRuins_Zone_3_0));
		mapList.push_back(this->buildDebugButton("Zone_2_7 (UR) Sky", MapResources::UnderflowRuins_Zone_2_7));
		mapList.push_back(this->buildDebugButton("Zone_2_6 (UR) Exit", MapResources::UnderflowRuins_Zone_2_6));
		mapList.push_back(this->buildDebugButton("Zone_2_5 (UR) Medusa", MapResources::UnderflowRuins_Zone_2_5));
		mapList.push_back(this->buildDebugButton("Zone_2_4 (UR) Flame #2", MapResources::UnderflowRuins_Zone_2_4));
		mapList.push_back(this->buildDebugButton("Zone_2_3 (UR) Flame #1", MapResources::UnderflowRuins_Zone_2_3));
		mapList.push_back(this->buildDebugButton("Zone_2_2 (UR) Pass", MapResources::UnderflowRuins_Zone_2_2));
		mapList.push_back(this->buildDebugButton("Zone_2_1 (UR) Puzzle", MapResources::UnderflowRuins_Zone_2_1));
		mapList.push_back(this->buildDebugButton("Zone_2_0 (UR) Entrance", MapResources::UnderflowRuins_Zone_2_0));
		mapList.push_back(this->buildDebugButton("Well (UR) DEV", MapResources::UnderflowRuins_Town_Well_Dev));
		mapList.push_back(this->buildDebugButton("Well (UR)", MapResources::UnderflowRuins_Town_Well));
		mapList.push_back(this->buildDebugButton("Hera (UR)", MapResources::UnderflowRuins_Home_Hera));
		mapList.push_back(this->buildDebugButton("Smith (UR)", MapResources::UnderflowRuins_Town_Smith));
		mapList.push_back(this->buildDebugButton("Smith (DEV) (UR)", MapResources::UnderflowRuins_Town_Smith_Questless));
		mapList.push_back(this->buildDebugButton("Alch (UR)", MapResources::UnderflowRuins_Town_Alch));
		mapList.push_back(this->buildDebugButton("Alch (DEV) (UR)", MapResources::UnderflowRuins_Town_Alch_Questless));
		mapList.push_back(this->buildDebugButton("Town (UR)", MapResources::UnderflowRuins_Town_Main));
		mapList.push_back(this->buildDebugButton("Zone_1_5 (UR)", MapResources::UnderflowRuins_Zone_1_5));
		mapList.push_back(this->buildDebugButton("Zone_1_4 (UR) Gauntlet", MapResources::UnderflowRuins_Zone_1_4));
		mapList.push_back(this->buildDebugButton("Zone_1_3 (UR)", MapResources::UnderflowRuins_Zone_1_3));
		mapList.push_back(this->buildDebugButton("Zone_1_2 (UR)", MapResources::UnderflowRuins_Zone_1_2));
		mapList.push_back(this->buildDebugButton("Zone_1_1 (UR)", MapResources::UnderflowRuins_Zone_1_1));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (UR)", MapResources::UnderflowRuins_Zone_1_0));
		mapList.push_back(this->buildDebugButton("Aphrodite (UR)", MapResources::UnderflowRuins_Home_Aphrodite));
		mapList.push_back(this->buildDebugButton("Shoreline (UR)", MapResources::UnderflowRuins_Shoreline));
		mapList.push_back(this->buildDebugButton("Docks (UR)", MapResources::UnderflowRuins_Town_Docks));
		mapList.push_back(this->buildDebugButton("PS Lighthouse Top (UR)", MapResources::PerilousSea_Home_Lighthouse_Top));
		mapList.push_back(this->buildDebugButton("PS Lighthouse (UR)", MapResources::PerilousSea_Home_Lighthouse));
		mapList.push_back(this->buildDebugButton("PS (UR)", MapResources::PerilousSea_Zone_1_0));

		// Traps:
		// - Reinstate water gun if we want it

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 3 - Push/Pop/and/or/xor/not + XOR Puzzle
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Data Mines");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Alch (DM)", MapResources::DataMines_Town_Alch));
		mapList.push_back(this->buildDebugButton("Inn (DM)", MapResources::DataMines_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (DM)", MapResources::DataMines_Town_Smith));
		mapList.push_back(this->buildDebugButton("Town (DM)", MapResources::DataMines_Town_Main));
		mapList.push_back(this->buildDebugButton("Town Train (DM)", MapResources::DataMines_Town_Train));
		mapList.push_back(this->buildDebugButton("Home Dawn (DM)", MapResources::DataMines_Home_Dawn));
		mapList.push_back(this->buildDebugButton("Home Cypress (DM)", MapResources::DataMines_Home_Cypress));
		mapList.push_back(this->buildDebugButton("Home Godiva (DM)", MapResources::DataMines_Home_Godiva));
		mapList.push_back(this->buildDebugButton("Home Burch (DM)", MapResources::DataMines_Home_Burch));
		mapList.push_back(this->buildDebugButton("Ship Main (PS)", MapResources::PerilousSea_Ship_Main));
		mapList.push_back(this->buildDebugButton("Ship Captain (PS)", MapResources::PerilousSea_Ship_Captain));
		mapList.push_back(this->buildDebugButton("Ship Hull (PS)", MapResources::PerilousSea_Ship_Hull));
		mapList.push_back(this->buildDebugButton("Zone_4_0 (DM)", MapResources::DataMines_Zone_4_0));
		mapList.push_back(this->buildDebugButton("Zone_3_8 (DM)", MapResources::DataMines_Zone_3_8));
		mapList.push_back(this->buildDebugButton("Zone_3_7 (DM)", MapResources::DataMines_Zone_3_7));
		mapList.push_back(this->buildDebugButton("Zone_3_6 (DM)", MapResources::DataMines_Zone_3_6));
		mapList.push_back(this->buildDebugButton("Zone_3_5 (DM)", MapResources::DataMines_Zone_3_5));
		mapList.push_back(this->buildDebugButton("Zone_3_4 (DM)", MapResources::DataMines_Zone_3_4));
		mapList.push_back(this->buildDebugButton("Zone_3_3 Stack Puzzle (DM)", MapResources::DataMines_Zone_3_3));
		mapList.push_back(this->buildDebugButton("Zone_3_2 (DM)", MapResources::DataMines_Zone_3_2));
		mapList.push_back(this->buildDebugButton("Zone_3_1 (DM)", MapResources::DataMines_Zone_3_1));
		mapList.push_back(this->buildDebugButton("Zone_3_0 (DM)", MapResources::DataMines_Zone_3_0));
		mapList.push_back(this->buildDebugButton("Zone_2_5 (DM)", MapResources::DataMines_Zone_2_5));
		mapList.push_back(this->buildDebugButton("Zone_2_4 (DM)", MapResources::DataMines_Zone_2_4));
		mapList.push_back(this->buildDebugButton("Zone_2_3 (DM)", MapResources::DataMines_Zone_2_3));
		mapList.push_back(this->buildDebugButton("Zone_2_2 (DM)", MapResources::DataMines_Zone_2_2));
		mapList.push_back(this->buildDebugButton("Zone_2_1 (DM)", MapResources::DataMines_Zone_2_1));
		mapList.push_back(this->buildDebugButton("Zone_2_0 (DM)", MapResources::DataMines_Zone_2_0));
		mapList.push_back(this->buildDebugButton("Zone_1_2 (DM)", MapResources::DataMines_Zone_1_2));
		mapList.push_back(this->buildDebugButton("Zone_1_1 (DM)", MapResources::DataMines_Zone_1_1));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (DM)", MapResources::DataMines_Zone_1_0));

		// * Traps: Missing Nature trap(s): ??

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 4 - Jumps/Loop/Test/more compares
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Castle Valgrind");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("DARK DEBUG (CV)", MapResources::CastleValgrind_Zone_Dark_Debug));
		mapList.push_back(this->buildDebugButton("Alch (CV)", MapResources::CastleValgrind_Town_Alch));
		mapList.push_back(this->buildDebugButton("Inn (CV)", MapResources::CastleValgrind_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (CV)", MapResources::CastleValgrind_Town_Smith));
		mapList.push_back(this->buildDebugButton("Town (CV)", MapResources::CastleValgrind_Town_Main));
		mapList.push_back(this->buildDebugButton("Town Train (CV)", MapResources::CastleValgrind_Town_Train));
		mapList.push_back(this->buildDebugButton("Throne Room (CV)", MapResources::CastleValgrind_Town_Throne_Room));
		mapList.push_back(this->buildDebugButton("Study (CV)", MapResources::CastleValgrind_Town_Study));
		mapList.push_back(this->buildDebugButton("[Dark] Alch (CV)", MapResources::CastleValgrind_Zone_Dark_Town_Alch));
		mapList.push_back(this->buildDebugButton("[Dark] Inn (CV)", MapResources::CastleValgrind_Zone_Dark_Town_Inn));
		mapList.push_back(this->buildDebugButton("[Dark] Smith (CV)", MapResources::CastleValgrind_Zone_Dark_Town_Smith));
		mapList.push_back(this->buildDebugButton("[Dark] Town (CV)", MapResources::CastleValgrind_Zone_Dark_Town_Main));
		mapList.push_back(this->buildDebugButton("[Dark] Study Dark (CV)", MapResources::CastleValgrind_Zone_Dark_Town_Study));
		mapList.push_back(this->buildDebugButton("Zone_2_1_a (CV)", MapResources::CastleValgrind_Zone_2_1_a));
		mapList.push_back(this->buildDebugButton("Zone_2_1 (CV)", MapResources::CastleValgrind_Zone_2_1));
		mapList.push_back(this->buildDebugButton("Zone_2_0_a (CV)", MapResources::CastleValgrind_Zone_2_0_a));
		mapList.push_back(this->buildDebugButton("Zone_2_0 (CV)", MapResources::CastleValgrind_Zone_2_0));
		mapList.push_back(this->buildDebugButton("Zone_1_2 (CV)", MapResources::CastleValgrind_Zone_1_2));
		mapList.push_back(this->buildDebugButton("Zone_1_1 (CV)", MapResources::CastleValgrind_Zone_1_1));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (CV)", MapResources::CastleValgrind_Zone_1_0));

		// ================== TODO ==================
		// Traps: Organ gun, cannon, catapult, ballista, heaven hug (FPU acceptable, given that jmps are pretty much done)

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 5 - FPU (f(i)ld, f(i)st(p), fxch, fcmov, fadd, fsub, fabs, fdiv, fmul, fsqrt, etc)
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Lambda Crypts");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Alch (LC)", MapResources::LambdaCrypts_Town_Alch));
		mapList.push_back(this->buildDebugButton("Inn (LC)", MapResources::LambdaCrypts_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (LC)", MapResources::LambdaCrypts_Town_Smith));
		mapList.push_back(this->buildDebugButton("Town (LC)", MapResources::LambdaCrypts_Town_Main));
		mapList.push_back(this->buildDebugButton("Church (LC)", MapResources::LambdaCrypts_Town_Church));
		mapList.push_back(this->buildDebugButton("Zone_4_1 (LC)", MapResources::LambdaCrypts_Zone_4_1));
		mapList.push_back(this->buildDebugButton("Zone_4_0_a (LC)", MapResources::LambdaCrypts_Zone_4_0_a));
		mapList.push_back(this->buildDebugButton("Zone_4_0 (LC)", MapResources::LambdaCrypts_Zone_4_0));
		mapList.push_back(this->buildDebugButton("Zone_3_3 (LC)", MapResources::LambdaCrypts_Zone_3_3));
		mapList.push_back(this->buildDebugButton("Zone_3_2 (LC)", MapResources::LambdaCrypts_Zone_3_2));
		mapList.push_back(this->buildDebugButton("Zone_3_1 (LC)", MapResources::LambdaCrypts_Zone_3_1));
		mapList.push_back(this->buildDebugButton("Zone_3_0 (LC)", MapResources::LambdaCrypts_Zone_3_0));
		mapList.push_back(this->buildDebugButton("Zone_3_Dev (LC)", MapResources::LambdaCrypts_Zone_3_0_Dev));
		mapList.push_back(this->buildDebugButton("Zone_2_0 (LC)", MapResources::LambdaCrypts_Zone_2_0));
		mapList.push_back(this->buildDebugButton("Zone_1_2 (LC)", MapResources::LambdaCrypts_Zone_1_2));
		mapList.push_back(this->buildDebugButton("Zone_1_1_a (LC)", MapResources::LambdaCrypts_Zone_1_1_a));
		mapList.push_back(this->buildDebugButton("Zone_1_1 (LC)", MapResources::LambdaCrypts_Zone_1_1));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (LC)", MapResources::LambdaCrypts_Zone_1_0));

		// ================== TODO ================== 
		// Traps: floating bombs, guillotine, spiked pendulum, spiked rotators
		// Avail for traps:
		// - SpellBind
		// - SpellCast
		// - WandCrystal
		// - fldpi + fsqrt + fcos/fsin/fptan/fpatan on launcher direction (can also use sqrt for distance based damage or something)
		// - fldpi/fldz/fld1
		// - other fcmov{cc}

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 6 - XMM* / More Jumps / Misc
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Firewall Fissure");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Town Main (FF)", MapResources::FirewallFissure_Town_Main));
		mapList.push_back(this->buildDebugButton("Alch (FF)", MapResources::FirewallFissure_Town_Alch));
		mapList.push_back(this->buildDebugButton("Inn (FF)", MapResources::FirewallFissure_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (FF)", MapResources::FirewallFissure_Town_Smith));
		mapList.push_back(this->buildDebugButton("Home Mittens (FF)", MapResources::FirewallFissure_Town_Home1));
		mapList.push_back(this->buildDebugButton("Home Hades (FF)", MapResources::FirewallFissure_Town_Home2));
		mapList.push_back(this->buildDebugButton("Zone_3_4 (FF)", MapResources::FirewallFissure_Zone_3_4));
		mapList.push_back(this->buildDebugButton("Zone_3_3 (FF) Azmodeus", MapResources::FirewallFissure_Zone_3_3));
		mapList.push_back(this->buildDebugButton("Zone_3_2 (FF)", MapResources::FirewallFissure_Zone_3_2));
		mapList.push_back(this->buildDebugButton("Zone_3_1_Dev (FF)", MapResources::FirewallFissure_Zone_3_Dev));
		mapList.push_back(this->buildDebugButton("Zone_3_1 (FF)", MapResources::FirewallFissure_Zone_3_1));
		mapList.push_back(this->buildDebugButton("Zone_3_0 (FF)", MapResources::FirewallFissure_Zone_3_0));
		mapList.push_back(this->buildDebugButton("Zone_2_3 (FF) Lava Escape", MapResources::FirewallFissure_Zone_2_3));
		mapList.push_back(this->buildDebugButton("Zone_2_2 (FF)", MapResources::FirewallFissure_Zone_2_2));
		mapList.push_back(this->buildDebugButton("Zone_2_1 (FF)", MapResources::FirewallFissure_Zone_2_1));
		mapList.push_back(this->buildDebugButton("Zone_2_0 (FF)", MapResources::FirewallFissure_Zone_2_0));
		mapList.push_back(this->buildDebugButton("Zone_1_0_a (FF)", MapResources::FirewallFissure_Zone_1_0_a));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (FF)", MapResources::FirewallFissure_Zone_1_0));

		// ================== TODO ================== 
		// Traps: Fire bird, fire launcher, TNT barrel, mortar

		// Avail for traps:
		// - Dice
		// - Candle
		// - SkullAndCrossbones
		// - Skull2
		// - SpellFire
		// - SunShield

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 7 - SET (really? What a waste)
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Ballmer Peaks");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Alch (BP)", MapResources::BallmerPeaks_Town_Alch));
		mapList.push_back(this->buildDebugButton("Inn (BP)", MapResources::BallmerPeaks_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (BP)", MapResources::BallmerPeaks_Town_Smith));
		mapList.push_back(this->buildDebugButton("Town Main (BP)", MapResources::BallmerPeaks_Town_Main));
		mapList.push_back(this->buildDebugButton("Town Hall (BP)", MapResources::BallmerPeaks_Town_Hall));
		mapList.push_back(this->buildDebugButton("Zone_3_2 (BP)", MapResources::BallmerPeaks_Zone_3_2));
		mapList.push_back(this->buildDebugButton("Zone_3_1 (BP)", MapResources::BallmerPeaks_Zone_3_1));
		mapList.push_back(this->buildDebugButton("Zone_3_0 (BP)", MapResources::BallmerPeaks_Zone_3_0));
		mapList.push_back(this->buildDebugButton("Zone_2_3 (BP)", MapResources::BallmerPeaks_Zone_2_3));
		mapList.push_back(this->buildDebugButton("Zone_2_2 (BP)", MapResources::BallmerPeaks_Zone_2_2));
		mapList.push_back(this->buildDebugButton("Zone_2_1 (BP)", MapResources::BallmerPeaks_Zone_2_1));
		mapList.push_back(this->buildDebugButton("Zone_2_0 (BP)", MapResources::BallmerPeaks_Zone_2_0));
		mapList.push_back(this->buildDebugButton("Zone_1_2 (BP)", MapResources::BallmerPeaks_Zone_1_2));
		mapList.push_back(this->buildDebugButton("Zone_1_1 (BP)", MapResources::BallmerPeaks_Zone_1_1));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (BP)", MapResources::BallmerPeaks_Zone_1_0));

		// ================== TODO ================== 
		// Traps: Icicle, bear trap (?), { cannon or catapult or portal } (to VS)
		// ASM Reference (General instructions) https://docs.oracle.com/cd/E26502_01/html/E28388/ennbz.html#eoizv
		// ASM Reference (AVX instructions) https://docs.oracle.com/cd/E36784_01/html/E36859/gntbd.html

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 8 - Call/Ret?
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Void Star");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Alch (VS)", MapResources::VoidStar_Town_Alch));
		mapList.push_back(this->buildDebugButton("Smith (VS)", MapResources::VoidStar_Town_Smith));
		mapList.push_back(this->buildDebugButton("Town (VS)", MapResources::VoidStar_Town_Main));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (VS)", MapResources::VoidStar_Zone_1_0));
		mapList.push_back(this->buildDebugButton("Zone_1_1 (VS)", MapResources::VoidStar_Zone_1_1));
		mapList.push_back(this->buildDebugButton("Zone_1_2 (VS)", MapResources::VoidStar_Zone_1_2));

		// Traps: Laser

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	for (ChapterDebugInfo& next : this->chapterDebugInfoList)
	{
		for (ClickableTextNode* mapButton : next.mapList)
		{
			next.scrollPane->addChild(mapButton);
		}

		this->addChild(next.scrollPane);
		this->addChild(next.titleButton);
	}
}

DeveloperScene::~DeveloperScene()
{
}

void DeveloperScene::onEnter()
{
	super::onEnter();

	this->selectChapter(0);
}

void DeveloperScene::initializePositions()
{
	super::initializePositions();

	CSize visibleSize = Director::getInstance()->getVisibleSize();

	for (int chapterIndex = 0; chapterIndex < int(this->chapterDebugInfoList.size()); chapterIndex++)
	{
		ChapterDebugInfo& next = this->chapterDebugInfoList[chapterIndex];

		next.titleButton->setPosition(Vec2(112.0f + float(chapterIndex) * 212.0f, visibleSize.height - 96.0f));
		next.scrollPane->setPosition(Vec2(visibleSize / 2.0f));

		for (int index = 0; index < int(next.mapList.size()); index++)
		{
			next.mapList[index]->setPosition(Vec2(0.0f, -128.0f - float(index) * 180.0f));
		}
	}
}

void DeveloperScene::initializeListeners()
{
	super::initializeListeners();
	
	this->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!GameUtils::isVisible(this))
		{
			return;
		}
		
		args->handle();
		
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return TitleScreen::getInstance(); }));
	});
}

void DeveloperScene::selectChapter(int index)
{
	for (ChapterDebugInfo& next : this->chapterDebugInfoList)
	{
		next.scrollPane->setVisible(false);
	}

	if (index < 0 || index >= int(this->chapterDebugInfoList.size()))
	{
		return;
	}

	this->chapterDebugInfoList[index].scrollPane->setVisible(true);
}

ScrollPane* DeveloperScene::buildScrollPane()
{
	return ScrollPane::create(CSize(1280.0f, 768.0f), UIResources::Menus_Buttons_SliderButton, UIResources::Menus_Buttons_SliderButtonSelected);
}

ClickableTextNode* DeveloperScene::buildTitleButton(std::string displayName)
{
	static int GlobalIndex = 0;
	int index = GlobalIndex;
	GlobalIndex++;

	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, ConstantString::create(displayName));
	LocalizedLabel* labelSelected = label->clone();

	label->enableOutline(Color4B::BLACK, 2);
	labelSelected->enableOutline(Color4B::BLACK, 2);
	
	ClickableTextNode* clickableTextNode = ClickableTextNode::create(label, labelSelected, UIResources::Menus_Buttons_DarkWoodButton, UIResources::Menus_Buttons_DarkWoodButtonSelected);

	clickableTextNode->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->selectChapter(index);
	});

	return clickableTextNode;
}

ClickableTextNode* DeveloperScene::buildDebugButton(std::string displayName, std::string mapResource)
{
	LocalizedLabel* label = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H2, ConstantString::create(displayName));
	LocalizedLabel* labelSelected = label->clone();

	label->enableOutline(Color4B::BLACK, 2);
	labelSelected->enableOutline(Color4B::BLACK, 2);
	
	ClickableTextNode* clickableTextNode = ClickableTextNode::create(label, labelSelected, UIResources::Menus_MinigamesMenu_Banner, UIResources::Menus_MinigamesMenu_BannerHover);

	clickableTextNode->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
		{
			const int UNUSED_SAVE_PROFILE = 99;

			SaveManager::DeleteAllProfileData(UNUSED_SAVE_PROFILE);
			SaveManager::SetActiveSaveProfile(UNUSED_SAVE_PROFILE);

			// SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyQuickPotionUnlocked, Value(true));

			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookArcane, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookFire, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookFrost, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookHoly, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookLightning, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookNature, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookShadow, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWater, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWind, Value(true));
			
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGuanoFound, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGeckyFound, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGrimFound, Value(true));
			// SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Guano::MapKey));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(GuanoPetrified::MapKey));
			// SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Gecky::MapKey));
			// SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Grim::MapKey));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));

			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySquallyEq, Value(5));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGeckyEq, Value(7));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyGrimEq, Value(10));
			
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyRespawnMap, Value(mapResource));

			PlatformerMap* map = PlatformerMap::create();

			map->loadMap(mapResource);

			return map;
		}));
	});

	return clickableTextNode;
}
