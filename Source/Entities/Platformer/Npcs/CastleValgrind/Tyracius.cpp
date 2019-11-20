#include "Tyracius.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/CastleValgrind/Tyracius.h"

using namespace cocos2d;

const std::string Tyracius::MapKeyTyracius = "tyracius";
HexusOpponentData* Tyracius::HexusOpponentDataInstance = nullptr;
const std::string Tyracius::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TYRACIUS";

Tyracius* Tyracius::deserialize(ValueMap& properties)
{
	Tyracius* instance = new Tyracius(properties);

	instance->autorelease();

	return instance;
}

Tyracius::Tyracius(ValueMap& properties) : super(properties,
	Tyracius::MapKeyTyracius,
	EntityResources::Npcs_CastleValgrind_Tyracius_Animations,
	EntityResources::Npcs_CastleValgrind_Tyracius_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Tyracius::getHexusOpponentData();
}

Tyracius::~Tyracius()
{
}

Vec2 Tyracius::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Tyracius::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Tyracius::create();
}

HexusOpponentData* Tyracius::getHexusOpponentData()
{
	if (Tyracius::HexusOpponentDataInstance == nullptr)
	{
		Tyracius::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-32.0f, -112.0f),
			Tyracius::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			HexusOpponentData::generateDeck(32, 0.500f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
			}),
			nullptr,
			nullptr
		);
	}

	return Tyracius::HexusOpponentDataInstance;
}