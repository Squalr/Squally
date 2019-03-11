//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "DemonRogue.h"

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

const std::string DemonRogue::MapKeyDemonRogue = "demon-rogue";
HexusOpponentData* DemonRogue::HexusOpponentDataInstance = nullptr;
const std::string DemonRogue::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_DEMON_ROGUE";

DemonRogue* DemonRogue::deserialize(ValueMap& initProperties)
{
	DemonRogue* instance = new DemonRogue(initProperties);

	instance->autorelease();

	return instance;
}

DemonRogue::DemonRogue(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_DaemonsHallow_DemonRogue_Animations,
	EntityResources::Enemies_DaemonsHallow_DemonRogue_Emblem,
	PlatformerCollisionType::Enemy,
	Size(212.0f, 268.0f),
	0.65f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = DemonRogue::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

DemonRogue::~DemonRogue()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 DemonRogue::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* DemonRogue::getHexusOpponentData()
{
	if (DemonRogue::HexusOpponentDataInstance == nullptr)
	{
		DemonRogue::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_DaemonsHallow_DemonRogue_Animations,
			UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
			0.65f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			DemonRogue::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateReward(0.62f),
			HexusOpponentData::generateDeck(25, 0.62f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			})
		);
	}

	return DemonRogue::HexusOpponentDataInstance;
}