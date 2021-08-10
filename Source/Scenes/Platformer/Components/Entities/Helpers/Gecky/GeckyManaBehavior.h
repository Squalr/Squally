#pragma once

#include "Engine/Components/GameComponent.h"

class Gecky;

class GeckyManaBehavior : public GameComponent
{
public:
	static GeckyManaBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyManaBehavior(GameObject* owner);
	virtual ~GeckyManaBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;
	
	void saveState();

	Gecky* guano;
};
