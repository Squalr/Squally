//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Thion.h"

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

const std::string Thion::MapKeyThion = "thion";
HexusOpponentData* Thion::HexusOpponentDataInstance = nullptr;
const std::string Thion::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_THION";

Thion* Thion::deserialize(ValueMap& initProperties)
{
	Thion* instance = new Thion(initProperties);

	instance->autorelease();

	return instance;
}

Thion::Thion(ValueMap& initProperties) : NpcBase(initProperties,
	EntityResources::Npcs_LambdaCrypts_Thion_Animations,
	EntityResources::Npcs_LambdaCrypts_Thion_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Thion::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

Thion::~Thion()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Thion::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* Thion::getHexusOpponentData()
{
	if (Thion::HexusOpponentDataInstance == nullptr)
	{
		Thion::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Npcs_LambdaCrypts_Thion_Animations,
			UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			Thion::HexusSaveKey,
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

	return Thion::HexusOpponentDataInstance;
}