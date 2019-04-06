////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuVoidStarPuzzle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/VoidStar/Barbarian.h"
#include "Entities/Platformer/Enemies/VoidStar/EvilEye.h"
#include "Entities/Platformer/Enemies/VoidStar/Exterminator.h"
#include "Entities/Platformer/Enemies/VoidStar/Gorilla.h"
#include "Entities/Platformer/Enemies/VoidStar/MechBoxDrone.h"
#include "Entities/Platformer/Enemies/VoidStar/MechDog.h"
#include "Entities/Platformer/Enemies/VoidStar/MechGolem.h"
#include "Entities/Platformer/Enemies/VoidStar/MechGuard.h"
#include "Entities/Platformer/Enemies/VoidStar/MiteBot.h"
#include "Entities/Platformer/Enemies/VoidStar/SkeletalPirate.h"
#include "Entities/Platformer/Enemies/VoidStar/Thug.h"
#include "Entities/Platformer/Enemies/VoidStar/Viking.h"
#include "Entities/Platformer/Enemies/VoidStar/VikingBot.h"
#include "Entities/Platformer/Enemies/VoidStar/VikingBotSmall.h"
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
	this->opponents.push_back(HexusOpponentPreview::create(Barbarian::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(EvilEye::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Exterminator::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Gorilla::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MechBoxDrone::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MechDog::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MechGolem::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MechGuard::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MiteBot::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalPirate::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Thug::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Viking::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(VikingBot::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(VikingBotSmall::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuVoidStarPuzzle::~HexusOpponentMenuVoidStarPuzzle()
{
}
