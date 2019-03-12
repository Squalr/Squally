//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Gargoyle.h"

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

const std::string Gargoyle::MapKeyGargoyle = "gargoyle";
HexusOpponentData* Gargoyle::HexusOpponentDataInstance = nullptr;
const std::string Gargoyle::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GARGOYLE";

Gargoyle* Gargoyle::deserialize(ValueMap& initProperties)
{
	Gargoyle* instance = new Gargoyle(initProperties);

	instance->autorelease();

	return instance;
}

Gargoyle::Gargoyle(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_Gargoyle_Animations,
	EntityResources::Enemies_LambdaCrypts_Gargoyle_Emblem,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 256.0f),
	0.9f,
	Vec2(-32.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Gargoyle::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Gargoyle::~Gargoyle()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Gargoyle::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* Gargoyle::getHexusOpponentData()
{
	if (Gargoyle::HexusOpponentDataInstance == nullptr)
	{
		Gargoyle::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_LambdaCrypts_Gargoyle_Animations,
			UIResources::Menus_Hexus_HexusFrameLambdaCrypts,
			0.9f,
			Vec2(-32.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			Gargoyle::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return Gargoyle::HexusOpponentDataInstance;
}