#include "HexusOpponentAres.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentAres::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ARES";
HexusOpponentAres* HexusOpponentAres::instance = nullptr;

HexusOpponentAres* HexusOpponentAres::getInstance()
{
	if (HexusOpponentAres::instance == nullptr)
	{
		HexusOpponentAres::instance = new HexusOpponentAres();
	}

	return HexusOpponentAres::instance;
}

HexusOpponentAres::HexusOpponentAres() : HexusOpponentData(
	EntityResources::Npcs_UnderflowRuins_Ares_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentAres::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.22f),
	HexusOpponentData::generateDeck(25, 0.22f,
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Addition),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentAres::~HexusOpponentAres()
{
}
