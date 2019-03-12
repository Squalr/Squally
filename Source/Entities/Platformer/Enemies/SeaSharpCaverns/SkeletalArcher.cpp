//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SkeletalArcher.h"

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

const std::string SkeletalArcher::MapKeySkeletalArcher = "skeletal-archer";
HexusOpponentData* SkeletalArcher::HexusOpponentDataInstance = nullptr;
const std::string SkeletalArcher::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_ARCHER";

SkeletalArcher* SkeletalArcher::deserialize(ValueMap& initProperties)
{
	SkeletalArcher* instance = new SkeletalArcher(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalArcher::SkeletalArcher(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalArcher_Animations,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalArcher_Emblem,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 216.0f),
	0.8f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = SkeletalArcher::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

SkeletalArcher::~SkeletalArcher()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 SkeletalArcher::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* SkeletalArcher::getHexusOpponentData()
{
	if (SkeletalArcher::HexusOpponentDataInstance == nullptr)
	{
		SkeletalArcher::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_SkeletalArcher_Animations,
			UIResources::Menus_Hexus_HexusFrameSeaSharpCaverns,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			SkeletalArcher::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return SkeletalArcher::HexusOpponentDataInstance;
}