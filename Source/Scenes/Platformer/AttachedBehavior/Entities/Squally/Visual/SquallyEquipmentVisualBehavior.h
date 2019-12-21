#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyEquipmentVisualBehavior : public AttachedBehavior
{
public:
	static SquallyEquipmentVisualBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyEquipmentVisualBehavior(GameObject* owner);
	~SquallyEquipmentVisualBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	void updateEquipmentVisual();

	Squally* squally;
};
