//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Werewolf.h"

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

const std::string Werewolf::MapKeyWerewolf = "werewolf";
HexusOpponentData* Werewolf::HexusOpponentDataInstance = nullptr;
const std::string Werewolf::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_WEREWOLF";

Werewolf* Werewolf::deserialize(ValueMap& initProperties)
{
	Werewolf* instance = new Werewolf(initProperties);

	instance->autorelease();

	return instance;
}

Werewolf::Werewolf(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_CastleValgrind_Werewolf_Animations,
	EntityResources::Enemies_CastleValgrind_Werewolf_Emblem,
	PlatformerCollisionType::Enemy,
	Size(196.0f, 512.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	16,
	8)
{
	this->hexusOpponentData = Werewolf::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/
	
	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Werewolf::~Werewolf()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Werewolf::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -160.0f);
}

HexusOpponentData* Werewolf::getHexusOpponentData()
{
	if (Werewolf::HexusOpponentDataInstance == nullptr)
	{
		Werewolf::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_CastleValgrind_Werewolf_Animations,
			HexusResources::Menus_HexusFrameCastleValgrind,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -160.0f),
			Werewolf::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Air,
			0.750f,
			HexusOpponentData::generateDeck(32, 0.750f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
CardList::getInstance()->cardListByName.at(CardKeys::Flip4),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary9),
CardList::getInstance()->cardListByName.at(CardKeys::Binary9),
CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
				},
				// Player decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal12),
				},
				// Player hex cards
				std::vector<CardData*>
				{
					
				},
				// Enemy binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal7),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
CardList::getInstance()->cardListByName.at(CardKeys::Hex6),
CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Werewolf::HexusOpponentDataInstance;
}