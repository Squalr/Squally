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

	virtual void pause() override;
	
private:
	typedef SmartNode super;
};
