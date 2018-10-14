#include "HexusOpponentEarthGolem.h"

const std::string HexusOpponentEarthGolem::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EARTH_GOLEM";
HexusOpponentEarthGolem* HexusOpponentEarthGolem::instance = nullptr;

HexusOpponentEarthGolem* HexusOpponentEarthGolem::getInstance()
{
	if (HexusOpponentEarthGolem::instance == nullptr)
	{
		HexusOpponentEarthGolem::instance = new HexusOpponentEarthGolem();
	}

	return HexusOpponentEarthGolem::instance;
}

HexusOpponentEarthGolem::HexusOpponentEarthGolem() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Caverns_Enemies_EarthGolem_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(-48.0f, -96.0f),
	HexusOpponentEarthGolem::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Shadow,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal2),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
	},
	HexusOpponentData::generateDeck(25, 0, 8, 0.33f, 0.33f,
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

HexusOpponentEarthGolem::~HexusOpponentEarthGolem()
{
}
