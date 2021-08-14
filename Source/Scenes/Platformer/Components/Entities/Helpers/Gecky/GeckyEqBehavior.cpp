#include "GeckyEqBehavior.h"

#include "Entities/Platformer/Helpers/DataMines/Gecky.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityEqBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string GeckyEqBehavior::MapKey = "gecky-eq";

GeckyEqBehavior* GeckyEqBehavior::create(GameObject* owner)
{
	GeckyEqBehavior* instance = new GeckyEqBehavior(owner);

	instance->autorelease();

	return instance;
}

GeckyEqBehavior::GeckyEqBehavior(GameObject* owner) : super(owner)
{
	this->gecky = dynamic_cast<Gecky*>(owner);

	if (this->gecky == nullptr)
	{
		this->invalidate();
	}
}

GeckyEqBehavior::~GeckyEqBehavior()
{
}

void GeckyEqBehavior::onLoad()
{
	this->gecky->watchForComponent<EntityEqBehavior>([=](EntityEqBehavior* entityEqBehavior)
	{
		entityEqBehavior->load(SaveKeys::SaveKeyGeckyEq, SaveKeys::SaveKeyGeckyEqExperience);
	});
}

void GeckyEqBehavior::onDisable()
{
	super::onDisable();
}
