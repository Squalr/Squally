#include "Medusa.h"

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

const std::string Medusa::MapKeyMedusa = "medusa";
HexusOpponentData* Medusa::HexusOpponentDataInstance = nullptr;
const std::string Medusa::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MEDUSA";

Medusa* Medusa::deserialize(ValueMap& initProperties)
{
	Medusa* instance = new Medusa(initProperties);

	instance->autorelease();

	return instance;
}

Medusa::Medusa(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	Medusa::MapKeyMedusa,
	EntityResources::Enemies_UnderflowRuins_Medusa_Animations,
	EntityResources::Enemies_UnderflowRuins_Medusa_Emblem,
	Size(224.0f, 304.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Medusa::getHexusOpponentData();
}

Medusa::~Medusa()
{
}

Vec2 Medusa::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -196.0f);
}

HexusOpponentData* Medusa::getHexusOpponentData()
{
	if (Medusa::HexusOpponentDataInstance == nullptr)
	{
		Medusa::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_UnderflowRuins_Medusa_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -196.0f),
			Medusa::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.833f,
			HexusOpponentData::generateDeck(32, 0.833f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Steal),
CardList::getInstance()->cardListByName.at(CardKeys::Kill),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex8),
CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
CardList::getInstance()->cardListByName.at(CardKeys::Hex4),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Medusa::HexusOpponentDataInstance;
}