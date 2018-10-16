#include "HexusOpponentTigress.h"

const std::string HexusOpponentTigress::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TIGRESS";
HexusOpponentTigress* HexusOpponentTigress::instance = nullptr;

HexusOpponentTigress* HexusOpponentTigress::getInstance()
{
	if (HexusOpponentTigress::instance == nullptr)
	{
		HexusOpponentTigress::instance = new HexusOpponentTigress();
	}

	return HexusOpponentTigress::instance;
}

HexusOpponentTigress::HexusOpponentTigress() : HexusOpponentData(
	Resources::Entities_Platformer_Environment_Ruins_Enemies_Tigress_Animations,
	Resources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentTigress::OpponentSaveKey,
	HexusOpponentData::Difficulty::Stupid,
	Card::CardStyle::Earth,
	{
		CardList::getInstance()->cardListByName->at(CardKeys::Decimal4),
		CardList::getInstance()->cardListByName->at(CardKeys::LogicalAnd),
		CardList::getInstance()->cardListByName->at(CardKeys::Hex4),
	},
	HexusOpponentData::generateDeck(25, 0.235f,
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

HexusOpponentTigress::~HexusOpponentTigress()
{
}
