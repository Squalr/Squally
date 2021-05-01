#pragma once

#include "Engine/Components/Component.h"

class Gecky;

class GeckyManaBehavior : public Component
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
	typedef Component super;
	
	void saveState();

	Gecky* guano;
};
