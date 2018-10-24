#include "HexusOpponentNecron.h"

const std::string HexusOpponentNecron::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_NECRON";
HexusOpponentNecron* HexusOpponentNecron::instance = nullptr;

HexusOpponentNecron* HexusOpponentNecron::getInstance()
{
	if (HexusOpponentNecron::instance == nullptr)
	{
		HexusOpponentNecron::instance = new HexusOpponentNecron();
	}

	return HexusOpponentNecron::instance;
}

HexusOpponentNecron::HexusOpponentNecron() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Obelisk_Npcs_Necron_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -72.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentNecron::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.84f),
	HexusOpponentData::generateDeck(25, 0.84f,
		{
			CardList::getInstance()->cardListByName->at(CardKeys::Addition),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentNecron::~HexusOpponentNecron()
{
}
