#include "Rhinoman.h"

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

const std::string Rhinoman::MapKeyRhinoman = "rhinoman";
HexusOpponentData* Rhinoman::HexusOpponentDataInstance = nullptr;
const std::string Rhinoman::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_RHINOMAN";

Rhinoman* Rhinoman::deserialize(ValueMap& properties)
{
	Rhinoman* instance = new Rhinoman(properties);

	instance->autorelease();

	return instance;
}

Rhinoman::Rhinoman(ValueMap& properties) : super(properties,
	Rhinoman::MapKeyRhinoman,
	EntityResources::Enemies_SeaSharpCaverns_Rhinoman_Animations,
	EntityResources::Enemies_SeaSharpCaverns_Rhinoman_Emblem,
	Size(592.0f, 592.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Rhinoman::getHexusOpponentData();
}

Rhinoman::~Rhinoman()
{
}

Vec2 Rhinoman::getDialogueOffset()
{
	return Vec2(0.0f, -420.0f);
}

LocalizedString* Rhinoman::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_SeaSharpCaverns_Rhinoman::create();
}

HexusOpponentData* Rhinoman::getHexusOpponentData()
{
	if (Rhinoman::HexusOpponentDataInstance == nullptr)
	{
		Rhinoman::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			Vec2(0.0f, -420.0f),
			Rhinoman::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateDeck(32, 1.000f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary4),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal15),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				}
			)
		);
	}

	return Rhinoman::HexusOpponentDataInstance;
}