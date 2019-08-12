#include "EarthElemental.h"

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

const std::string EarthElemental::MapKeyEarthElemental = "earth-elemental";
HexusOpponentData* EarthElemental::HexusOpponentDataInstance = nullptr;
const std::string EarthElemental::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EARTH_ELEMENTAL";

EarthElemental* EarthElemental::deserialize(ValueMap& initProperties)
{
	EarthElemental* instance = new EarthElemental(initProperties);

	instance->autorelease();

	return instance;
}

EarthElemental::EarthElemental(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EarthElemental::MapKeyEarthElemental,
	EntityResources::Enemies_SeaSharpCaverns_EarthElemental_Animations,
	EntityResources::Enemies_SeaSharpCaverns_EarthElemental_Emblem,
	Size(820.0f, 1480.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = EarthElemental::getHexusOpponentData();
}

EarthElemental::~EarthElemental()
{
}

Vec2 EarthElemental::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -224.0f);
}

HexusOpponentData* EarthElemental::getHexusOpponentData()
{
	if (EarthElemental::HexusOpponentDataInstance == nullptr)
	{
		EarthElemental::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_EarthElemental_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -224.0f),
			Vec2(-32.0f, -224.0f),
			EarthElemental::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Addition),
CardList::getInstance()->cardListByName.at(CardKeys::Subtraction),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal2),
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
CardList::getInstance()->cardListByName.at(CardKeys::Decimal12),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal12),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return EarthElemental::HexusOpponentDataInstance;
}