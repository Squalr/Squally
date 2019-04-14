////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuDaemonsHallowPuzzle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/Asmodeus.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/CritterDemon.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonDragon.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonGhost.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonGrunt.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonRogue.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonShaman.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonSwordsman.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/DemonWarrior.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/FireElemental.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/Krampus.h"
#include "Entities/Platformer/Enemies/DaemonsHallow/LavaGolem.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/DaemonsHallow/HexusChapterPreviewDaemonsHallowPuzzle.h"

using namespace cocos2d;

HexusOpponentMenuDaemonsHallowPuzzle* HexusOpponentMenuDaemonsHallowPuzzle::instance = nullptr;

void HexusOpponentMenuDaemonsHallowPuzzle::registerGlobalScene()
{
	if (HexusOpponentMenuDaemonsHallowPuzzle::instance == nullptr)
	{
		HexusOpponentMenuDaemonsHallowPuzzle::instance = new HexusOpponentMenuDaemonsHallowPuzzle();

		HexusOpponentMenuDaemonsHallowPuzzle::instance->autorelease();
		HexusOpponentMenuDaemonsHallowPuzzle::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuDaemonsHallowPuzzle::instance);
}

HexusOpponentMenuDaemonsHallowPuzzle::HexusOpponentMenuDaemonsHallowPuzzle() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleDaemonsHallow, HexusChapterPreviewDaemonsHallowPuzzle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Asmodeus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(CritterDemon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(DemonDragon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(DemonGhost::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(DemonGrunt::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(DemonRogue::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(DemonShaman::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(DemonSwordsman::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(DemonWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(FireElemental::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Krampus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(LavaGolem::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuDaemonsHallowPuzzle::~HexusOpponentMenuDaemonsHallowPuzzle()
{
}
