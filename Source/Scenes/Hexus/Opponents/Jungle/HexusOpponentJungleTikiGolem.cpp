#include "HexusOpponentJungleTikiGolem.h"

const std::string HexusOpponentJungleTikiGolem::StringKeyOpponentName = "Squally_Npc_Names_Jungle_Tiki_Golem";
HexusOpponentJungleTikiGolem* HexusOpponentJungleTikiGolem::instance = nullptr;

HexusOpponentJungleTikiGolem* HexusOpponentJungleTikiGolem::getInstance()
{
	if (HexusOpponentJungleTikiGolem::instance == nullptr)
	{
		HexusOpponentJungleTikiGolem::instance = new HexusOpponentJungleTikiGolem();
	}

	return HexusOpponentJungleTikiGolem::instance;
}

HexusOpponentJungleTikiGolem::HexusOpponentJungleTikiGolem() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_TikiGolem_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -144.0f),
	Vec2(-16.0f, -112.0f),
	HexusOpponentJungleTikiGolem::StringKeyOpponentName,
	GameState::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary9),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex10),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal9),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary6),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary7),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal8),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex6),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex7),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex8),
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::Flip3),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentJungleTikiGolem::~HexusOpponentJungleTikiGolem()
{
}
