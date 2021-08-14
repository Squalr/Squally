#pragma once
#include "Engine/UI/HUD/Hud.h"

class GlobalHud : public Hud
{
public:
	static GlobalHud* create();

protected:
	GlobalHud();
	virtual ~GlobalHud();
	
	void pause() override;

private:
	typedef Hud super;
};
