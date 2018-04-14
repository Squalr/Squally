#ifndef CCBONEINSTANCEINFO_H
#define CCBONEINSTANCEINFO_H

#include "2d/CCNode.h"
#include "SpriterPlusPlus/spriterengine/objectinfo/boneinstanceinfo.h"

NS_CC_BEGIN

	class CC_DLL CCBoneInstanceInfo : public SpriterEngine::BoneInstanceInfo
	{
	public:
		CCBoneInstanceInfo(SpriterEngine::point initialSize, cocos2d::Node* parent);

		void render() override;
	};

NS_CC_END

#endif // CCBONEINSTANCEINFO_H
