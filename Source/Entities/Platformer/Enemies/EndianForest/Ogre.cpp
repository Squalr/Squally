#include "Ogre.h"

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

const std::string Ogre::MapKeyOgre = "ogre";
HexusOpponentData* Ogre::HexusOpponentDataInstance = nullptr;
const std::string Ogre::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_OGRE";

Ogre* Ogre::deserialize(ValueMap& properties)
{
	Ogre* instance = new Ogre(properties);

	instance->autorelease();

	return instance;
}

Ogre::Ogre(ValueMap& properties) : PlatformerEnemy(properties,
	Ogre::MapKeyOgre,
	EntityResources::Enemies_EndianForest_Ogre_Animations,
	EntityResources::Enemies_EndianForest_Ogre_Emblem,
	Size(256.0f, 248.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Ogre::getHexusOpponentData();
}

Ogre::~Ogre()
{
}

Vec2 Ogre::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Ogre::getHexusOpponentData()
{
	if (Ogre::HexusOpponentDataInstance == nullptr)
	{
		Ogre::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_Ogre_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Ogre::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.846f,
			HexusOpponentData::generateDeck(32, 0.846f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Mov),
CardList::getInstance()->cardListByName.at(CardKeys::Mov),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal0),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Hex9),
CardList::getInstance()->cardListByName.at(CardKeys::Hex9),
CardList::getInstance()->cardListByName.at(CardKeys::Hex9),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Ogre::HexusOpponentDataInstance;
}