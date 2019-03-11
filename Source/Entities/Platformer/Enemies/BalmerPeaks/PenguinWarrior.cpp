//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "PenguinWarrior.h"

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

const std::string PenguinWarrior::MapKeyPenguinWarrior = "penguin-warrior";
HexusOpponentData* PenguinWarrior::HexusOpponentDataInstance = nullptr;
const std::string PenguinWarrior::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_PENGUIN_WARRIOR";

PenguinWarrior* PenguinWarrior::deserialize(ValueMap& initProperties)
{
	PenguinWarrior* instance = new PenguinWarrior(initProperties);

	instance->autorelease();

	return instance;
}

PenguinWarrior::PenguinWarrior(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_BalmerPeaks_PenguinWarrior_Animations,
	EntityResources::Enemies_BalmerPeaks_PenguinWarrior_Emblem,
	PlatformerCollisionType::Enemy,
	Size(212.0f, 296.0f),
	0.7f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = PenguinWarrior::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

PenguinWarrior::~PenguinWarrior()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 PenguinWarrior::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* PenguinWarrior::getHexusOpponentData()
{
	if (PenguinWarrior::HexusOpponentDataInstance == nullptr)
	{
		PenguinWarrior::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_BalmerPeaks_PenguinWarrior_Animations,
			UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
			0.7f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			PenguinWarrior::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateReward(0.62f),
			HexusOpponentData::generateDeck(25, 0.62f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
			})
		);
	}

	return PenguinWarrior::HexusOpponentDataInstance;
}