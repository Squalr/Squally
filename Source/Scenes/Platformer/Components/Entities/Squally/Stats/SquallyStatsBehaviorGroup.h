#pragma once

#include "Engine/Components/ComponentGroup.h"

class SquallyStatsBehaviorGroup : public ComponentGroup
{
public:
	static SquallyStatsBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyStatsBehaviorGroup(GameObject* owner);
	virtual ~SquallyStatsBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
