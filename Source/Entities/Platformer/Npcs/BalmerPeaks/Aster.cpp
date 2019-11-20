#include "Aster.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/BalmerPeaks/Aster.h"

using namespace cocos2d;

const std::string Aster::MapKeyAster = "aster";
HexusOpponentData* Aster::HexusOpponentDataInstance = nullptr;
const std::string Aster::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ASTER";

Aster* Aster::deserialize(ValueMap& properties)
{
	Aster* instance = new Aster(properties);

	instance->autorelease();

	return instance;
}

Aster::Aster(ValueMap& properties) : super(properties,
	Aster::MapKeyAster,
	nullptr,
	EntityResources::Npcs_BalmerPeaks_Aster_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Aster::getHexusOpponentData();
}

Aster::~Aster()
{
}

Vec2 Aster::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Aster::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_BalmerPeaks_Aster::create();
}

HexusOpponentData* Aster::getHexusOpponentData()
{
	if (Aster::HexusOpponentDataInstance == nullptr)
	{
		Aster::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			Vec2(-32.0f, -112.0f),
			Aster::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateDeck(32, 0.518f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::Kill),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
			}),
			nullptr,
			nullptr
		);
	}

	return Aster::HexusOpponentDataInstance;
}