#include "HexusOpponentMenuUnderflowRuinsPuzzle.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/AnubisPup.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/AnubisWarrior.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/LionMan.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Lioness.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Medusa.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Mermaid.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Minotaur.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/MummyPriest.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/MummyWarrior.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Osiris.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/TigerMan.h"
#include "Entities/Platformer/Enemies/UnderflowRuins/Tigress.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Menus/ChapterSelect/UnderflowRuins/HexusChapterPreviewUnderflowRuinsPuzzle.h"

using namespace cocos2d;

HexusOpponentMenuUnderflowRuinsPuzzle* HexusOpponentMenuUnderflowRuinsPuzzle::instance = nullptr;

HexusOpponentMenuUnderflowRuinsPuzzle* HexusOpponentMenuUnderflowRuinsPuzzle::getInstance()
{
	if (HexusOpponentMenuUnderflowRuinsPuzzle::instance == nullptr)
	{
		HexusOpponentMenuUnderflowRuinsPuzzle::instance = new HexusOpponentMenuUnderflowRuinsPuzzle();

		HexusOpponentMenuUnderflowRuinsPuzzle::instance->autorelease();

		GlobalDirector::registerGlobalScene(HexusOpponentMenuUnderflowRuinsPuzzle::instance);
	}

	return HexusOpponentMenuUnderflowRuinsPuzzle::instance;
}

HexusOpponentMenuUnderflowRuinsPuzzle::HexusOpponentMenuUnderflowRuinsPuzzle() : super(HexusChapterPreviewUnderflowRuinsPuzzle::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(AnubisPup::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(AnubisWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(LionMan::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Lioness::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Medusa::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Mermaid::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Minotaur::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MummyPriest::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(MummyWarrior::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Osiris::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(TigerMan::getHexusOpponentData()));
	this->opponents.push_back(HexusOpponentPreview::create(Tigress::getHexusOpponentData()));

	this->buildOpponentList();
}

HexusOpponentMenuUnderflowRuinsPuzzle::~HexusOpponentMenuUnderflowRuinsPuzzle()
{
}
