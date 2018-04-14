#ifndef ENTITYREFINSTANCE_H
#define ENTITYREFINSTANCE_H

#include "objectrefinstance.h"

namespace SpriterEngine
{

	class EntityInstanceData;
	class AnimationInstance;

	class EntityRefInstance : public ObjectRefInstance
	{
	public:
		EntityRefInstance(UniversalObjectInterface *initialResultObject, 
			TransformProcessor *initialParentTransformer,
			TimelineKey *initialKey,			
			EntityInstanceData *initialEntity,
			AnimationInstance *initialAnimation);

		void preProcess() override;
		void process(real currentTime) override;

	private:
		EntityInstanceData *entity;
		AnimationInstance *animation;
	};

}

#endif // ENTITYREFINSTANCE_H
