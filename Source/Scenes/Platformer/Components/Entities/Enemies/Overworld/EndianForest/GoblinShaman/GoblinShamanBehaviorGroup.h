#pragma once

#include "Engine/Components/GameComponentGroup.h"

class GoblinShamanBehaviorGroup : public GameComponentGroup
{
public:
	static GoblinShamanBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GoblinShamanBehaviorGroup(GameObject* owner);
	virtual ~GoblinShamanBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
