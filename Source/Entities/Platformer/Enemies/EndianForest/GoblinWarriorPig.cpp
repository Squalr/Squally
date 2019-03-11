//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "GoblinWarriorPig.h"

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

const std::string GoblinWarriorPig::MapKeyGoblinWarriorPig = "goblin-warrior-pig";
HexusOpponentData* GoblinWarriorPig::HexusOpponentDataInstance = nullptr;
const std::string GoblinWarriorPig::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_GOBLIN_WARRIOR_PIG";

GoblinWarriorPig* GoblinWarriorPig::deserialize(ValueMap& initProperties)
{
	GoblinWarriorPig* instance = new GoblinWarriorPig(initProperties);

	instance->autorelease();

	return instance;
}

GoblinWarriorPig::GoblinWarriorPig(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_GoblinWarriorPig_Animations,
	EntityResources::Enemies_EndianForest_GoblinWarriorPig_Emblem,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 296.0f),
	0.8f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = GoblinWarriorPig::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/

	this->registerAttack(BasicSlash::create(0.7f, 0.2f));

	this->dropTable[HealthPotion::SaveKeyHealthPotion] = 0.25f;
	this->dropTable[ManaPotion::SaveKeyManaPotion] = 0.25f;
	this->dropTable[SpeedPotion::SaveKeySpeedPotion] = 0.25f;

	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

GoblinWarriorPig::~GoblinWarriorPig()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 GoblinWarriorPig::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* GoblinWarriorPig::getHexusOpponentData()
{
	if (GoblinWarriorPig::HexusOpponentDataInstance == nullptr)
	{
		GoblinWarriorPig::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_GoblinWarriorPig_Animations,
			UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			GoblinWarriorPig::HexusSaveKey,
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

	return GoblinWarriorPig::HexusOpponentDataInstance;
}