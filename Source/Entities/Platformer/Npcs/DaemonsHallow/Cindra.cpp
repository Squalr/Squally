//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Cindra.h"

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

const std::string Cindra::MapKeyCindra = "cindra";
HexusOpponentData* Cindra::HexusOpponentDataInstance = nullptr;
const std::string Cindra::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CINDRA";

Cindra* Cindra::deserialize(ValueMap& initProperties)
{
	Cindra* instance = new Cindra(initProperties);

	instance->autorelease();

	return instance;
}

Cindra::Cindra(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_DaemonsHallow_Cindra_Animations,
	EntityResources::Npcs_DaemonsHallow_Cindra_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Cindra::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Cindra::~Cindra()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Cindra::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* Cindra::getHexusOpponentData()
{
	if (Cindra::HexusOpponentDataInstance == nullptr)
	{
		Cindra::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_DaemonsHallow_Cindra_Animations,
			UIResources::Menus_Hexus_HexusFrameDaemonsHallow,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			Cindra::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
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

	return Cindra::HexusOpponentDataInstance;
}