//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Minotaur.h"

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

const std::string Minotaur::MapKeyMinotaur = "minotaur";
HexusOpponentData* Minotaur::HexusOpponentDataInstance = nullptr;
const std::string Minotaur::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MINOTAUR";

Minotaur* Minotaur::deserialize(ValueMap& initProperties)
{
	Minotaur* instance = new Minotaur(initProperties);

	instance->autorelease();

	return instance;
}

Minotaur::Minotaur(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_Minotaur_Animations,
	EntityResources::Enemies_UnderflowRuins_Minotaur_Emblem,
	PlatformerCollisionType::Enemy,
	Size(278.0f, 288.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Minotaur::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Minotaur::~Minotaur()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Minotaur::getAvatarFrameOffset()
{
	return Vec2(-48.0f, -196.0f);
}

HexusOpponentData* Minotaur::getHexusOpponentData()
{
	if (Minotaur::HexusOpponentDataInstance == nullptr)
	{
		Minotaur::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_UnderflowRuins_Minotaur_Animations,
			HexusResources::Menus_HexusFrameUnderflowRuins,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-48.0f, -196.0f),
			Minotaur::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
			0.667f,
			HexusOpponentData::generateDeck(32, 0.667f,
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
					CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
CardList::getInstance()->cardListByName.at(CardKeys::Flip3),
				},
				// Enemy deck
				std::vector<CardData*>
				{
					
				},
				// Player hand
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Greed),
CardList::getInstance()->cardListByName.at(CardKeys::Flip2),
CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
CardList::getInstance()->cardListByName.at(CardKeys::Flip1),
CardList::getInstance()->cardListByName.at(CardKeys::Inverse),
				},
				// Enemy hand
				std::vector<CardData*>
				{
					
				},
				// Player binary cards
				std::vector<CardData*>
				{
					CardList::getInstance()->cardListByName.at(CardKeys::Binary3),
CardList::getInstance()->cardListByName.at(CardKeys::Binary5),
CardList::getInstance()->cardListByName.at(CardKeys::Binary7),
CardList::getInstance()->cardListByName.at(CardKeys::Binary9),
CardList::getInstance()->cardListByName.at(CardKeys::Binary11),
CardList::getInstance()->cardListByName.at(CardKeys::Binary12),
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
					CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
CardList::getInstance()->cardListByName.at(CardKeys::Binary15),
CardList::getInstance()->cardListByName.at(CardKeys::Binary13),
CardList::getInstance()->cardListByName.at(CardKeys::Binary11),
CardList::getInstance()->cardListByName.at(CardKeys::Binary11),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
CardList::getInstance()->cardListByName.at(CardKeys::Absorb),
				},
				// Enemy decimal cards
				std::vector<CardData*>
				{
					
				},
				// Enemy hex cards
				std::vector<CardData*>
				{
					
				},
				StateOverride::TutorialMode::NoTutorial
			)
		);
	}

	return Minotaur::HexusOpponentDataInstance;
}