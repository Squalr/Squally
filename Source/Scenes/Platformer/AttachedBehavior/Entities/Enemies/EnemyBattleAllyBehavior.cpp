#include "EnemyBattleAllyBehavior.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string EnemyBattleAllyBehavior::MapKey = "ally";

EnemyBattleAllyBehavior* EnemyBattleAllyBehavior::create(GameObject* owner)
{
	EnemyBattleAllyBehavior* instance = new EnemyBattleAllyBehavior(owner);

	instance->autorelease();

	return instance;
}

EnemyBattleAllyBehavior::EnemyBattleAllyBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EnemyBattleAllyBehavior::~EnemyBattleAllyBehavior()
{
}

void EnemyBattleAllyBehavior::initializePositions()
{
}

void EnemyBattleAllyBehavior::onLoad()
{
	this->entity->setVisible(false);

	// Allies should not have a drop pool
	if (dynamic_cast<PlatformerEnemy*>(this->entity) != nullptr)
	{
		dynamic_cast<PlatformerEnemy*>(this->entity)->setDropPool("");
	}
}

void EnemyBattleAllyBehavior::onDisable()
{
	super::onDisable();
}
