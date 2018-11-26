#include "HexusOpponentVampireLord.h"

const std::string HexusOpponentVampireLord::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VAMPIRE_LORD";
HexusOpponentVampireLord* HexusOpponentVampireLord::instance = nullptr;

HexusOpponentVampireLord* HexusOpponentVampireLord::getInstance()
{
	if (HexusOpponentVampireLord::instance == nullptr)
	{
		HexusOpponentVampireLord::instance = new HexusOpponentVampireLord();
	}

	return HexusOpponentVampireLord::instance;
}

HexusOpponentVampireLord::HexusOpponentVampireLord() : HexusOpponentData(
	EntityResources::Platformer_Environment_Castle_Enemies_VampireLord_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
	1.0f,
	Vec2(-32.0f, -32.0f),
	Vec2(-32.0f, -48.0f),
	HexusOpponentVampireLord::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.555f),
	HexusOpponentData::generateDeck(25, 0.555f,
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

HexusOpponentVampireLord::~HexusOpponentVampireLord()
{
}
