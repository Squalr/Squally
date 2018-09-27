#include "HexusOpponentMenuCastle.h"

const std::string HexusOpponentMenuCastle::StringKeyProgressSave = "SAVE_KEY_HEXUS_CASTLE_PROGRESS";

HexusOpponentMenuCastle * HexusOpponentMenuCastle::create()
{
	HexusOpponentMenuCastle* instance = new HexusOpponentMenuCastle();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuCastle::HexusOpponentMenuCastle() : HexusOpponentMenuBase(HexusOpponentMenuCastle::StringKeyProgressSave)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuCastle::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuCastle::~HexusOpponentMenuCastle()
{
}
