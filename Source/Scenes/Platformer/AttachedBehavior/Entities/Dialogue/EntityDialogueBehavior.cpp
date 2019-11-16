#include "EntityDialogueBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/DialogueSet.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

#include "Strings/Common/Brackets.h"
#include "Strings/Common/Dash.h"
#include "Strings/Common/Empty.h"
#include "Strings/Common/Newline.h"
#include "Strings/Common/Triconcat.h"
#include "Strings/Platformer/Dialogue/Goodbye.h"

using namespace cocos2d;

const std::string EntityDialogueBehavior::MapKeyAttachedBehavior = "entity-dialogue";

EntityDialogueBehavior* EntityDialogueBehavior::create(GameObject* owner)
{
	EntityDialogueBehavior* instance = new EntityDialogueBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityDialogueBehavior::EntityDialogueBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->squally = nullptr;
	this->interactMenu = InteractMenu::create(ConstantString::create("[V]"));
	this->canInteract = false;
	this->dialogueCollision = nullptr;
	this->pretextNode = Node::create();
	this->dialogueSetNode = Node::create();
	this->mainDialogueSet = DialogueSet::create();
	this->pretextQueue = std::queue<DialogueEvents::DialogueOpenArgs>();
	this->dialogueSets = std::vector<DialogueSet*>();
	this->activeDialogueSet = this->mainDialogueSet;
	this->optionsVisible = false;

	this->addDialogueSet(this->mainDialogueSet);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->dialogueCollision = CollisionObject::create(
			PhysicsBody::createBox(this->entity->getEntitySize()),
			(CollisionType)PlatformerCollisionType::Trigger,
			false,
			false
		);

		this->interactMenu->setPosition(this->entity->getCollisionOffset() + Vec2(0.0f, this->entity->getMovementSize().height / 2.0f));

		Vec2 collisionOffset = this->entity->getCollisionOffset();

		if (this->entity->isFlippedY())
		{
			Vec2 offset = Vec2(collisionOffset.x, -collisionOffset.y) - Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);
			this->dialogueCollision->inverseGravity();
			this->dialogueCollision->getPhysicsBody()->setPositionOffset(offset);
		}
		else
		{
			Vec2 offset = collisionOffset + Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);
			this->dialogueCollision->getPhysicsBody()->setPositionOffset(offset);
		}

		this->addChild(this->dialogueCollision);
	}

	this->pretextNode->setVisible(false);
	
	this->addChild(this->interactMenu);
	this->addChild(this->pretextNode);
	this->addChild(this->dialogueSetNode);
}

EntityDialogueBehavior::~EntityDialogueBehavior()
{
}

void EntityDialogueBehavior::onLoad()
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKeySqually);

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_V }, [=](InputEvents::InputArgs* args)
	{
		if (this->canInteract)
		{
			this->onInteract();
		}
	});

	this->dialogueCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		if (this->hasDialogueOptions() || !this->pretextQueue.empty())
		{
			this->canInteract = true;
			this->interactMenu->show();
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
		 
	this->dialogueCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->canInteract = false;
		this->interactMenu->hide();

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_1 }, [=](InputEvents::InputArgs* args)
	{
		this->chooseOption(1);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_2 }, [=](InputEvents::InputArgs* args)
	{
		this->chooseOption(2);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_3 }, [=](InputEvents::InputArgs* args)
	{
		this->chooseOption(3);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_4 }, [=](InputEvents::InputArgs* args)
	{
		this->chooseOption(4);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_5 }, [=](InputEvents::InputArgs* args)
	{
		this->chooseOption(5);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_6 }, [=](InputEvents::InputArgs* args)
	{
		this->chooseOption(6);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_7 }, [=](InputEvents::InputArgs* args)
	{
		this->chooseOption(7);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_8 }, [=](InputEvents::InputArgs* args)
	{
		this->chooseOption(8);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_9 }, [=](InputEvents::InputArgs* args)
	{
		this->chooseOption(9);
	});

	this->mainDialogueSet->addDialogueOption(DialogueOption::create(Strings::Platformer_Dialogue_Goodbye::create(), nullptr, false), 0.01f);
}

void EntityDialogueBehavior::enqueuePretext(DialogueEvents::DialogueOpenArgs pretext)
{
	std::function<void()> originalFunc = pretext.onDialogueClose;

	pretext.onDialogueClose = [=]()
	{
		if (originalFunc != nullptr)
		{
			originalFunc();
		}

		this->onInteract();
	};

	this->pretextQueue.push(pretext);
	this->pretextNode->addChild(pretext.dialogue);
	this->pretextNode->addChild(pretext.visualArgs.leftContentNode);
	this->pretextNode->addChild(pretext.visualArgs.rightContentNode);
}

