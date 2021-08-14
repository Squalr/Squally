#pragma once

#include "Engine/Components/GameComponent.h"

class Gecky;

class GeckyHealthBehavior : public GameComponent
{
public:
	static GeckyHealthBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyHealthBehavior(GameObject* owner);
	virtual ~GeckyHealthBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;
	
	void saveState();

	Gecky* gecky = nullptr;
};
