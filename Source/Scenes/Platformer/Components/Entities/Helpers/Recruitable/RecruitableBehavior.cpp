#include "RecruitableBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/ParticleResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string RecruitableBehavior::MapKey = "recruitable";

RecruitableBehavior* RecruitableBehavior::create(GameObject* owner)
{
	RecruitableBehavior* instance = new RecruitableBehavior(owner);

	instance->autorelease();

	return instance;
}

RecruitableBehavior::RecruitableBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->toggleQueryable(false);
}

RecruitableBehavior::~RecruitableBehavior()
{
}

void RecruitableBehavior::onLoad()
{
	// this->entity->despawn();

	this->entity->watchForComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		std::string helperName = GameUtils::getKeyOrDefault(this->entity->properties, GameObject::PropertyName, Value("")).asString();

		ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
		{
			this->squally = squally;

			if (this->squally->getRuntimeStateOrDefault(StateKeys::CurrentHelper, Value("")).asString() == helperName)
			{
				interactionBehavior->disableInteraction();
			}
		}, Squally::MapKey);

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			Strings::Menus_Cancel::create(),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->entity, true)
			),
			[=]()
			{
				this->defer([=]()
				{
					this->displayOptions();
				});
			},
			Voices::GetNextVoiceMedium(),
			false
		));
	});
}

void RecruitableBehavior::onDisable()
{
	super::onDisable();
}

void RecruitableBehavior::displayOptions()
{
	std::vector<LocalizedString*> options = std::vector<LocalizedString*>();
	std::vector<std::function<bool()>> callbacks = std::vector<std::function<bool()>>();
	
	options.push_back(Strings::Menus_Accept::create());
	options.push_back(Strings::Menus_Cancel::create());

	callbacks.push_back([=]()
	{
		this->entity->getComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
		{
			// Grant the new helper
			std::string helperName = GameUtils::getKeyOrDefault(this->entity->properties, GameObject::PropertyName, Value("")).asString();
			this->squally->setState(StateKeys::CurrentHelper, Value(helperName));
			interactionBehavior->disableInteraction();
		});
		return true;
	});

	callbacks.push_back([=]()
	{
		DialogueEvents::TriggerTryDialogueClose(DialogueEvents::DialogueCloseArgs([=]()
		{
		}));
		return true;
	});

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		DialogueEvents::BuildOptions(Strings::Platformer_Objects_Warps_WhereTo::create(), options),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Right,
			DialogueEvents::BuildPreviewNode(&this->squally, false),
			DialogueEvents::BuildPreviewNode(&this->entity, true)
		),
		[=]()
		{
		},
		"",
		true,
		false,
		callbacks,
		[=](){ return true; }
	));
}
