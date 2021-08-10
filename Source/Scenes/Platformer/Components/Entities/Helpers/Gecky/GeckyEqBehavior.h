#pragma once

#include "Engine/Components/GameComponent.h"

class Gecky;

class GeckyEqBehavior : public GameComponent
{
public:
	static GeckyEqBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyEqBehavior(GameObject* owner);
	virtual ~GeckyEqBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	Gecky* guano;
};
