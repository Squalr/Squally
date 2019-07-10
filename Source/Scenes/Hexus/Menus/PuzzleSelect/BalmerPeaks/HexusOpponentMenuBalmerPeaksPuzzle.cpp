#include "HexusOpponentMenuBalmerPeaksPuzzle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Cyrogen.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/FrostFiend.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/GoblinElf.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/IceGolem.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/PenguinGrunt.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/PenguinWarrior.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Santa.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/SnowFiend.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/ToySoldierGoblin.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Viking.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/WaterElemental.h"
#include "Entities/Platformer/Enemies/BalmerPeaks/Yeti.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/BalmerPeaks/HexusChapterPreviewBalmerPeaksPuzzle.h"

using namespace cocos2d;

HexusOpponentMenuBalmerPeaksPuzzle* HexusOpponentMenuBalmerPeaksPuzzle::instance = nullptr;

HexusOpponentMenuBalmerPeaksPuzzle* HexusOpponentMenuBalmerPeaksPuzzle::getInstance()
{
	if (HexusOpponentMenuBalmerPeaksPuzzle::instance == nullptr)
	{
		HexusOpponentMenuBalmerPeaksPuzzle::instance = new HexusOpponentMenuBalmerPeaksPuzzle();

		HexusOpponentMenuBalmerPeaksPuzzle::instance->autorelease();

		GlobalDirector::registerGlobalScene(HexusOpponentMenuBalmerPeaksPuzzle::instance);
	}

	return HexusOpponentMenuBalmerPeaksPuzzle::instance;
}

HexusOpponentMenuBalmerPeaksPuzzle::HexusOpponentMenuBalmerPeaksPuzzle() : super(HexusChapterPreviewBalmerPeaksPuzzle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Cyrogen::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(FrostFiend::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(GoblinElf::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(IceGolem::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PenguinGrunt::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(PenguinWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Santa::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SnowFiend::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(ToySoldierGoblin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Viking::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(WaterElemental::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Yeti::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuBalmerPeaksPuzzle::~HexusOpponentMenuBalmerPeaksPuzzle()
{
}
