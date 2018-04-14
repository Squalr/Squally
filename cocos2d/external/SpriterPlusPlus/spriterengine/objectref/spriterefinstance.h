#ifndef SPRITEREFINSTANCE_H
#define SPRITEREFINSTANCE_H

#include "objectrefinstance.h"

namespace SpriterEngine
{

	class FileReference;

	class SpriteRefInstance : public ObjectRefInstance
	{
	public:
		SpriteRefInstance(UniversalObjectInterface *initialResultObject,
			TransformProcessor *initialParentTransformer,
			TimelineKey *initialKey,
			FileReference *initialImageRef,
			bool initialUseDefaultPivotPoint);

		void preProcess() override;
		void process(real currentTime) override;

	private:
		FileReference *imageRef;
		bool useDefaultPivot;
	};

}

#endif // SPRITEREFINSTANCE_H
