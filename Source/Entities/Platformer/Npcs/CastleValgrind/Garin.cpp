//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Garin.h"

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

const std::string Garin::MapKeyGarin = "garin";
HexusOpponentData* Garin::HexusOpponentDataInstance = nullptr;
const std::string Garin::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GARIN";

Garin* Garin::deserialize(ValueMap& initProperties)
{
	Garin* instance = new Garin(initProperties);

	instance->autorelease();

	return instance;
}

Garin::Garin(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_CastleValgrind_Garin_Animations,
	EntityResources::Npcs_CastleValgrind_Garin_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Garin::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Garin::~Garin()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Garin::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Garin::getHexusOpponentData()
{
	if (Garin::HexusOpponentDataInstance == nullptr)
	{
		Garin::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_CastleValgrind_Garin_Animations,
			UIResources::Menus_Hexus_HexusFrameCastleValgrind,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Garin::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
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

	return Garin::HexusOpponentDataInstance;
}