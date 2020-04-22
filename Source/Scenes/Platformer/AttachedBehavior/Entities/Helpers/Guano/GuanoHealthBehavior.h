#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Guano;

class GuanoHealthBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;
	
	void saveState();

	Guano* guano;
};
