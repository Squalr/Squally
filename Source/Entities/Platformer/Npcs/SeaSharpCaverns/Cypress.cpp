#include "Cypress.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/SeaSharpCaverns/Cypress.h"

using namespace cocos2d;

const std::string Cypress::MapKeyCypress = "cypress";
HexusOpponentData* Cypress::HexusOpponentDataInstance = nullptr;
const std::string Cypress::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CYPRESS";

Cypress* Cypress::deserialize(ValueMap& properties)
{
	Cypress* instance = new Cypress(properties);

	instance->autorelease();

	return instance;
}

Cypress::Cypress(ValueMap& properties) : super(properties,
	Cypress::MapKeyCypress,
	nullptr,
	EntityResources::Npcs_SeaSharpCaverns_Cypress_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Cypress::getHexusOpponentData();
}

Cypress::~Cypress()
{
}

Vec2 Cypress::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Cypress::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_SeaSharpCaverns_Cypress::create();
}

HexusOpponentData* Cypress::getHexusOpponentData()
{
	if (Cypress::HexusOpponentDataInstance == nullptr)
	{
		Cypress::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -112.0f),
			Cypress::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.286f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			}),
			nullptr,
			nullptr
		);
	}

	return Cypress::HexusOpponentDataInstance;
}