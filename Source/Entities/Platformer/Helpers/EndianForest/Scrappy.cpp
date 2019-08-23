#include "Scrappy.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/math/CCGeometry.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/Sound.h"
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Cinematic/CinematicMarker.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"

#include "Resources/EntityResources.h"
#include "Resources/FXResources.h"
#include "Resources/HexusResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Platformer/EndOfDemo.h"
#include "Strings/Platformer/Entities/Names/Helpers/EndianForest/Scrappy.h"
#include "Strings/Platformer/Quests/Intro/SquallyTrapped.h"

using namespace cocos2d;

const std::string Scrappy::MapKeyScrappy = "scrappy";
HexusOpponentData* Scrappy::HexusOpponentDataInstance = nullptr;

const std::string Scrappy::HexusSaveKey = "HEXUS_OPPONENT_SAVE_KEY_SCRAPPY";
const std::string Scrappy::EventEndOfDemo = "event-end-of-demo";
const std::string Scrappy::EventSquallyTrapped = "event-squally-trapped";

Scrappy* Scrappy::deserialize(ValueMap& properties)
{
	Scrappy* instance = new Scrappy(properties);

	instance->autorelease();

	return instance;
}

Scrappy::Scrappy(ValueMap& properties) : super(properties,
	Scrappy::MapKeyScrappy,
	EntityResources::Helpers_EndianForest_Scrappy_Animations,
	EntityResources::Helpers_EndianForest_Scrappy_Emblem,
	Size(112.0f, 160.0f),
	1.0f,
	Vec2(0.0f, 0.0f))
{
	this->hexusOpponentData = Scrappy::getHexusOpponentData();

	this->droidAlarmedSound = Sound::create(SoundResources::Platformer_Entities_Droid_DroidAlarmed);
	this->droidBrief1Sound = Sound::create(SoundResources::Platformer_Entities_Droid_DroidBrief);
	this->droidBrief2Sound = Sound::create(SoundResources::Platformer_Entities_Droid_DroidBrief2);
	this->droidChatterSound = Sound::create(SoundResources::Platformer_Entities_Droid_DroidChatter);
	this->fireAnimation = SmartAnimationSequenceNode::create();

	this->droidAlarmedSound->toggleCameraDistanceFade(true);
	this->droidBrief1Sound->toggleCameraDistanceFade(true);
	this->droidBrief2Sound->toggleCameraDistanceFade(true);
	this->droidChatterSound->toggleCameraDistanceFade(true);
	this->fireAnimation->setFlippedY(true);
	this->fireAnimation->setScale(0.25f);

	this->belowAnimationNode->addChild(this->fireAnimation);
	this->addChild(this->droidAlarmedSound);
	this->addChild(this->droidBrief1Sound);
	this->addChild(this->droidBrief2Sound);
	this->addChild(this->droidChatterSound);
}

Scrappy::~Scrappy()
{
}

void Scrappy::onEnter()
{
	super::onEnter();

	if (this->state == Scrappy::EventEndOfDemo)
	{
		this->runEndOfDemoEvent();
	}

	this->fireAnimation->playAnimationRepeat(FXResources::FlameSmall_FlameSmall_0000, 0.045f);
}

void Scrappy::initializePositions()
{
	super::initializePositions();
	
	this->fireAnimation->setPosition(Vec2(0.0f, -16.0f));
}

void Scrappy::initializeListeners()
{
	super::initializeListeners();

	if (this->state == Scrappy::EventSquallyTrapped)
	{
		this->setVisible(false);

		this->listenForMapEvent(Scrappy::EventSquallyTrapped, [=](ValueMap args)
		{
			this->runSquallyTrappedEvent();
		});
	}
}

void Scrappy::runEndOfDemoEvent()
{
	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->droidChatterSound->play();
		}),
		CallFunc::create([=]()
		{
			this->speechBubble->runDialogue(Strings::Platformer_EndOfDemo::create());
		}),
		nullptr
	));
}

void Scrappy::runSquallyTrappedEvent()
{
	SaveManager::saveProfileData(SaveKeys::SaveKeyEventTriggeredPrefix + Scrappy::EventSquallyTrapped, Value(true));

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			this->setVisible(true);
			this->droidChatterSound->play();
		}),
		CallFunc::create([=]()
		{
			this->speechBubble->runDialogue(Strings::Platformer_Quests_Intro_SquallyTrapped::create());
		}),
		nullptr
	));
}

float Scrappy::getFloatHeight()
{
	return 64.0f;
}

Vec2 Scrappy::getDialogueOffset()
{
	return Vec2(-32.0f, -112.0f);
}

LocalizedString* Scrappy::getEntityName()
{
	return Strings::Platformer_Entities_Names_Helpers_EndianForest_Scrappy::create();
}

HexusOpponentData* Scrappy::getHexusOpponentData()
{
	if (Scrappy::HexusOpponentDataInstance == nullptr)
	{
		Scrappy::HexusOpponentDataInstance = new HexusOpponentData(
			EntityResources::Helpers_EndianForest_Scrappy_Animations,
			HexusResources::Menus_HexusFrameDaemonsHallow,
			1.0f,
			Vec2(0.0f, 0.0f),
			Vec2(-48.0f, -144.0f),
			Vec2(-32.0f, -112.0f),
			Scrappy::HexusSaveKey,
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

	return Scrappy::HexusOpponentDataInstance;
}