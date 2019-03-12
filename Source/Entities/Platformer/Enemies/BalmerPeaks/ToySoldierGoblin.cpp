//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ToySoldierGoblin.h"

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

const std::string ToySoldierGoblin::MapKeyToySoldierGoblin = "toy-soldier-goblin";
HexusOpponentData* ToySoldierGoblin::HexusOpponentDataInstance = nullptr;
const std::string ToySoldierGoblin::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_TOY_SOLDIER_GOBLIN";

ToySoldierGoblin* ToySoldierGoblin::deserialize(ValueMap& initProperties)
{
	ToySoldierGoblin* instance = new ToySoldierGoblin(initProperties);

	instance->autorelease();

	return instance;
}

ToySoldierGoblin::ToySoldierGoblin(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_ToySoldierGoblin_Animations,
	EntityResources::Enemies_BalmerPeaks_ToySoldierGoblin_Emblem,
	PlatformerCollisionType::Enemy,
	Size(112.0f, 288.0f),
	0.8f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = ToySoldierGoblin::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

ToySoldierGoblin::~ToySoldierGoblin()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 ToySoldierGoblin::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* ToySoldierGoblin::getHexusOpponentData()
{
	if (ToySoldierGoblin::HexusOpponentDataInstance == nullptr)
	{
		ToySoldierGoblin::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_BalmerPeaks_ToySoldierGoblin_Animations,
			UIResources::Menus_Hexus_HexusFrameBalmerPeaks,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			ToySoldierGoblin::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return ToySoldierGoblin::HexusOpponentDataInstance;
}