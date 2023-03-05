#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class ZombieGraspGenericPreview : public HackablePreview
{
public:
	static ZombieGraspGenericPreview* create();

	HackablePreview* clone() override;

protected:
	ZombieGraspGenericPreview();
	virtual ~ZombieGraspGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
