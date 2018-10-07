#include "HexusOpponentForestGoblinGuard.h"

const std::string HexusOpponentForestGoblinGuard::StringKeyOpponentName = "Squally_Npc_Names_Forest_Goblin_Guard";
HexusOpponentForestGoblinGuard* HexusOpponentForestGoblinGuard::instance = nullptr;

HexusOpponentForestGoblinGuard* HexusOpponentForestGoblinGuard::getInstance()
{
	if (HexusOpponentForestGoblinGuard::instance == nullptr)
	{
		HexusOpponentForestGoblinGuard::instance = new HexusOpponentForestGoblinGuard();
	}

	return HexusOpponentForestGoblinGuard::instance;
}

HexusOpponentForestGoblinGuard::HexusOpponentForestGoblinGuard() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Forest_Enemies_GoblinGuard_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	0.3f,
	Vec2(24.0f, -128.0f),
	Vec2(24.0f, -128.0f),
	HexusOpponentForestGoblinGuard::StringKeyOpponentName,
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

HexusOpponentForestGoblinGuard::~HexusOpponentForestGoblinGuard()
{
}
