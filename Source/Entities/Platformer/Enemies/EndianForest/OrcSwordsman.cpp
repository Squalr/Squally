#include "OrcSwordsman.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/EndianForest/OrcSwordsman.h"

using namespace cocos2d;

const std::string OrcSwordsman::MapKeyOrcSwordsman = "orc-swordsman";
HexusOpponentData* OrcSwordsman::HexusOpponentDataInstance = nullptr;
const std::string OrcSwordsman::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ORC_SWORDSMAN";

OrcSwordsman* OrcSwordsman::deserialize(ValueMap& properties)
{
	OrcSwordsman* instance = new OrcSwordsman(properties);

	instance->autorelease();

	return instance;
}

OrcSwordsman::OrcSwordsman(ValueMap& properties) : super(properties,
	OrcSwordsman::MapKeyOrcSwordsman,
	EntityResources::Enemies_EndianForest_OrcSwordsman_Animations,
	EntityResources::Enemies_EndianForest_OrcSwordsman_Emblem,
	Size(256.0f, 228.0f),
	0.9f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = OrcSwordsman::getHexusOpponentData();
}

OrcSwordsman::~OrcSwordsman()
{
}

Vec2 OrcSwordsman::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* OrcSwordsman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_EndianForest_OrcSwordsman::create();
}

HexusOpponentData* OrcSwordsman::getHexusOpponentData()
{
	if (OrcSwordsman::HexusOpponentDataInstance == nullptr)
	{
		OrcSwordsman::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_OrcSwordsman_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			OrcSwordsman::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.385f,
			HexusOpponentData::generateDeck(32, 0.385f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Kill),
					CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal12),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex11),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return OrcSwordsman::HexusOpponentDataInstance;
}