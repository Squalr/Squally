#pragma once

#include "Engine/Input/ClickableNode.h"

class HackButton : public ClickableNode
{
public:
	static HackButton* create();

protected:
	void initializeListeners() override;
	virtual void addEventListener(cocos2d::EventListener* listener) override;

private:
	typedef ClickableNode super;
	HackButton();
	~HackButton();
};
