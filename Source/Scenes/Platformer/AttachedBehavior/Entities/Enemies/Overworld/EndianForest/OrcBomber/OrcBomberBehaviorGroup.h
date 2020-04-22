#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

class OrcBomberBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static OrcBomberBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	OrcBomberBehaviorGroup(GameObject* owner);
	virtual ~OrcBomberBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
