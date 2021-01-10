#include "CursorSets.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Input/Input.h"
#include "Engine/UI/Mouse.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

void CursorSets::registerCursorSets()
{
	Mouse::getInstance()->registerCursorSet(
		CursorSet::Default,
		Mouse::CursorSet(UIResources::Cursors_MouseIdle, UIResources::Cursors_MousePoint, UIResources::Cursors_MousePointPressed, UIResources::Cursors_MouseDrag)
	);

	Mouse::getInstance()->registerCursorSet(
		CursorSet::Globe,
		Mouse::CursorSet(UIResources::Cursors_MouseIdle, UIResources::Cursors_Globe, UIResources::Cursors_Globe, UIResources::Cursors_MouseDrag)
	);

	Mouse::getInstance()->registerCursorSet(
		CursorSet::PickPocket,
		Mouse::CursorSet(UIResources::Cursors_MouseIdle, UIResources::Cursors_Store, UIResources::Cursors_Store, UIResources::Cursors_Store)
	);

	CursorSets::setActiveCursorSet(CursorSet::Default);
}

void CursorSets::setActiveCursorSet(CursorSet cursorSet)
{
	Mouse::getInstance()->setActiveCursorSet(cursorSet);

	InputEvents::TriggerMouseRefresh(Input::GetMouseEvent());
}