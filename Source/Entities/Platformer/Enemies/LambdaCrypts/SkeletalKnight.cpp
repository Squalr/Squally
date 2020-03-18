#include "SkeletalKnight.h"

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

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string SkeletalKnight::MapKeySkeletalKnight = "skeletal-knight";
HexusOpponentData* SkeletalKnight::HexusOpponentDataInstance = nullptr;
const std::string SkeletalKnight::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_KNIGHT";

SkeletalKnight* SkeletalKnight::deserialize(ValueMap& properties)
{
	SkeletalKnight* instance = new SkeletalKnight(properties);

	instance->autorelease();

	return instance;
}

SkeletalKnight::SkeletalKnight(ValueMap& properties) : super(properties,
	SkeletalKnight::MapKeySkeletalKnight,
	EntityResources::Enemies_LambdaCrypts_SkeletalKnight_Animations,
	EntityResources::Enemies_LambdaCrypts_SkeletalKnight_Emblem,
	Size(212.0f, 280.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = SkeletalKnight::getHexusOpponentData();
}

SkeletalKnight::~SkeletalKnight()
{
}

Vec2 SkeletalKnight::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* SkeletalKnight::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_SkeletalKnight::create();
}

HexusOpponentData* SkeletalKnight::getHexusOpponentData()
{
	if (SkeletalKnight::HexusOpponentDataInstance == nullptr)
	{
		SkeletalKnight::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			SkeletalKnight::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.833f,
			{

			}),
			nullptr,
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
					
				}
			)
		);
	}

	return SkeletalKnight::HexusOpponentDataInstance;
}