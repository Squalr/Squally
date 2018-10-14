#include "HexusOpponentFrostFiend.h"

const std::string HexusOpponentFrostFiend::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FROST_FIEND";
HexusOpponentFrostFiend* HexusOpponentFrostFiend::instance = nullptr;

HexusOpponentFrostFiend* HexusOpponentFrostFiend::getInstance()
{
	if (HexusOpponentFrostFiend::instance == nullptr)
	{
		HexusOpponentFrostFiend::instance = new HexusOpponentFrostFiend();
	}

	return HexusOpponentFrostFiend::instance;
}

HexusOpponentFrostFiend::HexusOpponentFrostFiend() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Snow_Enemies_FrostFiend_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentFrostFiend::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0, 10, 0.33f, 0.33f,
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

HexusOpponentFrostFiend::~HexusOpponentFrostFiend()
{
}
