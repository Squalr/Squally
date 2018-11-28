#include "HexusOpponentVampiress.h"

const std::string HexusOpponentVampiress::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VAMPIRESS";
HexusOpponentVampiress* HexusOpponentVampiress::instance = nullptr;

HexusOpponentVampiress* HexusOpponentVampiress::getInstance()
{
	if (HexusOpponentVampiress::instance == nullptr)
	{
		HexusOpponentVampiress::instance = new HexusOpponentVampiress();
	}

	return HexusOpponentVampiress::instance;
}

HexusOpponentVampiress::HexusOpponentVampiress() : HexusOpponentData(
	EntityResources::Environment_Castle_Enemies_Vampiress_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -32.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentVampiress::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.565f),
	HexusOpponentData::generateDeck(25, 0.565f,
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

HexusOpponentVampiress::~HexusOpponentVampiress()
{
}
