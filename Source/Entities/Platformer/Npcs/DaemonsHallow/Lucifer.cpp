#include "Lucifer.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/DaemonsHallow/Lucifer.h"

using namespace cocos2d;

const std::string Lucifer::MapKeyLucifer = "lucifer";
HexusOpponentData* Lucifer::HexusOpponentDataInstance = nullptr;
const std::string Lucifer::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LUCIFER";

Lucifer* Lucifer::deserialize(ValueMap& properties)
{
	Lucifer* instance = new Lucifer(properties);

	instance->autorelease();

	return instance;
}

Lucifer::Lucifer(ValueMap& properties) : super(properties,
	Lucifer::MapKeyLucifer,
	nullptr,
	EntityResources::Npcs_DaemonsHallow_Lucifer_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Lucifer::getHexusOpponentData();
}

Lucifer::~Lucifer()
{
}

Vec2 Lucifer::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Lucifer::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Lucifer::create();
}

HexusOpponentData* Lucifer::getHexusOpponentData()
{
	if (Lucifer::HexusOpponentDataInstance == nullptr)
	{
		Lucifer::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			Vec2(-32.0f, -112.0f),
			Lucifer::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateDeck(32, 0.705f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
			}),
			nullptr,
			nullptr
		);
	}

	return Lucifer::HexusOpponentDataInstance;
}