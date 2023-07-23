#pragma once

#include "Engine/Hackables/Menus/HackablePreview.h"

class DazeGenericPreview : public HackablePreview
{
public:
	static DazeGenericPreview* create();

	HackablePreview* clone() override;

protected:
	DazeGenericPreview();
	virtual ~DazeGenericPreview();

	void onEnter() override;
	void initializePositions() override;

private:
	typedef HackablePreview super;
};
