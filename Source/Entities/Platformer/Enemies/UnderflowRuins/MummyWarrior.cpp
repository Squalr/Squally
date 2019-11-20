#include "MummyWarrior.h"

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

#include "Strings/Platformer/Entities/Names/Enemies/UnderflowRuins/MummyWarrior.h"

using namespace cocos2d;

const std::string MummyWarrior::MapKeyMummyWarrior = "mummy-warrior";
HexusOpponentData* MummyWarrior::HexusOpponentDataInstance = nullptr;
const std::string MummyWarrior::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MUMMY_WARRIOR";

MummyWarrior* MummyWarrior::deserialize(ValueMap& properties)
{
	MummyWarrior* instance = new MummyWarrior(properties);

	instance->autorelease();

	return instance;
}

MummyWarrior::MummyWarrior(ValueMap& properties) : super(properties,
	MummyWarrior::MapKeyMummyWarrior,
	nullptr,
	EntityResources::Enemies_UnderflowRuins_MummyWarrior_Emblem,
	Size(128.0f, 256.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = MummyWarrior::getHexusOpponentData();
}

MummyWarrior::~MummyWarrior()
{
}

Vec2 MummyWarrior::getDialogueOffset()
{
	return Vec2(0.0f, -32.0f);
}

LocalizedString* MummyWarrior::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_UnderflowRuins_MummyWarrior::create();
}

HexusOpponentData* MummyWarrior::getHexusOpponentData()
{
	if (MummyWarrior::HexusOpponentDataInstance == nullptr)
	{
		MummyWarrior::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			Vec2(-32.0f, -112.0f),
			MummyWarrior::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			HexusOpponentData::generateDeck(32, 0.333f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
					CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
				}
			)
		);
	}

	return MummyWarrior::HexusOpponentDataInstance;
}