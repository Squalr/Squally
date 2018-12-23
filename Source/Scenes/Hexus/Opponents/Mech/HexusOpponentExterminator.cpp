#include "HexusOpponentExterminator.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentExterminator::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EXTERMINATOR";
HexusOpponentExterminator* HexusOpponentExterminator::instance = nullptr;

HexusOpponentExterminator* HexusOpponentExterminator::getInstance()
{
	if (HexusOpponentExterminator::instance == nullptr)
	{
		HexusOpponentExterminator::instance = new HexusOpponentExterminator();
	}

	return HexusOpponentExterminator::instance;
}

HexusOpponentExterminator::HexusOpponentExterminator() : HexusOpponentData(
	EntityResources::Enemies_VoidStar_Exterminator_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameMech,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-48.0f, -64.0f),
	HexusOpponentExterminator::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.965f),
	HexusOpponentData::generateDeck(25, 0.965f,
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

HexusOpponentExterminator::~HexusOpponentExterminator()
{
}
