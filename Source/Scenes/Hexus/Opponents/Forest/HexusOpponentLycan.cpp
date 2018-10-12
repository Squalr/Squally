#include "HexusOpponentLycan.h"

const std::string HexusOpponentLycan::StringKeyOpponentName = "Squally_Npc_Names_Lycan";
HexusOpponentLycan* HexusOpponentLycan::instance = nullptr;

HexusOpponentLycan* HexusOpponentLycan::getInstance()
{
	if (HexusOpponentLycan::instance == nullptr)
	{
		HexusOpponentLycan::instance = new HexusOpponentLycan();
	}

	return HexusOpponentLycan::instance;
}

HexusOpponentLycan::HexusOpponentLycan() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Npcs_Lycan_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	0.3f,
	Vec2(24.0f, -128.0f),
	Vec2(24.0f, -128.0f),
	HexusOpponentLycan::StringKeyOpponentName,
	GameState::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary0),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary1),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal0),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex0),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex2),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalXor),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentLycan::~HexusOpponentLycan()
{
}
