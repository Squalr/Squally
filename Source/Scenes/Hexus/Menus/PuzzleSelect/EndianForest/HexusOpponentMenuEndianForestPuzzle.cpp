////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuEndianForestPuzzle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/EndianForest/Centaur.h"
#include "Entities/Platformer/Enemies/EndianForest/Cyclops.h"
#include "Entities/Platformer/Enemies/EndianForest/GoblinGruntBoar.h"
#include "Entities/Platformer/Enemies/EndianForest/GoblinShaman.h"
#include "Entities/Platformer/Enemies/EndianForest/GoblinWarriorPig.h"
#include "Entities/Platformer/Enemies/EndianForest/KingGrogg.h"
#include "Entities/Platformer/Enemies/EndianForest/Ogre.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcBomber.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcGrunt.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcSwordsman.h"
#include "Entities/Platformer/Enemies/EndianForest/OrcWarrior.h"
#include "Entities/Platformer/Enemies/EndianForest/Troll.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/EndianForest/HexusChapterPreviewEndianForestPuzzle.h"

using namespace cocos2d;

HexusOpponentMenuEndianForestPuzzle* HexusOpponentMenuEndianForestPuzzle::instance = nullptr;

void HexusOpponentMenuEndianForestPuzzle::registerGlobalScene()
{
	if (HexusOpponentMenuEndianForestPuzzle::instance == nullptr)
	{
		HexusOpponentMenuEndianForestPuzzle::instance = new HexusOpponentMenuEndianForestPuzzle();

		HexusOpponentMenuEndianForestPuzzle::instance->autorelease();
		HexusOpponentMenuEndianForestPuzzle::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuEndianForestPuzzle::instance);
}

HexusOpponentMenuEndianForestPuzzle::HexusOpponentMenuEndianForestPuzzle() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleEndianForest, HexusChapterPreviewEndianForestPuzzle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Centaur::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Cyclops::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(GoblinGruntBoar::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(GoblinShaman::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(GoblinWarriorPig::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(KingGrogg::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ogre::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(OrcBomber::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(OrcGrunt::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(OrcSwordsman::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(OrcWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Troll::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuEndianForestPuzzle::~HexusOpponentMenuEndianForestPuzzle()
{
}
