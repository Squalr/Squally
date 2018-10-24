#include "HexusOpponentCentaur.h"

const std::string HexusOpponentCentaur::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CENTAUR";
HexusOpponentCentaur* HexusOpponentCentaur::instance = nullptr;

HexusOpponentCentaur* HexusOpponentCentaur::getInstance()
{
	if (HexusOpponentCentaur::instance == nullptr)
	{
		HexusOpponentCentaur::instance = new HexusOpponentCentaur();
	}

	return HexusOpponentCentaur::instance;
}

HexusOpponentCentaur::HexusOpponentCentaur() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Enemies_Centaur_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(0.0f, -96.0f),
	Vec2(-64.0f, -96.0f),
	HexusOpponentCentaur::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.355f),
	HexusOpponentData::generateDeck(25, 0.355f,
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

HexusOpponentCentaur::~HexusOpponentCentaur()
{
}
