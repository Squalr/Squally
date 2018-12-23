#include "HexusOpponentGoblinGruntBoar.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentGoblinGruntBoar::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GOBLIN_GRUNT_BOAR";
HexusOpponentGoblinGruntBoar* HexusOpponentGoblinGruntBoar::instance = nullptr;

HexusOpponentGoblinGruntBoar* HexusOpponentGoblinGruntBoar::getInstance()
{
	if (HexusOpponentGoblinGruntBoar::instance == nullptr)
	{
		HexusOpponentGoblinGruntBoar::instance = new HexusOpponentGoblinGruntBoar();
	}

	return HexusOpponentGoblinGruntBoar::instance;
}

HexusOpponentGoblinGruntBoar::HexusOpponentGoblinGruntBoar() : HexusOpponentData(
	EntityResources::Enemies_EndianForest_GoblinGruntBoar_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest,
	1.0f,
	Vec2(-48.0f, -32.0f),
	Vec2(-16.0f, -56.0f),
	HexusOpponentGoblinGruntBoar::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.125f),
	HexusOpponentData::generateDeck(25, 0.125f,
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

HexusOpponentGoblinGruntBoar::~HexusOpponentGoblinGruntBoar()
{
}
