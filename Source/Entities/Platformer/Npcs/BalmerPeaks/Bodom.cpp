#include "Bodom.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/BalmerPeaks/Bodom.h"

using namespace cocos2d;

const std::string Bodom::MapKeyBodom = "bodom";
HexusOpponentData* Bodom::HexusOpponentDataInstance = nullptr;
const std::string Bodom::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BODOM";

Bodom* Bodom::deserialize(ValueMap& properties)
{
	Bodom* instance = new Bodom(properties);

	instance->autorelease();

	return instance;
}

Bodom::Bodom(ValueMap& properties) : super(properties,
	Bodom::MapKeyBodom,
	nullptr,
	EntityResources::Npcs_BalmerPeaks_Bodom_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Bodom::getHexusOpponentData();
}

Bodom::~Bodom()
{
}

Vec2 Bodom::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Bodom::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Bodom::create();
}

HexusOpponentData* Bodom::getHexusOpponentData()
{
	if (Bodom::HexusOpponentDataInstance == nullptr)
	{
		Bodom::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			Vec2(-32.0f, -112.0f),
			Bodom::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateDeck(32, 0.536f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			}),
			nullptr,
			nullptr
		);
	}

	return Bodom::HexusOpponentDataInstance;
}