#pragma once

#include "Engine/Components/GameComponentGroup.h"

class ScrappyBehaviorGroup : public GameComponentGroup
{
public:
	static ScrappyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	ScrappyBehaviorGroup(GameObject* owner);
	virtual ~ScrappyBehaviorGroup();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponentGroup super;
};
