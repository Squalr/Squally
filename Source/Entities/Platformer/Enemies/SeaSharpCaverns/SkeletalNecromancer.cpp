//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SkeletalNecromancer.h"

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

const std::string SkeletalNecromancer::MapKeySkeletalNecromancer = "skeletal-necromancer";
HexusOpponentData* SkeletalNecromancer::HexusOpponentDataInstance = nullptr;
const std::string SkeletalNecromancer::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_NECROMANCER";

SkeletalNecromancer* SkeletalNecromancer::deserialize(ValueMap& initProperties)
{
	SkeletalNecromancer* instance = new SkeletalNecromancer(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalNecromancer::SkeletalNecromancer(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalNecromancer_Animations,
	EntityResources::Enemies_SeaSharpCaverns_SkeletalNecromancer_Emblem,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 228.0f),
	0.8f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = SkeletalNecromancer::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

SkeletalNecromancer::~SkeletalNecromancer()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 SkeletalNecromancer::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* SkeletalNecromancer::getHexusOpponentData()
{
	if (SkeletalNecromancer::HexusOpponentDataInstance == nullptr)
	{
		SkeletalNecromancer::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_SeaSharpCaverns_SkeletalNecromancer_Animations,
			UIResources::Menus_Hexus_HexusFrameSeaSharpCaverns,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			SkeletalNecromancer::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return SkeletalNecromancer::HexusOpponentDataInstance;
}