#include "SkeletalNecromancer.h"

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

const std::string SkeletalNecromancer::MapKey = "skeletal-necromancer";
HexusOpponentData* SkeletalNecromancer::HexusOpponentDataInstance = nullptr;
const std::string SkeletalNecromancer::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_NECROMANCER";

SkeletalNecromancer* SkeletalNecromancer::deserialize(ValueMap& properties)
{
	SkeletalNecromancer* instance = new SkeletalNecromancer(properties);

	instance->autorelease();

	return instance;
}

SkeletalNecromancer::SkeletalNecromancer(ValueMap& properties) : super(properties,
	SkeletalNecromancer::MapKey,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalNecromancer_Animations,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalNecromancer_Emblem,
	Size(128.0f, 228.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = SkeletalNecromancer::getHexusOpponentData();
}

SkeletalNecromancer::~SkeletalNecromancer()
{
}

Vec2 SkeletalNecromancer::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* SkeletalNecromancer::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_SkeletalNecromancer::create();
}

HexusOpponentData* SkeletalNecromancer::getHexusOpponentData()
{
	if (SkeletalNecromancer::HexusOpponentDataInstance == nullptr)
	{
		SkeletalNecromancer::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -112.0f),
			SkeletalNecromancer::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 0.500f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				}
			)
		);
	}

	return SkeletalNecromancer::HexusOpponentDataInstance;
}