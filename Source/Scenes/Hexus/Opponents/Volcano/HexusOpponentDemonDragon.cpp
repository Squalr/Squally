#include "HexusOpponentDemonDragon.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentDemonDragon::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_DRAGON";
HexusOpponentDemonDragon* HexusOpponentDemonDragon::instance = nullptr;

HexusOpponentDemonDragon* HexusOpponentDemonDragon::getInstance()
{
	if (HexusOpponentDemonDragon::instance == nullptr)
	{
		HexusOpponentDemonDragon::instance = new HexusOpponentDemonDragon();
	}

	return HexusOpponentDemonDragon::instance;
}

HexusOpponentDemonDragon::HexusOpponentDemonDragon() : HexusOpponentData(
	EntityResources::Enemies_DaemonsHallow_DemonDragon_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-96.0f, -56.0f),
	HexusOpponentDemonDragon::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.755f),
	HexusOpponentData::generateDeck(25, 0.755f,
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

HexusOpponentDemonDragon::~HexusOpponentDemonDragon()
{
}
