#pragma once

#include "Engine/Components/ComponentGroup.h"

class OrcBomberBehaviorGroup : public ComponentGroup
{
public:
	static OrcBomberBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	OrcBomberBehaviorGroup(GameObject* owner);
	virtual ~OrcBomberBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
