#include "HexusOpponentQueenElise.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentQueenElise::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_QUEEN_ELISE";
HexusOpponentQueenElise* HexusOpponentQueenElise::instance = nullptr;

HexusOpponentQueenElise* HexusOpponentQueenElise::getInstance()
{
	if (HexusOpponentQueenElise::instance == nullptr)
	{
		HexusOpponentQueenElise::instance = new HexusOpponentQueenElise();
	}

	return HexusOpponentQueenElise::instance;
}

HexusOpponentQueenElise::HexusOpponentQueenElise() : HexusOpponentData(
	EntityResources::Npcs_VoidStar_QueenElise_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentQueenElise::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.99f),
	HexusOpponentData::generateDeck(25, 0.99f,
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

HexusOpponentQueenElise::~HexusOpponentQueenElise()
{
}
