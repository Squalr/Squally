#pragma once

#include "Engine/Components/Component.h"

class Guano;

class GuanoEqBehavior : public Component
{
public:
	static GuanoEqBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoEqBehavior(GameObject* owner);
	virtual ~GuanoEqBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	Guano* guano;
};
