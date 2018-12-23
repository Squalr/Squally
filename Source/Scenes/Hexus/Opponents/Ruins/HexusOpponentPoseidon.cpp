#include "HexusOpponentPoseidon.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentPoseidon::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_POSEIDON";
HexusOpponentPoseidon* HexusOpponentPoseidon::instance = nullptr;

HexusOpponentPoseidon* HexusOpponentPoseidon::getInstance()
{
	if (HexusOpponentPoseidon::instance == nullptr)
	{
		HexusOpponentPoseidon::instance = new HexusOpponentPoseidon();
	}

	return HexusOpponentPoseidon::instance;
}

HexusOpponentPoseidon::HexusOpponentPoseidon() : HexusOpponentData(
	EntityResources::Npcs_UnderflowRuins_Poseidon_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins,
	1.0f,
	Vec2(-48.0f, -48.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentPoseidon::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.285f),
	HexusOpponentData::generateDeck(25, 0.285f,
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

HexusOpponentPoseidon::~HexusOpponentPoseidon()
{
}
