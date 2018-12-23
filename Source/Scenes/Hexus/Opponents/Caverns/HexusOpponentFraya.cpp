#include "HexusOpponentFraya.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentFraya::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FRAYA";
HexusOpponentFraya* HexusOpponentFraya::instance = nullptr;

HexusOpponentFraya* HexusOpponentFraya::getInstance()
{
	if (HexusOpponentFraya::instance == nullptr)
	{
		HexusOpponentFraya::instance = new HexusOpponentFraya();
	}

	return HexusOpponentFraya::instance;
}

HexusOpponentFraya::HexusOpponentFraya() : HexusOpponentData(
	EntityResources::Npcs_SeaSharpCaverns_Fraya_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCaverns,
	0.85f,
	Vec2(-32.0f, -40.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentFraya::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Shadow,
	HexusOpponentData::generateReward(0.44f),
	HexusOpponentData::generateDeck(25, 0.44f,
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

HexusOpponentFraya::~HexusOpponentFraya()
{
}
