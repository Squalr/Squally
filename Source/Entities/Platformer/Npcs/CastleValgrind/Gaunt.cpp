#include "Gaunt.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/CastleValgrind/Gaunt.h"

using namespace cocos2d;

const std::string Gaunt::MapKeyGaunt = "gaunt";
HexusOpponentData* Gaunt::HexusOpponentDataInstance = nullptr;
const std::string Gaunt::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GAUNT";

Gaunt* Gaunt::deserialize(ValueMap& properties)
{
	Gaunt* instance = new Gaunt(properties);

	instance->autorelease();

	return instance;
}

Gaunt::Gaunt(ValueMap& properties) : super(properties,
	Gaunt::MapKeyGaunt,
	EntityResources::Npcs_CastleValgrind_Gaunt_Animations,
	EntityResources::Npcs_CastleValgrind_Gaunt_Emblem,
	Size(112.0f, 160.0f),
	0.95f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Gaunt::getHexusOpponentData();
}

Gaunt::~Gaunt()
{
}

Vec2 Gaunt::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Gaunt::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_CastleValgrind_Gaunt::create();
}

HexusOpponentData* Gaunt::getHexusOpponentData()
{
	if (Gaunt::HexusOpponentDataInstance == nullptr)
	{
		Gaunt::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_CastleValgrind_Gaunt_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			0.95f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Gaunt::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.482f,
			HexusOpponentData::generateDeck(32, 0.482f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
			}),
			nullptr,
			nullptr
		);
	}

	return Gaunt::HexusOpponentDataInstance;
}