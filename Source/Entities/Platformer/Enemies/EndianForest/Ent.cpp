//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Ent.h"

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

const std::string Ent::MapKeyEnt = "ent";
HexusOpponentData* Ent::HexusOpponentDataInstance = nullptr;
const std::string Ent::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ENT";

Ent* Ent::deserialize(ValueMap& initProperties)
{
	Ent* instance = new Ent(initProperties);

	instance->autorelease();

	return instance;
}

Ent::Ent(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_Ent_Animations,
	EntityResources::Enemies_EndianForest_Ent_Emblem,
	PlatformerCollisionType::Enemy,
	Size(512.0f, 960.0f),
	0.9f,
	Vec2(24.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Ent::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Ent::~Ent()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Ent::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Ent::getHexusOpponentData()
{
	if (Ent::HexusOpponentDataInstance == nullptr)
	{
		Ent::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_Ent_Animations,
			UIResources::Menus_Hexus_HexusFrameEndianForest,
			0.9f,
			Vec2(24.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Ent::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return Ent::HexusOpponentDataInstance;
}