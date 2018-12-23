#include "HexusOpponentTinsel.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentTinsel::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TINSEL";
HexusOpponentTinsel* HexusOpponentTinsel::instance = nullptr;

HexusOpponentTinsel* HexusOpponentTinsel::getInstance()
{
	if (HexusOpponentTinsel::instance == nullptr)
	{
		HexusOpponentTinsel::instance = new HexusOpponentTinsel();
	}

	return HexusOpponentTinsel::instance;
}

HexusOpponentTinsel::HexusOpponentTinsel() : HexusOpponentData(
	EntityResources::Npcs_LambdaPeaks_Tinsel_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	0.85f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -24.0f),
	HexusOpponentTinsel::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.685f),
	HexusOpponentData::generateDeck(25, 0.685f,
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

HexusOpponentTinsel::~HexusOpponentTinsel()
{
}
