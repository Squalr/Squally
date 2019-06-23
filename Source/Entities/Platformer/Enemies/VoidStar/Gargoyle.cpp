//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Gargoyle.h"

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

using namespace cocos2d;

const std::string Gargoyle::MapKeyGargoyle = "gargoyle";
HexusOpponentData* Gargoyle::HexusOpponentDataInstance = nullptr;
const std::string Gargoyle::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GARGOYLE";

Gargoyle* Gargoyle::deserialize(ValueMap& initProperties)
{
	Gargoyle* instance = new Gargoyle(initProperties);

	instance->autorelease();

	return instance;
}

Gargoyle::Gargoyle(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_Gargoyle_Animations,
	EntityResources::Enemies_VoidStar_Gargoyle_Emblem,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 256.0f),
	0.9f,
	Vec2(-32.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Gargoyle::getHexusOpponentData();
}

Gargoyle::~Gargoyle()
{
}

Vec2 Gargoyle::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Gargoyle::getHexusOpponentData()
{
	if (Gargoyle::HexusOpponentDataInstance == nullptr)
	{
		Gargoyle::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_VoidStar_Gargoyle_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			0.9f,
			Vec2(-32.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Gargoyle::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.250f,
			HexusOpponentData::generateDeck(32, 0.250f,
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
					
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Gargoyle::HexusOpponentDataInstance;
}