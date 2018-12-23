#include "HexusOpponentViper.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentViper::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VIPER";
HexusOpponentViper* HexusOpponentViper::instance = nullptr;

HexusOpponentViper* HexusOpponentViper::getInstance()
{
	if (HexusOpponentViper::instance == nullptr)
	{
		HexusOpponentViper::instance = new HexusOpponentViper();
	}

	return HexusOpponentViper::instance;
}

HexusOpponentViper::HexusOpponentViper() : HexusOpponentData(
	EntityResources::Npcs_LexiconCrypts_Viper_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -48.0f),
	HexusOpponentViper::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.88f),
	HexusOpponentData::generateDeck(25, 0.8f,
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

HexusOpponentViper::~HexusOpponentViper()
{
}
