//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "VikingBot.h"

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

const std::string VikingBot::MapKeyVikingBot = "viking-bot";
HexusOpponentData* VikingBot::HexusOpponentDataInstance = nullptr;
const std::string VikingBot::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_VIKING_BOT";

VikingBot* VikingBot::deserialize(ValueMap& initProperties)
{
	VikingBot* instance = new VikingBot(initProperties);

	instance->autorelease();

	return instance;
}

VikingBot::VikingBot(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_VoidStar_VikingBot_Animations,
	EntityResources::Enemies_VoidStar_VikingBot_Emblem,
	PlatformerCollisionType::Enemy,
	Size(768.0f, 960.0f),
	0.5f,
	Vec2(-332.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = VikingBot::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

VikingBot::~VikingBot()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 VikingBot::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* VikingBot::getHexusOpponentData()
{
	if (VikingBot::HexusOpponentDataInstance == nullptr)
	{
		VikingBot::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_VoidStar_VikingBot_Animations,
			UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
			0.5f,
			Vec2(-332.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			VikingBot::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Shadow,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Addition),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),

			}),
			nullptr
		);
	}

	return VikingBot::HexusOpponentDataInstance;
}