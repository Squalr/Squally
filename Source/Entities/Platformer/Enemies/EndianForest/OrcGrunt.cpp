//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "OrcGrunt.h"

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

#include "Scenes/Platformer/Inventory/Items/Consumables/Health/HealthPotion.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/ManaPotion.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Speed/SpeedPotion.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Basic/BasicSlash.h"

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

using namespace cocos2d;

const std::string OrcGrunt::MapKeyOrcGrunt = "orc-grunt";
HexusOpponentData* OrcGrunt::HexusOpponentDataInstance = nullptr;
const std::string OrcGrunt::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_ORC_GRUNT";

OrcGrunt* OrcGrunt::deserialize(ValueMap& initProperties)
{
	OrcGrunt* instance = new OrcGrunt(initProperties);

	instance->autorelease();

	return instance;
}

OrcGrunt::OrcGrunt(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_OrcGrunt_Animations,
	EntityResources::Enemies_EndianForest_OrcGrunt_Emblem,
	PlatformerCollisionType::Enemy,
	Size(256.0f, 218.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = OrcGrunt::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	this->registerAttack(BasicSlash::create(1.2f, 0.4f));

	this->dropTable[HealthPotion::SaveKeyHealthPotion] = 0.25f;
	this->dropTable[ManaPotion::SaveKeyManaPotion] = 0.25f;
	this->dropTable[SpeedPotion::SaveKeySpeedPotion] = 0.25f;

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

OrcGrunt::~OrcGrunt()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 OrcGrunt::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* OrcGrunt::getHexusOpponentData()
{
	if (OrcGrunt::HexusOpponentDataInstance == nullptr)
	{
		OrcGrunt::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_OrcGrunt_Animations,
			UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			OrcGrunt::HexusSaveKey,
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

	return OrcGrunt::HexusOpponentDataInstance;
}