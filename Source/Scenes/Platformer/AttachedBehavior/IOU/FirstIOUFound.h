#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class IOUDrop;

class FirstIOUFound : public AttachedBehavior
{
public:
	static FirstIOUFound* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FirstIOUFound(GameObject* owner);
	virtual ~FirstIOUFound();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	IOUDrop* iou;
};
