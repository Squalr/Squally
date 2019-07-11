#include "HexusOpponentMenuSeaSharpCavernsPuzzle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/Barbarian.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/EarthElemental.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/EarthGolem.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/ForestGolem.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/Gorilla.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/LightningGolem.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/Rhinoman.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/Shaman.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/SkeletalArcher.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/SkeletalNecromancer.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/SkeletalWarrior.h"
#include "Entities/Platformer/Enemies/SeaSharpCaverns/TikiGolem.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/SeaSharpCaverns/HexusChapterPreviewSeaSharpCavernsPuzzle.h"

using namespace cocos2d;

HexusOpponentMenuSeaSharpCavernsPuzzle* HexusOpponentMenuSeaSharpCavernsPuzzle::instance = nullptr;

HexusOpponentMenuSeaSharpCavernsPuzzle* HexusOpponentMenuSeaSharpCavernsPuzzle::getInstance()
{
	if (HexusOpponentMenuSeaSharpCavernsPuzzle::instance == nullptr)
	{
		HexusOpponentMenuSeaSharpCavernsPuzzle::instance = new HexusOpponentMenuSeaSharpCavernsPuzzle();

		HexusOpponentMenuSeaSharpCavernsPuzzle::instance->autorelease();

		GlobalDirector::registerGlobalScene(HexusOpponentMenuSeaSharpCavernsPuzzle::instance);
	}

	return HexusOpponentMenuSeaSharpCavernsPuzzle::instance;
}

HexusOpponentMenuSeaSharpCavernsPuzzle::HexusOpponentMenuSeaSharpCavernsPuzzle() : super(HexusChapterPreviewSeaSharpCavernsPuzzle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(Barbarian::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(EarthElemental::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(EarthGolem::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(ForestGolem::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Gorilla::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(LightningGolem::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Rhinoman::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Shaman::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalArcher::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalNecromancer::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(SkeletalWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(TikiGolem::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuSeaSharpCavernsPuzzle::~HexusOpponentMenuSeaSharpCavernsPuzzle()
{
}
