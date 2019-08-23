#include "OrcWarrior.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/EndianForest/OrcWarrior.h"

using namespace cocos2d;

const std::string OrcWarrior::MapKeyOrcWarrior = "orc-warrior";
HexusOpponentData* OrcWarrior::HexusOpponentDataInstance = nullptr;
const std::string OrcWarrior::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ORC_WARRIOR";

OrcWarrior* OrcWarrior::deserialize(ValueMap& properties)
{
	OrcWarrior* instance = new OrcWarrior(properties);

	instance->autorelease();

	return instance;
}

OrcWarrior::OrcWarrior(ValueMap& properties) : super(properties,
	OrcWarrior::MapKeyOrcWarrior,
	EntityResources::Enemies_EndianForest_OrcWarrior_Animations,
	EntityResources::Enemies_EndianForest_OrcWarrior_Emblem,
	Size(256.0f, 228.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = OrcWarrior::getHexusOpponentData();
}

OrcWarrior::~OrcWarrior()
{
}

Vec2 OrcWarrior::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* OrcWarrior::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_OrcWarrior::create();
}

HexusOpponentData* OrcWarrior::getHexusOpponentData()
{
	if (OrcWarrior::HexusOpponentDataInstance == nullptr)
	{
		OrcWarrior::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_OrcWarrior_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			OrcWarrior::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.692f,
			HexusOpponentData::generateDeck(32, 0.692f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return OrcWarrior::HexusOpponentDataInstance;
}