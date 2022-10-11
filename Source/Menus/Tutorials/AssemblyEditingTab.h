#pragma once

#include "Menus/Tutorials/TutorialTabBase.h"

class AssemblyEditingTab : public TutorialTabBase
{
public:
	static AssemblyEditingTab* create();

protected:
	AssemblyEditingTab();
	virtual ~AssemblyEditingTab();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef TutorialTabBase super;
};
