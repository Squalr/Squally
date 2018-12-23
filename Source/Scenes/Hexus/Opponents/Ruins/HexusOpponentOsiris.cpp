#include "HexusOpponentOsiris.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentOsiris::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MUMMY_OSIRIS";
HexusOpponentOsiris* HexusOpponentOsiris::instance = nullptr;

HexusOpponentOsiris* HexusOpponentOsiris::getInstance()
{
	if (HexusOpponentOsiris::instance == nullptr)
	{
		HexusOpponentOsiris::instance = new HexusOpponentOsiris();
	}

	return HexusOpponentOsiris::instance;
}

HexusOpponentOsiris::HexusOpponentOsiris() : HexusOpponentData(
	EntityResources::Enemies_UnderflowRuins_Osiris_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-32.0f, -48.0f),
	Vec2(-32.0f, -72.0f),
	HexusOpponentOsiris::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.32f),
	HexusOpponentData::generateDeck(25, 0.32f,
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

HexusOpponentOsiris::~HexusOpponentOsiris()
{
}
