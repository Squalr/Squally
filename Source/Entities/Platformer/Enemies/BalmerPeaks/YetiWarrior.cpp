//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "YetiWarrior.h"

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

const std::string YetiWarrior::MapKeyYetiWarrior = "yeti-warrior";
HexusOpponentData* YetiWarrior::HexusOpponentDataInstance = nullptr;
const std::string YetiWarrior::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_YETI_WARRIOR";

YetiWarrior* YetiWarrior::deserialize(ValueMap& initProperties)
{
	YetiWarrior* instance = new YetiWarrior(initProperties);

	instance->autorelease();

	return instance;
}

YetiWarrior::YetiWarrior(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_YetiWarrior_Animations,
	EntityResources::Enemies_BalmerPeaks_YetiWarrior_Emblem,
	PlatformerCollisionType::Enemy,
	Size(380.0f, 572.0f),
	0.4f,
	Vec2(24.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = YetiWarrior::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

YetiWarrior::~YetiWarrior()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 YetiWarrior::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* YetiWarrior::getHexusOpponentData()
{
	if (YetiWarrior::HexusOpponentDataInstance == nullptr)
	{
		YetiWarrior::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_BalmerPeaks_YetiWarrior_Animations,
			UIResources::Menus_Hexus_HexusFrameBalmerPeaks,
			0.4f,
			Vec2(24.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			YetiWarrior::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return YetiWarrior::HexusOpponentDataInstance;
}