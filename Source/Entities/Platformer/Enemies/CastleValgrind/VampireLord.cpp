//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "VampireLord.h"

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

const std::string VampireLord::MapKeyVampireLord = "vampire-lord";
HexusOpponentData* VampireLord::HexusOpponentDataInstance = nullptr;
const std::string VampireLord::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VAMPIRE_LORD";

VampireLord* VampireLord::deserialize(ValueMap& initProperties)
{
	VampireLord* instance = new VampireLord(initProperties);

	instance->autorelease();

	return instance;
}

VampireLord::VampireLord(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_VampireLord_Animations,
	EntityResources::Enemies_CastleValgrind_VampireLord_Emblem,
	PlatformerCollisionType::Enemy,
	Size(240.0f, 312.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = VampireLord::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/
	
	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

VampireLord::~VampireLord()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 VampireLord::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -160.0f);
}

HexusOpponentData* VampireLord::getHexusOpponentData()
{
	if (VampireLord::HexusOpponentDataInstance == nullptr)
	{
		VampireLord::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_CastleValgrind_VampireLord_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -160.0f),
			VampireLord::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.500f,
			HexusOpponentData::generateDeck(32, 0.500f,
			{

			}),
			StateOverride::create(
				// Player losses
				1,
				// Enemy losses
				1,
				// Player's turn
				true,
				// Player passed
				true,
				// Enemy passed
				true,
				// Player deck
				std::vector<CardData*>
				{
					
				},
				// Enemy deck
				std::vector<CardData*>
				{
					
				},
				// Player hand
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeftCircular),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary1),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
CardList::getInstance()->cardListByName.at(CardKeys::Binary11),
CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
CardList::getInstance()->cardListByName.at(CardKeys::Binary14),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal1),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
CardList::getInstance()->cardListByName.at(CardKeys::Hex2),
CardList::getInstance()->cardListByName.at(CardKeys::Hex1),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return VampireLord::HexusOpponentDataInstance;
}