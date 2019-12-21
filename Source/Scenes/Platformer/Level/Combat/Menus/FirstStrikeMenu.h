#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Sprite;
}

class LocalizedLabel;
class Sound;

class FirstStrikeMenu : public Hud
{
public:
	static FirstStrikeMenu* create();

	void show(bool playerFirstStrike);

private:
	typedef Hud super;
	FirstStrikeMenu();
	~FirstStrikeMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

	cocos2d::Sprite* background;
	LocalizedLabel* firstStrikeLabel;
	Sound* sfx;
};
