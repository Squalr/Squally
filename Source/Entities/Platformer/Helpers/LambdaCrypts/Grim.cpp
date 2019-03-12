//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Grim.h"

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

const std::string Grim::MapKeyGrim = "grim";
HexusOpponentData* Grim::HexusOpponentDataInstance = nullptr;
const std::string Grim::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GRIM";

Grim* Grim::deserialize(ValueMap& initProperties)
{
	Grim* instance = new Grim(initProperties);

	instance->autorelease();

	return instance;
}

Grim::Grim(ValueMap& initProperties) : PlatformerEntity(initProperties,
	EntityResources::Helpers_LambdaCrypts_Grim_Animations,
	EntityResources::Helpers_LambdaCrypts_Grim_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(224.0f, 440.0f),
	0.3f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Grim::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Grim::~Grim()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Grim::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* Grim::getHexusOpponentData()
{
	if (Grim::HexusOpponentDataInstance == nullptr)
	{
		Grim::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Helpers_LambdaCrypts_Grim_Animations,
			UIResources::Menus_Hexus_HexusFrameLambdaCrypts,
			0.3f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			Grim::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return Grim::HexusOpponentDataInstance;
}