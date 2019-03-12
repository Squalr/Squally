//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GoblinWarriorPig.h"

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

const std::string GoblinWarriorPig::MapKeyGoblinWarriorPig = "goblin-warrior-pig";
HexusOpponentData* GoblinWarriorPig::HexusOpponentDataInstance = nullptr;
const std::string GoblinWarriorPig::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GOBLIN_WARRIOR_PIG";

GoblinWarriorPig* GoblinWarriorPig::deserialize(ValueMap& initProperties)
{
	GoblinWarriorPig* instance = new GoblinWarriorPig(initProperties);

	instance->autorelease();

	return instance;
}

GoblinWarriorPig::GoblinWarriorPig(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_GoblinWarriorPig_Animations,
	EntityResources::Enemies_EndianForest_GoblinWarriorPig_Emblem,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 296.0f),
	0.8f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = GoblinWarriorPig::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

GoblinWarriorPig::~GoblinWarriorPig()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 GoblinWarriorPig::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* GoblinWarriorPig::getHexusOpponentData()
{
	if (GoblinWarriorPig::HexusOpponentDataInstance == nullptr)
	{
		GoblinWarriorPig::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_GoblinWarriorPig_Animations,
			UIResources::Menus_Hexus_HexusFrameEndianForest,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			GoblinWarriorPig::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return GoblinWarriorPig::HexusOpponentDataInstance;
}