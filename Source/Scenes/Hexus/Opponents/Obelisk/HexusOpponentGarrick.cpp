#include "HexusOpponentGarrick.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentGarrick::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GARRICK";
HexusOpponentGarrick* HexusOpponentGarrick::instance = nullptr;

HexusOpponentGarrick* HexusOpponentGarrick::getInstance()
{
	if (HexusOpponentGarrick::instance == nullptr)
	{
		HexusOpponentGarrick::instance = new HexusOpponentGarrick();
	}

	return HexusOpponentGarrick::instance;
}

HexusOpponentGarrick::HexusOpponentGarrick() : HexusOpponentData(
	EntityResources::Npcs_LexiconCrypts_Garrick_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.85f,
	Vec2(-48.0f, -80.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentGarrick::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.81f),
	HexusOpponentData::generateDeck(25, 0.81f,
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

HexusOpponentGarrick::~HexusOpponentGarrick()
{
}
