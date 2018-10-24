#include "HexusOpponentJack.h"

const std::string HexusOpponentJack::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_JACK";
HexusOpponentJack* HexusOpponentJack::instance = nullptr;

HexusOpponentJack* HexusOpponentJack::getInstance()
{
	if (HexusOpponentJack::instance == nullptr)
	{
		HexusOpponentJack::instance = new HexusOpponentJack();
	}

	return HexusOpponentJack::instance;
}

HexusOpponentJack::HexusOpponentJack() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Castle_Enemies_Jack_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(-32.0f, -64.0f),
	HexusOpponentJack::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.535f),
	HexusOpponentData::generateDeck(25, 0.535f,
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

HexusOpponentJack::~HexusOpponentJack()
{
}
