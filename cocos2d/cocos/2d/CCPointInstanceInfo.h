#ifndef CCPOINTINSTANCEINFO_H
#define CCPOINTINSTANCEINFO_H

#include "2d/CCNode.h"
#include "SpriterPlusPlus/spriterengine/objectinfo/pointinstanceinfo.h"

NS_CC_BEGIN

	class CC_DLL CCPointInstanceInfo : public SpriterEngine::PointInstanceInfo
	{
	public:
		CCPointInstanceInfo(cocos2d::Node* parent);

		void render() override;

	private:
        cocos2d::Node* parent;

	};

NS_CC_END

#endif // CCPOINTINSTANCEINFO_H
