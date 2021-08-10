#pragma once

#include "Engine/Components/GameComponentGroup.h"

class SnowmanBehaviorGroup : public GameComponentGroup
{
public:
	static SnowmanBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SnowmanBehaviorGroup(GameObject* owner);
	virtual ~SnowmanBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponentGroup super;
};
