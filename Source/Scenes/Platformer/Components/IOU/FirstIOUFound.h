#pragma once

#include "Engine/Components/GameComponent.h"

class IOUDrop;

class FirstIOUFound : public GameComponent
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
	typedef GameComponent super;

	IOUDrop* iou;
};
