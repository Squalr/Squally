#pragma once
#include "Engine/UI/HUD/hud.h"

namespace cocos2d
{
	class EventListener;
}

class GlobalHud : public Hud
{
public:
	virtual ~GlobalHud() = default;

	void pause() override;
	virtual void addGlobalEventListener(cocos2d::EventListener* listener);
private:
	typedef Hud super;
};
