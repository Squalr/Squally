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
	- Hexus bugs:
		- Win a hexus puzzle, next one will show massive row score deltas
		- Leave button stuck visible after losing a puzzle
		- Enemy should pre-calc the best play when player has passed (hard)
	- OVERWORLD ATTACKS:
		- Troll swing if you jump them
		- Cyclops swing if you jump them	
	- Camera harsh leaving camera targets (which?)
	- Can get stuck on roof of maps (see UR 3_1)
	- Sleeping Lycan face anim
	- Icons on title screen buttons (at least options, to reduce pains of wrong language selection)
	- Rerun “TODO” translations
	- Rhinoman fight too early. Need shaman enemy before, and maybe a puzzle/trap
	- Maybe give IOUs instead of cards as a prize, force players to purchase cards from Bars
	- Something feels off about torch puzzles. Colors? Give control over top and bottom? Hard to say, but rework it.
	- Mages guild accessible from all maps, but use the return portal. This incentivizes other travel (sky masters, boats)
		- Destroy all warp maps as a result (?) can still keep the zone portals for the return location
	- Kill Limestone temple map, replace with rare reward
	- Maybe hard code some rewards. It'd be nice to get SHL from the puzzle where you learn it.
	- Lexicon from menu
	- Seagulls should blink
	- Ursula is a lego bitch. Please fix.
	- Pan is a lego bitch too :^(
	- Torches should flicker by sky tower doors
	- Sky masters
	- Mystery crash / ensures when waiting on victory screen (matrix letters task func)
	- Enemy should not necessarily prio 0 bin/hex/dec cards when player has passed (unless they can make a 200 iq play)
	- No interrupt if damage attack modified to heal
	- Eliminate Collision Offset parameter entirely

	- Just get a few top down replacement maps in. Should be able to do this fairly seamlessly.
		- Invisible helpers. Some way to pull helpers into combat
	- 3Q Perspective
	- Reinstate Cipher with asm or something
	- Reinstate ball roll game? It wasn't really fixable
	- Interchangeable helpers from Inn map.
		- Helper abilities or something.
		- Helper equipment? Would fucking blow for menuing.

	- Necron hitbox wrong in Mages guild (inconsistent?)
	- Guano is behind the EF grass area gate (maybe after a layer xfer)
	- Maybe some mana gain on enemy kills? Literally any small amount. (maybe less of an issue w/ exp fix?)
	- Please god new anim system would be soo cool perf wise (especially on maps with a large number of entities)
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
		mapList.push_back(this->buildDebugButton("Balmer's Peak", MapResources::BallmerPeaks_Town_Main));
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

		// Show the electricity ON/OFF in Lions Cistern water visually somehow
		// Fix CMOV (railed spiked logs) on mac
		// Needs Dark Tiger scripting (Maybe recycle a SHL or SHR instead of a CMOV)

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
		mapList.push_back(this->buildDebugButton("Home Dawn (DM)", MapResources::DataMines_Home_Dawn));
		mapList.push_back(this->buildDebugButton("Home Finch (DM)", MapResources::DataMines_Home_Finch));
		mapList.push_back(this->buildDebugButton("Home Mildred (DM)", MapResources::DataMines_Home_Mildred));
		mapList.push_back(this->buildDebugButton("Zone_5_0 (DM)", MapResources::DataMines_Zone_5_0));
		mapList.push_back(this->buildDebugButton("Zone_3_3 (DM)", MapResources::DataMines_Zone_4_3));
		mapList.push_back(this->buildDebugButton("Zone_3_2 (DM)", MapResources::DataMines_Zone_4_2));
		mapList.push_back(this->buildDebugButton("Zone_3_1 (DM)", MapResources::DataMines_Zone_4_1));
		mapList.push_back(this->buildDebugButton("Zone_3_0 (DM)", MapResources::DataMines_Zone_4_0));
		mapList.push_back(this->buildDebugButton("Zone_2_3 (DM)", MapResources::DataMines_Zone_3_3));
		mapList.push_back(this->buildDebugButton("Zone_2_2 (DM)", MapResources::DataMines_Zone_3_2));
		mapList.push_back(this->buildDebugButton("Zone_2_1 (DM)", MapResources::DataMines_Zone_3_1));
		mapList.push_back(this->buildDebugButton("Zone_2_0 (DM)", MapResources::DataMines_Zone_3_0));
		mapList.push_back(this->buildDebugButton("Zone_2_5 (DM)", MapResources::DataMines_Zone_2_5));
		mapList.push_back(this->buildDebugButton("Zone_2_4 (DM)", MapResources::DataMines_Zone_2_4));
		mapList.push_back(this->buildDebugButton("Zone_2_3 (DM)", MapResources::DataMines_Zone_2_3));
		mapList.push_back(this->buildDebugButton("Zone_2_2 (DM)", MapResources::DataMines_Zone_2_2));
		mapList.push_back(this->buildDebugButton("Zone_2_1 (DM)", MapResources::DataMines_Zone_2_1));
		mapList.push_back(this->buildDebugButton("Zone_2_0 (DM)", MapResources::DataMines_Zone_2_0));
		mapList.push_back(this->buildDebugButton("Zone_1_2 (DM)", MapResources::DataMines_Zone_1_2));
		mapList.push_back(this->buildDebugButton("Zone_1_1 (DM)", MapResources::DataMines_Zone_1_1));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (DM)", MapResources::DataMines_Zone_1_0));

		// Traps: Crushing stone blocks trap
		// Finish restore power quest
		// Inn needs sign
		// Dawn home needs to be more regal
		// Make sure DH is properly gated before release
		// Needs Hexus fights
		// Needs Hexus puzzles
		// Skleletal archer arrow retrieval anim on shoot does not properly hide arrow
		
		/*
		Tiki Golem			=> X 1_1 Push/Pop const buff (call of the ancients - outgoing AND incoming damage)
		Shaman				=> X 1_2 AND (Shadow Bomb)
		[B] Rhinoman		=> O 4_3 <recycle> (Name)
		
		Forest golem		=> X 4_0 ROL (REJUVINATE)
		Earth golem			=> X 4_1 ROR (ROCKSLIDE)
		Earth Elemental		=> X 4_2 OR (REGERATION)
		
		Skeletal Pirate		=> X 3_2 XOR (BLIND)
		Skeletal Archer		=> X 2_1 PUSH / POP REG (MULTISHOT debuff - curse of the ancients - tick on targets)
		Skeletal Warrior	=> X 2_0 PUSH [REG PTR] / POP REG (blessing of the ancients - outgoing damage)
		Skeletal Necromancer => X 3_0 PUSH [REG PTR] / POP [REG PTR] (pact of the ancients - health link)
		[B] Krampus			=> O 3_3 NOT (No idea)

		Gorilla				=> Cage him and make him a prop (cursed person? again tho?)

		Jasper			?? (H) (swap with Cypress for spellbook)
		Alder			?
		Cypress			Technically in mage's guild
		Sarude			Technically in mage's guild

		Burch			Zone 3_x (H)

		Fraya			Town_Alch
		Brock			Town_BS
		Shen			Town_Inn
		Bonnie			Town_Inn (H) (non-vendor)

		Raka			Zone 2_3 (H)

		Princess Dawn	Town (H)
		Mildred			Town (H)
		Olive			Town (H)

		-- Stolen
		Finch			Flight Master
		*/

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 4 - Jumps/Loop/Test/more compares
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Castle Valgrind");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room (CV)", MapResources::CastleValgrind_Mages_Warp));
		mapList.push_back(this->buildDebugButton("Alch (CV)", MapResources::CastleValgrind_Town_Alch));
		mapList.push_back(this->buildDebugButton("Inn (CV)", MapResources::CastleValgrind_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (CV)", MapResources::CastleValgrind_Town_Smith));
		mapList.push_back(this->buildDebugButton("Town (CV)", MapResources::CastleValgrind_Town_Main));
		mapList.push_back(this->buildDebugButton("Study Dark (CV)", MapResources::CastleValgrind_Study_Dark));
		mapList.push_back(this->buildDebugButton("Study (CV)", MapResources::CastleValgrind_Study));
		mapList.push_back(this->buildDebugButton("Zone_2_3 (CV)", MapResources::CastleValgrind_Zone_2_3));
		mapList.push_back(this->buildDebugButton("Zone_2_2 (CV)", MapResources::CastleValgrind_Zone_2_2));
		mapList.push_back(this->buildDebugButton("Zone_2_1 (CV)", MapResources::CastleValgrind_Zone_2_1));
		mapList.push_back(this->buildDebugButton("Zone_2_0 (CV)", MapResources::CastleValgrind_Zone_2_0));
		mapList.push_back(this->buildDebugButton("Zone_1_2 (CV)", MapResources::CastleValgrind_Zone_1_2));
		mapList.push_back(this->buildDebugButton("Zone_1_1 (CV)", MapResources::CastleValgrind_Zone_1_1));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (CV)", MapResources::CastleValgrind_Zone_1_0));

		// Traps: Organ gun, cannon, catapult, ballista, heaven hug
		// Finish maps and corresponding "dark" maps (alternatively a game flag that is toggled to load in the correct layers)
		// Puzzles in dark maps can influence objects in normal maps. Typical inverse world puzzles.
		// WIP flow:
		// 	- Clock to go to dark side
		// 	- Study default locked
		// 	- Key is in the bar or something (maybe the barkeep has a hint about this)
		// 	- Secret room behind throne room (dark side only, helps make shit easier for me) leading to 2_x zones
		// Needs hexus battles
		// Needs hexus puzzles

		/*
		- CV - See http://unixwiz.net/techtips/x86-jumps.html because its hard to condense names and capture flags on the same chart.
			- Barbarian				1_x		=> jmp 			--
			- Thug					1_x		=> J[E]CXZ		%[E]CX = 0
			- ReanimatedFighter		1_x		=> J[N]E/Z		ZF
			- WereWolf				dark	=> J[N]P[E]		PF		// Odd or even! PF = 0 odd. All combinations valid except JNPE
			- Wraith				dark	=> J[N]S		SF		// Sign flag set if the FIRST operand is negative. Can be used to block negative damage.
			- Reaper				dark	=> J[N]O		OF
			- Vampiress				dark	=> J[N]G[E]		ZF/SF/OF
			- VampireLord			dark	=> J[N]L[E]		ZF/SF/OF
			- Abomination			2_x		=> J[N]B[E]		ZF/OF
			- SkeletalBaron			2_x		=> J[N]A[E]		ZF/OF
			- Jack					2_x		=> J[N]C		CF		// Immortality. Copy undying logic, but include a subtract.
			- [B] Agnes				2_x 	=> 
			
			- Garin					=> Train
			- King Redsong			=> Dark Throne
			- King Redsong Slime	=> Throne
			- Leopold				=> Alch
			- Mabel					=> Study
			- Merlin				=> XXXXX nope
			- Princess Opal			=> Throne
			- Raven					=> Inn
			- Thurstan				=> Smith
			- Gaunt					=> Main
			- Leroy					=> Main
			- Rogas					=> Main
			- Tyracius				=> Main
			- Zana					=> Main
		*/

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 5 - FPU
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Lambda Crypts");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room (LC)", MapResources::LambdaCrypts_Mages_Warp));
		mapList.push_back(this->buildDebugButton("Alch (LC)", MapResources::LambdaCrypts_Town_Alch));
		mapList.push_back(this->buildDebugButton("Inn (LC)", MapResources::LambdaCrypts_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (LC)", MapResources::LambdaCrypts_Town_Smith));
		mapList.push_back(this->buildDebugButton("Town (LC)", MapResources::LambdaCrypts_Town_Main));
		mapList.push_back(this->buildDebugButton("Zone_4_1 (LC)", MapResources::LambdaCrypts_Zone_4_1));
		mapList.push_back(this->buildDebugButton("Zone_4_0 (LC)", MapResources::LambdaCrypts_Zone_4_0));
		mapList.push_back(this->buildDebugButton("Zone_3_1 (LC)", MapResources::LambdaCrypts_Zone_3_1));
		mapList.push_back(this->buildDebugButton("Zone_3_0 (LC)", MapResources::LambdaCrypts_Zone_3_0));
		mapList.push_back(this->buildDebugButton("Zone_2_2 (LC)", MapResources::LambdaCrypts_Zone_2_2));
		mapList.push_back(this->buildDebugButton("Zone_2_1 (LC)", MapResources::LambdaCrypts_Zone_2_1));
		mapList.push_back(this->buildDebugButton("Zone_2_0_a (LC)", MapResources::LambdaCrypts_Zone_2_0_a));
		mapList.push_back(this->buildDebugButton("Zone_2_0 (LC)", MapResources::LambdaCrypts_Zone_2_0));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (LC)", MapResources::LambdaCrypts_Zone_1_0));

		// Traps: floating bombs, guillotine, spiked pendulum, spiked rotators
		// Needs enemy scripting according to notes on which instructions this zone covers
		// Needs hexus puzzles
		// 3x more enemies than is standard, which makes this harder
		// 3 crypts that need to be cleared. Can either be "orderless" or force linearity with keys.
		//	- town key (rusty?), bone key, demon key, This helps force a progression of 1_x => town => 2_x => 3x		
		// 1_x overworld enemies (zombie, pig, undead)
		// 2_x assassin, fiend, mystic (left crypt / hole)
			// TODO: Maybe redo this as a dirt environment, to differentiate it from crypts and break up LC repetativeness
		// 3_x warlock, hunter, knight (right crypt, unlock w/ bone)
		// 4_x cleaver, knight, priestess (central crypt, unlock w/ demon)
		// Dual boss with King Zul and Lazarus. Give Lazarus a rez or self rez?

		/*
		- BoneFiend				=>  
		- Hunter				=>  
		- ZombieElric			=>  
		- ReanimatedPig			=>  
		- Mystic				=>  
		- Zombie				=>  
		- Undead				=>  
		- [B] Lazarus			=> 
		- SkeletalPriestess		=>  
		- SkeletalKnight		=>  
		- SkeletalCleaver		=>  
		- [B] KingZul			=>  
		*/

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 6 - XMM*
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Daemons' Hallow");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room (DH)", MapResources::DaemonsHallow_Mages_Warp));
		mapList.push_back(this->buildDebugButton("Town Main (DH)", MapResources::DaemonsHallow_Town_Main));
		mapList.push_back(this->buildDebugButton("Alch (DH)", MapResources::DaemonsHallow_Town_Alch));
		mapList.push_back(this->buildDebugButton("Inn (DH)", MapResources::DaemonsHallow_Town_Inn));
		mapList.push_back(this->buildDebugButton("Smith (DH)", MapResources::DaemonsHallow_Town_Smith));
		mapList.push_back(this->buildDebugButton("Zone_3_1 (DH)", MapResources::DaemonsHallow_Zone_3_1));
		mapList.push_back(this->buildDebugButton("Zone_3_0 (DH)", MapResources::DaemonsHallow_Zone_3_0));
		mapList.push_back(this->buildDebugButton("Zone_2_3 (DH)", MapResources::DaemonsHallow_Zone_2_3));
		mapList.push_back(this->buildDebugButton("Zone_2_2 (DH)", MapResources::DaemonsHallow_Zone_2_2));
		mapList.push_back(this->buildDebugButton("Zone_2_1 (DH)", MapResources::DaemonsHallow_Zone_2_1));
		mapList.push_back(this->buildDebugButton("Zone_2_0 (DH)", MapResources::DaemonsHallow_Zone_2_0));
		mapList.push_back(this->buildDebugButton("Zone_1_4 (DH)", MapResources::DaemonsHallow_Zone_1_4));
		mapList.push_back(this->buildDebugButton("Zone_1_3 (DH)", MapResources::DaemonsHallow_Zone_1_3));
		mapList.push_back(this->buildDebugButton("Zone_1_2 (DH)", MapResources::DaemonsHallow_Zone_1_2));
		mapList.push_back(this->buildDebugButton("Zone_1_1 (DH)", MapResources::DaemonsHallow_Zone_1_1));
		mapList.push_back(this->buildDebugButton("Zone_1_0_a (DH)", MapResources::DaemonsHallow_Zone_1_0_a));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (DH)", MapResources::DaemonsHallow_Zone_1_0));

		// Traps: Fire bird, fire launcher, TNT barrel, mortar
		// Hexus puzzles
		// Hexus fights
		// 1_x should be the initial overworld + caves (Dragon, Ghost, Elemental, Golem)
		// 2_x should be more caves connecting town to the 3_x maps (Shaman, Swordsman, Rogue)
		// 3_x is all overworld (Tiger, Warrior, Grunt, Archer)

		/*
			Surface:
			- DemonRogue			=>  1_X
			- DemonShaman			=>  1_X
			- DemonSwordsman		=>  1_X
			
			Caves:
			- DemonDragon			=>  2_X
			- DemonGhost			=>  2_X
			- FireElemental			=>  2_X
			- LavaGolem				=>  2_X
			
			Surface 2?
			- DemonArcher			=>  3_X
			- DemonGrunt			=>  3_X
			- DemonWarrior			=>  3_X
			- FireTiger				=>  3_X
			
			- [B] Asmodeus			=> 	4_X
			
			-----------------
			
			- Ash				=> 1_x (H)
			
			- Hades				=> 2_x (H)
			
			- Cindra			=> 3_x (barricade)(H?)
			- Scaldor			=> 3_x (barricade)(H?)
			- Magnus			=> 3_x (barricade)(H?)
			
			- Mittens			=> 2_x (H)
			- Celeste			=> 3_x (barricade)(H?)
			
			- Lucifer			=> Town (H)
			- Brine				=> Town_Main (Exterior) (H)
			- Queen Elise		=> Town_Main
			- Pan				=> Alch
			- Ragnis			=> Smith
			- Thatcher			=> Inn
		*/

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 7 - Jumps/More compares
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

		// Traps: Icicle, bear trap (?), { cannon or catapult or portal } (to VS)
		// Vertical town (maybe two sections, one inaccessible at first to spread out NPCs)
		// 1_x typical EF style outdoors leading to town (viking, penguin grunt, penguin warrior, frost fiend (technically in 3_x))
		// 2_x for some frost caverns (ice golem, water elemental, yeti) => cryogen
		// 3_x for blizzard environment? (goblin elf, toy soldier goblin, snow fiend) => santa => sky cannon

		/*
		O Aspen
		O Bodom
		X Cookie => Santa
		X Cooper => Inn
		X Jingles => Santa
		O Juniper
		X Kringle => Santa
		X Luna => alch
		O Nessie
		O Princess Pepper
		X Theldar => smith
		X Tinsel => Santa
		O Ysara
		X Irmik => SkyMaster

		- PenguinGrunt		1_x		=> jmp 			--
		- PenguinWarrior	1_x		=> J[E]CXZ		%[E]CX = 0
		- Viking			1_x		=> J[N]E/Z		ZF
		- IceGolem			2_x		=> J[N]P[E]		PF		// Odd or even! PF = 0 odd. All combinations valid except JNPE
		- Yeti				2_x		=> J[N]S		SF		// Sign flag set if the FIRST operand is negative. Can be used to block negative damage.
		- WaterElemental	2_x		=> J[N]O		OF
		- FrostFiend		2_x 	=> J[N]G[E]		ZF/SF/OF
		- GoblinElf			3_x		=> J[N]L[E]		ZF/SF/OF
		- ToySoldierGoblin	3_x		=> J[N]B[E]		ZF/OF
		- SnowFiend			3_x		=> J[N]A[E]		ZF/OF
		- [B?] Santa		3_x		=> J[N]C		CF		// Immortality. Copy undying logic, but include a subtract.
		- [B] Cryogen		3_x 	=> 

		*/

		// Needs enemy scripting according to notes on which instructions this zone covers
		// Needs hexus puzzles

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	// CHAPTER 8 - bswap? lol
	{
		ClickableTextNode* titleButton = this->buildTitleButton("Void Star");
		std::vector<ClickableTextNode*> mapList = std::vector<ClickableTextNode*>();
		ScrollPane* scrollPane = this->buildScrollPane();

		mapList.push_back(this->buildDebugButton("Warp Room (VS)", MapResources::VoidStar_Mages_Warp));
		mapList.push_back(this->buildDebugButton("Alch (VS)", MapResources::VoidStar_Town_Alch));
		mapList.push_back(this->buildDebugButton("Smith (VS)", MapResources::VoidStar_Town_Smith));
		mapList.push_back(this->buildDebugButton("Town (VS)", MapResources::VoidStar_Town_Main));
		mapList.push_back(this->buildDebugButton("Zone_1_0 (VS)", MapResources::VoidStar_Zone_1_0));

		// Likely just 1-2 interim maps before boss. Keep this zone really short.
		// Traps: Laser
		// Needs enemy scripting according to notes on which instructions this zone covers
		// Needs hexus puzzles

		this->chapterDebugInfoList.push_back(ChapterDebugInfo(titleButton, mapList, scrollPane));
	}

	/*
	TRANSITIONS:
	- EF => EF LimeStone (blimp 1) - ??????
	- EF => CV (blimp 2) - Finch
	- CV => BP (blimp 3) - Irmik
	- CV => LC (train) - Garin
	- DM => DH (viking ship or smth) - Drak
	- BP => BP (viking ship or smth) - <Any>

	- RELOCATED:
		- Abomination			=>  
		- Assassin				=>  
		- BoneKnight			=>  
		- DarkTiger				=>  
		- Exterminator			=>  
		- Gargoyle				=>  
		- LightningGolem		=>  
		- Shade					=>  
		- VoidArcher			=>  
		- VoidDemon				=>  

	- VS - LOOP / CALL / RET
		- [B] EvilEye			=>  

	======================

	Puzzles:
	A				EF	2_0		orc-grunt
	B				EF	2_2		
	C				EF	2_4_a
	D				EF	2_4
	E				EF	2_6
	F				EF	3_0
	G				EF	3_1

	Level order / Mage
	EF		//	Fraya? Mabel?
	UR		//	Alder
	DM		//	Cypress
	CV		//	Merlin
	BP		//	Aster
	DH		//	Igneus
	LC		//	Necron
	VS		//	Marcel

	////////// UR //////////

	------------------------

	Lioness			Zone 1_x
	LionMan			Zone 1_x
	Tigress			Zone 1_x
	TigerMan		Zone 1_x

	Medusa			Zone 2_x
	Mermaid			Zone 2_x
	Minotaur		Zone 2_x

	Anubis pup		Zone 3_x
	Anubis warrior	Zone 3_x
	Mummy priest	Zone 3_x
	Mummy warrior	Zone 3_x

	Osiris			Zone 3_x (boss)

	Omit these:
	Alder			_dupe_
	Cypress			_dupe_ Zone x_x (spellbook)
	Sarude			_dupe_

	====== SPELLBOOKS ======

	Water - EF
	Wind - EF
	Lightning - UR
	Holy - UR
	Nature - Mines?
	<none in castle>
	Fire - Daemons
	Frost - Ballmer
	Shadow - Crypts
	Arcane - Void?

	===== Animals ====

	// EF
	Cat				EF	Jail cell
	Cow				EF	2_2
	Dog				EF	Inn Upstairs
	Duck			EF	!!!!!!!! UNPLACED
	Bear			EF	Shack
	Fox				EF	Lianna Back
	Monkey			EF	3_0

	// (Boat)
	Whale			EF => UR

	// UR
	Giraffe			UR	Inn upstairs
	Hippo			UR	1_0
	Squid			UR	1_2
	Snail			UR	2_1
	Zebra			UR	2_2
	Mouse			UR	3_2
	Squirrel		UR	3_4

	// DM
	Bat				DM	1_x
	Bird			DM	1_x
	Pig				DM	2_x
	Raccoon			DM	2_x
	Rhino			DM	3_x
	Sheep			DM	3_x
	Skunk			DM	Town

	// BP
	Blowfish		BP	??
	Bunny			BP	??
	KillerWhale		BP	??
	Penguin			BP	??
	Reindeer		BP	??
	Yeti			BP	??
	Goat			BP	Town

	// DH
	Bee				DH 1_x
	Crocodile		DH 1_x
	Dinosaur		DH 2_x
	Ladybug			DH 2_x
	Lizard			DH 3_x
	Snake			DH 3_x
	Tucan			DH Town

	// LC
	Bull
	Chicken
	Lion
	MountainLion
	Tiger
	Wolf
	Worm

	// VS
	Beaver
	Hedgehog
	Horse
	Koala
	Panda
	Parrot
	Turtle

	- 1 freebie
	- 1 swim hax
	- 1 in Lianna’s house backdoor
	- 1 by old man
	- 1 on the path to Gorgon (wind)
	- 1 in the inn, somehow or another

	- 1 on ship

	50 / 8 = 6 per zone, 2 bonus (probably on ships)

	Spell ideas:
	- Call of the Dead (skele's attacking from portal under target) - https://www.gamedevmarket.net/asset/skeleton-warrior-mega-game-sprite-pack/
	- Bat attack AoE (Ch4)
	- Hot potato health decrease
	- Blind (details tbd)

	WOOD		- T0 - EF
	COPPER		- T1 - EF
	STEEL		- T2 - UR
	GOLD		- T3 - DM
	MITHRIL		- T4 - DM
	CRYSTAL		- T5 - BP
	DEMONIC		- T6 - DH
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


	Archers		-> T6
	Bone		-> T8
	Frost		-> T5
	Hunters		-> T1
	Composite	-> T2
	Ivory		-> T7
	Olympus		-> T3
	War			-> T4

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
	Sulf		- T6		DH
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

			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookArcane, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookFire, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookFrost, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookHoly, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookLightning, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookNature, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookShadow, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWater, Value(true));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeySpellBookWind, Value(true));
			
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Guano::MapKey));
			// SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(Gecky::MapKey));
			
			// SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyHelperName, Value(GuanoPetrified::MapKey));
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyScrappyFound, Value(true));
			
			SaveManager::SoftSaveProfileData(SaveKeys::SaveKeyRespawnMap, Value(mapResource));

			PlatformerMap* map = PlatformerMap::create();

			map->loadMap(mapResource);

			return map;
		}));
	});

	return clickableTextNode;
}
