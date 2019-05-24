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
#include "Resources/SoundResources.h"
#include "Resources/UIResources.h"

///////////////////////////////////////////////////
// BEGIN: CODE NOT AFFECTED BY GENERATE SCRIPTS: //
////A////A////A////A////A////A////A////A////A////A/

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Strings/Dialogue/EndOfDemo.h"
#include "Strings/Dialogue/Story/Intro/GetYouPatched.h"
#include "Strings/Dialogue/Story/Intro/HackerMode.h"
#include "Strings/Dialogue/Story/Intro/OgreSpotted.h"
#include "Strings/Dialogue/Story/Intro/TentHeal.h"
#include "Strings/Dialogue/Story/Intro/YoureAlive.h"

const std::string FlyBot::EventEndOfDemo = "event-end-of-demo";
const std::string FlyBot::EventGreetSqually = "event-greet-squally";
const std::string FlyBot::EventHelpSquallyHeal = "event-help-squally-heal";
const std::string FlyBot::EventTeachHackerMode = "event-teach-hacker-mode";
const std::string FlyBot::EventSpotOgre = "event-spot-ogre";

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
	this->droidAlarmedSound = Sound::create(SoundResources::Platformer_Voices_Droid_DroidAlarmed);
	this->droidBrief1Sound = Sound::create(SoundResources::Platformer_Voices_Droid_DroidBrief);
	this->droidBrief2Sound = Sound::create(SoundResources::Platformer_Voices_Droid_DroidBrief2);
	this->droidChatterSound = Sound::create(SoundResources::Platformer_Voices_Droid_DroidChatter);

	this->addChild(this->droidAlarmedSound);
	this->addChild(this->droidBrief1Sound);
	this->addChild(this->droidBrief2Sound);
	this->addChild(this->droidChatterSound);
	
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

void FlyBot::onEnter()
{
	super::onEnter();

	if (this->state == FlyBot::EventEndOfDemo)
	{
		this->runEndOfDemoEvent();
	}
}

void FlyBot::initializeListeners()
{
	super::initializeListeners();

	if (this->state == FlyBot::EventGreetSqually)
	{
		if (!SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyEventTriggeredPrefix + FlyBot::EventGreetSqually, Value(false)).asBool())
		{
			this->addEventListener(EventListenerCustom::create(ObjectEvents::EventBroadCastMapObjectStatePrefix + FlyBot::EventGreetSqually, [=](EventCustom*)
			{
				this->runGreetEvent();
			}));
		}
		else
		{
			this->setVisible(false);
		}
	}

	if (this->state == FlyBot::EventHelpSquallyHeal)
	{
		if (!SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyEventTriggeredPrefix + FlyBot::EventHelpSquallyHeal, Value(false)).asBool())
		{
			this->addEventListener(EventListenerCustom::create(ObjectEvents::EventBroadCastMapObjectStatePrefix + FlyBot::EventHelpSquallyHeal, [=](EventCustom*)
			{
				this->runHelpHealEvent();
			}));
		}
		else
		{
			this->setVisible(false);
		}
	}

	if (this->state == FlyBot::EventTeachHackerMode)
	{
		if (!SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyEventTriggeredPrefix + FlyBot::EventTeachHackerMode, Value(false)).asBool())
		{
			this->addEventListener(EventListenerCustom::create(ObjectEvents::EventBroadCastMapObjectStatePrefix + FlyBot::EventTeachHackerMode, [=](EventCustom*)
			{
				this->runTeachHackerModeEvent();
			}));
		}
		else
		{
			this->setVisible(false);
		}
	}

	if (this->state == FlyBot::EventSpotOgre)
	{
		if (!SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyEventTriggeredPrefix + FlyBot::EventSpotOgre, Value(false)).asBool())
		{
			this->addEventListener(EventListenerCustom::create(ObjectEvents::EventBroadCastMapObjectStatePrefix + FlyBot::EventSpotOgre, [=](EventCustom*)
			{
				this->runSpotOgreEvent();
			}));
		}
		else
		{
			this->setVisible(false);
		}
	}
}

void FlyBot::runEndOfDemoEvent()
{
	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->droidChatterSound->play();
		}),
		CallFunc::create([=]()
		{
			this->speechBubble->runDialogue(Strings::Dialogue_EndOfDemo::create());
		}),
		nullptr
	));
}

