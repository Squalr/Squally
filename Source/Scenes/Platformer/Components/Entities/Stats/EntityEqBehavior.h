#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class EntityEqBehavior : public Component
{
public:
	static EntityEqBehavior* create(GameObject* owner);

	void load(std::string saveKeyEq, std::string saveKeyExp);
	void setEq(int eq);
	int getEq();
	bool setEqExperience(int eqExperience);
	bool addEqExperience(int eqExperience);
	int getEqExperience();
	
	static const int DefaultEq;

protected:
	EntityEqBehavior(GameObject* owner);
	virtual ~EntityEqBehavior();

	void onLoad() override;
	void onDisable() override;

	PlatformerEntity* entity;

private:
	typedef Component super;

	void save();

	std::string saveKeyEq;
	std::string saveKeyExp;
};
