#include "MummyWarrior.h"

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

const std::string MummyWarrior::MapKeyMummyWarrior = "mummy-warrior";
HexusOpponentData* MummyWarrior::HexusOpponentDataInstance = nullptr;
const std::string MummyWarrior::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MUMMY_WARRIOR";

MummyWarrior* MummyWarrior::deserialize(ValueMap& initProperties)
{
	MummyWarrior* instance = new MummyWarrior(initProperties);

	instance->autorelease();

	return instance;
}

MummyWarrior::MummyWarrior(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_MummyWarrior_Animations,
	EntityResources::Enemies_UnderflowRuins_MummyWarrior_Emblem,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = MummyWarrior::getHexusOpponentData();
}

MummyWarrior::~MummyWarrior()
{
}

Vec2 MummyWarrior::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* MummyWarrior::getHexusOpponentData()
{
	if (MummyWarrior::HexusOpponentDataInstance == nullptr)
	{
		MummyWarrior::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_UnderflowRuins_MummyWarrior_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			MummyWarrior::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return MummyWarrior::HexusOpponentDataInstance;
}