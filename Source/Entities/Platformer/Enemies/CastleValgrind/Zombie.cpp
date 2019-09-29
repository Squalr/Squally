#include "Zombie.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/CastleValgrind/Zombie.h"

using namespace cocos2d;

const std::string Zombie::MapKeyZombie = "zombie";
HexusOpponentData* Zombie::HexusOpponentDataInstance = nullptr;
const std::string Zombie::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ZOMBIE";

Zombie* Zombie::deserialize(ValueMap& properties)
{
	Zombie* instance = new Zombie(properties);

	instance->autorelease();

	return instance;
}

Zombie::Zombie(ValueMap& properties) : super(properties,
	Zombie::MapKeyZombie,
	EntityResources::Enemies_CastleValgrind_Zombie_Animations,
	EntityResources::Enemies_CastleValgrind_Zombie_Emblem,
	Size(146.0f, 248.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Zombie::getHexusOpponentData();
}

Zombie::~Zombie()
{
}

Vec2 Zombie::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* Zombie::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_Zombie::create();
}

HexusOpponentData* Zombie::getHexusOpponentData()
{
	if (Zombie::HexusOpponentDataInstance == nullptr)
	{
		Zombie::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_CastleValgrind_Zombie_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Zombie::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.083f,
			HexusOpponentData::generateDeck(32, 0.083f,
			{

			}),
			StateOverride::create(
				// Player losses
				1,
				// Enemy losses
				1,
				// Player's turn
				true,
				// Player passed
				true,
				// Enemy passed
				true,
				// Player deck
				std::vector<CardData*>
				{
					
				},
				// Enemy deck
				std::vector<CardData*>
				{
					
				},
				// Player hand
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
CardList::getInstance()->cardListByName.at(CardKeys::Binary14),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				}
			)
		);
	}

	return Zombie::HexusOpponentDataInstance;
}