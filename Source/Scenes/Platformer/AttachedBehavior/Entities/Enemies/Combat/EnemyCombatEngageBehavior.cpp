#include "EnemyCombatEngageBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerHelper.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Combat/SquallyCombatBehaviorGroup.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Huds/CombatFadeInHuds/CombatFadeInHud.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string EnemyCombatEngageBehavior::MapKeyAttachedBehavior = "enemy-combat-engage";

EnemyCombatEngageBehavior* EnemyCombatEngageBehavior::create(GameObject* owner)
{
	EnemyCombatEngageBehavior* instance = new EnemyCombatEngageBehavior(owner);

	instance->autorelease();

	return instance;
}

EnemyCombatEngageBehavior::EnemyCombatEngageBehavior(GameObject* owner) : super(owner)
{
	this->enemy = dynamic_cast<PlatformerEnemy*>(owner);
	this->canEngage = true;

	if (this->enemy == nullptr)
	{
		this->invalidate();
	}
}

EnemyCombatEngageBehavior::~EnemyCombatEngageBehavior()
{
}

void EnemyCombatEngageBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEngageEnemy, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::EngageEnemyArgs* args = static_cast<PlatformerEvents::EngageEnemyArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->enemy != nullptr && args->enemy == this->enemy)
		{
			this->engageEnemy(args->firstStrike);
		}

		this->stopAllEntityActions();
	}));
}

void EnemyCombatEngageBehavior::stopAllEntityActions()
{
	this->enemy->clearState(StateKeys::PatrolDestinationX);
	this->enemy->setState(StateKeys::CinematicHijacked, Value(true));
	this->enemy->setState(StateKeys::PatrolHijacked, Value(true));
	this->canEngage = false;
}

void EnemyCombatEngageBehavior::engageEnemy(bool firstStrike)
{
	std::vector<CombatMap::CombatData> playerCombatData = std::vector<CombatMap::CombatData>();
	std::vector<CombatMap::CombatData> enemyCombatData = std::vector<CombatMap::CombatData>();

	// Build player team
	playerCombatData.push_back(CombatMap::CombatData(Squally::MapKeySqually, SquallyCombatBehaviorGroup::MapKeyAttachedBehavior));
	
	ObjectEvents::QueryObjects<PlatformerHelper>(QueryObjectsArgs<PlatformerHelper>([&](PlatformerHelper* helper)
	{
		playerCombatData.push_back(CombatMap::CombatData(helper->getEntityKey(), helper->getBattleBehavior()));
	}), Squally::BattleTag);

	// Build enemy team
	enemyCombatData.push_back(CombatMap::CombatData(this->enemy->getEntityKey(), this->enemy->getBattleBehavior(), this->enemy->getDropPool()));

	if (!this->enemy->getBattleTag().empty())
	{
		ObjectEvents::QueryObjects<PlatformerEnemy>(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* enemyAlly)
		{
			if (enemyAlly != this->enemy)
			{
				enemyCombatData.push_back(CombatMap::CombatData(enemyAlly->getEntityKey(), enemyAlly->getBattleBehavior(), enemyAlly->getDropPool()));
			}
		}), this->enemy->getBattleTag());
	}

	PlatformerEvents::TriggerEnemyEngaged(PlatformerEvents::EnemyEngagedArgs());

	this->runAction(Sequence::create(
		DelayTime::create(CombatFadeInHud::AnimationTimeBudget + 0.25f),
		CallFunc::create([=]()
		{
			// Start combat
			CombatMap* combatMap = CombatMap::create(
				this->enemy->getBattleMapResource(),
				firstStrike,
				this->enemy->getUniqueIdentifier(),
				playerCombatData,
				enemyCombatData
			);

			NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(combatMap));
		}),
		nullptr
	));
}
