#ifndef OBJECTREFINSTANCE_H
#define OBJECTREFINSTANCE_H

#include "../global/global.h"

namespace SpriterEngine
{

	class EntityInstance;
	class UniversalObjectInterface;
	class TransformProcessor;
	class TimelineKey;

	class ObjectRefInstance
	{
	public:
		ObjectRefInstance(UniversalObjectInterface *initialResultObject,
			TransformProcessor *initialParentTransformer,
			TimelineKey *initialKey);
		virtual ~ObjectRefInstance() {}

		virtual void preProcess();
		virtual void process(real currentTime);

		void processKey(real currentTime);
		void blendKey(real currentTime, real blendRatio);
		virtual void processTransform();

	protected:
		UniversalObjectInterface *resultObject() const;

	private:
		UniversalObjectInterface *resultObjectInterface;
		TransformProcessor *parentTransformer;
		TimelineKey *key;
	};

}

#endif // OBJECTREFINSTANCE_H
