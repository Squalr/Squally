//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "SkeletalCleaver.h"

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

const std::string SkeletalCleaver::MapKeySkeletalCleaver = "skeletal-cleaver";
HexusOpponentData* SkeletalCleaver::HexusOpponentDataInstance = nullptr;
const std::string SkeletalCleaver::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SKELETAL_CLEAVER";

SkeletalCleaver* SkeletalCleaver::deserialize(ValueMap& initProperties)
{
	SkeletalCleaver* instance = new SkeletalCleaver(initProperties);

	instance->autorelease();

	return instance;
}

SkeletalCleaver::SkeletalCleaver(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_SkeletalCleaver_Animations,
	EntityResources::Enemies_LambdaCrypts_SkeletalCleaver_Emblem,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 312.0f),
	0.8f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = SkeletalCleaver::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

SkeletalCleaver::~SkeletalCleaver()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 SkeletalCleaver::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* SkeletalCleaver::getHexusOpponentData()
{
	if (SkeletalCleaver::HexusOpponentDataInstance == nullptr)
	{
		SkeletalCleaver::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_LambdaCrypts_SkeletalCleaver_Animations,
			UIResources::Menus_Hexus_HexusFrameLambdaCrypts,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			SkeletalCleaver::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return SkeletalCleaver::HexusOpponentDataInstance;
}