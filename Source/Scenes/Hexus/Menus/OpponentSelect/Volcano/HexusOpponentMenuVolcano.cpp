#include "HexusOpponentMenuVolcano.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Scenes/Hexus/Menus/ChapterSelect/Volcano/HexusChapterPreviewVolcano.h"
#include "Scenes/Hexus/Menus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Volcano/VolcanoHexusOpponents.h"

using namespace cocos2d;

HexusOpponentMenuVolcano* HexusOpponentMenuVolcano::instance = nullptr;

void HexusOpponentMenuVolcano::registerGlobalScene()
{
	if (HexusOpponentMenuVolcano::instance == nullptr)
	{
		HexusOpponentMenuVolcano::instance = new HexusOpponentMenuVolcano();

		HexusOpponentMenuVolcano::instance->autorelease();
		HexusOpponentMenuVolcano::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuVolcano::instance);
}

HexusOpponentMenuVolcano::HexusOpponentMenuVolcano() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::Volcano, HexusChapterPreviewVolcano::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentBrine::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLavaGolem::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentZelina::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonGhost::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAsh::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonRogue::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCeleste::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonShaman::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCindra::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonSwordsman::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentIgneus::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonDragon::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentLucifer::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonGrunt::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentMagnus::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentDemonWarrior::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPan::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentFireElemental::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentRagnis::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentScaldor::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAsmodeus::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuVolcano::~HexusOpponentMenuVolcano()
{
}
