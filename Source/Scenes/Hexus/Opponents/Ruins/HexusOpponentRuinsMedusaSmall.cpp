#include "HexusOpponentRuinsMedusaSmall.h"

const std::string HexusOpponentRuinsMedusaSmall::StringKeyOpponentName = "Squally_Npc_Names_Ruins_Medusa_Small";
HexusOpponentRuinsMedusaSmall* HexusOpponentRuinsMedusaSmall::instance = nullptr;

HexusOpponentRuinsMedusaSmall* HexusOpponentRuinsMedusaSmall::getInstance()
{
	if (HexusOpponentRuinsMedusaSmall::instance == nullptr)
	{
		HexusOpponentRuinsMedusaSmall::instance = new HexusOpponentRuinsMedusaSmall();
	}

	return HexusOpponentRuinsMedusaSmall::instance;
}

HexusOpponentRuinsMedusaSmall::HexusOpponentRuinsMedusaSmall() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Enemies_MedusaSmall_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	0.9f,
	Vec2(-48.0f, -24.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentRuinsMedusaSmall::StringKeyOpponentName,
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

HexusOpponentRuinsMedusaSmall::~HexusOpponentRuinsMedusaSmall()
{
}
