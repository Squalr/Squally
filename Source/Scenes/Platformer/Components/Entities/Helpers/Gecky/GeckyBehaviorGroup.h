#pragma once

#include "Engine/Components/GameComponentGroup.h"

class GeckyBehaviorGroup : public GameComponentGroup
{
public:
	static GeckyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyBehaviorGroup(GameObject* owner);
	virtual ~GeckyBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
