#include "Cryogen.h"

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

const std::string Cryogen::MapKey = "cryogen";
HexusOpponentData* Cryogen::HexusOpponentDataInstance = nullptr;
const std::string Cryogen::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CYROGEN";

Cryogen* Cryogen::deserialize(ValueMap& properties)
{
	Cryogen* instance = new Cryogen(properties);

	instance->autorelease();

	return instance;
}

Cryogen::Cryogen(ValueMap& properties) : super(properties,
	Cryogen::MapKey,
	EntityResources::Enemies_BalmerPeaks_Cryogen_Animations,
	EntityResources::Enemies_BalmerPeaks_Cryogen_Emblem,
	Size(420.0f, 420.0f),
	0.8f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Cryogen::getHexusOpponentData();
}

Cryogen::~Cryogen()
{
}

Vec2 Cryogen::getDialogueOffset()
{
	return Vec2(-48.0f, -232.0f);
}

LocalizedString* Cryogen::getEntityName()
{
	return Strings::Platformer_Entities_Names_Enemies_BalmerPeaks_Cryogen::create();
}

HexusOpponentData* Cryogen::getHexusOpponentData()
{
	if (Cryogen::HexusOpponentDataInstance == nullptr)
	{
		Cryogen::HexusOpponentDataInstance = new HexusOpponentData(
			nullptr,
			HexusResources::Menus_HexusFrameBalmerPeaks,
			Vec2(-48.0f, -232.0f),
			Cryogen::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
					CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary11),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
					CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
					CardList::getInstance()->cardListByName.at(CardKeys::Hex9),
				}
			)
		);
	}

	return Cryogen::HexusOpponentDataInstance;
}