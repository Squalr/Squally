#include "Hades.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/UnderflowRuins/Hades.h"

using namespace cocos2d;

const std::string Hades::MapKeyHades = "hades";
HexusOpponentData* Hades::HexusOpponentDataInstance = nullptr;
const std::string Hades::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_HADES";

Hades* Hades::deserialize(ValueMap& properties)
{
	Hades* instance = new Hades(properties);

	instance->autorelease();

	return instance;
}

Hades::Hades(ValueMap& properties) : super(properties,
	Hades::MapKeyHades,
	EntityResources::Npcs_UnderflowRuins_Hades_Animations,
	EntityResources::Npcs_UnderflowRuins_Hades_Emblem,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Hades::getHexusOpponentData();
}

Hades::~Hades()
{
}

Vec2 Hades::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Hades::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_UnderflowRuins_Hades::create();
}

HexusOpponentData* Hades::getHexusOpponentData()
{
	if (Hades::HexusOpponentDataInstance == nullptr)
	{
		Hades::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_UnderflowRuins_Hades_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Hades::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.196f,
			HexusOpponentData::generateDeck(32, 0.196f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
			}),
			{ },
			nullptr
		);
	}

	return Hades::HexusOpponentDataInstance;
}