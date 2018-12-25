#pragma once

#include "Engine/UI/Controls/MenuSprite.h"

class HackButton : public MenuSprite
{
public:
	static HackButton* create();

protected:
	virtual void addEventListener(cocos2d::EventListener* listener) override;

private:
	HackButton();
	~HackButton();
};
