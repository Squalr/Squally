#include "Rusty.h"

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

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string Rusty::MapKeyRusty = "rusty";
HexusOpponentData* Rusty::HexusOpponentDataInstance = nullptr;
const std::string Rusty::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RUSTY";

Rusty* Rusty::deserialize(ValueMap& properties)
{
	Rusty* instance = new Rusty(properties);

	instance->autorelease();

	return instance;
}

Rusty::Rusty(ValueMap& properties) : super(properties,
	Rusty::MapKeyRusty,
	EntityResources::Npcs_DaemonsHallow_Rusty_Animations,
	EntityResources::Npcs_DaemonsHallow_Rusty_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Rusty::getHexusOpponentData();
}

Rusty::~Rusty()
{
}

Vec2 Rusty::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Rusty::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Rusty::create();
}

HexusOpponentData* Rusty::getHexusOpponentData()
{
	if (Rusty::HexusOpponentDataInstance == nullptr)
	{
		Rusty::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			Rusty::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.643f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
			}),
			nullptr,
			nullptr
		);
	}

	return Rusty::HexusOpponentDataInstance;
}