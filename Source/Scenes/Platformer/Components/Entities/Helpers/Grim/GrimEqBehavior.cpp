#include "GrimEqBehavior.h"

#include "Entities/Platformer/Helpers/CastleValgrind/Grim.h"
#include "Scenes/Platformer/Components/Entities/Stats/EntityEqBehavior.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string GrimEqBehavior::MapKey = "grim-eq";
const int GrimEqBehavior::DefaultLevel = 8;

GrimEqBehavior* GrimEqBehavior::create(GameObject* owner)
{
	GrimEqBehavior* instance = new GrimEqBehavior(owner);

	instance->autorelease();

	return instance;
}

GrimEqBehavior::GrimEqBehavior(GameObject* owner) : super(owner)
{
	this->grim = dynamic_cast<Grim*>(owner);

	if (this->grim == nullptr)
	{
		this->invalidate();
	}
}

GrimEqBehavior::~GrimEqBehavior()
{
}

void GrimEqBehavior::onLoad()
{
	this->grim->watchForComponent<EntityEqBehavior>([=](EntityEqBehavior* entityEqBehavior)
	{
		entityEqBehavior->load(SaveKeys::SaveKeyGrimEq, SaveKeys::SaveKeyGrimEqExperience, GrimEqBehavior::DefaultLevel);
	});
}

void GrimEqBehavior::onDisable()
{
	super::onDisable();
}
