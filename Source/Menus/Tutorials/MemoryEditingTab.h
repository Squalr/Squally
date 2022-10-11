#pragma once

#include "Menus/Tutorials/TutorialTabBase.h"

class PlatformerEntity;
class TutorialEntry;

class MemoryEditingTab : public TutorialTabBase
{
public:
	static MemoryEditingTab* create();

protected:
	MemoryEditingTab();
	virtual ~MemoryEditingTab();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef TutorialTabBase super;

	void loadKnownValueIntTutorial();
	void loadKnownValueFloatTutorial();
	void loadUnknownValueIntTutorial();
	void loadUnknownValueFloatTutorial();
	void loadKnownValueDoubleTutorial();
	void loadUnknownValueFloatTutorialAdvanced();

	TutorialEntry* knownValueInt = nullptr;
	TutorialEntry* knownValueFloat = nullptr;
	TutorialEntry* unknownValueInt = nullptr;
	TutorialEntry* unknownValueFloat = nullptr;
	TutorialEntry* knownValueDouble = nullptr;
	TutorialEntry* unknownValueFloatAdvanced = nullptr;
	
	PlatformerEntity* kingZul = nullptr;
	PlatformerEntity* agnes = nullptr;
	PlatformerEntity* lazarus = nullptr;
	PlatformerEntity* asmodeus = nullptr;
	PlatformerEntity* cryogen = nullptr;
	PlatformerEntity* krampus = nullptr;
};
