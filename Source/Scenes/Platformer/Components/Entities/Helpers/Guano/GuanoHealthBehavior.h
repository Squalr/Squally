#pragma once

#include "Engine/Components/GameComponent.h"

class Guano;

class GuanoHealthBehavior : public GameComponent
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
	typedef GameComponent super;
	
	void saveState();

	Guano* guano = nullptr;
};
