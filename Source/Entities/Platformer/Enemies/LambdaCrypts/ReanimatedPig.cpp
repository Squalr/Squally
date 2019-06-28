//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ReanimatedPig.h"

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

const std::string ReanimatedPig::MapKeyReanimatedPig = "reanimated-pig";
HexusOpponentData* ReanimatedPig::HexusOpponentDataInstance = nullptr;
const std::string ReanimatedPig::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_REANIMATED_PIG";

ReanimatedPig* ReanimatedPig::deserialize(ValueMap& initProperties)
{
	ReanimatedPig* instance = new ReanimatedPig(initProperties);

	instance->autorelease();

	return instance;
}

ReanimatedPig::ReanimatedPig(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_ReanimatedPig_Animations,
	EntityResources::Enemies_LambdaCrypts_ReanimatedPig_Emblem,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 240.0f),
	0.8f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = ReanimatedPig::getHexusOpponentData();
}

ReanimatedPig::~ReanimatedPig()
{
}

Vec2 ReanimatedPig::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* ReanimatedPig::getHexusOpponentData()
{
	if (ReanimatedPig::HexusOpponentDataInstance == nullptr)
	{
		ReanimatedPig::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_LambdaCrypts_ReanimatedPig_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			ReanimatedPig::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
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
					
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return ReanimatedPig::HexusOpponentDataInstance;
}