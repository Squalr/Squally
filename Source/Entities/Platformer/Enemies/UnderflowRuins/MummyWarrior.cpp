//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "MummyWarrior.h"

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

const std::string MummyWarrior::MapKeyMummyWarrior = "mummy-warrior";
HexusOpponentData* MummyWarrior::HexusOpponentDataInstance = nullptr;
const std::string MummyWarrior::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_MUMMY_WARRIOR";

MummyWarrior* MummyWarrior::deserialize(ValueMap& initProperties)
{
	MummyWarrior* instance = new MummyWarrior(initProperties);

	instance->autorelease();

	return instance;
}

MummyWarrior::MummyWarrior(ValueMap& initProperties) : PlatformerEnemy(initProperties,
	EntityResources::Enemies_UnderflowRuins_MummyWarrior_Animations,
	EntityResources::Enemies_UnderflowRuins_MummyWarrior_Emblem,
	PlatformerCollisionType::Enemy,
	Size(128.0f, 256.0f),
	0.8f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = MummyWarrior::getHexusOpponentData();

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

MummyWarrior::~MummyWarrior()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 MummyWarrior::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

HexusOpponentData* MummyWarrior::getHexusOpponentData()
{
	if (MummyWarrior::HexusOpponentDataInstance == nullptr)
	{
		MummyWarrior::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Enemies_UnderflowRuins_MummyWarrior_Animations,
			UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle,
			0.8f,
			Vec2(0.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			MummyWarrior::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Light,
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

	return MummyWarrior::HexusOpponentDataInstance;
}