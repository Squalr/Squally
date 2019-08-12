#include "Minotaur.h"

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

const std::string Minotaur::MapKeyMinotaur = "minotaur";
HexusOpponentData* Minotaur::HexusOpponentDataInstance = nullptr;
const std::string Minotaur::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MINOTAUR";

Minotaur* Minotaur::deserialize(ValueMap& initProperties)
{
	Minotaur* instance = new Minotaur(initProperties);

	instance->autorelease();

	return instance;
}

Minotaur::Minotaur(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	Minotaur::MapKeyMinotaur,
	EntityResources::Enemies_UnderflowRuins_Minotaur_Animations,
	EntityResources::Enemies_UnderflowRuins_Minotaur_Emblem,
	Size(278.0f, 288.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Minotaur::getHexusOpponentData();
}

Minotaur::~Minotaur()
{
}

Vec2 Minotaur::getAvatarFrameOffset()
{
	return Vec2(-48.0f, -196.0f);
}

HexusOpponentData* Minotaur::getHexusOpponentData()
{
	if (Minotaur::HexusOpponentDataInstance == nullptr)
	{
		Minotaur::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_UnderflowRuins_Minotaur_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-48.0f, -196.0f),
			Minotaur::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
CardList::getInstance()->cardListByName.at(CardKeys::Binary10),
CardList::getInstance()->cardListByName.at(CardKeys::Binary2),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
CardList::getInstance()->cardListByName.at(CardKeys::Hex3),
CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
CardList::getInstance()->cardListByName.at(CardKeys::Hex2),
CardList::getInstance()->cardListByName.at(CardKeys::Hex2),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Minotaur::HexusOpponentDataInstance;
}