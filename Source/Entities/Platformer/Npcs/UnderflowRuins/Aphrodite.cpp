#include "Aphrodite.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/UnderflowRuins/Aphrodite.h"

using namespace cocos2d;

const std::string Aphrodite::MapKeyAphrodite = "aphrodite";
HexusOpponentData* Aphrodite::HexusOpponentDataInstance = nullptr;
const std::string Aphrodite::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_APHRODITE";

Aphrodite* Aphrodite::deserialize(ValueMap& properties)
{
	Aphrodite* instance = new Aphrodite(properties);

	instance->autorelease();

	return instance;
}

Aphrodite::Aphrodite(ValueMap& properties) : super(properties,
	Aphrodite::MapKeyAphrodite,
	EntityResources::Npcs_UnderflowRuins_Aphrodite_Animations,
	EntityResources::Npcs_UnderflowRuins_Aphrodite_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Aphrodite::getHexusOpponentData();
}

Aphrodite::~Aphrodite()
{
}

Vec2 Aphrodite::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Aphrodite::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Aphrodite::create();
}

HexusOpponentData* Aphrodite::getHexusOpponentData()
{
	if (Aphrodite::HexusOpponentDataInstance == nullptr)
	{
		Aphrodite::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -112.0f),
			Aphrodite::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.134f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
			}),
			nullptr,
			nullptr
		);
	}

	return Aphrodite::HexusOpponentDataInstance;
}