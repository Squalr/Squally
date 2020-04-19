#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Guano;

class GuanoEqBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	Guano* guano;
};
