#include "ZombieElric.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ZombieElric::MapKeyZombieElric = "zombie-elric";
HexusOpponentData* ZombieElric::HexusOpponentDataInstance = nullptr;
const std::string ZombieElric::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ZOMBIE_ELRIC";

ZombieElric* ZombieElric::deserialize(ValueMap& properties)
{
	ZombieElric* instance = new ZombieElric(properties);

	instance->autorelease();

	return instance;
}

ZombieElric::ZombieElric(ValueMap& properties) : super(properties,
	ZombieElric::MapKeyZombieElric,
	EntityResources::Enemies_CastleValgrind_ZombieElric_Animations,
	EntityResources::Enemies_CastleValgrind_ZombieElric_Emblem,
	Size(114.0f, 208.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = ZombieElric::getHexusOpponentData();
}

ZombieElric::~ZombieElric()
{
}

Vec2 ZombieElric::getDialogueOffset()
{
	return Vec2(-16.0f, -112.0f);
}

LocalizedString* ZombieElric::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_CastleValgrind_ZombieElric::create();
}

HexusOpponentData* ZombieElric::getHexusOpponentData()
{
	if (ZombieElric::HexusOpponentDataInstance == nullptr)
	{
		ZombieElric::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameCastleValgrind,
			Vec2(-16.0f, -112.0f),
			ZombieElric::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			HexusOpponentData::generateDeck(32, 0.833f,
			{

			}),
			nullptr,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal10),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal4),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal3),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal2),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				}
			)
		);
	}

	return ZombieElric::HexusOpponentDataInstance;
}