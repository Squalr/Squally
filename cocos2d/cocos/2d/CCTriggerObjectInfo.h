#ifndef CCTRIGGEROBJECTINFO_H
#define CCTRIGGEROBJECTINFO_H

#include "2d/CCNode.h"
#include "base/CCConsole.h"
#include "SpriterPlusPlus/spriterengine/objectinfo/triggerobjectinfo.h"

NS_CC_BEGIN

	class CC_DLL CCTriggerObjectInfo : public SpriterEngine::TriggerObjectInfo
	{
	public:
		CCTriggerObjectInfo(const std::string& name);

		void playTrigger() override;

	private:
        const std::string name;
	};

NS_CC_END

#endif // CCTRIGGEROBJECTINFO_H
