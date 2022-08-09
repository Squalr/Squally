#pragma once

#include "Engine/Components/GameComponentGroup.h"

class KillingMachineBehaviorGroup : public GameComponentGroup
{
public:
	static KillingMachineBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	KillingMachineBehaviorGroup(GameObject* owner);
	virtual ~KillingMachineBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