void EntityDialogueBehavior::onInteract()
{
	if (this->pretextQueue.empty())
	{
		if (this->hasDialogueOptions())
		{
			this->setActiveDialogueSet(this->getMainDialogueSet());
			return;
		}
	}
	else 
	{
		DialogueEvents::TriggerDialogueOpen(this->pretextQueue.front());
		this->pretextQueue.pop();
	}
}

void EntityDialogueBehavior::setActiveDialogueSet(DialogueSet* dialogueSet, bool showDialogue)
{
	this->activeDialogueSet = dialogueSet;

	if (showDialogue)
	{
		this->showOptions();
	}
}

void EntityDialogueBehavior::addDialogueSet(DialogueSet* dialogueSet)
{
	this->dialogueSets.push_back(dialogueSet);
	this->dialogueSetNode->addChild(dialogueSet);
}

void EntityDialogueBehavior::removeDialogueSet(DialogueSet* dialogueSet)
{
	this->dialogueSets.erase(std::find(this->dialogueSets.begin(), this->dialogueSets.end(), dialogueSet));
	this->dialogueSetNode->removeChild(dialogueSet);
}

DialogueSet* EntityDialogueBehavior::getMainDialogueSet()
{
	return this->mainDialogueSet;
}

void EntityDialogueBehavior::chooseOption(int option)
{
	std::vector<std::tuple<DialogueOption*, float>> dialogueOptions = this->activeDialogueSet->getDialogueOptions();

	if (!this->optionsVisible || --option < 0 || option >= int(dialogueOptions.size()))
	{
		return;
	}
	
	DialogueEvents::TriggerTryDialogueClose(DialogueEvents::DialogueCloseArgs([=]()
	{
		if (std::get<0>(dialogueOptions[option])->onDialogueChosen != nullptr)
		{
			std::get<0>(dialogueOptions[option])->onDialogueChosen();
		}
	}));

}

void EntityDialogueBehavior::showOptions()
{
	std::vector<std::tuple<DialogueOption*, float>> dialogueOptions = this->activeDialogueSet->getDialogueOptions();

	if (dialogueOptions.empty() || (this->squally != nullptr && this->squally->getStateOrDefaultBool(StateKeys::CinematicHijacked, false)))
	{
		return;
	}

	LocalizedString* options = Strings::Common_Triconcat::create();
	LocalizedString* nextOption = options;
	LocalizedString* currentOption = nextOption;
	int index = 1;

	this->optionsVisible = true;

	for (auto it = dialogueOptions.begin(); it != dialogueOptions.end(); it++, index++)
	{
		bool lastIter = it == (--dialogueOptions.end());

		LocalizedString* optionRaw = std::get<0>(*it)->dialogueOption;
		LocalizedString* newline = Strings::Common_Newline::create();
		nextOption = lastIter ? (LocalizedString*)Strings::Common_Empty::create() : (LocalizedString*)Strings::Common_Triconcat::create();
		LocalizedString* option = this->getOptionString(index, optionRaw == nullptr ? optionRaw : optionRaw->clone());

		currentOption->setStringReplacementVariables({option , newline, nextOption });
		currentOption = nextOption;
	}

	DialogueEvents::TriggerDialogueOpen(DialogueEvents::DialogueOpenArgs(
		options,
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(this->entity, false),
			DialogueEvents::BuildPreviewNode(this->squally, true)
		),
		[=]()
		{
			this->optionsVisible = false;
		},
		"",
		true
	));
}

bool EntityDialogueBehavior::hasDialogueOptions()
{
	if (this->activeDialogueSet == nullptr)
	{
		return false;
	}

	std::vector<std::tuple<DialogueOption*, float>> dialogueOptions = this->activeDialogueSet->getDialogueOptions();

	if (dialogueOptions.size() > 1)
	{
		return true;
	}

	return std::get<0>(dialogueOptions[0])->isShownIfUnique();
}

LocalizedString* EntityDialogueBehavior::getOptionString(int index, LocalizedString* optionText)
{
	LocalizedString* dash = Strings::Common_Dash::create();
	LocalizedString* brackets = Strings::Common_Brackets::create();

	brackets->setStringReplacementVariables(ConstantString::create(std::to_string(index)));

	dash->setStringReplacementVariables({ brackets, optionText });

	return dash;
}
