#include "CursorSets.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Input/Input.h"
#include "Engine/UI/Mouse.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

void CursorSets::RegisterCursorSets()
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

	Mouse::getInstance()->registerCursorSet(
		CursorSet::Repair,
		Mouse::CursorSet(UIResources::Cursors_MouseIdle, UIResources::Cursors_Craft, UIResources::Cursors_Craft, UIResources::Cursors_Craft)
	);

	Mouse::getInstance()->registerCursorSet(
		CursorSet::SoulHarvest,
		Mouse::CursorSet(UIResources::Cursors_MouseIdle, UIResources::Cursors_Door, UIResources::Cursors_Door, UIResources::Cursors_Door)
	);

	CursorSets::SetActiveCursorSet(CursorSet::Default);
}

void CursorSets::SetActiveCursorSet(CursorSet cursorSet)
{
	Mouse::getInstance()->setActiveCursorSet(cursorSet);

	InputEvents::TriggerMouseRefresh(Input::GetMouseEvent());
}

CursorSets::CursorSet CursorSets::GetActiveCursorSet()
{
	return (CursorSet)Mouse::getInstance()->getActiveCursorSet();
}