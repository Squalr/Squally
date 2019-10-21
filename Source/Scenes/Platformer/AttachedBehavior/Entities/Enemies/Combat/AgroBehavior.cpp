#include "AgroBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string AgroBehavior::MapKeyAttachedBehavior = "agro";
const float AgroBehavior::AgroRangeX = 640.0f;
const float AgroBehavior::AgroRangeY = 512.0f;

AgroBehavior* AgroBehavior::create(GameObject* owner)
{
	AgroBehavior* instance = new AgroBehavior(owner);

	instance->autorelease();

	return instance;
}

AgroBehavior::AgroBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->squally = nullptr;
}

AgroBehavior::~AgroBehavior()
{
}

void AgroBehavior::onLoad()
{
	ObjectEvents::watchForObject<Squally>(this, [=](Squally* squally)
	{
		this->squally = squally;
	});
}

void AgroBehavior::update(float dt)
{
	super::update(dt);

	if (this->squally == nullptr || this->entity == nullptr)
	{
		return;
	}

	Vec2 squallyPosition = GameUtils::getWorldCoords(this->squally);
	Vec2 entityPosition = GameUtils::getWorldCoords(this->entity);

	if (std::abs(squallyPosition.x - entityPosition.x) <= AgroBehavior::AgroRangeX &&
		std::abs(squallyPosition.y - entityPosition.y) <= AgroBehavior::AgroRangeY)
	{
		this->entity->setState(StateKeys::CinematicDestinationX, Value(squallyPosition.x));
	}
}
