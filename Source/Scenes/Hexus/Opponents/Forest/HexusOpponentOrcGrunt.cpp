#include "HexusOpponentOrcGrunt.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentOrcGrunt::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ORC_GRUNT";
HexusOpponentOrcGrunt* HexusOpponentOrcGrunt::instance = nullptr;

HexusOpponentOrcGrunt* HexusOpponentOrcGrunt::getInstance()
{
	if (HexusOpponentOrcGrunt::instance == nullptr)
	{
		HexusOpponentOrcGrunt::instance = new HexusOpponentOrcGrunt();
	}

	return HexusOpponentOrcGrunt::instance;
}

HexusOpponentOrcGrunt::HexusOpponentOrcGrunt() : HexusOpponentData(
	EntityResources::Enemies_EndianForest_OrcGrunt_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-64.0f, -48.0f),
	HexusOpponentOrcGrunt::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.315f),
	HexusOpponentData::generateDeck(25, 0.315f,
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

HexusOpponentOrcGrunt::~HexusOpponentOrcGrunt()
{
}
