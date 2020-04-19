#include "GuanoEqBehavior.h"

#include "Entities/Platformer/Helpers/EndianForest/Guano.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityEqBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string GuanoEqBehavior::MapKey = "guano-eq";

GuanoEqBehavior* GuanoEqBehavior::create(GameObject* owner)
{
	GuanoEqBehavior* instance = new GuanoEqBehavior(owner);

	instance->autorelease();

	return instance;
}

GuanoEqBehavior::GuanoEqBehavior(GameObject* owner) : super(owner)
{
	this->guano = dynamic_cast<Guano*>(owner);

	if (this->guano == nullptr)
	{
		this->invalidate();
	}
}

GuanoEqBehavior::~GuanoEqBehavior()
{
}

void GuanoEqBehavior::onLoad()
{
	this->guano->watchForAttachedBehavior<EntityEqBehavior>([=](EntityEqBehavior* entityEqBehavior)
	{
		entityEqBehavior->load(SaveKeys::SaveKeyGuanoEq, SaveKeys::SaveKeyGuanoEqExperience);
	});
}

void GuanoEqBehavior::onDisable()
{
	super::onDisable();
}
