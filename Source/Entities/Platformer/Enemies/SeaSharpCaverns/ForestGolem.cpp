//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ForestGolem.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////A////A////A////A////A////A////A////A////A////A/

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

using namespace cocos2d;

const std::string ForestGolem::MapKeyForestGolem = "forest-golem";
HexusOpponentData* ForestGolem::HexusOpponentDataInstance = nullptr;
const std::string ForestGolem::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FOREST_GOLEM";

ForestGolem* ForestGolem::deserialize(ValueMap& initProperties)
{
	ForestGolem* instance = new ForestGolem(initProperties);

	instance->autorelease();

	return instance;
}

ForestGolem::ForestGolem(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_ForestGolem_Animations,
	EntityResources::Enemies_SeaSharpCaverns_ForestGolem_Emblem,
	PlatformerCollisionType::Enemy,
	Size(768.0f, 840.0f),
	0.30f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = ForestGolem::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

ForestGolem::~ForestGolem()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 ForestGolem::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* ForestGolem::getHexusOpponentData()
{
	if (ForestGolem::HexusOpponentDataInstance == nullptr)
	{
		ForestGolem::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_ForestGolem_Animations,
			UIResources::Menus_Hexus_HexusFrameSeaSharpCaverns,
			0.30f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			ForestGolem::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return ForestGolem::HexusOpponentDataInstance;
}