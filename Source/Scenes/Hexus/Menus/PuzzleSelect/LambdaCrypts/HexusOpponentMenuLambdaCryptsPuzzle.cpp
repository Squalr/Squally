#include "HexusOpponentMenuLambdaCryptsPuzzle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/BoneFiend.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Hunter.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/KingZul.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Mystic.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ReanimatedFighter.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/ReanimatedPig.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalBaron.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalCleaver.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalKnight.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/SkeletalPriestess.h"
#include "Entities/Platformer/Enemies/LambdaCrypts/Undead.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/LambdaCrypts/HexusChapterPreviewLambdaCryptsPuzzle.h"

using namespace cocos2d;

HexusOpponentMenuLambdaCryptsPuzzle* HexusOpponentMenuLambdaCryptsPuzzle::instance = nullptr;

HexusOpponentMenuLambdaCryptsPuzzle* HexusOpponentMenuLambdaCryptsPuzzle::getInstance()
{
	if (HexusOpponentMenuLambdaCryptsPuzzle::instance == nullptr)
	{
		HexusOpponentMenuLambdaCryptsPuzzle::instance = new HexusOpponentMenuLambdaCryptsPuzzle();

		HexusOpponentMenuLambdaCryptsPuzzle::instance->autorelease();

		GlobalDirector::registerGlobalScene(HexusOpponentMenuLambdaCryptsPuzzle::instance);
	}

	return HexusOpponentMenuLambdaCryptsPuzzle::instance;
}

HexusOpponentMenuLambdaCryptsPuzzle::HexusOpponentMenuLambdaCryptsPuzzle() : super(HexusChapterPreviewLambdaCryptsPuzzle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(BoneFiend::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Hunter::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(KingZul::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Mystic::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(ReanimatedFighter::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(ReanimatedPig::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalBaron::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalCleaver::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalKnight::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalPriestess::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Undead::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuLambdaCryptsPuzzle::~HexusOpponentMenuLambdaCryptsPuzzle()
{
}
