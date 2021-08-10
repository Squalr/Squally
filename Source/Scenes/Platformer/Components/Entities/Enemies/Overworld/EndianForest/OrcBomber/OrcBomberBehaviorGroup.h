#pragma once

#include "Engine/Components/GameComponentGroup.h"

class OrcBomberBehaviorGroup : public GameComponentGroup
{
public:
	static OrcBomberBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	OrcBomberBehaviorGroup(GameObject* owner);
	virtual ~OrcBomberBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
