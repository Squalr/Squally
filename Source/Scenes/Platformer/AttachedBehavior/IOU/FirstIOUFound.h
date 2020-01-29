#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class IOUDrop;

class FirstIOUFound : public AttachedBehavior
{
public:
	static FirstIOUFound* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	FirstIOUFound(GameObject* owner);
	~FirstIOUFound();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	IOUDrop* iou;
};
