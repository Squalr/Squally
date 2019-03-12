//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "YetiBaby.h"

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

const std::string YetiBaby::MapKeyYetiBaby = "yeti-baby";
HexusOpponentData* YetiBaby::HexusOpponentDataInstance = nullptr;
const std::string YetiBaby::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_YETI_BABY";

YetiBaby* YetiBaby::deserialize(ValueMap& initProperties)
{
	YetiBaby* instance = new YetiBaby(initProperties);

	instance->autorelease();

	return instance;
}

YetiBaby::YetiBaby(ValueMap& initProperties) : PlatformerEntity(initProperties,
	EntityResources::Helpers_BalmerPeaks_YetiBaby_Animations,
	EntityResources::Helpers_BalmerPeaks_YetiBaby_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = YetiBaby::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

YetiBaby::~YetiBaby()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 YetiBaby::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* YetiBaby::getHexusOpponentData()
{
	if (YetiBaby::HexusOpponentDataInstance == nullptr)
	{
		YetiBaby::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Helpers_BalmerPeaks_YetiBaby_Animations,
			UIResources::Menus_Hexus_HexusFrameBalmerPeaks,
			0.3f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			YetiBaby::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Water,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return YetiBaby::HexusOpponentDataInstance;
}