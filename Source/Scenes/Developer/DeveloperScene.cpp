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

		mapList.push_back(this->buildDebugButton("DBG Cages", MapResources::Dev_Cages));
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
	- Misc Minor:
		v Pacing behavior is broken for portal maps
		v Camera harsh leaving camera targets (which?)
		v Necron hitbox wrong in Mages guild (inconsistent?)
		v No interrupt if damage attack modified to heal
		v Seagulls should blink

	- Localization / Scripting
		- Text navigation is pretty bad in long scripts.
		- Multi-line comments in scripts can cause line counter to become disrupted
		- Long scripts can fail to show blinking cursor sometimes (??)
		- Should really expand scripting text editor
			- Support click-to-place cursor
		- User-made script titles can go TOFU upon language change. Wontfix? Save original language, and reset to current if the user clears the title?
		v If ever re-instating Arabic, Ctrl+F all "ar": "! and "ar": ". strings to find places where punctuation was messed up and fix them
		v If ever re-instating Arabic, probably force English for scripting. Mixing RTL and LTR language is awful. Or use Arabic romanization.

	- Game Feel / Design / Lore:
		** Credits
		** Final Boss Fight
		* Cracks in simulation for story
		* Very early Perceptron encounter?
			* Encounter in EF? Where?
			* Add an encounter in DM 1_0 (Have Perceptron block the bridge path, require ducking behind debris to avoid death)
		- Squally
			** Can get stuck on roof of maps (see UR 3_1)
			* Squally death anim improvement (and disable float hover. maybe for all entities, as IsAlive check)
		- SFX
			- Add CPU noises when turned on in DM
			- Add Train noises in DM/CV
		- Sub-categories for alchemy lab
		- Chapter transitions can be more special
		- Maybe give IOUs instead of cards as a prize, force players to purchase cards from Inns
		- 2nd pass on all spells
		- Overworld attacks for many enemies
		- Remaining spellbooks + abilities
			- Nature (needs ability?)
			- Shadow
			- Frost
			- Fire (Possibly use to dispel firewall)
			- VS special book
		- Helpers
			- Abilities unlocked at certain levels
			- Equipment? Would fucking blow for menuing, also unclear how this works with only 1 helper allowed at a time.
	
	- Music
		- Good desert music (The Letter sucked)
		- https://michelemclaughlin.com/pages/contact (Preserverence)
		- https://www.instagram.com/strayghostofficial/?hl=en (Two Steps)

	- Level Design:
		- ? Mages guild accessible from all maps, but use the return portal. This incentivizes other travel (sky masters, boats)
			- ? Destroy all warp maps as a result (?) can still keep the zone portals for the return location
		- ? What to do with these now?
			- Sky masters
				- Find Finch to get to BP
				- Find Irmik to get to BP peaks
			- Kill 2nd sky tower map?

	- Mini-Games:
		- Something feels off about torch puzzles. Colors? Give control over top and bottom? Hard to say, but rework it.
		- A few 3Q Perspective maps
			- Invisible helpers. Some way to pull helpers into combat
		- Cipher:
			* Reinstate? What's the new play? Asm? Macro magic to avoid emulation (store state to a struct after each instruction).
				- Probably like Hexus puzzles, with preset C++ classes rather than map-property defined.
		- P-Trace:
			* Reinstate? What's the new play? Can this be that circuit game I was thinking? Maybe can flip circuit switches to incentivize using brain
			- isometric squally, and some form of strategy element that isn't prone to trial-and-error.
				- Another play is to make these actual "maps" that you can pass through.
			- Could make a mini-game in towns? Inns? Where? Maybe just one machine in a zone of my choosing? (I kinda prefer DM or CV)
		- Hexus:
			- Sanity check card localization (due to art changes)
			- Can pass after auto-loss
			- Win a hexus puzzle, next one will show massive row score deltas
			- Leave button stuck visible after losing a puzzle
				- Enemy should pre-calc the best play when player has passed (hard)
			- Maybe hard code some rewards. It'd be nice to get SHL from the puzzle where you learn it.
	
	- Performance / Stability / Code quality:
		- Please god new anim system would be soo cool perf wise (especially on maps with a large number of entities, ie FF)
		- Mystery crash / ensures when waiting on victory screen (matrix letters task func)
		- Crash reports probably are broken?
	
	- Polish!
		- Enemy anims for getting hit
		- Enemy anims for combat begin (temporarily pausing timeline)
	*/

	// CHAPTER 1 - Mov/add/sub/inc/dec/div/mul + AND Puzzle
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Endian Forest");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room (EF)", MapResources::EndianForest_Mages_Warp));
		mapList.push_back(this->buildDebugButton("Boat EF => UR", MapResources::EndianForest_Ship_Main));
		mapList.push_back(this->buildDebugButton("Docks (EF)", MapResources::EndianForest_Town_Docks));
		mapList.push_back(this->buildDebugButton("Elbridge", MapResources::EndianForest_Town_Main));
		mapList.push_back(this->buildDebugButton("Inn (EF)", MapResources::EndianForest_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (EF)", MapResources::EndianForest_Town_Smith));
		mapList.push_back(this->buildDebugButton("Alch (EF)", MapResources::EndianForest_Town_Alch));
		mapList.push_back(this->buildDebugButton("Ballmer's Peak", MapResources::BallmerPeaks_Town_Main));
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
		mapList.push_back(this->buildDebugButton("Guano's Cell", MapResources::EndianForest_Home_Guano));
		mapList.push_back(this->buildDebugButton("Mage's Prison", MapResources::EndianForest_Mages_Prison));
		mapList.push_back(this->buildDebugButton("Mage's Guild",MapResources::EndianForest_Mages_Guild));
		mapList.push_back(this->buildDebugButton("Mage's Gauntlet", MapResources::EndianForest_Mages_Gauntlet_Entrance));
		mapList.push_back(this->buildDebugButton("Mage's Gauntlet #1", MapResources::EndianForest_Mages_Gauntlet_1));
		mapList.push_back(this->buildDebugButton("Mage's Gauntlet #2", MapResources::EndianForest_Mages_Gauntlet_2));
		mapList.push_back(this->buildDebugButton("Mage's Gauntlet #3", MapResources::EndianForest_Mages_Gauntlet_3));
		mapList.push_back(this->buildDebugButton("Mage's Gauntlet #4", MapResources::EndianForest_Mages_Gauntlet_4));

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));

		// Hexus Puzzles:
		// - A	=> 2_0 (Orc Grunt)
		// - B	=> 2_2 (Troll)
		// - C	=> 2_4_a (Goblin Warrior Pig)
		// - D	=> 2_4 (Orc Warrior)
		// - E	=> 2_6 (Goblin Grunt Boar)
		// - F	=> 3_0 (Ogre)
		// - G	=> 3_1 (Cyclops)

		// Puzzles:
		// A				EF	2_0		orc-grunt
		// B				EF	2_2		
		// C				EF	2_4
		// D				EF	2_6
		// E				EF	3_0
		// F				EF	3_1

		// TODO:
		// Overworld attacks (Troll / Cyclops swing)
		// Troll Strength ability seems additive rather than absolute damage
		// Hot potato debuff for swordsman (dec on target)
	}

	// CHAPTER 2 - Compare/CMOV/Neg/SHL/SHR + OR Puzzle
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Underflow Ruins");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room (UR)", MapResources::UnderflowRuins_Mages_Warp));
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
		mapList.push_back(this->buildDebugButton("Well (UR)", MapResources::UnderflowRuins_Town_Well));
		mapList.push_back(this->buildDebugButton("Hera (UR)", MapResources::UnderflowRuins_Home_Hera));
		mapList.push_back(this->buildDebugButton("Smith (UR)", MapResources::UnderflowRuins_Town_Smith));
		mapList.push_back(this->buildDebugButton("Smith (DEV) (UR)", MapResources::UnderflowRuins_Town_Smith_Questless));
		mapList.push_back(this->buildDebugButton("Alch (UR)", MapResources::UnderflowRuins_Town_Alch));
		mapList.push_back(this->buildDebugButton("Alch (DEV) (UR)", MapResources::UnderflowRuins_Town_Alch_Questless));
		mapList.push_back(this->buildDebugButton("Town (UR)", MapResources::UnderflowRuins_Town_Main));
		mapList.push_back(this->buildDebugButton("Zone_1_5 (UR)", MapResources::UnderflowRuins_Zone_1_5));
		mapList.push_back(this->buildDebugButton("Zone_1_4 (UR)", MapResources::UnderflowRuins_Zone_1_4));
		mapList.push_back(this->buildDebugButton("Zone_1_3 (UR)", MapResources::UnderflowRuins_Zone_1_3));
		mapList.push_back(this->buildDebugButton("Zone_1_2 (UR)", MapResources::UnderflowRuins_Zone_1_2));
		mapList.push_back(this->buildDebugButton("Zone_1_1 (UR)", MapResources::UnderflowRuins_Zone_1_1));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (UR)", MapResources::UnderflowRuins_Zone_1_0));
		mapList.push_back(this->buildDebugButton("Aphrodite (UR)", MapResources::UnderflowRuins_Home_Aphrodite));
		mapList.push_back(this->buildDebugButton("Shoreline (UR)", MapResources::UnderflowRuins_Shoreline));
		mapList.push_back(this->buildDebugButton("Docks (UR)", MapResources::UnderflowRuins_Town_Docks));

		// Hexus Puzzles:
		// - A	=> 1_0 (Lioness)
		// - B	=> 1_2_a (Tiger Man)
		// - C	=> 2_2 (Mermaid)
		// - D	=> 2_3 (Minotaur)
		// - E	=> 3_3 (Mummy Warrior)
		// - F	=> 3_6 (Anubis Pup)

		// ================== TODO ================== 
		// Despawn dead gauntlet vehicles
		// Add aura for undying that makes the effect obvious
		// Guano warps to Squally on unpetrification, which looks like trash
		// Reinstate water gun if we want it
		// Show the electricity ON/OFF in Lions Cistern water visually somehow
		// Overworld attacks

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 3 - Push/Pop/and/or/xor/not + XOR Puzzle
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Data Mines");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room (DM)", MapResources::DataMines_Mages_Warp));
		mapList.push_back(this->buildDebugButton("Alch (DM)", MapResources::DataMines_Town_Alch));
		mapList.push_back(this->buildDebugButton("Inn (DM)", MapResources::DataMines_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (DM)", MapResources::DataMines_Town_Smith));
		mapList.push_back(this->buildDebugButton("Town (DM)", MapResources::DataMines_Town_Main));
		mapList.push_back(this->buildDebugButton("Town Train (DM)", MapResources::DataMines_Town_Train));
		mapList.push_back(this->buildDebugButton("Home Dawn (DM)", MapResources::DataMines_Home_Dawn));
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

		// ================== TODO ==================
		// Maybe hint to use 'or' on shadow bomb
		// Earth golem cast anim kinda shit
		// Earth elem cast anim shit
		// Double check green light defaults on DM xor puzzle
		// Boat combat map for Krampus fight
		// Rhinoman hovers off platform when dead in fight
		// Train SFX
		// Terrain in tent map has wrong corner connectors
		// Tiki anims still broken (bad Spriter implementation strikes again)
		// Train anims broken (for same reason)
		// Nature spellbook, even if just for an ability? What ability?

		// Hexus puzzles:
		// - A	=> 1_x (Tiki)
		// - B	=> 1_x (Shaman)
		// - C	=> 2_1 (Forest Golem)
		// - D	=> 2_5 (Earth Golem)
		// - E	=> 3_1 (Skeletal Warrior)
		// - F	=> 3_4 (Skeletal Pirate)
		
		/*
		X Tiki Golem			=> X 1_1 Push/Pop const buff (call of the ancients - outgoing AND incoming damage)
		X Shaman				=> X 1_2 AND (Shadow Bomb)
		X [B] Rhinoman			=> X 1_x AND debuff (Brittle Bones)
		X Forest golem			=> X 2_0 ROL (REJUVINATE)
		X Earth golem			=> X 2_1 ROR (ROCKSLIDE)
		X Earth Elemental		=> X 2_2 OR (REGERATION)
		X Skeletal Pirate		=> X 3_2 XOR (BLIND)
		X Skeletal Archer		=> X 3_1 PUSH / POP REG (MULTISHOT debuff - curse of the ancients - damage dealt)
		X Skeletal Warrior		=> X 3_0 PUSH [REG PTR + offset] / POP [REG PTR + offset] (blessing of the ancients - outgoing damage)
		X Skeletal Necromancer 	=> X 3_0 PUSH const / POP [REG PTR] (pact of the ancients - health link)
		X [B] Krampus			=> X 3_3 LEA

		X Olive			Zone 1_1 (H_1)
		X Bonnie		Town_Inn (H_2) (non-vendor)
		X Princess Dawn	Home_Dawn
		X Burch			Zone 2_x (H_3)
		X Raka			Zone 3_3 (Push/Pop Puzzle) (H_4)
		X Ralson		Home_Ralston (H_5)
		X Godiva		Home_Godiva (H_6)
		X Bancroft		Town_Train (H_7)
		X Mildred		Town_Train (H_8)
		X Fraya			Town_Alch
		X Brock			Town_BS
		X Shen			Town_Inn

		- Cypress		Zone 2_x nature spellbook (or cut from the game, it doesn't fit well. Can also keep this optional, and have it just grant an ability)
		- Alder			Technically in mage's guild
		- Jasper		Technically in mage's guild
		- Sarude		Technically in mage's guild
		- Gorilla		Deprecate
		*/

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 4 - Jumps/Loop/Test/more compares
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Castle Valgrind");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room (CV)", MapResources::CastleValgrind_Mages_Warp));
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

		/*
		See http://unixwiz.net/techtips/x86-jumps.html because its hard to condense names and capture flags on the same chart.
		X Thug					1_x		=> jmp 			--			Heavy blade
		X Barbarian				1_x		=> jle			ZF/SF/OF	Defensive Stance
		X ReanimatedFighter		1_x		=> jg			ZF/SF/OF	Diseased
		X Wraith				dark	=> jne			ZF/SF/OF	Manifest <Spirit, invert rabies as damage buff>
		X Abomination			dark	=> jnz			ZF/SF/OF	<Radiation, RNG per tick to do -5 dmg or something>
		X Reaper				dark	=> je			ZF/SF/OF	<AngelFigurine, immortality>
		X Vampiress				dark	=> jz			ZF/SF/OF	Leech <SwordGlowBlue, RNG mana steal?>
		X VampireLord			dark	=> jl			ZF/SF/OF	Vampirism <SkullAndCrossbones, HP Steal>
		X SkeletalBaron			dark	=> js			SF			Parry <ShieldAdorned, convert damage to zero>
		X WereWolf				2_x		=> jge			ZF/SF/OF	Rabies <Fangs, speed drain>
		X Jack					2_x		=> jns			SF			<Stab, Bloodletting RNG Per Tick>
		X [B] Agnes				dark_t	=> jecxz		%ecx == 0	Bat Swarm <Bats, Bat Swarm RNG per tick to attack>

		// Hexus puzzles:
		// - A	=> 1_1 (Thug)
		// - B	=> Town_Main (Reanimated Fighter)
		// - C	=> Town_Study (Reaper)
		// - D	=> 2_0_a (Wraith)
		// - E	=> 2_1 (Abomination)
		// - F	=> Town_Throne (Skeletal Baron)

		- Garin					=> Town_Train
		- Zana					=> 1_2 (X H_1)
		- Gaunt					=> Main (X H_2)
		- Leon					=> Main (X H_3)
		- Atreus				=> Main
		- Mabel					=> Study (X H_5)
		- Illia					=> Main
		- Tyracius				=> 2_x (X H_6)
		- Princess Opal			=> Town_Throne
		- [Slime] King Redsong	=> [Dark_]Town_Throne
		- Rogas					=> Town_Inn (X H_4)
		- Leopold				=> Town_Alch
		- Raven					=> Town_Inn
		- Thurstan				=> Town_Smith

		- Merlin				=> XXXXX nope
		*/

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 5 - FPU (f(i)ld, f(i)st(p), fxch, fcmov, fadd, fsub, fabs, fdiv, fmul, fsqrt, etc)
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Lambda Crypts");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room (LC)", MapResources::LambdaCrypts_Mages_Warp));
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
		// * Make final 4_x maps less bad. Exit door should be placed more reasonably. Maybe gated behind boss kill.
		// * Mage tower? Portal map?
		// * Perceptron is on the map with DM door just sitting there. Remove him? Or despawn him properly if there is an encounter.

		/*
		X Assassin				=>  1_x <ThrowingStar,		fiadd> 		=> Focus / add to damage
		X BoneFiend				=>  1_x <AxeGlowPurp,		fdiv>  		=> CursedSwings debuff / reduce damage by 75% or something (int)
		X Mystic				=>  1_x <VoodooZombie,		fimul> 		=> Hex / speed decrease
		X ReanimatedPig			=>  2_x <Piggy,				fisub> 		=> Thick Hide / dmg decrease
		X Zombie				=>  2_x <ZombieGrasp,		fild/fistp> => Zombie Grasp / raw damage dealt debuff
		X Undead				=>  2_x <DeadGrasp,			fabs>		=> Dead Grasp / convert damage to healing
		X Zombie Elric			=> 	2_x 								=> Recycle (ZombieGrasp)
		X BoneKnight			=>  3_x <ShieldGlowOrange,	fidiv> 		=> Shield Wall / constant 25% damage recv
		X Warlock				=>  3_x <WandSkeleton,		fmul/frndint> 	=> Enchantment / 50% damage increase (rounded)
		X Hunter				=>  3_x <PoisonSpears,		ja>  		=> PoisonedArrows - either radiation or diseased copy
		X [B] Lazarus			=>	3_x <Tombstone, 		fcmove> 	=> UnholyProtection (rename) / undying effect
		X [B] Lazarus			=>	3_x <GhostBolts,		fchs> 		=> Ghostbolts / reflectable spell (Copy FireBall I guess?) but make 1 per teammate (ie 2 lol)
		X SkeletalPriestess		=>  4_x <Book,				jbe> 		=> Spell of Binding - Speed Decrease
		X SkeletalKnight		=>  4_x <SwordGlowPurp,		jae>  		=> CursedBlade - Reduce damage
		X SkeletalCleaver		=>  4_x <SwordGlowYel,		jb> 		=> UnholyBlade - Damage to healing
		X [B] KingZul			=>  4_x <Daze,			fcmovbe> 		=> Daze / chance to do less damage (use cool daze FX)

		Avail for traps:
		- SpellBind
		- SpellCast
		- WandCrystal
		- fldpi + fsqrt + fcos/fsin/fptan/fpatan on launcher direction (can also use sqrt for distance based damage or something)
		- fldpi/fldz/fld1
		- other fcmov{cc}

		// Hexus puzzles:
		// - A	=> 1_1 (Bone fiend)
		// - B	=> 2_0 (zombie)
		// - C	=> Town_Main (Undead)
		// - D	=> Town_Church (Reanimated Pig)
		// - E	=> 3_0 (Bone Knight)
		// - F	=> 4_0_a (Skeletal Priestess)
		
		- Ursula				=> 1_x (H1)
		- Thion					=> Town_Main (H2)
		- Viper					=> Town_Inn (H3)
		- Amelia				=> Town_Church
		- Azmus					=> Town_Smith
		- Garrick				=> Town_Inn
		- Johann				=> Town_Church (H4)
		- Princess Nebea		=> Town_Church
		- Zelina				=> 3_x (H5)
		- Roger					=> 4_x (H6)
		- Vesuvius				=> Town_Alch
		- [Zombie] Elric		=> 2_x
		*/

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 6 - XMM* / More Jumps / Misc
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Firewall Fissure");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room (FF)", MapResources::FirewallFissure_Mages_Warp));
		mapList.push_back(this->buildDebugButton("Town Main (FF)", MapResources::FirewallFissure_Town_Main));
		mapList.push_back(this->buildDebugButton("Alch (FF)", MapResources::FirewallFissure_Town_Alch));
		mapList.push_back(this->buildDebugButton("Inn (FF)", MapResources::FirewallFissure_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (FF)", MapResources::FirewallFissure_Town_Smith));
		mapList.push_back(this->buildDebugButton("Home Mittens (FF)", MapResources::FirewallFissure_Town_Home1));
		mapList.push_back(this->buildDebugButton("Home Hades (FF)", MapResources::FirewallFissure_Town_Home2));
		mapList.push_back(this->buildDebugButton("Zone_3_3 (FF)", MapResources::FirewallFissure_Zone_3_3));
		mapList.push_back(this->buildDebugButton("Zone_3_2 (FF)", MapResources::FirewallFissure_Zone_3_2));
		mapList.push_back(this->buildDebugButton("Zone_3_1_Dev (FF)", MapResources::FirewallFissure_Zone_3_Dev));
		mapList.push_back(this->buildDebugButton("Zone_3_1 (FF)", MapResources::FirewallFissure_Zone_3_1));
		mapList.push_back(this->buildDebugButton("Zone_3_0 (FF)", MapResources::FirewallFissure_Zone_3_0));
		mapList.push_back(this->buildDebugButton("Zone_2_3 (FF)", MapResources::FirewallFissure_Zone_2_3));
		mapList.push_back(this->buildDebugButton("Zone_2_2 (FF)", MapResources::FirewallFissure_Zone_2_2));
		mapList.push_back(this->buildDebugButton("Zone_2_1 (FF)", MapResources::FirewallFissure_Zone_2_1));
		mapList.push_back(this->buildDebugButton("Zone_2_0 (FF)", MapResources::FirewallFissure_Zone_2_0));
		mapList.push_back(this->buildDebugButton("Zone_1_0_a (FF)", MapResources::FirewallFissure_Zone_1_0_a));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (FF)", MapResources::FirewallFissure_Zone_1_0));

		// ================== TODO ================== 
		// Traps: Fire bird, fire launcher, TNT barrel, mortar
		// Remove wanted poster after Asmodeus dead. Maybe some Elise dialogue.

		/*
		Surface:
			X DemonRogue			=>  1_X		<SkullGlowRed, 		movss> 	=> BloodBoil / Fixed damage debuff
			X DemonShaman			=>  1_X		<BookSpellsFire,	addss> 	=> Cauterize / Self Heal Tick
			X DemonSwordsman		=>  1_X		<AxeGlowRed,		mulss> 	=> Scalding Blade / Damage+
		Caves:
			X LavaGolem				=>  2_X		<Fire,			rdrand> 		=> Enflame / Burn Tick
			X DemonDragon			=>  2_X		<Bone,			divss> 			=> Calcify / Defense+ 
			X DemonGhost			=>  2_X		<SkullLavaEyes,	xchg>		 	=> Inner Fire / Siphon HP tick
			X FireElemental			=>  2_X		<FireBolts,		cmpss/comiss> 	=> Fire Rain / AoE damage
		Surface 2?
			X DemonArcher			=>  3_X		<CrossBow,			call/ret>		=> Arrow Volley / team compare damage
			X DemonGrunt			=>  3_X		<DaggerGlowYellow,	sete> 			=> Seeking Blade / Damage+ based on rng
			X DemonWarrior			=>  3_X		<FlamingScroll,		setne> 			=> Melt / Damage- based on RNG
			X FireTiger				=>  3_X		<Chains,			bswap> 			=> Entwined / Health Link
			- [B] Asmodeus			=> 	4_X		<AxeGlowOrange,		call/ret?>		=> Searing Blade / Giant axe that falls counter-clockwise, redirectable?

		Avail for traps:
		- Dice
		- Candle
		- SkullAndCrossbones
		- Skull2
		- SpellFire
		- SunShield

		-----------------
		
		// Hexus puzzles:
		// - A	=> 1_1 (Bone fiend)
		// - B	=> 2_0 (zombie)
		// - C	=> Town_Main (Undead)
		// - D	=> Town_Church (Reanimated Pig)
		// - E	=> 3_0 (Bone Knight)
		// - F	=> 4_0_a (Skeletal Priestess)

		X Ash			=> 1_x (H1)
		X Lucifer		=> 2_x (H2)
		X Brine			=> Town_Main (Exterior) (H3)
		X Hades			=> Town_Main (H4)
		X Mittens		=> Town_Main
		X Celeste		=> Town_Main
		X Cindra		=> Town_Main
		X Scaldor		=> 3_x (barricade) (H5)
		X Magnus		=> 3_x (barricade) (H6)
		X Queen Elise	=> Town_Main
		X Pan			=> Alch
		X Ragnis		=> Smith
		X Thatcher		=> Inn
		- Finch			? Zone 2_x Flight Master -- Start flight master quest?
		*/

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 7 - SET (really? What a waste)
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Ballmer Peaks");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room (BP)", MapResources::BallmerPeaks_Mages_Warp));
		mapList.push_back(this->buildDebugButton("Alch (BP)", MapResources::BallmerPeaks_Town_Alch));
		mapList.push_back(this->buildDebugButton("Inn (BP)", MapResources::BallmerPeaks_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (BP)", MapResources::BallmerPeaks_Town_Smith));
		mapList.push_back(this->buildDebugButton("Town Main (BP)", MapResources::BallmerPeaks_Town_Main));
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
		// Vertical town (maybe two sections, one inaccessible at first to spread out NPCs)
		// ** 1_x typical EF style outdoors leading to town (viking, penguin grunt, penguin warrior, frost fiend (technically in 3_x))
		// ** 2_x for some frost caverns (ice golem, water elemental, yeti) => cryogen
		// ** 3_x for blizzard environment? (goblin elf, toy soldier goblin, snow fiend) => santa => sky cannon
		// ** Needs hexus battles
		// ** Tune hexus battle special cards
		// ** Needs animals
		// ** Needs enemy scripting according to notes on which instructions this zone covers

		/*
		ASM Reference (General instructions) https://docs.oracle.com/cd/E26502_01/html/E28388/ennbz.html#eoizv
		ASM Reference (AVX instructions) https://docs.oracle.com/cd/E36784_01/html/E36859/gntbd.html

		- PenguinGrunt		1_x		=> <Feather, 		setge> // Speed?
		- PenguinWarrior	1_x		=> <AxeGlowBlue, 	setl> 
		- Viking			1_x		=> <Anchor, 		setle> 
		- IceGolem			2_x		=> <Diamond, 		setg> // Immortality. Copy undying logic, but include a subtract.
		- Yeti				2_x		=> <AxeMoon?, 		setng> 
		- WaterElemental	2_x		=> <SpellImpactBlue, 	setnge>
		- FrostFiend		2_x 	=> <Blizzard, 			setnl> 
		- GoblinElf			3_x		=> <AxeGlowGreen, 		setnle> 
		- ToySoldierGoblin	3_x		=> <ChristmasPresent, 	setns> // Non-negative
		- SnowFiend			3_x		=> <Snowflake, 			setnz> // Non-zero
		- [B?] Santa		3_x		=> <Gift, 				sets> // Negative // RNG?
		- [B] Cryogen		3_x 	=> <SwordsLight, 		setz> // Zero

		- Aspen
		- Bodom
		X Cookie => Santa
		X Cooper => Inn
		X Jingles => Santa
		- Juniper
		X Kringle => Santa
		X Luna => alch
		- Nessie
		- Princess Pepper
		X Theldar => smith
		X Tinsel => Santa
		- Ysara
		X Irmik => SkyMaster
		*/

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 8 - Call/Ret?
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Void Star");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room (VS)", MapResources::VoidStar_Mages_Warp));
		mapList.push_back(this->buildDebugButton("Alch (VS)", MapResources::VoidStar_Town_Alch));
		mapList.push_back(this->buildDebugButton("Smith (VS)", MapResources::VoidStar_Town_Smith));
		mapList.push_back(this->buildDebugButton("Town (VS)", MapResources::VoidStar_Town_Main));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (VS)", MapResources::VoidStar_Zone_1_0));

		// ================== TODO ================== 
		// Traps: Laser
		// * Needs enemy scripting according to notes on which instructions this zone covers
		// * Quest granting money and health manip
		// 		* Potentially no mage tower? Final boss room is a portal room (maybe with bigger windows to see other worlds?)

		/*
		Enemies
		- Exterminator				=>  
		- Void Demon				=>  
		- [B] Perceptron			=>  

		Available icons:
		- ShovelGlowGreen
		*/

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	/*
	TRANSITIONS:
	- EF => EF LimeStone (blimp 1) - ??????
	- EF => CV (blimp 2) - Finch
	- CV => BP (blimp 3) - Irmik
	- CV => LC (train) - Garin
	- DM => FF (viking ship or smth) - Drak
	- BP => BP (viking ship or smth) - <Any>

	======================

	Level order / Mage
	EF		//	Fraya? Mabel?
	UR		//	Alder
	DM		//	Cypress
	CV		//	Merlin
	BP		//	Aster
	FF		//	Igneus
	LC		//	Necron
	VS		//	Marcel

	////////// UR //////////

	------------------------

	X Lioness			Zone 1_x
	X LionMan			Zone 1_x
	X Tigress			Zone 1_x
	X TigerMan		Zone 1_x

	X Medusa			Zone 2_x
	X Mermaid			Zone 2_x
	X Minotaur		Zone 2_x

	X Anubis pup		Zone 3_x
	X Anubis warrior	Zone 3_x
	X Mummy priest	Zone 3_x
	X Mummy warrior	Zone 3_x

	X Osiris			Zone 3_x (boss)

	===== Animals ====

	// EF
	X Cat			EF	Jail cell
	X Cow			EF	2_2
	X Dog			EF	Inn Upstairs
	X Bear			EF	Shack
	X Fox			EF	Lianna Back
	X Monkey		EF	3_0

	// (Boat)
	X Whale			EF => UR

	// UR
	X Giraffe		UR	Inn upstairs
	X Hippo			UR	1_0
	X Squid			UR	1_2
	X Snail			UR	2_1
	X Zebra			UR	2_2
	X Mouse			UR	3_2
	X Squirrel		UR	3_4

	// DM
	X Bat			DM	Inn upstairs
	X Bird			DM	1_1_a
	X Turtle		DM	2_0
	X Raccoon		DM	2_3
	X Rhino			DM	3_x
	X Sheep			DM	Home Godiva
	X Skunk			DM	Home Ralson

	// (Boat)
	X Duck			DM charter ship

	// CV
	X Beaver		CV Inn upstairs
	X Pig			CV Dark Inn Upstairs
	X Hedgehog		CV 
	X Horse			CV 
	X Koala			CV 
	X Panda			CV 
	X Parrot		CV 

	// LC
	X Bull			LC Inn upstairs
	X Chicken		LC 2_2
	X Lion			LC Church upstairs
	X MountainLion	LC 2_0
	X Tiger			LC 3_2
	X Wolf			LC 4_0_a
	X Worm			LC 1_1_a

	// FF
	X Bee			FF 1_x
	X Ladybug		FF 1_x
	X Dinosaur		FF 2_x
	X Lizard		FF 2_x
	X Snake			FF 3_x
	X Crocodile		FF 3_x
	X Tucan			FF Inn upstairs

	// BP
	Blowfish		BP	??
	Bunny			BP	??
	KillerWhale		BP	??
	Penguin			BP	??
	Reindeer		BP	??
	Yeti			BP	??
	Goat			BP	Town

	Spell ideas:
	- Hot potato health decrease

	WOOD		- T0 - EF
	COPPER		- T1 - EF
	STEEL		- T2 - UR
	GOLD		- T3 - DM
	MITHRIL		- T4 - DM
	CRYSTAL		- T5 - BP
	DEMONIC		- T6 - FF
	BONE		- T7 - LC
	VOID		- T8 - VS

	Ashen		- T7
	Battle		- T4
	Blue		- T4
	Candy		- T5
	Crystal		- T8
	Fang		- T4
	Gladiator	- > T2.5
	Gladius		- > T2.5
	Harbinger	- T6
	Iron		- > T1
	Katana		- T3
	Moon		- T3
	Rapier		- > T1.5
	Steel		- > T2
	Viking		- > T1.5
	War			- > T1.5

	Battle		-> T6
	Bone		-> T7
	Crystal		-> T8
	Flail		-> T5? if implemented? Just due to the fucking additional programming
	Iron		-> T2
	Judgement	-> T3
	Skull		-> T4
	Spiked		-> T1.5
	Wooden		-> T1

	Battle		-> T6
	Blue		-> T4
	Cleaver		-> T3
	Fire		-> T6
	Hand		-> T1
	HeadSplit	-> T8
	Hedge		-> T5
	Iron		-> T2
	Mithril		-> T5
	Rend		-> T4
	Scythe		-> T4
	Star		-> T3
	Steel		-> T2
	WoodC		-> T7

	Impaler		-> T5 due to gap in T5 weapons, I guess

	Arcane		-> T5
	Chieftains	-> T6
	Crystal		-> T8
	Cursed		-> T4
	Enchanted	-> T2
	Holy		-> T7
	Mana		-> T4
	Necro		-> T7
	Serpent		-> T3
	Taser		-> T5
	Witch		-> T1.5
	Wooden		-> T1

	Bone		-> T8
	Hunters		-> T1
	Composite	-> T2
	Olympus		-> T3
	War			-> T4
	Frost		-> T5
	Archers		-> T6
	Ivory		-> T7

	// Gems
	Quartz		- T2
	Emerald 	- T3
	Sapphire	- T4
	Diamond		- T5
	Ruby		- T6
	Sulfur		- T7

	// Metals
	Copper 		- T1		EF/UR
	Iron 		- T2		UR
	Tin 		- T2+		?
	Gold		- T3		DM	
	Mithril		- T5		CV
	Crystal		- T4		BP
	Sulf		- T6		FF
	Bone		- T7		LC
	Obsidian	- T8		VS

	// Alchemy
	Coal 		- T1

	// Weapons
	Wood/Copper
	Steel
	Gold
	Mithril
	Crystal
	Sulf
	Bone
	Void

	Obsidian	- T8
	*/

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
			// SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(GuanoPetrified::MapKey));
			// SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Gecky::MapKey));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Grim::MapKey));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));

			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySquallyEq, Value(8));
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
