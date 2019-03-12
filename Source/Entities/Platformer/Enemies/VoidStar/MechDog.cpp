//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MechDog.h"

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

const std::string MechDog::MapKeyMechDog = "mech-dog";
HexusOpponentData* MechDog::HexusOpponentDataInstance = nullptr;
const std::string MechDog::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MECH_DOG";

MechDog* MechDog::deserialize(ValueMap& initProperties)
{
	MechDog* instance = new MechDog(initProperties);

	instance->autorelease();

	return instance;
}

MechDog::MechDog(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_MechDog_Animations,
	EntityResources::Enemies_VoidStar_MechDog_Emblem,
	PlatformerCollisionType::Enemy,
	Size(540.0f, 340.0f),
	0.7f,
	Vec2(-64.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = MechDog::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

MechDog::~MechDog()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 MechDog::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* MechDog::getHexusOpponentData()
{
	if (MechDog::HexusOpponentDataInstance == nullptr)
	{
		MechDog::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_VoidStar_MechDog_Animations,
			UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
			0.7f,
			Vec2(-64.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			MechDog::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return MechDog::HexusOpponentDataInstance;
}