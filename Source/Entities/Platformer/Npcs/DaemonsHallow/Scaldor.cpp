//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Scaldor.h"

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

const std::string Scaldor::MapKeyScaldor = "scaldor";
HexusOpponentData* Scaldor::HexusOpponentDataInstance = nullptr;
const std::string Scaldor::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SCALDOR";

Scaldor* Scaldor::deserialize(ValueMap& initProperties)
{
	Scaldor* instance = new Scaldor(initProperties);

	instance->autorelease();

	return instance;
}

Scaldor::Scaldor(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_DaemonsHallow_Scaldor_Animations,
	EntityResources::Npcs_DaemonsHallow_Scaldor_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Scaldor::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Scaldor::~Scaldor()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Scaldor::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Scaldor::getHexusOpponentData()
{
	if (Scaldor::HexusOpponentDataInstance == nullptr)
	{
		Scaldor::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_DaemonsHallow_Scaldor_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			1.05f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Scaldor::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			0.750f,
			HexusOpponentData::generateDeck(32, 0.750f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::BonusMoves),

			}),
			nullptr
		);
	}

	return Scaldor::HexusOpponentDataInstance;
}