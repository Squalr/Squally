#include "spriterefinstance.h"

#include "../objectinfo/universalobjectinterface.h"
#include "../file/filereference.h"
#include "../override/imagefile.h"

namespace SpriterEngine
{

	SpriteRefInstance::SpriteRefInstance(UniversalObjectInterface *initialResultObject,
		TransformProcessor *initialParentTransformer,
		TimelineKey *initialKey,
		FileReference *initialImageRef,
		bool initialUseDefaultPivotPoint) :
		ObjectRefInstance(initialResultObject, initialParentTransformer, initialKey),
		imageRef(initialImageRef),
		useDefaultPivot(initialUseDefaultPivotPoint)
	{
	}

	void SpriteRefInstance::preProcess()
	{
		resultObject()->setImage(imageRef->image());
		if (useDefaultPivot && imageRef->image())
		{
			resultObject()->setPivot(imageRef->image()->defaultPivot);
		}
	}

	void SpriteRefInstance::process(real currentTime)
	{
		preProcess();
		ObjectRefInstance::process(currentTime);	
	}

}
