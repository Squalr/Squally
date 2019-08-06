#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEnemy;
class Squally;

class SquallyEquipmentVisuals : public AttachedBehavior
{
public:
	static SquallyEquipmentVisuals* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyEquipmentVisuals(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyEquipmentVisuals();

	void onLoad() override;

private:
	typedef AttachedBehavior super;
	
	void updateEquipmentVisual();

	Squally* squally;
};
