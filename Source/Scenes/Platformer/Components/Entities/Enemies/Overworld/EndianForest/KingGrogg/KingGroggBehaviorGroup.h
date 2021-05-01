#pragma once

#include "Engine/Components/ComponentGroup.h"

class KingGroggBehaviorGroup : public ComponentGroup
{
public:
	static KingGroggBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	KingGroggBehaviorGroup(GameObject* owner);
	virtual ~KingGroggBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
