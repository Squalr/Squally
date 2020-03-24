#pragma once
#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class EventListener;
}

class GlobalHud : public Hud
{
public:
	static GlobalHud* create();

	GlobalHud();
	virtual ~GlobalHud();

	void pause() override;

private:
	typedef Hud super;
};
