#pragma once

#include "Engine/Components/Component.h"

class IOUDrop;

class FirstIOUFound : public Component
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
	typedef Component super;

	IOUDrop* iou;
};
