#pragma once

#include "Engine/Components/GameComponentGroup.h"

class GuanoPetrifiedBehaviorGroup : public GameComponentGroup
{
public:
	static GuanoPetrifiedBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoPetrifiedBehaviorGroup(GameObject* owner);
	virtual ~GuanoPetrifiedBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
