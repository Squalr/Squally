#include "EnemyAllyDropBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string EnemyAllyDropBehavior::MapKey = "ally-drop";

EnemyAllyDropBehavior* EnemyAllyDropBehavior::create(GameObject* owner)
{
	EnemyAllyDropBehavior* instance = new EnemyAllyDropBehavior(owner);

	instance->autorelease();

	return instance;
}

EnemyAllyDropBehavior::EnemyAllyDropBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EnemyAllyDropBehavior::~EnemyAllyDropBehavior()
{
}

void EnemyAllyDropBehavior::initializePositions()
{
}

void EnemyAllyDropBehavior::onLoad()
{
	// Allies should not have a drop pool // ZAC : Why are drop pools on the entity and not a separate behavior?
	if (dynamic_cast<PlatformerEnemy*>(this->entity) != nullptr)
	{
		dynamic_cast<PlatformerEnemy*>(this->entity)->setDropPool("");
	}
}

void EnemyAllyDropBehavior::onDisable()
{
	super::onDisable();
}
