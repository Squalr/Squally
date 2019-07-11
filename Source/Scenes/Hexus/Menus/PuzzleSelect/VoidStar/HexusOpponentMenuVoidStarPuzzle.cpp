#include "HexusOpponentMenuVoidStarPuzzle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/VoidStar/Abomination.h"
#include "Entities/Platformer/Enemies/VoidStar/Assassin.h"
#include "Entities/Platformer/Enemies/VoidStar/BoneKnight.h"
#include "Entities/Platformer/Enemies/VoidStar/DarkTiger.h"
#include "Entities/Platformer/Enemies/VoidStar/EvilEye.h"
#include "Entities/Platformer/Enemies/VoidStar/Exterminator.h"
#include "Entities/Platformer/Enemies/VoidStar/Gargoyle.h"
#include "Entities/Platformer/Enemies/VoidStar/Shade.h"
#include "Entities/Platformer/Enemies/VoidStar/VoidArcher.h"
#include "Entities/Platformer/Enemies/VoidStar/VoidDemon.h"
#include "Entities/Platformer/Enemies/VoidStar/Warlock.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/VoidStar/HexusChapterPreviewVoidStarPuzzle.h"

using namespace cocos2d;

HexusOpponentMenuVoidStarPuzzle* HexusOpponentMenuVoidStarPuzzle::instance = nullptr;

HexusOpponentMenuVoidStarPuzzle* HexusOpponentMenuVoidStarPuzzle::getInstance()
{
	if (HexusOpponentMenuVoidStarPuzzle::instance == nullptr)
	{
		HexusOpponentMenuVoidStarPuzzle::instance = new HexusOpponentMenuVoidStarPuzzle();

		HexusOpponentMenuVoidStarPuzzle::instance->autorelease();

		GlobalDirector::registerGlobalScene(HexusOpponentMenuVoidStarPuzzle::instance);
	}

	return HexusOpponentMenuVoidStarPuzzle::instance;
}

HexusOpponentMenuVoidStarPuzzle::HexusOpponentMenuVoidStarPuzzle() : super(HexusChapterPreviewVoidStarPuzzle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Abomination::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Assassin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(BoneKnight::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(DarkTiger::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(EvilEye::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Exterminator::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Gargoyle::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Shade::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(VoidArcher::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(VoidDemon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Warlock::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuVoidStarPuzzle::~HexusOpponentMenuVoidStarPuzzle()
{
}
