//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Cleopatra.h"

#include "cocos/math/CCGeometry.h"

#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/EntityResources.h"
#include "Resources/HexusResources.h"
#include "Resources/UIResources.h"

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////A////A////A////A////A////A////A////A////A////A/

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

using namespace cocos2d;

const std::string Cleopatra::MapKeyCleopatra = "cleopatra";
HexusOpponentData* Cleopatra::HexusOpponentDataInstance = nullptr;
const std::string Cleopatra::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CLEOPATRA";

Cleopatra* Cleopatra::deserialize(ValueMap& initProperties)
{
	Cleopatra* instance = new Cleopatra(initProperties);

	instance->autorelease();

	return instance;
}

Cleopatra::Cleopatra(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_UnderflowRuins_Cleopatra_Animations,
	EntityResources::Npcs_UnderflowRuins_Cleopatra_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Cleopatra::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Cleopatra::~Cleopatra()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Cleopatra::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -144.0f);
}

HexusOpponentData* Cleopatra::getHexusOpponentData()
{
	if (Cleopatra::HexusOpponentDataInstance == nullptr)
	{
		Cleopatra::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_UnderflowRuins_Cleopatra_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -172.0f),
			Vec2(-32.0f, -144.0f),
			Cleopatra::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.250f,
			HexusOpponentData::generateDeck(25, 0.250f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return Cleopatra::HexusOpponentDataInstance;
}