#include "Zeus.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Zeus::MapKeyZeus = "zeus";
HexusOpponentData* Zeus::HexusOpponentDataInstance = nullptr;
const std::string Zeus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ZEUS";

Zeus* Zeus::deserialize(ValueMap& properties)
{
	Zeus* instance = new Zeus(properties);

	instance->autorelease();

	return instance;
}

Zeus::Zeus(ValueMap& properties) : super(properties,
	Zeus::MapKeyZeus,
	EntityResources::Npcs_UnderflowRuins_Zeus_Animations,
	EntityResources::Npcs_UnderflowRuins_Zeus_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Zeus::getHexusOpponentData();
}

Zeus::~Zeus()
{
}

Vec2 Zeus::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Zeus::getHexusOpponentData()
{
	if (Zeus::HexusOpponentDataInstance == nullptr)
	{
		Zeus::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_UnderflowRuins_Zeus_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Zeus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.232f,
			HexusOpponentData::generateDeck(32, 0.232f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),

			}),
			nullptr
		);
	}

	return Zeus::HexusOpponentDataInstance;
}