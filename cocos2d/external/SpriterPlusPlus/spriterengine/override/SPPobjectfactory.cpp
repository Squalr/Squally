#include "SPPobjectfactory.h"

#include "../objectinfo/pointinstanceinfo.h"
#include "../objectinfo/boneinstanceinfo.h"
#include "../objectinfo/boxinstanceinfo.h"
#include "../objectinfo/triggerobjectinfo.h"
#include "../objectinfo/spriteobjectinfo.h"

namespace SpriterEngine
{

	ObjectFactory::ObjectFactory()
	{
	}

	PointInstanceInfo * ObjectFactory::newPointInstanceInfo()
	{
		return new PointInstanceInfo();
	}

	BoneInstanceInfo * ObjectFactory::newBoneInstanceInfo(point size)
	{
		return new BoneInstanceInfo(size);
	}

	BoxInstanceInfo * ObjectFactory::newBoxInstanceInfo(point size)
	{
		return new BoxInstanceInfo(size);
	}

	TriggerObjectInfo * ObjectFactory::newTriggerObjectInfo(std::string newTriggerName)
	{
		return new TriggerObjectInfo();
	}

	SpriteObjectInfo *ObjectFactory::newSpriteObjectinfo()
	{
		return new SpriteObjectInfo();
	}
}