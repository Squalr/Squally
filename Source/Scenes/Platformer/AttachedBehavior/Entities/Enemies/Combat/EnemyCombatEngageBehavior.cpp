#include "EnemyCombatEngageBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Sound/Sound.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerHelper.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Combat/SquallyCombatBehaviorGroup.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Huds/CombatFadeInHuds/CombatFadeInHud.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string EnemyCombatEngageBehavior::MapKey = "enemy-combat-engage";

EnemyCombatEngageBehavior* EnemyCombatEngageBehavior::create(GameObject* owner)
{
	EnemyCombatEngageBehavior* instance = new EnemyCombatEngageBehavior(owner);

	instance->autorelease();

	return instance;
}

EnemyCombatEngageBehavior::EnemyCombatEngageBehavior(GameObject* owner) : super(owner)
{
	this->enemy = dynamic_cast<PlatformerEnemy*>(owner);
	this->engageSound = Sound::create(SoundResources::Platformer_Combat_CombatEngage1);
	this->canEngage = true;

	if (this->enemy == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->engageSound);
}

EnemyCombatEngageBehavior::~EnemyCombatEngageBehavior()
{
}

void EnemyCombatEngageBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEngageEnemy, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::EngageEnemyArgs* args = static_cast<PlatformerEvents::EngageEnemyArgs*>(eventCustom->getData());

		if (args != nullptr && args->enemy != nullptr && args->enemy == this->enemy)
		{
			PlatformerEvents::TriggerCinematicHijack();
			this->engageEnemy(args->firstStrike);
		}

		this->stopAllEntityActions();
	}));

	if (!this->enemy->getListenEvent().empty())
	{
		this->enemy->listenForMapEventOnce(this->enemy->getListenEvent(), [=](ValueMap)
		{
			PlatformerEvents::TriggerCinematicHijack();
			this->engageEnemy(false);
			this->stopAllEntityActions();
		});
	}
}

void EnemyCombatEngageBehavior::onDisable()
{
	super::onDisable();
}

void EnemyCombatEngageBehavior::stopAllEntityActions()
{
	this->enemy->clearState(StateKeys::PatrolSourceX);
	this->enemy->clearState(StateKeys::PatrolDestinationX);
	this->enemy->setState(StateKeys::CinematicHijacked, Value(true));
	this->enemy->setState(StateKeys::PatrolHijacked, Value(true));
	this->canEngage = false;
}

void EnemyCombatEngageBehavior::engageEnemy(bool firstStrike)
{
	if (!this->canEngage)
	{
		return;
	}

	std::vector<CombatMap::CombatData> playerCombatData = std::vector<CombatMap::CombatData>();
	std::vector<CombatMap::CombatData> enemyCombatData = std::vector<CombatMap::CombatData>();
	
	ObjectEvents::QueryObjects<Squally>(QueryObjectsArgs<Squally>([&](Squally* squally)
	{
		playerCombatData.push_back(CombatMap::CombatData(
			squally->getEntityKey(),
			squally->getUniqueIdentifier(),
			squally->getBattleBehavior(),
			CombatMap::StatsOverrides(
				squally->getRuntimeStateOrDefault(StateKeys::Health, Value(8888)).asInt(),
				squally->getRuntimeStateOrDefault(StateKeys::Mana, Value(8888)).asInt()
			)
		));
	}), Squally::MapKey);
	
	ObjectEvents::QueryObjects<PlatformerHelper>(QueryObjectsArgs<PlatformerHelper>([&](PlatformerHelper* helper)
	{
		playerCombatData.push_back(CombatMap::CombatData(
			helper->getEntityKey(),
			helper->getUniqueIdentifier(),
			helper->getBattleBehavior(),
			CombatMap::StatsOverrides(
				helper->getRuntimeStateOrDefault(StateKeys::Health, Value(8888)).asInt(),
				helper->getRuntimeStateOrDefault(StateKeys::Mana, Value(8888)).asInt()
			)
		));
	}), Squally::TeamTag);

	// Build enemy team
	enemyCombatData.push_back(CombatMap::CombatData(
		this->enemy->getEntityKey(),
		this->enemy->getUniqueIdentifier(),
		this->enemy->getBattleBehavior(),
		CombatMap::StatsOverrides(
			this->enemy->getRuntimeStateOrDefault(StateKeys::Health, Value(8888)).asInt(),
			this->enemy->getRuntimeStateOrDefault(StateKeys::Mana, Value(8888)).asInt()
		),
		this->enemy->getDropPool()
	));

	if (!this->enemy->getBattleTag().empty())
	{
		ObjectEvents::QueryObjects<PlatformerEnemy>(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* enemyAlly)
		{
			if (enemyAlly != this->enemy && enemyAlly->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				enemyCombatData.push_back(CombatMap::CombatData(
					enemyAlly->getEntityKey(),
					enemyAlly->getUniqueIdentifier(),
					enemyAlly->getBattleBehavior(),
					CombatMap::StatsOverrides(
						enemyAlly->getRuntimeStateOrDefault(StateKeys::Health, Value(8888)).asInt(),
						enemyAlly->getRuntimeStateOrDefault(StateKeys::Mana, Value(8888)).asInt()
					),
					enemyAlly->getDropPool()
				));
			}
		}), this->enemy->getBattleTag());
	}

	PlatformerEvents::TriggerEnemyEngaged(PlatformerEvents::EnemyEngagedArgs());
	
	if (!this->engageSound->isPlaying())
	{
		this->engageSound->play();
	}

	this->runAction(Sequence::create(
		DelayTime::create(CombatFadeInHud::AnimationTimeBudget + 0.25f),
		CallFunc::create([=]()
		{
			// Start combat
			NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
			{
				CombatMap* combatMap = CombatMap::create(
					this->enemy->getBattleMapResource(),
					firstStrike,
					playerCombatData,
					enemyCombatData
				);

				return combatMap;
			}));
		}),
		nullptr
	));
}
