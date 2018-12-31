#include "HexusOpponentMenuIceCaps.h"

#include "Engine/GlobalDirector.h"
#include "Engine/UI/Controls/ScrollPane.h"
#include "Menus/Hexus/ChapterSelect/IceCaps/HexusChapterPreviewIceCaps.h"
#include "Menus/Hexus/OpponentSelect/HexusOpponentPreview.h"
#include "Scenes/Hexus/Opponents/Snow/SnowHexusOpponents.h"

using namespace cocos2d;

HexusOpponentMenuIceCaps* HexusOpponentMenuIceCaps::instance = nullptr;

void HexusOpponentMenuIceCaps::registerGlobalScene()
{
	if (HexusOpponentMenuIceCaps::instance == nullptr)
	{
		HexusOpponentMenuIceCaps::instance = new HexusOpponentMenuIceCaps();

		HexusOpponentMenuIceCaps::instance->autorelease();
		HexusOpponentMenuIceCaps::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(HexusOpponentMenuIceCaps::instance);
}

HexusOpponentMenuIceCaps::HexusOpponentMenuIceCaps() : super(NavigationEvents::NavigateHexusOpponentSelectArgs::Chapter::IceCaps, HexusChapterPreviewIceCaps::SaveKeyChapterName)
{
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentToySoldierGoblin::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentNessie::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentYeti::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAspen::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPenguinGrunt::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentAster::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentGoblinElf::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCookie::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPenguinWarrior::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentIrmik::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentYetiWarrior::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJingles::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentIceGolem::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJuniper::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentFrostFiend::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentKringle::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentWaterElemental::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTinsel::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSnowFiend::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentTheldar::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentPrincessPepper::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentSanta::getInstance()));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCryogen::getInstance()));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuIceCaps::~HexusOpponentMenuIceCaps()
{
}
