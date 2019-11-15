#include "HexusBehaviorBase.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/DialogueSet.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/HexusEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

#include "Strings/Hexus/Hexus.h"
#include "Strings/Platformer/Dialogue/Hexus/ADraw.h"
#include "Strings/Platformer/Dialogue/Hexus/BetterLuckNextTime.h"
#include "Strings/Platformer/Dialogue/Hexus/GoodGame.h"
#include "Strings/Platformer/Dialogue/Hexus/WellPlayed.h"
#include "Strings/Platformer/Dialogue/Hexus/HowAboutARematch.h"
#include "Strings/Platformer/Dialogue/Hexus/HowAboutARoundOfHexus.h"
#include "Strings/Platformer/Notifications/ItemWon.h"

using namespace cocos2d;

HexusBehaviorBase::HexusBehaviorBase(GameObject* owner, LocalizedString* dialogueChoiceOverride) : super(owner)
{
	this->winCallbacks = std::vector<std::function<void()>>();
	this->lossCallbacks = std::vector<std::function<void()>>();
	this->drawCallbacks = std::vector<std::function<void()>>();
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->dialogueChoiceOverride = dialogueChoiceOverride;
	this->rewardPool = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	if (this->dialogueChoiceOverride != nullptr)
	{
		this->addChild(this->dialogueChoiceOverride);
	}
}

HexusBehaviorBase::~HexusBehaviorBase()
{
}

void HexusBehaviorBase::registerWinCallback(std::function<void()> winCallback)
{
	this->winCallbacks.push_back(winCallback);
}

void HexusBehaviorBase::registerLossCallback(std::function<void()> lossCallback)
{
	this->lossCallbacks.push_back(lossCallback);
}

void HexusBehaviorBase::registerDrawCallback(std::function<void()> drawCallback)
{
	this->drawCallbacks.push_back(drawCallback);
}

void HexusBehaviorBase::onLoad()
{
	this->rewardPool = this->generateReward();

	if (this->rewardPool != nullptr)
	{
		this->addChild(this->rewardPool);
	}

	this->entity->watchForAttachedBehavior<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		if (this->dialogueChoiceOverride != nullptr)
		{
			interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
				this->dialogueChoiceOverride->clone(),
				[=]()
				{
					HexusEvents::TriggerOpenHexus(HexusEvents::HexusOpenArgs(this->createOpponentData()));
				}),
				0.5f
			);
		}
		else
		{
			if (!this->entity->getObjectStateOrDefault(this->getWinLossSaveKey(), Value(false)).asBool())
			{
				interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
					Strings::Platformer_Dialogue_Hexus_HowAboutARoundOfHexus::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
					[=]()
					{
						HexusEvents::TriggerOpenHexus(HexusEvents::HexusOpenArgs(this->createOpponentData()));
					}),
					0.5f
				);
			}
			else
			{
				interactionBehavior->getMainDialogueSet()->addDialogueOption(DialogueOption::create(
					Strings::Platformer_Dialogue_Hexus_HowAboutARematch::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()),
					[=]()
					{
						HexusEvents::TriggerOpenHexus(HexusEvents::HexusOpenArgs(this->createOpponentData()));
					}),
					0.5f
				);
			}
		}
	});
}

void HexusBehaviorBase::onWin()
{
	static int DialogueOptionCount = 2;
	static int DialogueIndex = RandomHelper::random_int(0, DialogueOptionCount);

	switch (DialogueIndex++ % DialogueOptionCount)
	{
		default:
		case 0:
		{
			this->entity->speechBubble->runDialogue(Strings::Platformer_Dialogue_Hexus_WellPlayed::create());
			break;
		}
		case 1:
		{
			this->entity->speechBubble->runDialogue(Strings::Platformer_Dialogue_Hexus_GoodGame::create());
			break;
		}
	}

	if (!this->entity->getObjectStateOrDefault(this->getWinLossSaveKey(), Value(false)).asBool())
	{
		if (this->rewardPool != nullptr)
		{
			std::vector<Item*> items = this->rewardPool->getItems();

			for (auto it = items.begin(); it != items.end(); it++)
			{
				PlatformerEvents::TriggerGiveItem(PlatformerEvents::GiveItemArgs(*it, Strings::Platformer_Notifications_ItemWon::create()));
			}
		}

		this->entity->saveObjectState(this->getWinLossSaveKey(), Value(true));
	}

	for (auto it = this->winCallbacks.begin(); it != this->winCallbacks.end(); it++)
	{
		(*it)();
	}
}

void HexusBehaviorBase::onLoss()
{
	static int DialogueOptionCount = 1;
	static int DialogueIndex = RandomHelper::random_int(0, DialogueOptionCount);

	switch (DialogueIndex++ % DialogueOptionCount)
	{
		default:
		case 0:
		{
			this->entity->speechBubble->runDialogue(Strings::Platformer_Dialogue_Hexus_BetterLuckNextTime::create());
			break;
		}
	}

	for (auto it = this->lossCallbacks.begin(); it != this->lossCallbacks.end(); it++)
	{
		(*it)();
	}
}

void HexusBehaviorBase::onDraw()
{
	static int DialogueOptionCount = 1;
	static int DialogueIndex = RandomHelper::random_int(0, DialogueOptionCount);

	switch (DialogueIndex++ % DialogueOptionCount)
	{
		default:
		case 0:
		{
			this->entity->speechBubble->runDialogue(Strings::Platformer_Dialogue_Hexus_ADraw::create());
			break;
		}
	}

	for (auto it = this->drawCallbacks.begin(); it != this->drawCallbacks.end(); it++)
	{
		(*it)();
	}
}

HexusOpponentData* HexusBehaviorBase::createOpponentData()
{
    return HexusOpponentData::create( 
        // TODO: This needs to work similar to the dialogue boxes, and pass the entity to a builder that accounts for scale/offsets
        this->entity->getAnimations()->getAnimationResource(),
        this->getBackgroundResource(),
        this->entity->getScale(), // DEPRECATED
		Vec2::ZERO, // DEPRECATED
        Vec2::ZERO, // DEPRECATED
        this->entity->getDialogueOffset() - Vec2(0.0f, 72.0f),
        this->getWinLossSaveKey(),
        HexusOpponentData::Strategy::Random,
        Card::CardStyle::Light,
        0.0f, // DEPRECATED
        this->generateDeck(),
        [=](HexusOpponentData::Result result)
        {
			switch(result)
			{
				case HexusOpponentData::Result::Win:
				default:
				{
                	this->onWin();
					break;
				}
				case HexusOpponentData::Result::Loss:
				{
                	this->onLoss();
					break;
				}
				case HexusOpponentData::Result::Draw:
				{
                	this->onDraw();
					break;
				}
			}
        },
		this->getStateOverride(),
		this->getTutorials()
	);
}

std::vector<TutorialBase*> HexusBehaviorBase::getTutorials()
{
	return { };
}
