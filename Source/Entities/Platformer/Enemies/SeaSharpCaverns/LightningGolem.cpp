#include "LightningGolem.h"

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

const std::string LightningGolem::MapKeyLightningGolem = "lightning-golem";
HexusOpponentData* LightningGolem::HexusOpponentDataInstance = nullptr;
const std::string LightningGolem::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LIGHTNING_GOLEM";

LightningGolem* LightningGolem::deserialize(ValueMap& properties)
{
	LightningGolem* instance = new LightningGolem(properties);

	instance->autorelease();

	return instance;
}

LightningGolem::LightningGolem(ValueMap& properties) : super(properties,
	LightningGolem::MapKeyLightningGolem,
	EntityResources::Enemies_SeaSharpCaverns_LightningGolem_Animations,
	EntityResources::Enemies_SeaSharpCaverns_LightningGolem_Emblem,
	Size(768.0f, 840.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = LightningGolem::getHexusOpponentData();
}

LightningGolem::~LightningGolem()
{
}

Vec2 LightningGolem::getDialogueOffset()
{
	return Vec2(-32.0f, -380.0f);
}

LocalizedString* LightningGolem::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_LightningGolem::create();
}

HexusOpponentData* LightningGolem::getHexusOpponentData()
{
	if (LightningGolem::HexusOpponentDataInstance == nullptr)
	{
		LightningGolem::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(-32.0f, -380.0f),
			LightningGolem::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
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
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary3),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
				}
			)
		);
	}

	return LightningGolem::HexusOpponentDataInstance;
}