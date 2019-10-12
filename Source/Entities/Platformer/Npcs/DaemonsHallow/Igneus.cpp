#include "Igneus.h"

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

#include "Strings/Platformer/Entities/Names/Npcs/DaemonsHallow/Igneus.h"

using namespace cocos2d;

const std::string Igneus::MapKeyIgneus = "igneus";
HexusOpponentData* Igneus::HexusOpponentDataInstance = nullptr;
const std::string Igneus::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_IGNEUS";

Igneus* Igneus::deserialize(ValueMap& properties)
{
	Igneus* instance = new Igneus(properties);

	instance->autorelease();

	return instance;
}

Igneus::Igneus(ValueMap& properties) : super(properties,
	Igneus::MapKeyIgneus,
	EntityResources::Npcs_DaemonsHallow_Igneus_Animations,
	EntityResources::Npcs_DaemonsHallow_Igneus_Emblem,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Igneus::getHexusOpponentData();
}

Igneus::~Igneus()
{
}

Vec2 Igneus::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Igneus::getEntityName()
{
	return Strings::Platformer_Entities_Names_Npcs_DaemonsHallow_Igneus::create();
}

HexusOpponentData* Igneus::getHexusOpponentData()
{
	if (Igneus::HexusOpponentDataInstance == nullptr)
	{
		Igneus::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_DaemonsHallow_Igneus_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			1.05f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Igneus::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.696f,
			HexusOpponentData::generateDeck(32, 0.696f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::ReturnToHand),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
			}),
			{ },
			nullptr
		);
	}

	return Igneus::HexusOpponentDataInstance;
}