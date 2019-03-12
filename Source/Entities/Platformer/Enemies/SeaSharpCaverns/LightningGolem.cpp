//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LightningGolem.h"

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

const std::string LightningGolem::MapKeyLightningGolem = "lightning-golem";
HexusOpponentData* LightningGolem::HexusOpponentDataInstance = nullptr;
const std::string LightningGolem::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_LIGHTNING_GOLEM";

LightningGolem* LightningGolem::deserialize(ValueMap& initProperties)
{
	LightningGolem* instance = new LightningGolem(initProperties);

	instance->autorelease();

	return instance;
}

LightningGolem::LightningGolem(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_LightningGolem_Animations,
	EntityResources::Enemies_SeaSharpCaverns_LightningGolem_Emblem,
	PlatformerCollisionType::Enemy,
	Size(768.0f, 840.0f),
	0.30f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = LightningGolem::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

LightningGolem::~LightningGolem()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 LightningGolem::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* LightningGolem::getHexusOpponentData()
{
	if (LightningGolem::HexusOpponentDataInstance == nullptr)
	{
		LightningGolem::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_LightningGolem_Animations,
			UIResources::Menus_Hexus_HexusFrameSeaSharpCaverns,
			0.30f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			LightningGolem::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return LightningGolem::HexusOpponentDataInstance;
}