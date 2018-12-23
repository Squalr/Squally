#include "HexusOpponentGorilla.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentGorilla::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GORILLA";
HexusOpponentGorilla* HexusOpponentGorilla::instance = nullptr;

HexusOpponentGorilla* HexusOpponentGorilla::getInstance()
{
	if (HexusOpponentGorilla::instance == nullptr)
	{
		HexusOpponentGorilla::instance = new HexusOpponentGorilla();
	}

	return HexusOpponentGorilla::instance;
}

HexusOpponentGorilla::HexusOpponentGorilla() : HexusOpponentData(
	EntityResources::Enemies_VoidStar_Gorilla_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameJungle,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-80.0f, -32.0f),
	HexusOpponentGorilla::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.135f),
	HexusOpponentData::generateDeck(25, 0.135f,
		{
			CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
			CardList::getInstance()->cardListByName.at(CardKeys::Hex0),
			CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
			CardList::getInstance()->cardListByName.at(CardKeys::Addition),
			CardList::getInstance()->cardListByName.at(CardKeys::Addition),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
		})
	)
{
}

HexusOpponentGorilla::~HexusOpponentGorilla()
{
}
