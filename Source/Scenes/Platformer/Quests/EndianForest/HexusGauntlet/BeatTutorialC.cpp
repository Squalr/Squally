#include "BeatTutorialC.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/DialogueSet.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/QuestEvents.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/DialogueEvents.h"
#include "Events/HexusEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Doors/MagePortals/MagePortal.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/Components/Components.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"

#include "Resources/HexusResources.h"

#include "Strings/Hexus/Hexus.h"
#include "Strings/Platformer/Quests/EndianForest/HexusGauntlet/TeachMeHexus.h"

using namespace cocos2d;

const std::string BeatTutorialC::MapKeyQuest = "beat-tutorial-C";
const std::string BeatTutorialC::WinLossTrackIdentifier = "Tutorial-C";
const std::string BeatTutorialC::QuestPortalTag = "quest-portal";

BeatTutorialC* BeatTutorialC::create(GameObject* owner, QuestLine* questLine,  std::string questTag)
{
	BeatTutorialC* instance = new BeatTutorialC(owner, questLine, questTag);

	instance->autorelease();

	return instance;
}

BeatTutorialC::BeatTutorialC(GameObject* owner, QuestLine* questLine, std::string questTag) : super(owner, questLine, BeatTutorialC::MapKeyQuest, questTag, false)
{
	this->mage = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;
	this->portal = nullptr;
}

BeatTutorialC::~BeatTutorialC()
{
}

void BeatTutorialC::onLoad(QuestState questState)
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	});

	ObjectEvents::watchForObject<MagePortal>(this, [=](MagePortal* portal)
	{
		this->portal = portal;
		
		if (questState == QuestState::Complete)
		{
			this->portal->openPortal(true);
		}
		else
		{
			this->portal->closePortal(true);
		}
	}, BeatTutorialC::QuestPortalTag);
}

void BeatTutorialC::onActivate(bool isActiveThroughSkippable)
{
	this->mage->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
			Strings::Platformer_Quests_EndianForest_HexusGauntlet_TeachMeHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
			[=]()
			{
				HexusEvents::TriggerOpenHexus(HexusEvents::HexusOpenArgs(this->createOpponentData()));
			}),
			0.5f
		);
	});
}

void BeatTutorialC::onComplete()
{
	if (this->portal != nullptr)
	{
		this->portal->openPortal(true);
	}
}

void BeatTutorialC::onSkipped()
{
	this->removeAllListeners();
}

void BeatTutorialC::registerDialogue()
{
	PlatformerEvents::TriggerCinematicHijack();

	this->runAction(Sequence::create(
		DelayTime::create(3.0f),
		CallFunc::create([=]()
		{
			DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
				nullptr,
				DialogueBox::DialogueDock::Top,
				DialogueBox::DialogueAlignment::Left,
				[=]()
				{
				},
				DialogueEvents::BuildPreviewNode(this->mage, false),
				DialogueEvents::BuildPreviewNode(this->squally, true),
				false
			));
		}),
		nullptr
	));
}

void BeatTutorialC::onWin()
{
    this->complete();
}

void BeatTutorialC::onLoss()
{
}

HexusOpponentData* BeatTutorialC::createOpponentData()
{
    return HexusOpponentData::create( 
        // TODO: This needs to work similar to the dialogue boxes, and pass the entity to a builder that accounts for scale/offsets
        this->mage->getAnimations()->getAnimationResource(),
        HexusResources::Menus_HexusFrameCastleValgrind,
        1.0f,
        Vec2(-32.0f, -64.0f),
        Vec2(-48.0f, -144.0f),
        Vec2(0.0f, -48.0f),
        BeatTutorialC::WinLossTrackIdentifier,
        HexusOpponentData::Strategy::Random,
        Card::CardStyle::Light,
        0.07f,
        HexusOpponentData::generateDeck(25, 0.07f,
        {
        }),
        [=](HexusOpponentData::Result result)
        {
            if (result == HexusOpponentData::Result::Win)
            {
                this->onWin();
            }
            else
            {
                this->onLoss();
            }
        },
        StateOverride::create(
            // Player losses
            0,
            // Enemy losses
            1,
            // Player's turn
            true,
            // Player passed
            false,
            // Enemy passed
            true,
            // Player deck
            std::vector<CardData*>
            {
            },
            // Enemy deck
            std::vector<CardData*>
            {
            },
            // Player hand
            std::vector<CardData*>
            {
                CardList::getInstance()->cardListByName.at(CardKeys::Binary14),
            },
            // Enemy hand
            std::vector<CardData*>
            {
                CardList::getInstance()->cardListByName.at(CardKeys::Decimal8),
            },
            // Player binary cards
            std::vector<CardData*>
            {
                CardList::getInstance()->cardListByName.at(CardKeys::Binary0),
                CardList::getInstance()->cardListByName.at(CardKeys::Binary12),
            },
            // Player decimal cards
            std::vector<CardData*>
            {
                CardList::getInstance()->cardListByName.at(CardKeys::Decimal6),
            },
            // Player hex cards
            std::vector<CardData*>
            {
            },
            // Enemy binary cards
            std::vector<CardData*>
            {
            },
            // Enemy decimal cards
            std::vector<CardData*>
            {
                CardList::getInstance()->cardListByName.at(CardKeys::Decimal13),
                CardList::getInstance()->cardListByName.at(CardKeys::Decimal5),
            },
            // Enemy hex cards
            std::vector<CardData*>
            {
                CardList::getInstance()->cardListByName.at(CardKeys::Hex7),
                CardList::getInstance()->cardListByName.at(CardKeys::Hex13),
            },
            { TutorialCIntroSequence::create() })
	);
}
