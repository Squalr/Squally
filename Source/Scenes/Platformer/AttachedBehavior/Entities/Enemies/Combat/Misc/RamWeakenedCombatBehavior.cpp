#include "RamWeakenedCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Quests/QuestTask.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Quests/EndianForest/SaveTown/RepairRam.h"
#include "Scenes/Platformer/Quests/EndianForest/SaveTown/SaveTownLine.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string RamWeakenedCombatBehavior::MapKey = "ram-weakened";

RamWeakenedCombatBehavior* RamWeakenedCombatBehavior::create(GameObject* owner)
{
	RamWeakenedCombatBehavior* instance = new RamWeakenedCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

RamWeakenedCombatBehavior::RamWeakenedCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->saveTownLine = SaveTownLine::create();

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->addChild(this->saveTownLine);
}

RamWeakenedCombatBehavior::~RamWeakenedCombatBehavior()
{
}

void RamWeakenedCombatBehavior::initializePositions()
{
}

void RamWeakenedCombatBehavior::onLoad()
{
	super::onLoad();
	
	if (QuestTask::getQuestStateForTask(this->saveTownLine, RepairRam::MapKeyQuest) == QuestTask::QuestState::Complete)
	{
		this->entity->watchForAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
		{
			healthBehavior->setHealth(healthBehavior->getMaxHealth() / 2);
		});
	}
}
