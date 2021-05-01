#pragma once

#include "Engine/Components/ComponentGroup.h"

class SnowmanBehaviorGroup : public ComponentGroup
{
public:
	static SnowmanBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SnowmanBehaviorGroup(GameObject* owner);
	virtual ~SnowmanBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef ComponentGroup super;
};
