//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DemonSwordsman.h"

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

const std::string DemonSwordsman::MapKeyDemonSwordsman = "demon-swordsman";
HexusOpponentData* DemonSwordsman::HexusOpponentDataInstance = nullptr;
const std::string DemonSwordsman::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_SWORDSMAN";

DemonSwordsman* DemonSwordsman::deserialize(ValueMap& initProperties)
{
	DemonSwordsman* instance = new DemonSwordsman(initProperties);

	instance->autorelease();

	return instance;
}

DemonSwordsman::DemonSwordsman(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonSwordsman_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonSwordsman_Emblem,
	PlatformerCollisionType::Enemy,
	Size(212.0f, 268.0f),
	0.65f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = DemonSwordsman::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

DemonSwordsman::~DemonSwordsman()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 DemonSwordsman::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* DemonSwordsman::getHexusOpponentData()
{
	if (DemonSwordsman::HexusOpponentDataInstance == nullptr)
	{
		DemonSwordsman::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_DemonSwordsman_Animations,
			UIResources::Menus_Hexus_HexusFrameDaemonsHallow,
			0.65f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			DemonSwordsman::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			1.000f,
			HexusOpponentData::generateDeck(25, 1.000f,
			{

			}),
			nullptr
		);
	}

	return DemonSwordsman::HexusOpponentDataInstance;
}