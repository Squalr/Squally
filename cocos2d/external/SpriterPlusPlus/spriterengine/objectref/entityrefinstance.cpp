#include "entityrefinstance.h"

#include "../entity/entityinstance.h"

#include "../animation/animationinstance.h"

namespace SpriterEngine
{

	EntityRefInstance::EntityRefInstance(UniversalObjectInterface *initialResultObject,
		TransformProcessor *initialParentTransformer,
		TimelineKey *initialKey,
		EntityInstanceData *initialEntity,
		AnimationInstance *initialAnimation) :
		ObjectRefInstance(initialResultObject, initialParentTransformer, initialKey),
		entity(initialEntity),
		animation(initialAnimation)
	{
	}

	void EntityRefInstance::preProcess()
	{
		resultObject()->setCurrentEntity(entity);
		resultObject()->setCurrentAnimation(animation);
	}

	void EntityRefInstance::process(real currentTime)
	{
		preProcess();
		ObjectRefInstance::process(currentTime);
		resultObject()->reprocessCurrentTime();
	}

}
