#include "Raven.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/CastleValgrind/Raven.h"

using namespace cocos2d;

const std::string Raven::MapKeyRaven = "raven";
HexusOpponentData* Raven::HexusOpponentDataInstance = nullptr;
const std::string Raven::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RAVEN";

Raven* Raven::deserialize(ValueMap& properties)
{
	Raven* instance = new Raven(properties);

	instance->autorelease();

	return instance;
}

Raven::Raven(ValueMap& properties) : super(properties,
	Raven::MapKeyRaven,
	EntityResources::Npcs_CastleValgrind_Raven_Animations,
	EntityResources::Npcs_CastleValgrind_Raven_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Raven::getHexusOpponentData();
}

Raven::~Raven()
{
}

Vec2 Raven::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Raven::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Raven::create();
}

HexusOpponentData* Raven::getHexusOpponentData()
{
	if (Raven::HexusOpponentDataInstance == nullptr)
	{
		Raven::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-32.0f, -112.0f),
			Raven::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			HexusOpponentData::generateDeck(32, 0.455f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
			}),
			nullptr,
			nullptr
		);
	}

	return Raven::HexusOpponentDataInstance;
}