//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OrcBomber.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string OrcBomber::MapKeyOrcBomber = "orc-bomber";
HexusOpponentData* OrcBomber::HexusOpponentDataInstance = nullptr;
const std::string OrcBomber::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ORC_BOMBER";

OrcBomber* OrcBomber::deserialize(ValueMap& initProperties)
{
	OrcBomber* instance = new OrcBomber(initProperties);

	instance->autorelease();

	return instance;
}

OrcBomber::OrcBomber(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_OrcBomber_Animations,
	EntityResources::Enemies_EndianForest_OrcBomber_Emblem,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 218.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = OrcBomber::getHexusOpponentData();
}

OrcBomber::~OrcBomber()
{
}

Vec2 OrcBomber::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* OrcBomber::getHexusOpponentData()
{
	if (OrcBomber::HexusOpponentDataInstance == nullptr)
	{
		OrcBomber::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_OrcBomber_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			OrcBomber::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.769f,
			HexusOpponentData::generateDeck(32, 0.769f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Mov),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return OrcBomber::HexusOpponentDataInstance;
}