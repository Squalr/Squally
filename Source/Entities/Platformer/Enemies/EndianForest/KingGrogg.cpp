#include "KingGrogg.h"

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

const std::string KingGrogg::MapKeyKingGrogg = "king-grogg";
HexusOpponentData* KingGrogg::HexusOpponentDataInstance = nullptr;
const std::string KingGrogg::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_KING_GROGG";

KingGrogg* KingGrogg::deserialize(ValueMap& initProperties)
{
	KingGrogg* instance = new KingGrogg(initProperties);

	instance->autorelease();

	return instance;
}

KingGrogg::KingGrogg(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_KingGrogg_Animations,
	EntityResources::Enemies_EndianForest_KingGrogg_Emblem,
	Size(412.0f, 412.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = KingGrogg::getHexusOpponentData();
}

KingGrogg::~KingGrogg()
{
}

Vec2 KingGrogg::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -280.0f);
}

HexusOpponentData* KingGrogg::getHexusOpponentData()
{
	if (KingGrogg::HexusOpponentDataInstance == nullptr)
	{
		KingGrogg::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_KingGrogg_Animations,
			HexusResources::Menus_HexusFrameEndianForest,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -160.0f),
			Vec2(-32.0f, -280.0f),
			KingGrogg::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			1.000f,
			HexusOpponentData::generateDeck(32, 1.000f,
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
CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal9),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal9),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal9),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return KingGrogg::HexusOpponentDataInstance;
}