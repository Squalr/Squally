#pragma once

#include "Engine/Components/ComponentGroup.h"

class GuanoBehaviorGroup : public ComponentGroup
{
public:
	static GuanoBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoBehaviorGroup(GameObject* owner);
	virtual ~GuanoBehaviorGroup();

	void onLoad() override;

private:
	typedef ComponentGroup super;
};
