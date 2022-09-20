#pragma once

#include "Engine/Components/GameComponentGroup.h"

class RepairableBehaviorGroup : public GameComponentGroup
{
public:
	static RepairableBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	RepairableBehaviorGroup(GameObject* owner);
	virtual ~RepairableBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
