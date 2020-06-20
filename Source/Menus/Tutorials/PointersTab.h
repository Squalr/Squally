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
