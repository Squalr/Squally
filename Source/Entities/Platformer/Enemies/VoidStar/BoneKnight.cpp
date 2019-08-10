#include "BoneKnight.h"

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

const std::string BoneKnight::MapKeyBoneKnight = "bone-knight";
HexusOpponentData* BoneKnight::HexusOpponentDataInstance = nullptr;
const std::string BoneKnight::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BONE_KNIGHT";

BoneKnight* BoneKnight::deserialize(ValueMap& initProperties)
{
	BoneKnight* instance = new BoneKnight(initProperties);

	instance->autorelease();

	return instance;
}

BoneKnight::BoneKnight(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_BoneKnight_Animations,
	EntityResources::Enemies_VoidStar_BoneKnight_Emblem,
	PlatformerCollisionType::Enemy,
	Size(540.0f, 340.0f),
	1.0f,
	Vec2(-64.0f, 0.0f))
{
	this->hexusOpponentData = BoneKnight::getHexusOpponentData();
}

BoneKnight::~BoneKnight()
{
}

Vec2 BoneKnight::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* BoneKnight::getHexusOpponentData()
{
	if (BoneKnight::HexusOpponentDataInstance == nullptr)
	{
		BoneKnight::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_VoidStar_BoneKnight_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			1.0f,
			Vec2(-64.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			BoneKnight::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.333f,
			HexusOpponentData::generateDeck(32, 0.333f,
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

	return BoneKnight::HexusOpponentDataInstance;
}