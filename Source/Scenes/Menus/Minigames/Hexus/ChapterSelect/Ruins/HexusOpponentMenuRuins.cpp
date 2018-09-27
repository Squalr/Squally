#include "HexusOpponentMenuRuins.h"

const std::string HexusOpponentMenuRuins::StringKeyProgressSave = "SAVE_KEY_HEXUS_RUINS_PROGRESS";

HexusOpponentMenuRuins * HexusOpponentMenuRuins::create()
{
	HexusOpponentMenuRuins* instance = new HexusOpponentMenuRuins();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuRuins::HexusOpponentMenuRuins() : HexusOpponentMenuBase(HexusOpponentMenuRuins::StringKeyProgressSave)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuRuins::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuRuins::~HexusOpponentMenuRuins()
{
}
