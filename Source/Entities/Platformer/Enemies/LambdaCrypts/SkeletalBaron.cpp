//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SkeletalBaron.h"

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

const std::string SkeletalBaron::MapKeySkeletalBaron = "skeletal-baron";
HexusOpponentData* SkeletalBaron::HexusOpponentDataInstance = nullptr;
const std::string SkeletalBaron::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_BARON";

SkeletalBaron* SkeletalBaron::deserialize(ValueMap& initProperties)
{
	SkeletalBaron* instance = new SkeletalBaron(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalBaron::SkeletalBaron(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_SkeletalBaron_Animations,
	EntityResources::Enemies_LambdaCrypts_SkeletalBaron_Emblem,
	PlatformerCollisionType::Enemy,
	Size(112.0f, 368.0f),
	0.8f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = SkeletalBaron::getHexusOpponentData();
}

SkeletalBaron::~SkeletalBaron()
{
}

Vec2 SkeletalBaron::getAvatarFrameOffset()
{
	return Vec2(16.0f, -112.0f);
}

HexusOpponentData* SkeletalBaron::getHexusOpponentData()
{
	if (SkeletalBaron::HexusOpponentDataInstance == nullptr)
	{
		SkeletalBaron::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_LambdaCrypts_SkeletalBaron_Animations,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, -144.0f),
			Vec2(16.0f, -112.0f),
			SkeletalBaron::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.750f,
			HexusOpponentData::generateDeck(32, 0.750f,
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

	return SkeletalBaron::HexusOpponentDataInstance;
}