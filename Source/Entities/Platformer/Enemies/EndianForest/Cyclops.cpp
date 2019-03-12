//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "Cyclops.h"

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

const std::string Cyclops::MapKeyCyclops = "cyclops";
HexusOpponentData* Cyclops::HexusOpponentDataInstance = nullptr;
const std::string Cyclops::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_CYCLOPS";

Cyclops* Cyclops::deserialize(ValueMap& initProperties)
{
	Cyclops* instance = new Cyclops(initProperties);

	instance->autorelease();

	return instance;
}

Cyclops::Cyclops(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_EndianForest_Cyclops_Animations,
	EntityResources::Enemies_EndianForest_Cyclops_Emblem,
	PlatformerCollisionType::Enemy,
	Size(296.0f, 256.0f),
	0.9f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = Cyclops::getHexusOpponentData();

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

Cyclops::~Cyclops()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 Cyclops::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* Cyclops::getHexusOpponentData()
{
	if (Cyclops::HexusOpponentDataInstance == nullptr)
	{
		Cyclops::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_EndianForest_Cyclops_Animations,
			UIResources::Menus_Hexus_HexusFrameEndianForest,
			0.9f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			Cyclops::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Earth,
			HexusOpponentData::generateReward(0.615f),
			HexusOpponentData::generateDeck(25, 0.615f,
			{

			}),
			nullptr
		);
	}

	return Cyclops::HexusOpponentDataInstance;
}