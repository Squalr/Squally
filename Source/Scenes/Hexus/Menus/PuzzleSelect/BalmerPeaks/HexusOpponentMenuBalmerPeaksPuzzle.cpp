////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuBalmerPeaksPuzzle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Cyrogen.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/FrostFiend.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/GoblinElf.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/IceGolem.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Krampus.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/PenguinGrunt.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/PenguinWarrior.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Santa.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/SnowFiend.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/ToySoldierGoblin.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/WaterElemental.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Yeti.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/YetiWarrior.h"
#include "Entities/Platformer/Helpers/BalmerPeaks/Snowman.h"
#include "Entities/Platformer/Helpers/BalmerPeaks/YetiBaby.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Cyrogen.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/FrostFiend.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/GoblinElf.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/IceGolem.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Krampus.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/PenguinGrunt.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/PenguinWarrior.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Santa.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/SnowFiend.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/ToySoldierGoblin.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/WaterElemental.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Yeti.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/YetiWarrior.h"
#include "Entities/Platformer/Helpers/BalmerPeaks/Snowman.h"
#include "Entities/Platformer/Helpers/BalmerPeaks/YetiBaby.h"
#include "Scenes/Hexus/Menus/ChapterSelect/BalmerPeaks/HexusChapterPreviewBalmerPeaksPuzzle.h"

using namespace cocos2d;

HexusOpponentMenuBalmerPeaksPuzzle* HexusOpponentMenuBalmerPeaksPuzzle::instance = nullptr;

void HexusOpponentMenuBalmerPeaksPuzzle::registerGlobalScene()
{
	if (HexusOpponentMenuBalmerPeaksPuzzle::instance == nullptr)
	{
		HexusOpponentMenuBalmerPeaksPuzzle::instance = new HexusOpponentMenuBalmerPeaksPuzzle();

		HexusOpponentMenuBalmerPeaksPuzzle::instance->autorelease();
		HexusOpponentMenuBalmerPeaksPuzzle::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuBalmerPeaksPuzzle::instance);
}

HexusOpponentMenuBalmerPeaksPuzzle::HexusOpponentMenuBalmerPeaksPuzzle() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleBalmerPeaks, HexusChapterPreviewBalmerPeaksPuzzle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Cyrogen::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(FrostFiend::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(GoblinElf::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(IceGolem::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Krampus::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PenguinGrunt::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PenguinWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Santa::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SnowFiend::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(ToySoldierGoblin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(WaterElemental::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Yeti::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(YetiWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Snowman::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(YetiBaby::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuBalmerPeaksPuzzle::~HexusOpponentMenuBalmerPeaksPuzzle()
{
}
