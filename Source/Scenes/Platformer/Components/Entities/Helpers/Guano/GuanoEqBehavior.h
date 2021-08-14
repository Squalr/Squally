#pragma once

#include "Engine/Components/GameComponent.h"

class Guano;

class GuanoEqBehavior : public GameComponent
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
	typedef GameComponent super;

	Guano* guano = nullptr;
};
