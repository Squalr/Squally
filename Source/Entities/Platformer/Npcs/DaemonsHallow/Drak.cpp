#include "Drak.h"

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

const std::string Drak::MapKeyDrak = "drak";
HexusOpponentData* Drak::HexusOpponentDataInstance = nullptr;
const std::string Drak::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DRAK";

Drak* Drak::deserialize(ValueMap& properties)
{
	Drak* instance = new Drak(properties);

	instance->autorelease();

	return instance;
}

Drak::Drak(ValueMap& properties) : super(properties,
	Drak::MapKeyDrak,
	EntityResources::Npcs_DaemonsHallow_Drak_Animations,
	EntityResources::Npcs_DaemonsHallow_Drak_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Drak::getHexusOpponentData();
}

Drak::~Drak()
{
}

Vec2 Drak::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Drak::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Drak::create();
}

HexusOpponentData* Drak::getHexusOpponentData()
{
	if (Drak::HexusOpponentDataInstance == nullptr)
	{
		Drak::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			Drak::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.688f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
			}),
			nullptr,
			nullptr
		);
	}

	return Drak::HexusOpponentDataInstance;
}