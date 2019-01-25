#include "HexusOpponentNecron.h"

#include "cocos/math/Vec2.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusOpponentNecron::OpponentSaveKey = "HEXUS_OPPONENT_SAVE_KEY_NECRON";
HexusOpponentNecron* HexusOpponentNecron::instance = nullptr;

HexusOpponentNecron* HexusOpponentNecron::getInstance()
{
	if (HexusOpponentNecron::instance == nullptr)
	{
		HexusOpponentNecron::instance = new HexusOpponentNecron();
	}

	return HexusOpponentNecron::instance;
}

HexusOpponentNecron::HexusOpponentNecron() : HexusOpponentData(
	EntityResources::Npcs_LambdaCrypts_Necron_Animations,
	UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk,
	1.0f,
	Vec2(-48.0f, -72.0f),
	Vec2(-16.0f, -40.0f),
	HexusOpponentNecron::OpponentSaveKey,
	HexusOpponentData::Strategy::Random,
	Card::CardStyle::Earth,
	HexusOpponentData::generateReward(0.84f),
	HexusOpponentData::generateDeck(25, 0.84f,
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

HexusOpponentNecron::~HexusOpponentNecron()
{
}
