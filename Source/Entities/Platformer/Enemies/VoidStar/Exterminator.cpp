//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Exterminator.h"

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

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////A////A////A////A////A////A////A////A////A////A/

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

using namespace cocos2d;

const std::string Exterminator::MapKeyExterminator = "exterminator";
HexusOpponentData* Exterminator::HexusOpponentDataInstance = nullptr;
const std::string Exterminator::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_EXTERMINATOR";

Exterminator* Exterminator::deserialize(ValueMap& initProperties)
{
	Exterminator* instance = new Exterminator(initProperties);

	instance->autorelease();

	return instance;
}

Exterminator::Exterminator(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_Exterminator_Animations,
	EntityResources::Enemies_VoidStar_Exterminator_Emblem,
	PlatformerCollisionType::Enemy,
	Size(320.0f, 278.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Exterminator::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/
	
	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Exterminator::~Exterminator()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Exterminator::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Exterminator::getHexusOpponentData()
{
	if (Exterminator::HexusOpponentDataInstance == nullptr)
	{
		Exterminator::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_VoidStar_Exterminator_Animations,
			HexusResources::Menus_HexusFrameVoidStar,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Exterminator::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			0.917f,
			HexusOpponentData::generateDeck(32, 0.917f,
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

	return Exterminator::HexusOpponentDataInstance;
}