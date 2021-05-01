#pragma once

#include "Engine/Components/ComponentGroup.h"

class ScrappyBehaviorGroup : public ComponentGroup
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
	typedef ComponentGroup super;
};
