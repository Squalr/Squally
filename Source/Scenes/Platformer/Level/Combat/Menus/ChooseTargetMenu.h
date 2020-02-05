#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;

class ChooseTargetMenu : public Hud
{
public:
	static ChooseTargetMenu* create();

	void show(bool playerFirstStrike);

protected:
	ChooseTargetMenu();
	virtual ~ChooseTargetMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Hud super;

	cocos2d::Sprite* background;
	cocos2d::Node* iconPreviewNode;
	LocalizedLabel* firstStrikeLabel;
};