void FlyBot::runGreetEvent()
{
	SaveManager::saveProfileData(SaveKeys::SaveKeyEventTriggeredPrefix + FlyBot::EventGreetSqually, Value(true));

	Vec2 positionA = Vec2::ZERO;
	Vec2 positionB = Vec2::ZERO;

	ObjectEvents::QueryObjects(QueryObjectsArgs<CinematicMarker>([&](CinematicMarker* cinematicMarker)
	{
		switch(cinematicMarker->getId())
		{
			case 0:
			{
				positionA = cinematicMarker->getPosition();
				break;
			}
			case 1:
			{
				positionB = cinematicMarker->getPosition();
				break;
			}
			default:
			{
				break;
			}
		}
	}));

	PlatformerEvents::TriggerCinematicHijack();

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->droidAlarmedSound->play();
		}),
		EaseSineInOut::create(MoveTo::create(2.0f, positionA)),
		CallFunc::create([=]()
		{
			this->speechBubble->runDialogue(Strings::Dialogue_Story_Intro_YoureAlive::create());
		}),
		DelayTime::create(2.0f),
		CallFunc::create([=]()
		{
			this->droidBrief1Sound->play();
			this->speechBubble->runDialogue(Strings::Dialogue_Story_Intro_GetYouPatched::create());
		}),
		DelayTime::create(4.0f),
		CallFunc::create([=]()
		{
			this->speechBubble->hideDialogue();
		}),
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicRestore();
		}),
		EaseSineInOut::create(MoveTo::create(2.0f, positionB)),
		CallFunc::create([=]()
		{
			this->setVisible(false);
		}),
		nullptr
	));
}

void FlyBot::runHelpHealEvent()
{
	SaveManager::saveProfileData(SaveKeys::SaveKeyEventTriggeredPrefix + FlyBot::EventHelpSquallyHeal, Value(true));

	Vec2 positionA = Vec2::ZERO;

	ObjectEvents::QueryObjects(QueryObjectsArgs<CinematicMarker>([&](CinematicMarker* cinematicMarker)
	{
		switch(cinematicMarker->getId())
		{
			case 0:
			{
				positionA = cinematicMarker->getPosition();
				break;
			}
			default:
			{
				break;
			}
		}
	}));

	PlatformerEvents::TriggerCinematicHijack();

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->droidBrief2Sound->play();
		}),
		CallFunc::create([=]()
		{
			this->speechBubble->runDialogue(Strings::Dialogue_Story_Intro_TentHeal::create());
		}),
		DelayTime::create(4.0f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicRestore();
			this->speechBubble->hideDialogue();
		}),
		DelayTime::create(1.0f),
		EaseSineInOut::create(MoveTo::create(2.0f, positionA)),
		CallFunc::create([=]()
		{
			this->setVisible(false);
		}),
		nullptr
	));
}

void FlyBot::runTeachHackerModeEvent()
{
	SaveManager::saveProfileData(SaveKeys::SaveKeyEventTriggeredPrefix + FlyBot::EventTeachHackerMode, Value(true));

	Vec2 positionB = Vec2::ZERO;

	ObjectEvents::QueryObjects(QueryObjectsArgs<CinematicMarker>([&](CinematicMarker* cinematicMarker)
	{
		switch(cinematicMarker->getId())
		{
			case 1:
			{
				positionB = cinematicMarker->getPosition();
				break;
			}
			default:
			{
				break;
			}
		}
	}));

	PlatformerEvents::TriggerCinematicHijack();

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->droidChatterSound->play();
		}),
		CallFunc::create([=]()
		{
			this->speechBubble->runDialogue(Strings::Dialogue_Story_Intro_HackerMode::create());
		}),
		DelayTime::create(4.0f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicRestore();
			this->speechBubble->hideDialogue();
		}),
		DelayTime::create(1.0f),
		EaseSineInOut::create(MoveTo::create(2.0f, positionB)),
		CallFunc::create([=]()
		{
			this->setVisible(false);
		}),
		nullptr
	));
}

void FlyBot::runSpotOgreEvent()
{
	SaveManager::saveProfileData(SaveKeys::SaveKeyEventTriggeredPrefix + FlyBot::EventSpotOgre, Value(true));

	PlatformerEvents::TriggerCinematicHijack();

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->droidChatterSound->play();
		}),
		CallFunc::create([=]()
		{
			this->speechBubble->runDialogue(Strings::Dialogue_Story_Intro_OgreSpotted::create());
		}),
		DelayTime::create(4.0f),
		CallFunc::create([=]()
		{
			PlatformerEvents::TriggerCinematicRestore();
		}),
		DelayTime::create(4.0f),
		CallFunc::create([=]()
		{
			this->speechBubble->hideDialogue();
		}),
		nullptr
	));
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