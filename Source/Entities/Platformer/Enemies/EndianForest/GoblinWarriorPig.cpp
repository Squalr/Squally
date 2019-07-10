#include "GoblinWarriorPig.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Consumables/Speed/ThrowSpeedRune.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/Slash.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string GoblinWarriorPig::MapKeyGoblinWarriorPig = "goblin-warrior-pig";
HexusOpponentData* GoblinWarriorPig::HexusOpponentDataInstance = nullptr;
const std::string GoblinWarriorPig::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GOBLIN_WARRIOR_PIG";

GoblinWarriorPig* GoblinWarriorPig::deserialize(ValueMap& initProperties)
{
	GoblinWarriorPig* instance = new GoblinWarriorPig(initProperties);

	instance->autorelease();

	return instance;
}

GoblinWarriorPig::GoblinWarriorPig(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_GoblinWarriorPig_Animations,
	EntityResources::Enemies_EndianForest_GoblinWarriorPig_Emblem,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 296.0f),
	0.8f,
	Vec2(0.0f, 0.0f),
	14,
	8)
{
	this->hexusOpponentData = GoblinWarriorPig::getHexusOpponentData();

	this->registerAttack(Slash::create(0.7f, 0.2f));
	// this->registerAttack(ThrowSpeedRune::create());

	this->dropTable.push_back(this->createDrop(SpeedRune::SaveKeySpeedRune, 0.35f));
}

GoblinWarriorPig::~GoblinWarriorPig()
{
}

Vec2 GoblinWarriorPig::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* GoblinWarriorPig::getHexusOpponentData()
{
	if (GoblinWarriorPig::HexusOpponentDataInstance == nullptr)
	{
		GoblinWarriorPig::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_GoblinWarriorPig_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			GoblinWarriorPig::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.154f,
			HexusOpponentData::generateDeck(32, 0.154f,
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
CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
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
CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return GoblinWarriorPig::HexusOpponentDataInstance;
}