#include "EnemyHealthBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EnemyHealthBehavior::MapKeyAttachedBehavior = "enemy-health";
const std::string EnemyHealthBehavior::SaveKeyIsDead = "is-dead";

EnemyHealthBehavior* EnemyHealthBehavior::create(GameObject* owner)
{
	EnemyHealthBehavior* instance = new EnemyHealthBehavior(owner);

	instance->autorelease();

	return instance;
}

EnemyHealthBehavior::EnemyHealthBehavior(GameObject* owner) : super(owner)
{
}

EnemyHealthBehavior::~EnemyHealthBehavior()
{
}

void EnemyHealthBehavior::onLoad()
{
	/*
	if (this->entity->getObjectStateOrDefault(EnemyHealthBehavior::SaveKeyIsDead, Value(false)).asBool())
	{
		this->kill(true);

		if (!this->mapEvent.empty())
		{
			ObjectEvents::TriggerBroadCastMapObjectState(this->mapEvent, ValueMap());
		}
	}
	*/
}

void EnemyHealthBehavior::saveState()
{
}

/*
void EnemyHealthBehavior::kill(bool loadDeadAnim)
{
	super::kill(loadDeadAnim);

	if (!this->entity->getMapEvent().empty())
	{
		ObjectEvents::TriggerBroadCastMapObjectState(this->mapEvent, ValueMap());
	}

	this->entity->saveObjectState(EnemyHealthBehavior::SaveKeyIsDead, Value(true));
}

void EnemyHealthBehavior::revive()
{
	super::revive();

	this->entity->saveObjectState(EnemyHealthBehavior::SaveKeyIsDead, Value(false));
}
*/
