//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Abomination.h"

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

const std::string Abomination::MapKeyAbomination = "abomination";
HexusOpponentData* Abomination::HexusOpponentDataInstance = nullptr;
const std::string Abomination::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ABOMINATION";

Abomination* Abomination::deserialize(ValueMap& initProperties)
{
	Abomination* instance = new Abomination(initProperties);

	instance->autorelease();

	return instance;
}

Abomination::Abomination(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_LambdaCrypts_Abomination_Animations,
	EntityResources::Enemies_LambdaCrypts_Abomination_Emblem,
	PlatformerCollisionType::Enemy,
	Size(296.0f, 356.0f),
	0.6f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Abomination::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Abomination::~Abomination()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Abomination::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* Abomination::getHexusOpponentData()
{
	if (Abomination::HexusOpponentDataInstance == nullptr)
	{
		Abomination::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_LambdaCrypts_Abomination_Animations,
			UIResources::Menus_Hexus_HexusFrameLambdaCrypts,
			0.6f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			Abomination::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return Abomination::HexusOpponentDataInstance;
}