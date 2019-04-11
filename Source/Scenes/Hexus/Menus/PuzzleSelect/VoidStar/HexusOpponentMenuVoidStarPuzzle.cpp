////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuVoidStarPuzzle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/VoidStar/Assassin.h"
#include "Entities/Platformer/Enemies/VoidStar/BoneFiend.h"
#include "Entities/Platformer/Enemies/VoidStar/BoneKnight.h"
#include "Entities/Platformer/Enemies/VoidStar/EvilEye.h"
#include "Entities/Platformer/Enemies/VoidStar/Exterminator.h"
#include "Entities/Platformer/Enemies/VoidStar/Grep.h"
#include "Entities/Platformer/Enemies/VoidStar/Hunter.h"
#include "Entities/Platformer/Enemies/VoidStar/Mittens.h"
#include "Entities/Platformer/Enemies/VoidStar/Mystic.h"
#include "Entities/Platformer/Enemies/VoidStar/Teddy.h"
#include "Entities/Platformer/Enemies/VoidStar/Unicorn.h"
#include "Entities/Platformer/Enemies/VoidStar/Warlock.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/VoidStar/HexusChapterPreviewVoidStarPuzzle.h"

using namespace cocos2d;

HexusOpponentMenuVoidStarPuzzle* HexusOpponentMenuVoidStarPuzzle::instance = nullptr;

void HexusOpponentMenuVoidStarPuzzle::registerGlobalScene()
{
	if (HexusOpponentMenuVoidStarPuzzle::instance == nullptr)
	{
		HexusOpponentMenuVoidStarPuzzle::instance = new HexusOpponentMenuVoidStarPuzzle();

		HexusOpponentMenuVoidStarPuzzle::instance->autorelease();
		HexusOpponentMenuVoidStarPuzzle::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuVoidStarPuzzle::instance);
}

HexusOpponentMenuVoidStarPuzzle::HexusOpponentMenuVoidStarPuzzle() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleVoidStar, HexusChapterPreviewVoidStarPuzzle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Assassin::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(BoneFiend::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(BoneKnight::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(EvilEye::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Exterminator::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Grep::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Hunter::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Mittens::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Mystic::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Teddy::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Unicorn::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Warlock::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuVoidStarPuzzle::~HexusOpponentMenuVoidStarPuzzle()
{
}
