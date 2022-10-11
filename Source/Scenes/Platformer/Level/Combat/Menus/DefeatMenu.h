#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;
class Sound;

class DefeatMenu : public SmartNode
{
public:
	static DefeatMenu* create();
	
	void show();

protected:
	DefeatMenu();
	virtual ~DefeatMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	cocos2d::Sprite* defeatBanner = nullptr;
	LocalizedLabel* defeatLabel = nullptr;
	ClickableTextNode* returnButton = nullptr;
	Sound* defeatSound = nullptr;
};
