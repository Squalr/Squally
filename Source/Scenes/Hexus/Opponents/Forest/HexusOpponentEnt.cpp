#include "HexusOpponentEnt.h"

const std::string HexusOpponentEnt::StringKeyOpponentName = "Squally_Npc_Names_Ent";
HexusOpponentEnt* HexusOpponentEnt::instance = nullptr;

HexusOpponentEnt* HexusOpponentEnt::getInstance()
{
	if (HexusOpponentEnt::instance == nullptr)
	{
		HexusOpponentEnt::instance = new HexusOpponentEnt();
	}

	return HexusOpponentEnt::instance;
}

HexusOpponentEnt::HexusOpponentEnt() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Enemies_Ent_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	0.3f,
	Vec2(24.0f, -128.0f),
	Vec2(24.0f, -128.0f),
	HexusOpponentEnt::StringKeyOpponentName,
	HexusOpponentData::Difficulty::Stupid,
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

HexusOpponentEnt::~HexusOpponentEnt()
{
}
