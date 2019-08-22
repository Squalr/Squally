#include "Athena.h"

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

using namespace cocos2d;

const std::string Athena::MapKeyAthena = "athena";
HexusOpponentData* Athena::HexusOpponentDataInstance = nullptr;
const std::string Athena::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ATHENA";

Athena* Athena::deserialize(ValueMap& properties)
{
	Athena* instance = new Athena(properties);

	instance->autorelease();

	return instance;
}

Athena::Athena(ValueMap& properties) : super(properties,
	Athena::MapKeyAthena,
	EntityResources::Npcs_UnderflowRuins_Athena_Animations,
	EntityResources::Npcs_UnderflowRuins_Athena_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Athena::getHexusOpponentData();
}

Athena::~Athena()
{
}

Vec2 Athena::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Athena::getHexusOpponentData()
{
	if (Athena::HexusOpponentDataInstance == nullptr)
	{
		Athena::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_UnderflowRuins_Athena_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Athena::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.170f,
			HexusOpponentData::generateDeck(32, 0.170f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return Athena::HexusOpponentDataInstance;
}