#include "HexusOpponentSarude.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentSarude::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SARUDE";
HexusOpponentSarude* HexusOpponentSarude::instance = nullptr;

HexusOpponentSarude* HexusOpponentSarude::getInstance()
{
	if (HexusOpponentSarude::instance == nullptr)
	{
		HexusOpponentSarude::instance = new HexusOpponentSarude();
	}

	return HexusOpponentSarude::instance;
}

HexusOpponentSarude::HexusOpponentSarude() : HexusOpponentData(
	EntityResources::Npcs_SeaSharpCaverns_Sarude_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	1.0f,
	Vec2(-32.0f, -64.0f),
	Vec2(-24.0f, -32.0f),
	HexusOpponentSarude::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.505f),
	HexusOpponentData::generateDeck(25, 0.505f,
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

HexusOpponentSarude::~HexusOpponentSarude()
{
}
