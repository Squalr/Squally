#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;
class ScrollPane;

class HomeTab : public SmartNode
{
public:
	static HomeTab* create();

protected:
	HomeTab();
	virtual ~HomeTab();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef SmartNode super;
	
	LocalizedLabel* disclaimer;
};
