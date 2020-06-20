#pragma once

#include "Menus/Tutorials/TutorialTabBase.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class LocalizedLabel;
class PlatformerEntity;
class ScrollPane;
class TutorialEntry;

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
