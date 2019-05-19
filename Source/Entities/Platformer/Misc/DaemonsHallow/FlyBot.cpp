//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS C++ FILE IS GENERATED. ONLY EDIT NON-GENERATED SECTIONS. RUN GenerateDataFiles.py TO GENERATE THIS FILE //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "FlyBot.h"

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

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/Squally/Squally.h"

const std::string FlyBot::EventGreetSqually = "event-greet-squally";

////B////B////B////B////B////B////B////B////B////B/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

using namespace cocos2d;

const std::string FlyBot::MapKeyFlyBot = "fly-bot";
HexusOpponentData* FlyBot::HexusOpponentDataInstance = nullptr;
const std::string FlyBot::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_FLY_BOT";

FlyBot* FlyBot::deserialize(ValueMap& initProperties)
{
	FlyBot* instance = new FlyBot(initProperties);

	instance->autorelease();

	return instance;
}

FlyBot::FlyBot(ValueMap& initProperties) : PlatformerEntity(initProperties,
	EntityResources::Misc_DaemonsHallow_FlyBot_Animations,
	EntityResources::Misc_DaemonsHallow_FlyBot_Emblem,
	PlatformerCollisionType::FriendlyNpc,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f),
	10,
	10)
{
	this->hexusOpponentData = FlyBot::getHexusOpponentData();

	///////////////////////////////////////////////////
	// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
	////Y////Y////Y////Y////Y////Y////Y////Y////Y////Y/
	
	this->entityCollision->setPhysicsEnabled(false);
	
	////Z////Z////Z////Z////Z////Z////Z////Z////Z////Z/
	// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
	///////////////////////////////////////////////////
}

FlyBot::~FlyBot()
{
}

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////X////X////X////X////X////X////X////X////X////X/

void FlyBot::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(ObjectEvents::EventBroadCastMapObjectStatePrefix + FlyBot::EventGreetSqually, [=](EventCustom*)
	{
		ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([&](Squally* squally)
		{
			this->runAction(Sequence::create(
				EaseSineInOut::create(MoveTo::create(2.0f, squally->getPosition() + Vec2(256.0f, 256.0f))),
				nullptr
			));
		}));
	}));
}

////O////O////O////O////O////O////O////O////O////O/
// END: CODE NOT AFFECTED BY GENERATE SCRIPTS    //
///////////////////////////////////////////////////

Vec2 FlyBot::getAvatarFrameOffset()
{
	return Vec2(-32.0f, -112.0f);
}

HexusOpponentData* FlyBot::getHexusOpponentData()
{
	if (FlyBot::HexusOpponentDataInstance == nullptr)
	{
		FlyBot::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Misc_DaemonsHallow_FlyBot_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			FlyBot::HexusSaveKey,
			HexusOpponentData::Strategy::Random,
			Card::CardStyle::Fire,
			1.000f,
			HexusOpponentData::generateDeck(32, 1.000f,
			{
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::Greed),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftLeft),
				CardList::getInstance()->cardListByName.at(CardKeys::Steal),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalOr),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalXor),
				CardList::getInstance()->cardListByName.at(CardKeys::ShiftRight),
				CardList::getInstance()->cardListByName.at(CardKeys::LogicalAnd),

			}),
			nullptr
		);
	}

	return FlyBot::HexusOpponentDataInstance;
}