#pragma once

#include "Engine/Components/GameComponentGroup.h"

class SquallyCollisionBehaviorGroup : public GameComponentGroup
{
public:
	static SquallyCollisionBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyCollisionBehaviorGroup(GameObject* owner);
	virtual ~SquallyCollisionBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
