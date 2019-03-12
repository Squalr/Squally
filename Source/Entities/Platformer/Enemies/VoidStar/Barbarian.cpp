//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Barbarian.h"

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

const std::string Barbarian::MapKeyBarbarian = "barbarian";
HexusOpponentData* Barbarian::HexusOpponentDataInstance = nullptr;
const std::string Barbarian::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_BARBARIAN";

Barbarian* Barbarian::deserialize(ValueMap& initProperties)
{
	Barbarian* instance = new Barbarian(initProperties);

	instance->autorelease();

	return instance;
}

Barbarian::Barbarian(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_Barbarian_Animations,
	EntityResources::Enemies_VoidStar_Barbarian_Emblem,
	PlatformerCollisionType::Enemy,
	Size(278.0f, 288.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Barbarian::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Barbarian::~Barbarian()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Barbarian::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Barbarian::getHexusOpponentData()
{
	if (Barbarian::HexusOpponentDataInstance == nullptr)
	{
		Barbarian::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_VoidStar_Barbarian_Animations,
			UIResources::Menus_Hexus_HexusFrameVoidStar,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Barbarian::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return Barbarian::HexusOpponentDataInstance;
}