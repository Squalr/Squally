#include "HexusOpponentKingZul.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentKingZul::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_ZUL";
HexusOpponentKingZul* HexusOpponentKingZul::instance = nullptr;

HexusOpponentKingZul* HexusOpponentKingZul::getInstance()
{
	if (HexusOpponentKingZul::instance == nullptr)
	{
		HexusOpponentKingZul::instance = new HexusOpponentKingZul();
	}

	return HexusOpponentKingZul::instance;
}

HexusOpponentKingZul::HexusOpponentKingZul() : HexusOpponentData(
	EntityResources::Enemies_LexiconCrypts_KingZul_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -64.0f),
	HexusOpponentKingZul::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.92f),
	HexusOpponentData::generateDeck(25, 0.92f,
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

HexusOpponentKingZul::~HexusOpponentKingZul()
{
}
