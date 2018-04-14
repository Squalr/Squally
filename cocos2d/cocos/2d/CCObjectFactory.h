#ifndef CCOBJECTFACTORY_H
#define CCOBJECTFACTORY_H

#include "2d/CCNode.h"
#include "SpriterPlusPlus/spriterengine/override/spriterobjectfactory.h"
#include "CCPointInstanceInfo.h"
#include "CCBoxInstanceInfo.h"
#include "CCBoneInstanceInfo.h"
#include "CCTriggerobjectInfo.h"

NS_CC_BEGIN

	class CC_DLL CCObjectFactory : public SpriterEngine::ObjectFactory
	{
	public:
		CCObjectFactory(cocos2d::Node* parent);
		
		SpriterEngine::PointInstanceInfo *newPointInstanceInfo() override;

		SpriterEngine::BoxInstanceInfo *newBoxInstanceInfo(SpriterEngine::point size) override;

		SpriterEngine::BoneInstanceInfo *newBoneInstanceInfo(SpriterEngine::point size) override;

		SpriterEngine::TriggerObjectInfo *newTriggerObjectInfo(std::string triggerName) override;
	private:
		cocos2d::Node* parent;
	};

NS_CC_END

#endif // CCOBJECTFACTORY_H
