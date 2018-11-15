#include "HexusOpponentMagnus.h"

const std::string HexusOpponentMagnus::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MAGNUS";
HexusOpponentMagnus* HexusOpponentMagnus::instance = nullptr;

HexusOpponentMagnus* HexusOpponentMagnus::getInstance()
{
	if (HexusOpponentMagnus::instance == nullptr)
	{
		HexusOpponentMagnus::instance = new HexusOpponentMagnus();
	}

	return HexusOpponentMagnus::instance;
}

HexusOpponentMagnus::HexusOpponentMagnus() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Volcano_Npcs_Magnus_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -24.0f),
	HexusOpponentMagnus::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.75f),
	HexusOpponentData::generateDeck(25, 0.75f,
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

HexusOpponentMagnus::~HexusOpponentMagnus()
{
}
