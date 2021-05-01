#pragma once

#include "Engine/Components/Component.h"

class Guano;

class GuanoHealthBehavior : public Component
{
public:
	static GuanoHealthBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoHealthBehavior(GameObject* owner);
	virtual ~GuanoHealthBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;
	
	void saveState();

	Guano* guano;
};
