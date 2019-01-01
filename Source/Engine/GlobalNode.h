#pragma once
#include "Engine/SmartNode.h"

namespace cocos2d
{
	class EventListener;
}

class GlobalNode : public SmartNode
{
public:
	virtual ~GlobalNode() = default;

	virtual void pause() override;
	virtual void addGlobalEventListener(cocos2d::EventListener* listener);
private:
	typedef SmartNode super;
};
