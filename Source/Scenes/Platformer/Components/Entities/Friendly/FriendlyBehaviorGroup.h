#pragma once

#include "Engine/Components/ComponentGroup.h"

class FriendlyBehaviorGroup : public ComponentGroup
{
public:
	static FriendlyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FriendlyBehaviorGroup(GameObject* owner);
	virtual ~FriendlyBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
