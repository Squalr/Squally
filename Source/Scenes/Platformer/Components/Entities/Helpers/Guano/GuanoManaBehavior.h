#pragma once

#include "Engine/Components/GameComponent.h"

class Guano;

class GuanoManaBehavior : public GameComponent
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
	typedef GameComponent super;
	
	void saveState();

	Guano* guano;
};
