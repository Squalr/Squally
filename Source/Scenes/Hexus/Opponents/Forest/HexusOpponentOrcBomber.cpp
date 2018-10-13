#include "HexusOpponentOrcBomber.h"

const std::string HexusOpponentOrcBomber::StringKeyOpponentName = "Squally_Npc_Names_Orc_Bomber";
HexusOpponentOrcBomber* HexusOpponentOrcBomber::instance = nullptr;

HexusOpponentOrcBomber* HexusOpponentOrcBomber::getInstance()
{
	if (HexusOpponentOrcBomber::instance == nullptr)
	{
		HexusOpponentOrcBomber::instance = new HexusOpponentOrcBomber();
	}

	return HexusOpponentOrcBomber::instance;
}

HexusOpponentOrcBomber::HexusOpponentOrcBomber() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Enemies_OrcBomber_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(0.0f, -48.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentOrcBomber::StringKeyOpponentName,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex7),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary7),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal7),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex6),
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::Flip3),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalOr),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentOrcBomber::~HexusOpponentOrcBomber()
{
}
