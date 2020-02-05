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

protected:
	FirstStrikeMenu();
	virtual ~FirstStrikeMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Hud super;

	cocos2d::Sprite* background;
	LocalizedLabel* firstStrikeLabel;
	Sound* sfx;
};
