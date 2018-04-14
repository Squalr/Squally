#include "CCObjectFactory.h"

NS_CC_BEGIN

	CCObjectFactory::CCObjectFactory(cocos2d::Node* parent) : parent(parent)
	{
	}

	SpriterEngine::PointInstanceInfo* CCObjectFactory::newPointInstanceInfo()
	{
		return new CCPointInstanceInfo(parent);
	}

	SpriterEngine::BoxInstanceInfo* CCObjectFactory::newBoxInstanceInfo(SpriterEngine::point size)
	{
		return new CCBoxInstanceInfo(size);
	}

	SpriterEngine::BoneInstanceInfo* CCObjectFactory::newBoneInstanceInfo(SpriterEngine::point size)
	{
		return new CCBoneInstanceInfo(size, parent);
	}

	SpriterEngine::TriggerObjectInfo *CCObjectFactory::newTriggerObjectInfo(std::string triggerName) {
		return new CCTriggerObjectInfo(triggerName);
	}
	
NS_CC_END
