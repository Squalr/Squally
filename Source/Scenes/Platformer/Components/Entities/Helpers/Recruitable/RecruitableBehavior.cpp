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
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/BallmerPeaks/Snowman.h"
#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Entities/Platformer/Helpers/CastleValgrind/Grim.h"
#include "Entities/Platformer/Helpers/UnderflowRuins/GuanoPetrified.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Dialogue/Voices.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
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
	else
	{
		this->entity->setQueryable(false);
	}
}

RecruitableBehavior::~RecruitableBehavior()
{
}

void RecruitableBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;

		std::string currentHelperName = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyHelperName, Value("")).asString();

		this->updateStateForCurrentHelper(currentHelperName, false);

		this->squally->listenForStateWrite(StateKeys::CurrentHelper, [=](Value value)
		{
			this->updateStateForCurrentHelper(value.asString(), true);
		});
	}, Squally::MapKey);
}

void RecruitableBehavior::onDisable()
{
	super::onDisable();
}

void RecruitableBehavior::updateStateForCurrentHelper(std::string currentHelperName, bool playAnims)
{
	this->entity->getComponent<EntityDialogueBehavior>([=](EntityDialogueBehavior* interactionBehavior)
	{
		std::string helperName = GameUtils::getKeyOrDefault(this->entity->properties, GameObject::PropertyName, Value("")).asString();
		bool isHelperAvailable = true;

		if (helperName == Guano::MapKey && !SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGuanoFound, Value(false)).asBool())
		{
			isHelperAvailable = false;
		}
		else if (helperName == Gecky::MapKey && !SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGeckyFound, Value(false)).asBool())
		{
			isHelperAvailable = false;
		}
		else if (helperName == Grim::MapKey && !SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyGrimFound, Value(false)).asBool())
		{
			isHelperAvailable = false;
		}

		if (currentHelperName == helperName || !isHelperAvailable)
		{
			interactionBehavior->clearPretext();
			interactionBehavior->disableInteraction();
			this->entity->runAction(FadeTo::create(playAnims ? 0.5f : 0.0f, 0));
			return;
		}
		else
		{
			interactionBehavior->enableInteraction();
			this->entity->runAction(FadeTo::create(playAnims ? 0.5f : 0.0f, 255));
		}

		LocalizedString* dialog = nullptr;

		if (helperName == Guano::MapKey)
		{
			dialog = Strings::Platformer_Dialogue_Recruitable_GuanoRecruitable::create();
		}
		else if (helperName == Gecky::MapKey)
		{
			dialog = Strings::Platformer_Dialogue_Recruitable_GeckyRecruitable::create();
		}
		else if (helperName == Grim::MapKey)
		{
			dialog = Strings::Platformer_Dialogue_Recruitable_GrimRecruitable::create();
		}

		interactionBehavior->clearPretext();
		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			dialog,
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Right,
				DialogueEvents::BuildPreviewNode(&this->squally, false),
				DialogueEvents::BuildPreviewNode(&this->entity, true)
			),
			[=]()
			{
			},
			Voices::GetNextVoiceMedium(),
			false
		));
		
		std::vector<LocalizedString*> options = std::vector<LocalizedString*>();
		std::vector<std::function<bool()>> callbacks = std::vector<std::function<bool()>>();
		
		options.push_back(Strings::Platformer_Dialogue_Recruitable_RecruitableAccept::create());
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

		interactionBehavior->enqueuePretext(DialogueEvents::DialogueOpenArgs(
			DialogueEvents::BuildOptions(Strings::Platformer_Dialogue_Recruitable_RecruitableChoose::create(), options),
			DialogueEvents::DialogueVisualArgs(
				DialogueBox::DialogueDock::Bottom,
				DialogueBox::DialogueAlignment::Left,
				DialogueEvents::BuildPreviewNode(&this->scrappy, false),
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
	});
}
