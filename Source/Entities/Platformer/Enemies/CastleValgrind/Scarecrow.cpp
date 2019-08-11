#include "Scarecrow.h"

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

const std::string Scarecrow::MapKeyScarecrow = "scarecrow";
HexusOpponentData* Scarecrow::HexusOpponentDataInstance = nullptr;
const std::string Scarecrow::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SCARECROW";

Scarecrow* Scarecrow::deserialize(ValueMap& initProperties)
{
	Scarecrow* instance = new Scarecrow(initProperties);

	instance->autorelease();

	return instance;
}

Scarecrow::Scarecrow(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_Scarecrow_Animations,
	EntityResources::Enemies_CastleValgrind_Scarecrow_Emblem,
	Size(196.0f, 512.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Scarecrow::getHexusOpponentData();
}

Scarecrow::~Scarecrow()
{
}

Vec2 Scarecrow::getAvatarFrameOffset()
{
	return Vec2(0.0f, -312.0f);
}

HexusOpponentData* Scarecrow::getHexusOpponentData()
{
	if (Scarecrow::HexusOpponentDataInstance == nullptr)
	{
		Scarecrow::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_CastleValgrind_Scarecrow_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -196.0f),
			Vec2(0.0f, -312.0f),
			Scarecrow::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.667f,
			HexusOpponentData::generateDeck(32, 0.667f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal2),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Scarecrow::HexusOpponentDataInstance;
}