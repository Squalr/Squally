#include "HexusOpponentMenuObelisk.h"

const std::string HexusOpponentMenuObelisk::StringKeyProgressSave = "SAVE_KEY_HEXUS_OBELISK_PROGRESS";

HexusOpponentMenuObelisk * HexusOpponentMenuObelisk::create()
{
	HexusOpponentMenuObelisk* instance = new HexusOpponentMenuObelisk();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuObelisk::HexusOpponentMenuObelisk() : HexusOpponentMenuBase(HexusOpponentMenuObelisk::StringKeyProgressSave)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuObelisk::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuObelisk::~HexusOpponentMenuObelisk()
{
}
