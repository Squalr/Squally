#pragma once

#include "Engine/Components/Component.h"

class Gecky;

class GeckyHealthBehavior : public Component
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
	typedef Component super;
	
	void saveState();

	Gecky* guano;
};
