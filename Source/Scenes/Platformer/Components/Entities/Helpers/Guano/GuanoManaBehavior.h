#pragma once

#include "Engine/Components/Component.h"

class Guano;

class GuanoManaBehavior : public Component
{
public:
	static GuanoManaBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoManaBehavior(GameObject* owner);
	virtual ~GuanoManaBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;
	
	void saveState();

	Guano* guano;
};
