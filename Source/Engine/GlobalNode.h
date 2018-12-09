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
	virtual void addEventListener(cocos2d::EventListener* listener) override;
};
