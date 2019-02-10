#pragma once
#include "Engine/SmartNode.h"

namespace cocos2d
{
	class EventListener;
}

class GlobalNode : public SmartNode
{
public:
	static GlobalNode* create();

	GlobalNode();
	virtual ~GlobalNode();

	void pause() override;
	virtual void addGlobalEventListener(cocos2d::EventListener* listener);
private:
	typedef SmartNode super;
};
