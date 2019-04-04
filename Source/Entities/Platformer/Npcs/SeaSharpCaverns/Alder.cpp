//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Alder.h"

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

const std::string Alder::MapKeyAlder = "alder";
HexusOpponentData* Alder::HexusOpponentDataInstance = nullptr;
const std::string Alder::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ALDER";

Alder* Alder::deserialize(ValueMap& initProperties)
{
	Alder* instance = new Alder(initProperties);

	instance->autorelease();

	return instance;
}

Alder::Alder(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_SeaSharpCaverns_Alder_Animations,
	EntityResources::Npcs_SeaSharpCaverns_Alder_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	0.85f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Alder::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Alder::~Alder()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Alder::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Alder::getHexusOpponentData()
{
	if (Alder::HexusOpponentDataInstance == nullptr)
	{
		Alder::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_SeaSharpCaverns_Alder_Animations,
			HexusResources::Menus_HexusFrameSeaSharpCaverns,
			0.85f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Alder::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			0.260f,
			HexusOpponentData::generateDeck(32, 0.260f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Poison),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Heal),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),

			}),
			nullptr
		);
	}

	return Alder::HexusOpponentDataInstance;
}