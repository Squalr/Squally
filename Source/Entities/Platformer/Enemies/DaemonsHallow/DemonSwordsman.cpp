//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DemonSwordsman.h"

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

const std::string DemonSwordsman::MapKeyDemonSwordsman = "demon-swordsman";
HexusOpponentData* DemonSwordsman::HexusOpponentDataInstance = nullptr;
const std::string DemonSwordsman::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_SWORDSMAN";

DemonSwordsman* DemonSwordsman::deserialize(ValueMap& initProperties)
{
	DemonSwordsman* instance = new DemonSwordsman(initProperties);

	instance->autorelease();

	return instance;
}

DemonSwordsman::DemonSwordsman(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonSwordsman_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonSwordsman_Emblem,
	PlatformerCollisionType::Enemy,
	Size(212.0f, 268.0f),
	0.65f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = DemonSwordsman::getHexusOpponentData();
}

DemonSwordsman::~DemonSwordsman()
{
}

Vec2 DemonSwordsman::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* DemonSwordsman::getHexusOpponentData()
{
	if (DemonSwordsman::HexusOpponentDataInstance == nullptr)
	{
		DemonSwordsman::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_DemonSwordsman_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			0.65f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			DemonSwordsman::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.083f,
			HexusOpponentData::generateDeck(32, 0.083f,
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

	return DemonSwordsman::HexusOpponentDataInstance;
}