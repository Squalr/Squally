#include "HexusOpponentNessie.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentNessie::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_NESSIE";
HexusOpponentNessie* HexusOpponentNessie::instance = nullptr;

HexusOpponentNessie* HexusOpponentNessie::getInstance()
{
	if (HexusOpponentNessie::instance == nullptr)
	{
		HexusOpponentNessie::instance = new HexusOpponentNessie();
	}

	return HexusOpponentNessie::instance;
}

HexusOpponentNessie::HexusOpponentNessie() : HexusOpponentData(
	EntityResources::Npcs_BalmerPeaks_Nessie_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps,
	1.0f,
	Vec2(-48.0f, -64.0f),
	Vec2(-16.0f, -32.0f),
	HexusOpponentNessie::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.605f),
	HexusOpponentData::generateDeck(25, 0.605f,
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

HexusOpponentNessie::~HexusOpponentNessie()
{
}
