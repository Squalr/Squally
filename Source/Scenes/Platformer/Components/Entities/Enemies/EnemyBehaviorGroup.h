#pragma once

#include "Engine/Components/GameComponentGroup.h"

class EnemyBehaviorGroup : public GameComponentGroup
{
public:
	static EnemyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EnemyBehaviorGroup(GameObject* owner);
	virtual ~EnemyBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
