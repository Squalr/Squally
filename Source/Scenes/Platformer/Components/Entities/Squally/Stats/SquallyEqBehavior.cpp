#include "SquallyEqBehavior.h"

#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityEqBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string SquallyEqBehavior::MapKey = "squally-eq";

SquallyEqBehavior* SquallyEqBehavior::create(GameObject* owner)
{
	SquallyEqBehavior* instance = new SquallyEqBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyEqBehavior::SquallyEqBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyEqBehavior::~SquallyEqBehavior()
{
}

void SquallyEqBehavior::onLoad()
{
	this->squally->watchForComponent<EntityEqBehavior>([=](EntityEqBehavior* entityEqBehavior)
	{
		entityEqBehavior->load(SaveKeys::SaveKeySquallyEq, SaveKeys::SaveKeySquallyEqExperience);
	});
}

void SquallyEqBehavior::onDisable()
{
	super::onDisable();
}
