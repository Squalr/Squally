//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ReanimatedFighter.h"

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

const std::string ReanimatedFighter::MapKeyReanimatedFighter = "reanimated-fighter";
HexusOpponentData* ReanimatedFighter::HexusOpponentDataInstance = nullptr;
const std::string ReanimatedFighter::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_REANIMATED_FIGHTER";

ReanimatedFighter* ReanimatedFighter::deserialize(ValueMap& initProperties)
{
	ReanimatedFighter* instance = new ReanimatedFighter(initProperties);

	instance->autorelease();

	return instance;
}

ReanimatedFighter::ReanimatedFighter(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_ReanimatedFighter_Animations,
	EntityResources::Enemies_LambdaCrypts_ReanimatedFighter_Emblem,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 248.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = ReanimatedFighter::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

ReanimatedFighter::~ReanimatedFighter()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 ReanimatedFighter::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* ReanimatedFighter::getHexusOpponentData()
{
	if (ReanimatedFighter::HexusOpponentDataInstance == nullptr)
	{
		ReanimatedFighter::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_LambdaCrypts_ReanimatedFighter_Animations,
			UIResources::Menus_Hexus_HexusFrameLambdaCrypts,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			ReanimatedFighter::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return ReanimatedFighter::HexusOpponentDataInstance;
}