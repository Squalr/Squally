#pragma once

#include "Engine/Components/GameComponentGroup.h"

class SquallyBehaviorGroup : public GameComponentGroup
{
public:
	static SquallyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyBehaviorGroup(GameObject* owner);
	virtual ~SquallyBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
