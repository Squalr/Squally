#pragma once

#include "Engine/Components/GameComponentGroup.h"

class SquallyVisualBehaviorGroup : public GameComponentGroup
{
public:
	static SquallyVisualBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyVisualBehaviorGroup(GameObject* owner);
	virtual ~SquallyVisualBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponentGroup super;
};
