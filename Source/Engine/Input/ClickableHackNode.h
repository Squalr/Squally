#pragma once

#include "Engine/Input/ClickableNode.h"

class ClickableHackNode : public ClickableNode
{
public:
	static ClickableHackNode* create(std::string resource, std::string resourceSelected);

protected:
	ClickableHackNode(std::string resource, std::string resourceSelected);
	virtual ~ClickableHackNode();
	
	void initializeListeners() override;
	virtual void addEventListener(cocos2d::EventListenerCustom* listener) override;

private:
	typedef ClickableNode super;
};
