//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "FireElemental.h"

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

const std::string FireElemental::MapKeyFireElemental = "fire-elemental";
HexusOpponentData* FireElemental::HexusOpponentDataInstance = nullptr;
const std::string FireElemental::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FIRE_ELEMENTAL";

FireElemental* FireElemental::deserialize(ValueMap& initProperties)
{
	FireElemental* instance = new FireElemental(initProperties);

	instance->autorelease();

	return instance;
}

FireElemental::FireElemental(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_FireElemental_Animations,
	EntityResources::Enemies_DaemonsHallow_FireElemental_Emblem,
	PlatformerCollisionType::Enemy,
	Size(820.0f, 1480.0f),
	0.20f,
	Vec2(64.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = FireElemental::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

FireElemental::~FireElemental()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 FireElemental::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* FireElemental::getHexusOpponentData()
{
	if (FireElemental::HexusOpponentDataInstance == nullptr)
	{
		FireElemental::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_FireElemental_Animations,
			UIResources::Menus_Hexus_HexusFrameDaemonsHallow,
			0.20f,
			Vec2(64.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			FireElemental::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return FireElemental::HexusOpponentDataInstance;
}