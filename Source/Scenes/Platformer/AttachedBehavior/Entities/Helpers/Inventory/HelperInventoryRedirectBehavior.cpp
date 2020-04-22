#include "HelperInventoryRedirectBehavior.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string HelperInventoryRedirectBehavior::MapKey = "helper-inventory-redirect";

HelperInventoryRedirectBehavior* HelperInventoryRedirectBehavior::create(GameObject* owner)
{
	HelperInventoryRedirectBehavior* instance = new HelperInventoryRedirectBehavior(owner);

	instance->autorelease();

	return instance;
}

HelperInventoryRedirectBehavior::HelperInventoryRedirectBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

HelperInventoryRedirectBehavior::~HelperInventoryRedirectBehavior()
{
}

void HelperInventoryRedirectBehavior::onLoad()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		squally->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* squallyInventoryBehavior)
		{
			this->entity->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
			{
				entityInventoryBehavior->redirectInventoryTo(squallyInventoryBehavior->getInventory());
			});
		});
	}, Squally::MapKey);
}

void HelperInventoryRedirectBehavior::onDisable()
{
	super::onDisable();
}
