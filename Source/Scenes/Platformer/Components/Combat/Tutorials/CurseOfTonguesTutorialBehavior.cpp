#include "CurseOfTonguesTutorialBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/CombatEvents.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Combat/Projectiles/Fireball/Fireball.h"
#include "Scenes/Platformer/Components/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Scrappy/Combat/ScrappyHackableCueBehavior.h"
#include "Scenes/Platformer/Hackables/ScrappyClippy.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/CurseOfTongues/CurseOfTongues.h"

#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CurseOfTonguesTutorialBehavior::MapKey = "curse-of-tongues-tutorial";

CurseOfTonguesTutorialBehavior* CurseOfTonguesTutorialBehavior::create(GameObject* owner)
{
	CurseOfTonguesTutorialBehavior* instance = new CurseOfTonguesTutorialBehavior(owner);

	instance->autorelease();

	return instance;
}

CurseOfTonguesTutorialBehavior::CurseOfTonguesTutorialBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->scrappy = nullptr;
	this->squally = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

CurseOfTonguesTutorialBehavior::~CurseOfTonguesTutorialBehavior()
{
}

void CurseOfTonguesTutorialBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventBuffApplied, [=](EventCustom* eventCustom)
	{
		CombatEvents::BuffAppliedArgs* args = static_cast<CombatEvents::BuffAppliedArgs*>(eventCustom->getData());

		if (args != nullptr && args->buff != nullptr && dynamic_cast<CurseOfTongues*>(args->buff) != nullptr)
		{
			args->buff->registerClippyOnto(CurseOfTongues::CurseOfTonguesIdentifier, [=]
			{
				return ScrappyClippy::create(Strings::Menus_Hacking_ClippyHelp_Abilities_CurseOfTongues_CurseOfTonguesScriptCopy::create()
					->setStringReplacementVariables(Strings::Menus_Hacking_Abilities_Debuffs_CurseOfTongues_ReduceCurse::create()));
			});
		}
	}));

	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	}, Squally::MapKey);
}

void CurseOfTonguesTutorialBehavior::onDisable()
{
	super::onDisable();
}
