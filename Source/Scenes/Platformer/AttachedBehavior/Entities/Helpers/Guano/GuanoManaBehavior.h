#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Guano;

class GuanoManaBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;
	
	void saveState();

	Guano* guano;
};
