#include "TikiGolem.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/SeaSharpCaverns/TikiGolem.h"

using namespace cocos2d;

const std::string TikiGolem::MapKeyTikiGolem = "tiki-golem";
HexusOpponentData* TikiGolem::HexusOpponentDataInstance = nullptr;
const std::string TikiGolem::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TIKI_GOLEM";

TikiGolem* TikiGolem::deserialize(ValueMap& properties)
{
	TikiGolem* instance = new TikiGolem(properties);

	instance->autorelease();

	return instance;
}

TikiGolem::TikiGolem(ValueMap& properties) : super(properties,
	TikiGolem::MapKeyTikiGolem,
	EntityResources::Enemies_SeaSharpCaverns_TikiGolem_Animations,
	EntityResources::Enemies_SeaSharpCaverns_TikiGolem_Emblem,
	Size(284.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = TikiGolem::getHexusOpponentData();
}

TikiGolem::~TikiGolem()
{
}

Vec2 TikiGolem::getDialogueOffset()
{
	return Vec2(-32.0f, -128.0f);
}

LocalizedString* TikiGolem::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_TikiGolem::create();
}

HexusOpponentData* TikiGolem::getHexusOpponentData()
{
	if (TikiGolem::HexusOpponentDataInstance == nullptr)
	{
		TikiGolem::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_TikiGolem_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -128.0f),
			TikiGolem::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.917f,
			HexusOpponentData::generateDeck(32, 0.917f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex10),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return TikiGolem::HexusOpponentDataInstance;
}