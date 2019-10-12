#include "Robin.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/EndianForest/Robin.h"

using namespace cocos2d;

const std::string Robin::MapKeyRobin = "robin";
HexusOpponentData* Robin::HexusOpponentDataInstance = nullptr;
const std::string Robin::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ROBIN";

Robin* Robin::deserialize(ValueMap& properties)
{
	Robin* instance = new Robin(properties);

	instance->autorelease();

	return instance;
}

Robin::Robin(ValueMap& properties) : super(properties,
	Robin::MapKeyRobin,
	EntityResources::Npcs_EndianForest_Robin_Animations,
	EntityResources::Npcs_EndianForest_Robin_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Robin::getHexusOpponentData();
}

Robin::~Robin()
{
}

Vec2 Robin::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Robin::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_EndianForest_Robin::create();
}

HexusOpponentData* Robin::getHexusOpponentData()
{
	if (Robin::HexusOpponentDataInstance == nullptr)
	{
		Robin::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_EndianForest_Robin_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Robin::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.036f,
			HexusOpponentData::generateDeck(32, 0.036f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
			}),
			nullptr,
			nullptr
		);
	}

	return Robin::HexusOpponentDataInstance;
}