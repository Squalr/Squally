//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SkeletalPriestess.h"

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

const std::string SkeletalPriestess::MapKeySkeletalPriestess = "skeletal-priestess";
HexusOpponentData* SkeletalPriestess::HexusOpponentDataInstance = nullptr;
const std::string SkeletalPriestess::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_PRIESTESS";

SkeletalPriestess* SkeletalPriestess::deserialize(ValueMap& initProperties)
{
	SkeletalPriestess* instance = new SkeletalPriestess(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalPriestess::SkeletalPriestess(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_SkeletalPriestess_Animations,
	EntityResources::Enemies_LambdaCrypts_SkeletalPriestess_Emblem,
	PlatformerCollisionType::Enemy,
	Size(196.0f, 312.0f),
	0.8f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = SkeletalPriestess::getHexusOpponentData();
}

SkeletalPriestess::~SkeletalPriestess()
{
}

Vec2 SkeletalPriestess::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* SkeletalPriestess::getHexusOpponentData()
{
	if (SkeletalPriestess::HexusOpponentDataInstance == nullptr)
	{
		SkeletalPriestess::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_LambdaCrypts_SkeletalPriestess_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			SkeletalPriestess::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
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

	return SkeletalPriestess::HexusOpponentDataInstance;
}