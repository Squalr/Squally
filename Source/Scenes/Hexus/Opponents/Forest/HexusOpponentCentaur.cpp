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
	EntityResources::Enemies_EndianForest_Centaur_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(0.0f, -96.0f),
	Vec2(-64.0f, -96.0f),
	HexusOpponentCentaur::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
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
