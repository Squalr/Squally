#include "HexusOpponentDemonGrunt.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentDemonGrunt::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_GRUNT";
HexusOpponentDemonGrunt* HexusOpponentDemonGrunt::instance = nullptr;

HexusOpponentDemonGrunt* HexusOpponentDemonGrunt::getInstance()
{
	if (HexusOpponentDemonGrunt::instance == nullptr)
	{
		HexusOpponentDemonGrunt::instance = new HexusOpponentDemonGrunt();
	}

	return HexusOpponentDemonGrunt::instance;
}

HexusOpponentDemonGrunt::HexusOpponentDemonGrunt() : HexusOpponentData(
	EntityResources::Enemies_DaemonsHallow_DemonGrunt_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameVolcano,
	0.85f,
	Vec2(-48.0f, -48.0f),
	Vec2(-32.0f, -64.0f),
	HexusOpponentDemonGrunt::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.765f),
	HexusOpponentData::generateDeck(25, 0.765f,
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

HexusOpponentDemonGrunt::~HexusOpponentDemonGrunt()
{
}
