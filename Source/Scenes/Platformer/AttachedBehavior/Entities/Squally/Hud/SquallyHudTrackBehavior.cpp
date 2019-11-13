#include "SquallyHudTrackBehavior.h"

#include "cocos/math/CCGeometry.h"

#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/Squally/Squally.h"

using namespace cocos2d;

const std::string SquallyHudTrackBehavior::MapKeyAttachedBehavior = "squally-hud-track";

SquallyHudTrackBehavior* SquallyHudTrackBehavior::create(GameObject* owner)
{
	SquallyHudTrackBehavior* instance = new SquallyHudTrackBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyHudTrackBehavior::SquallyHudTrackBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyHudTrackBehavior::~SquallyHudTrackBehavior()
{
}

void SquallyHudTrackBehavior::onLoad()
{
	// Request camera & hud track player
	PlatformerEvents::TriggerHudTrackEntity(PlatformerEvents::HudTrackEntityArgs(this->squally));
}
