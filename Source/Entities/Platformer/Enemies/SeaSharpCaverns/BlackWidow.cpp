//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "BlackWidow.h"

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

const std::string BlackWidow::MapKeyBlackWidow = "black-widow";
HexusOpponentData* BlackWidow::HexusOpponentDataInstance = nullptr;
const std::string BlackWidow::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BLACK_WIDOW";

BlackWidow* BlackWidow::deserialize(ValueMap& initProperties)
{
	BlackWidow* instance = new BlackWidow(initProperties);

	instance->autorelease();

	return instance;
}

BlackWidow::BlackWidow(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_BlackWidow_Animations,
	EntityResources::Enemies_SeaSharpCaverns_BlackWidow_Emblem,
	PlatformerCollisionType::Enemy,
	Size(1280.0f, 920.0f),
	0.20f,
	Vec2(-112.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = BlackWidow::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

BlackWidow::~BlackWidow()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 BlackWidow::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* BlackWidow::getHexusOpponentData()
{
	if (BlackWidow::HexusOpponentDataInstance == nullptr)
	{
		BlackWidow::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_BlackWidow_Animations,
			UIResources::Menus_Hexus_HexusFrameSeaSharpCaverns,
			0.20f,
			Vec2(-112.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			BlackWidow::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return BlackWidow::HexusOpponentDataInstance;
}