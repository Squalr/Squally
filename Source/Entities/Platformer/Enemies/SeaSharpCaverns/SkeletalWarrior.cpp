#include "SkeletalWarrior.h"

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

const std::string SkeletalWarrior::MapKeySkeletalWarrior = "skeletal-warrior";
HexusOpponentData* SkeletalWarrior::HexusOpponentDataInstance = nullptr;
const std::string SkeletalWarrior::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_WARRIOR";

SkeletalWarrior* SkeletalWarrior::deserialize(ValueMap& initProperties)
{
	SkeletalWarrior* instance = new SkeletalWarrior(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalWarrior::SkeletalWarrior(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	SkeletalWarrior::MapKeySkeletalWarrior,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalWarrior_Animations,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalWarrior_Emblem,
	Size(128.0f, 216.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = SkeletalWarrior::getHexusOpponentData();
}

SkeletalWarrior::~SkeletalWarrior()
{
}

Vec2 SkeletalWarrior::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* SkeletalWarrior::getHexusOpponentData()
{
	if (SkeletalWarrior::HexusOpponentDataInstance == nullptr)
	{
		SkeletalWarrior::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_SkeletalWarrior_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			SkeletalWarrior::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.250f,
			HexusOpponentData::generateDeck(32, 0.250f,
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
CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
CardList::getInstance()->cardListByName.at(CardKeys::Hex5),
CardList::getInstance()->cardListByName.at(CardKeys::Hex2),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return SkeletalWarrior::HexusOpponentDataInstance;
}