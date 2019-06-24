//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Centaur.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Centaur::MapKeyCentaur = "centaur";
HexusOpponentData* Centaur::HexusOpponentDataInstance = nullptr;
const std::string Centaur::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CENTAUR";

Centaur* Centaur::deserialize(ValueMap& initProperties)
{
	Centaur* instance = new Centaur(initProperties);

	instance->autorelease();

	return instance;
}

Centaur::Centaur(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_Centaur_Animations,
	EntityResources::Enemies_EndianForest_Centaur_Emblem,
	PlatformerCollisionType::Enemy,
	Size(296.0f, 256.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Centaur::getHexusOpponentData();
}

Centaur::~Centaur()
{
}

Vec2 Centaur::getAvatarFrameOffset()
{
	return Vec2(-48.0f, -212.0f);
}

HexusOpponentData* Centaur::getHexusOpponentData()
{
	if (Centaur::HexusOpponentDataInstance == nullptr)
	{
		Centaur::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_Centaur_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-48.0f, -212.0f),
			Centaur::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.231f,
			HexusOpponentData::generateDeck(32, 0.231f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Addition),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Centaur::HexusOpponentDataInstance;
}