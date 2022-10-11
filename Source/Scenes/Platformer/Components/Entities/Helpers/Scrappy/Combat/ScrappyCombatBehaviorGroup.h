#pragma once

#include "Engine/Components/GameComponentGroup.h"

class ScrappyCombatBehaviorGroup : public GameComponentGroup
{
public:
	static ScrappyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ScrappyCombatBehaviorGroup(GameObject* owner);
	virtual ~ScrappyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
