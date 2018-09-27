#include "HexusOpponentMenuTraining.h"

const std::string HexusOpponentMenuTraining::StringKeyProgressSave = "SAVE_KEY_HEXUS_TRAINING_PROGRESS";

HexusOpponentMenuTraining * HexusOpponentMenuTraining::create()
{
	HexusOpponentMenuTraining* instance = new HexusOpponentMenuTraining();

	instance->autorelease();

	return instance;
}

HexusOpponentMenuTraining::HexusOpponentMenuTraining() : HexusOpponentMenuBase(HexusOpponentMenuTraining::StringKeyProgressSave)
{
	auto callback = CC_CALLBACK_1(HexusOpponentMenuTraining::onGameEndCallback, this);

	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps));
	this->opponents.push_back(HexusOpponentPreview::create(HexusOpponentCentaur::getInstance(), callback, Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));

	for (std::vector<HexusOpponentPreview*>::iterator it = this->opponents.begin(); it != this->opponents.end(); ++it)
	{
		this->scrollPane->addChild(*it);
	}
}

HexusOpponentMenuTraining::~HexusOpponentMenuTraining()
{
}
