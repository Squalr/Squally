#include "EntityDialogueBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/DialogueOption.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Menus/Interact/InteractMenu.h"
#include "Scenes/Platformer/Dialogue/DialogueSet.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string EntityDialogueBehavior::MapKey = "entity-dialogue";

EntityDialogueBehavior* EntityDialogueBehavior::create(GameObject* owner)
{
	EntityDialogueBehavior* instance = new EntityDialogueBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityDialogueBehavior::EntityDialogueBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->interactMenu = InteractMenu::create(ConstantString::create("[V]"));
	this->canInteract = false;
	this->hasCollision = false;
	this->dialogueCollision = nullptr;
	this->scrappy = nullptr;
	this->pretextNode = Node::create();
	this->dialogueSetNode = Node::create();

	// This is just a default. Can be overriden for specific needs
	this->mainDialogueSet = DialogueSet::create(DialogueEvents::DialogueVisualArgs(
		DialogueBox::DialogueDock::Bottom,
		DialogueBox::DialogueAlignment::Left,
		DialogueEvents::BuildPreviewNode(&this->scrappy, false),
		DialogueEvents::BuildPreviewNode(&this->entity, true)
	));

	this->speechBubble = SpeechBubble::create();
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
			CollisionObject::createBox(this->entity->getEntitySize()),
			(CollisionType)PlatformerCollisionType::Trigger,
			CollisionObject::Properties(false, false),
			Color4F::ORANGE
		);

		this->interactMenu->setPosition(this->entity->getCollisionOffset() + Vec2(0.0f, this->entity->getMovementSize().height / 2.0f));

		Vec2 collisionOffset = this->entity->getCollisionOffset();
		Vec2 offset = collisionOffset + Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);

		this->dialogueCollision->setPosition(offset);

		this->addChild(this->dialogueCollision);
	}

	this->pretextNode->setVisible(false);
	
	this->addChild(this->interactMenu);
	this->addChild(this->pretextNode);
	this->addChild(this->dialogueSetNode);
	this->addChild(this->speechBubble);
}

EntityDialogueBehavior::~EntityDialogueBehavior()
{
}

void EntityDialogueBehavior::initializePositions()
{
	super::initializePositions();

	if (this->entity != nullptr)
	{
		Vec2 offset = this->entity->getCollisionOffset() + Vec2(0.0f, this->entity->getEntitySize().height + this->entity->getHoverHeight() / 2.0f + 16.0f);

		this->speechBubble->setPosition(offset);
	}
}

void EntityDialogueBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_V }, [=](InputEvents::InputArgs* args)
	{
		if (this->canInteract && this->hasCollision)
		{
			this->onInteract();
		}
	});

	this->dialogueCollision->whenCollidesWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->hasCollision = true;

		this->updateInteractVisibility();

		return CollisionObject::CollisionResult::DoNothing;
	});
		 
	this->dialogueCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Player }, [=](CollisionObject::CollisionData data)
	{
		this->hasCollision = false;

		this->updateInteractVisibility();

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

	this->scheduleUpdate();
}

void EntityDialogueBehavior::onDisable()
{
	super::onDisable();
}

void EntityDialogueBehavior::update(float dt)
{
	super::update(dt);

	// Update on a loop -- this is to catch the case where dialogue options are added to a dialogue set, which isn't caught otherwise.
	this->updateInteractVisibility();
}

SpeechBubble* EntityDialogueBehavior::getSpeechBubble()
{
	return this->speechBubble;
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

		this->progressDialogue();
	};

	this->pretextQueue.push(pretext);

	if (pretext.dialogue != nullptr)
	{
		this->pretextNode->addChild(pretext.dialogue);
	}

	this->updateInteractVisibility();
}

void EntityDialogueBehavior::clearPretext()
{
	this->pretextQueue = std::queue<DialogueEvents::DialogueOpenArgs>();
	this->pretextNode->removeAllChildren();
}

void EntityDialogueBehavior::onInteract()
{
	if (this->entity->getStateOrDefaultBool(StateKeys::CinematicHijacked, false))
	{
		return;
	}

	this->progressDialogue();
}

void EntityDialogueBehavior::progressDialogue()
{
	if (this->pretextQueue.empty())
	{
		if (this->hasDialogueOptions())
		{
			this->setActiveDialogueSet(this->getMainDialogueSet());
		}
	}
	else 
	{
		DialogueEvents::TriggerOpenDialogue(this->pretextQueue.front());
		this->pretextQueue.pop();
	}
	
	this->updateInteractVisibility();
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

	if (dialogueOptions.empty())
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

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		options,
		this->activeDialogueSet->getArgs(),
		[=]()
		{
			this->optionsVisible = false;
		},
		"",
		true,
		false
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

void EntityDialogueBehavior::updateInteractVisibility()
{
	if (!(this->hasDialogueOptions() || !this->pretextQueue.empty()))
	{
		this->canInteract = false;
	}
	else
	{
		this->canInteract = true;
	}
	
	if (this->canInteract && this->hasCollision)
	{
		this->interactMenu->show();
	}
	else
	{
		this->interactMenu->hide();
	}
}

LocalizedString* EntityDialogueBehavior::getOptionString(int index, LocalizedString* optionText)
{
	LocalizedString* dash = Strings::Common_Dash::create();
	LocalizedString* brackets = Strings::Common_Brackets::create();

	brackets->setStringReplacementVariables(ConstantString::create(std::to_string(index)));

	dash->setStringReplacementVariables({ brackets, optionText });

	return dash;
}
