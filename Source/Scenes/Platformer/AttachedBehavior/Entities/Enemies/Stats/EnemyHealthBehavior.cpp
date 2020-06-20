#include "EnemyHealthBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SaveEvents.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EnemyHealthBehavior::MapKey = "enemy-health";
const std::string EnemyHealthBehavior::SaveKeyIsDead = "is-dead";

EnemyHealthBehavior* EnemyHealthBehavior::create(GameObject* owner)
{
	EnemyHealthBehavior* instance = new EnemyHealthBehavior(owner);

	instance->autorelease();

	return instance;
}

EnemyHealthBehavior::EnemyHealthBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEnemy*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EnemyHealthBehavior::~EnemyHealthBehavior()
{
}

void EnemyHealthBehavior::onLoad()
{
	if (this->entity != nullptr)
	{
		this->entity->listenForStateWrite(StateKeys::IsAlive, [=](Value value)
		{
			if (!value.asBool())
			{
				this->entity->broadcastMapEvent(this->entity->getSendEvent(), ValueMap());
			}

			this->entity->saveObjectState(EnemyHealthBehavior::SaveKeyIsDead, Value(!value.asBool()));
		});

		if (this->entity->loadObjectStateOrDefault(EnemyHealthBehavior::SaveKeyIsDead, Value(false)).asBool())
		{
			this->entity->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
			{
				healthBehavior->kill(false);
			});
		}
	}
}

void EnemyHealthBehavior::onDisable()
{
	super::onDisable();
}
