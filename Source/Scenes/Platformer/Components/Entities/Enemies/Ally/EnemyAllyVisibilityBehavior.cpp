#include "EnemyAllyVisibilityBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string EnemyAllyVisibilityBehavior::MapKey = "ally-visibility";

EnemyAllyVisibilityBehavior* EnemyAllyVisibilityBehavior::create(GameObject* owner)
{
	EnemyAllyVisibilityBehavior* instance = new EnemyAllyVisibilityBehavior(owner);

	instance->autorelease();

	return instance;
}

EnemyAllyVisibilityBehavior::EnemyAllyVisibilityBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EnemyAllyVisibilityBehavior::~EnemyAllyVisibilityBehavior()
{
}

void EnemyAllyVisibilityBehavior::initializePositions()
{
}

void EnemyAllyVisibilityBehavior::onLoad()
{
	this->entity->setVisible(false);
}

void EnemyAllyVisibilityBehavior::onDisable()
{
	super::onDisable();
}
