//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Thurstan.h"

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

const std::string Thurstan::MapKeyThurstan = "thurstan";
HexusOpponentData* Thurstan::HexusOpponentDataInstance = nullptr;
const std::string Thurstan::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THURSTAN";

Thurstan* Thurstan::deserialize(ValueMap& initProperties)
{
	Thurstan* instance = new Thurstan(initProperties);

	instance->autorelease();

	return instance;
}

Thurstan::Thurstan(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_CastleValgrind_Thurstan_Animations,
	EntityResources::Npcs_CastleValgrind_Thurstan_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(124.0f, 160.0f),
	1.05f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Thurstan::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/
	
	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Thurstan::~Thurstan()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Thurstan::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* Thurstan::getHexusOpponentData()
{
	if (Thurstan::HexusOpponentDataInstance == nullptr)
	{
		Thurstan::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_CastleValgrind_Thurstan_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			1.05f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Thurstan::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.490f,
			HexusOpponentData::generateDeck(32, 0.490f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::Mov),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),

			}),
			nullptr
		);
	}

	return Thurstan::HexusOpponentDataInstance;
}