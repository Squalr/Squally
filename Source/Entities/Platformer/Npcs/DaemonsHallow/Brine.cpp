#include "Brine.h"

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

const std::string Brine::MapKeyBrine = "brine";
HexusOpponentData* Brine::HexusOpponentDataInstance = nullptr;
const std::string Brine::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BRINE";

Brine* Brine::deserialize(ValueMap& properties)
{
	Brine* instance = new Brine(properties);

	instance->autorelease();

	return instance;
}

Brine::Brine(ValueMap& properties) : super(properties,
	Brine::MapKeyBrine,
	EntityResources::Npcs_DaemonsHallow_Brine_Animations,
	EntityResources::Npcs_DaemonsHallow_Brine_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Brine::getHexusOpponentData();
}

Brine::~Brine()
{
}

Vec2 Brine::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* Brine::getEntityName()
{
	return nullptr;
}

HexusOpponentData* Brine::getHexusOpponentData()
{
	if (Brine::HexusOpponentDataInstance == nullptr)
	{
		Brine::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_DaemonsHallow_Brine_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			1.05f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Brine::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.661f,
			HexusOpponentData::generateDeck(32, 0.661f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),

			}),
			nullptr
		);
	}

	return Brine::HexusOpponentDataInstance;
}