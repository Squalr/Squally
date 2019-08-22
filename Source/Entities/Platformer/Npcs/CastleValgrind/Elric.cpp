#include "Elric.h"

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

const std::string Elric::MapKeyElric = "elric";
HexusOpponentData* Elric::HexusOpponentDataInstance = nullptr;
const std::string Elric::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ELRIC";

Elric* Elric::deserialize(ValueMap& properties)
{
	Elric* instance = new Elric(properties);

	instance->autorelease();

	return instance;
}

Elric::Elric(ValueMap& properties) : super(properties,
	Elric::MapKeyElric,
	EntityResources::Npcs_CastleValgrind_Elric_Animations,
	EntityResources::Npcs_CastleValgrind_Elric_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Elric::getHexusOpponentData();
}

Elric::~Elric()
{
}

Vec2 Elric::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Elric::getHexusOpponentData()
{
	if (Elric::HexusOpponentDataInstance == nullptr)
	{
		Elric::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_CastleValgrind_Elric_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			1.05f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Elric::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.384f,
			HexusOpponentData::generateDeck(32, 0.384f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),

			}),
			nullptr
		);
	}

	return Elric::HexusOpponentDataInstance;
}