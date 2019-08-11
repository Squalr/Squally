#include "Yeti.h"

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

const std::string Yeti::MapKeyYeti = "yeti";
HexusOpponentData* Yeti::HexusOpponentDataInstance = nullptr;
const std::string Yeti::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_YETI";

Yeti* Yeti::deserialize(ValueMap& initProperties)
{
	Yeti* instance = new Yeti(initProperties);

	instance->autorelease();

	return instance;
}

Yeti::Yeti(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_Yeti_Animations,
	EntityResources::Enemies_BalmerPeaks_Yeti_Emblem,
	Size(380.0f, 572.0f),
	1.0f,
	Vec2(24.0f, 0.0f))
{
	this->hexusOpponentData = Yeti::getHexusOpponentData();
}

Yeti::~Yeti()
{
}

Vec2 Yeti::getAvatarFrameOffset()
{
	return Vec2(-64.0f, -160.0f);
}

HexusOpponentData* Yeti::getHexusOpponentData()
{
	if (Yeti::HexusOpponentDataInstance == nullptr)
	{
		Yeti::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_BalmerPeaks_Yeti_Animations,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			1.0f,
			Vec2(24.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-64.0f, -160.0f),
			Yeti::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			0.083f,
			HexusOpponentData::generateDeck(32, 0.083f,
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
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
CardList::getInstance()->cardListByName.at(CardKeys::Binary9),
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

	return Yeti::HexusOpponentDataInstance;
}