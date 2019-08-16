#include "IceGolem.h"

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

const std::string IceGolem::MapKeyIceGolem = "ice-golem";
HexusOpponentData* IceGolem::HexusOpponentDataInstance = nullptr;
const std::string IceGolem::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ICE_GOLEM";

IceGolem* IceGolem::deserialize(ValueMap& properties)
{
	IceGolem* instance = new IceGolem(properties);

	instance->autorelease();

	return instance;
}

IceGolem::IceGolem(ValueMap& properties) : PlatformerEnemy(properties,
	IceGolem::MapKeyIceGolem,
	EntityResources::Enemies_BalmerPeaks_IceGolem_Animations,
	EntityResources::Enemies_BalmerPeaks_IceGolem_Emblem,
	Size(1680.0f, 996.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = IceGolem::getHexusOpponentData();
}

IceGolem::~IceGolem()
{
}

Vec2 IceGolem::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -160.0f);
}

HexusOpponentData* IceGolem::getHexusOpponentData()
{
	if (IceGolem::HexusOpponentDataInstance == nullptr)
	{
		IceGolem::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_BalmerPeaks_IceGolem_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -160.0f),
			IceGolem::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return IceGolem::HexusOpponentDataInstance;
}