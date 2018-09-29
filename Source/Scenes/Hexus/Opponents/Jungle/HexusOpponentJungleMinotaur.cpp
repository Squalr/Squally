#include "HexusOpponentJungleMinotaur.h"

const std::string HexusOpponentJungleMinotaur::StringKeyOpponentName = "Squally_Npc_Names_Jungle_Minotaur";
HexusOpponentJungleMinotaur* HexusOpponentJungleMinotaur::instance = nullptr;

HexusOpponentJungleMinotaur* HexusOpponentJungleMinotaur::getInstance()
{
	if (HexusOpponentJungleMinotaur::instance == nullptr)
	{
		HexusOpponentJungleMinotaur::instance = new HexusOpponentJungleMinotaur();
	}

	return HexusOpponentJungleMinotaur::instance;
}

HexusOpponentJungleMinotaur::HexusOpponentJungleMinotaur() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Jungle_Enemies_Minotaur_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-48.0f, -64.0f),
	HexusOpponentJungleMinotaur::StringKeyOpponentName,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex7),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	},
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Binary3),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary4),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary5),
		CardList::getInstance()->cardListByName->at(CardKeys::Binary6),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal1),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal3),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal5),
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal6),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex3),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex5),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex6),
		CardList::getInstance()->cardListByName->at(CardKeys::Subtraction),
		CardList::getInstance()->cardListByName->at(CardKeys::Flip3),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Addition),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftLeft),
		CardList::getInstance()->cardListByName->at(CardKeys::ShiftRight),
	})
{
}

HexusOpponentJungleMinotaur::~HexusOpponentJungleMinotaur()
{
}
