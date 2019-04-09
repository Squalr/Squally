//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "AnubisWarrior.h"

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

const std::string AnubisWarrior::MapKeyAnubisWarrior = "anubis-warrior";
HexusOpponentData* AnubisWarrior::HexusOpponentDataInstance = nullptr;
const std::string AnubisWarrior::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ANUBIS_WARRIOR";

AnubisWarrior* AnubisWarrior::deserialize(ValueMap& initProperties)
{
	AnubisWarrior* instance = new AnubisWarrior(initProperties);

	instance->autorelease();

	return instance;
}

AnubisWarrior::AnubisWarrior(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_AnubisWarrior_Animations,
	EntityResources::Enemies_UnderflowRuins_AnubisWarrior_Emblem,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 292.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	27,
	17)
{
	this->hexusOpponentData = AnubisWarrior::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

AnubisWarrior::~AnubisWarrior()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 AnubisWarrior::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -196.0f);
}

HexusOpponentData* AnubisWarrior::getHexusOpponentData()
{
	if (AnubisWarrior::HexusOpponentDataInstance == nullptr)
	{
		AnubisWarrior::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_UnderflowRuins_AnubisWarrior_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -196.0f),
			AnubisWarrior::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.917f,
			HexusOpponentData::generateDeck(32, 0.917f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::Steal),
CardList::getInstance()->cardListByName.at(CardKeys::Kill),
CardList::getInstance()->cardListByName.at(CardKeys::ShiftRightCircular),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
CardList::getInstance()->cardListByName.at(CardKeys::Binary8),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
CardList::getInstance()->cardListByName.at(CardKeys::Binary6),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Hex8),
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return AnubisWarrior::HexusOpponentDataInstance;
}