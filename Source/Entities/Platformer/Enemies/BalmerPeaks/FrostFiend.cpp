#include "FrostFiend.h"

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

const std::string FrostFiend::MapKeyFrostFiend = "frost-fiend";
HexusOpponentData* FrostFiend::HexusOpponentDataInstance = nullptr;
const std::string FrostFiend::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FROST_FIEND";

FrostFiend* FrostFiend::deserialize(ValueMap& initProperties)
{
	FrostFiend* instance = new FrostFiend(initProperties);

	instance->autorelease();

	return instance;
}

FrostFiend::FrostFiend(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_FrostFiend_Animations,
	EntityResources::Enemies_BalmerPeaks_FrostFiend_Emblem,
	PlatformerCollisionType::Enemy,
	Size(212.0f, 296.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = FrostFiend::getHexusOpponentData();
}

FrostFiend::~FrostFiend()
{
}

Vec2 FrostFiend::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -128.0f);
}

HexusOpponentData* FrostFiend::getHexusOpponentData()
{
	if (FrostFiend::HexusOpponentDataInstance == nullptr)
	{
		FrostFiend::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_BalmerPeaks_FrostFiend_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -128.0f),
			FrostFiend::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
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
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
CardList::getInstance()->cardListByName.at(CardKeys::Hex11),
CardList::getInstance()->cardListByName.at(CardKeys::Hex12),
CardList::getInstance()->cardListByName.at(CardKeys::Hex14),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return FrostFiend::HexusOpponentDataInstance;
}