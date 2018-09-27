#include "HexusOpponentMenuJungle.h"

const std::string HexusOpponentMenuJungle::StringKeyProgressSave = "SAVE_KEY_HEXUS_JUNGLE_PROGRESS";

HexusOpponentMenuJungle * HexusOpponentMenuJungle::create()
{
	HexusOpponentMenuJungle* instance = new HexusOpponentMenuJungle();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuJungle::HexusOpponentMenuJungle() : HexusOpponentMenuBase(HexusOpponentMenuJungle::StringKeyProgressSave)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuJungle::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleBarbarian::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleDwarf::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleFighter::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleGeezer::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleHades::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJunglePeasant::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJunglePirate::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJunglePrincess::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleThor::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentJungleViking::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuJungle::~HexusOpponentMenuJungle()
{
}
