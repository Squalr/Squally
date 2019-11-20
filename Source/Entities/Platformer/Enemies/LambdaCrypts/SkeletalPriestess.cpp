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

#include "Strings/Platformer/Entities/Names/Enemies/LambdaCrypts/SkeletalPriestess.h"

using namespace cocos2d;

const std::string SkeletalPriestess::MapKeySkeletalPriestess = "skeletal-priestess";
HexusOpponentData* SkeletalPriestess::HexusOpponentDataInstance = nullptr;
const std::string SkeletalPriestess::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_PRIESTESS";

SkeletalPriestess* SkeletalPriestess::deserialize(ValueMap& properties)
{
	SkeletalPriestess* instance = new SkeletalPriestess(properties);

	instance->autorelease();

	return instance;
}

SkeletalPriestess::SkeletalPriestess(ValueMap& properties) : super(properties,
	SkeletalPriestess::MapKeySkeletalPriestess,
	nullptr,
	EntityResources::Enemies_LambdaCrypts_SkeletalPriestess_Emblem,
	Size(196.0f, 312.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = SkeletalPriestess::getHexusOpponentData();
}

SkeletalPriestess::~SkeletalPriestess()
{
}

Vec2 SkeletalPriestess::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* SkeletalPriestess::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_LambdaCrypts_SkeletalPriestess::create();
}

HexusOpponentData* SkeletalPriestess::getHexusOpponentData()
{
	if (SkeletalPriestess::HexusOpponentDataInstance == nullptr)
	{
		SkeletalPriestess::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameLambdaCrypts,
			Vec2(-32.0f, -112.0f),
			SkeletalPriestess::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateDeck(32, 0.917f,
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

	return SkeletalPriestess::HexusOpponentDataInstance;
}