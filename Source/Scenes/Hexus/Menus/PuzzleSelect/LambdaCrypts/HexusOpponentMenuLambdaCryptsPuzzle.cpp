////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED DO NOT EDIT. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
////////////////////////////////////////////////////////////////////////////////////////////

#include "HexusOpponentMenuLambdaCryptsPuzzle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Abomination.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Gargoyle.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/KingZul.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ReanimatedFighter.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ReanimatedPig.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalBaron.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalCleaver.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalKnight.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalPriestess.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Undead.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/VoidArcher.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/VoidDemon.h"
#include "Entities/Platformer/Helpers/LambdaCrypts/Ghost.h"
#include "Entities/Platformer/Helpers/LambdaCrypts/Grim.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Abomination.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Gargoyle.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/KingZul.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ReanimatedFighter.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ReanimatedPig.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalBaron.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalCleaver.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalKnight.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalPriestess.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Undead.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/VoidArcher.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/VoidDemon.h"
#include "Entities/Platformer/Helpers/LambdaCrypts/Ghost.h"
#include "Entities/Platformer/Helpers/LambdaCrypts/Grim.h"
#include "Scenes/Hexus/Menus/ChapterSelect/LambdaCrypts/HexusChapterPreviewLambdaCryptsPuzzle.h"

using namespace cocos2d;

HexusOpponentMenuLambdaCryptsPuzzle* HexusOpponentMenuLambdaCryptsPuzzle::instance = nullptr;

void HexusOpponentMenuLambdaCryptsPuzzle::registerGlobalScene()
{
	if (HexusOpponentMenuLambdaCryptsPuzzle::instance == nullptr)
	{
		HexusOpponentMenuLambdaCryptsPuzzle::instance = new HexusOpponentMenuLambdaCryptsPuzzle();

		HexusOpponentMenuLambdaCryptsPuzzle::instance->autorelease();
		HexusOpponentMenuLambdaCryptsPuzzle::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuLambdaCryptsPuzzle::instance);
}

HexusOpponentMenuLambdaCryptsPuzzle::HexusOpponentMenuLambdaCryptsPuzzle() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::PuzzleLambdaCrypts, HexusChapterPreviewLambdaCryptsPuzzle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Abomination::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Gargoyle::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(KingZul::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(ReanimatedFighter::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(ReanimatedPig::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalBaron::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalCleaver::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalKnight::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalPriestess::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Undead::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(VoidArcher::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(VoidDemon::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Ghost::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Grim::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuLambdaCryptsPuzzle::~HexusOpponentMenuLambdaCryptsPuzzle()
{
}
