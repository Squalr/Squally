#include "HexusOpponentRuinsAnubisWarrior.h"

const std::string HexusOpponentRuinsAnubisWarrior::StringKeyOpponentName = "Squally_Npc_Names_Ruins_Anubis_Warrior";
HexusOpponentRuinsAnubisWarrior* HexusOpponentRuinsAnubisWarrior::instance = nullptr;

HexusOpponentRuinsAnubisWarrior* HexusOpponentRuinsAnubisWarrior::getInstance()
{
	if (HexusOpponentRuinsAnubisWarrior::instance == nullptr)
	{
		HexusOpponentRuinsAnubisWarrior::instance = new HexusOpponentRuinsAnubisWarrior();
	}

	return HexusOpponentRuinsAnubisWarrior::instance;
}

HexusOpponentRuinsAnubisWarrior::HexusOpponentRuinsAnubisWarrior() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Enemies_AnubisWarrior_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentRuinsAnubisWarrior::StringKeyOpponentName,
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

HexusOpponentRuinsAnubisWarrior::~HexusOpponentRuinsAnubisWarrior()
{
}
