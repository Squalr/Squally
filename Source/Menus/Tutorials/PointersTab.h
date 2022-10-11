#pragma once

#include "Menus/Tutorials/TutorialTabBase.h"

class PointersTab : public TutorialTabBase
{
public:
	static PointersTab* create();

protected:
	PointersTab();
	virtual ~PointersTab();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef TutorialTabBase super;
};
