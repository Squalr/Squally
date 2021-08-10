#pragma once

#include "Engine/Components/GameComponentGroup.h"

class Squally;

class SquallyAbilityBehaviorGroup : public GameComponentGroup
{
public:
	static SquallyAbilityBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyAbilityBehaviorGroup(GameObject* owner);
	virtual ~SquallyAbilityBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
