#include "HexusOpponentRhinoman.h"

const std::string HexusOpponentRhinoman::StringKeyOpponentName = "Squally_Npc_Names_Rhinoman";
HexusOpponentRhinoman* HexusOpponentRhinoman::instance = nullptr;

HexusOpponentRhinoman* HexusOpponentRhinoman::getInstance()
{
	if (HexusOpponentRhinoman::instance == nullptr)
	{
		HexusOpponentRhinoman::instance = new HexusOpponentRhinoman();
	}

	return HexusOpponentRhinoman::instance;
}

HexusOpponentRhinoman::HexusOpponentRhinoman() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_Rhinoman_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(32.0f, -96.0f),
	HexusOpponentRhinoman::StringKeyOpponentName,
	GameState::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary10),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex9),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal10),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary6),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary7),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary8),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary9),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary10),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal8),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal9),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal10),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex6),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex7),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex8),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex9),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex10),
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::Flip3),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentRhinoman::~HexusOpponentRhinoman()
{
}
