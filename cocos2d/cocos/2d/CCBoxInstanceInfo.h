#ifndef CCBOXINSTANCEINFO_H
#define CCBOXINSTANCEINFO_H

#include "2d/CCNode.h"
#include "SpriterPlusPlus/spriterengine/objectinfo/boxinstanceinfo.h"

NS_CC_BEGIN

	class CC_DLL CCBoxInstanceInfo : public SpriterEngine::BoxInstanceInfo
	{
	public:
		CCBoxInstanceInfo(SpriterEngine::point initialSize);

		void render() override;
	};

NS_CC_END

#endif // SFMLBOXINSTANCEINFO_H
