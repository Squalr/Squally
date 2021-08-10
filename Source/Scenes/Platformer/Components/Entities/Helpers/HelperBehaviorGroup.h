#pragma once

#include "Engine/Components/GameComponentGroup.h"

class HelperBehaviorGroup : public GameComponentGroup
{
public:
	static HelperBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	HelperBehaviorGroup(GameObject* owner);
	virtual ~HelperBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponentGroup super;
};
