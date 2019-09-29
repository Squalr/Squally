#include "GoblinElf.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/BalmerPeaks/GoblinElf.h"

using namespace cocos2d;

const std::string GoblinElf::MapKeyGoblinElf = "goblin-elf";
HexusOpponentData* GoblinElf::HexusOpponentDataInstance = nullptr;
const std::string GoblinElf::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GOBLIN_ELF";

GoblinElf* GoblinElf::deserialize(ValueMap& properties)
{
	GoblinElf* instance = new GoblinElf(properties);

	instance->autorelease();

	return instance;
}

GoblinElf::GoblinElf(ValueMap& properties) : super(properties,
	GoblinElf::MapKeyGoblinElf,
	EntityResources::Enemies_BalmerPeaks_GoblinElf_Animations,
	EntityResources::Enemies_BalmerPeaks_GoblinElf_Emblem,
	Size(140.0f, 296.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = GoblinElf::getHexusOpponentData();
}

GoblinElf::~GoblinElf()
{
}

Vec2 GoblinElf::getDialogueOffset()
{
	return Vec2(-32.0f, -128.0f);
}

LocalizedString* GoblinElf::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BalmerPeaks_GoblinElf::create();
}

HexusOpponentData* GoblinElf::getHexusOpponentData()
{
	if (GoblinElf::HexusOpponentDataInstance == nullptr)
	{
		GoblinElf::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_BalmerPeaks_GoblinElf_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -128.0f),
			GoblinElf::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			0.500f,
			HexusOpponentData::generateDeck(32, 0.500f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
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

	return GoblinElf::HexusOpponentDataInstance;
}