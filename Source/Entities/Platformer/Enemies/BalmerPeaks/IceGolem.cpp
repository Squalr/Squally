//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "IceGolem.h"

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

const std::string IceGolem::MapKeyIceGolem = "ice-golem";
HexusOpponentData* IceGolem::HexusOpponentDataInstance = nullptr;
const std::string IceGolem::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ICE_GOLEM";

IceGolem* IceGolem::deserialize(ValueMap& initProperties)
{
	IceGolem* instance = new IceGolem(initProperties);

	instance->autorelease();

	return instance;
}

IceGolem::IceGolem(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_IceGolem_Animations,
	EntityResources::Enemies_BalmerPeaks_IceGolem_Emblem,
	PlatformerCollisionType::Enemy,
	Size(1680.0f, 996.0f),
	0.35f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = IceGolem::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

IceGolem::~IceGolem()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 IceGolem::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* IceGolem::getHexusOpponentData()
{
	if (IceGolem::HexusOpponentDataInstance == nullptr)
	{
		IceGolem::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_BalmerPeaks_IceGolem_Animations,
			UIResources::Menus_Hexus_HexusFrameBalmerPeaks,
			0.35f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			IceGolem::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return IceGolem::HexusOpponentDataInstance;
}