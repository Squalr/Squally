#include "Input.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCInputEvents.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"

using namespace cocos2d;

Input* Input::Instance = nullptr;
InputEvents::MouseEventArgs Input::MouseState = InputEvents::MouseEventArgs();
std::unordered_map<int, bool> Input::PressedKeysPrevious = std::unordered_map<int, bool>();
std::unordered_map<int, bool> Input::PressedKeys = std::unordered_map<int, bool>();
float Input::MinDragDistance = 4.0f;

void Input::registerGlobalNode()
{
	if (Input::Instance == nullptr)
	{
		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(Input::GetInstance());
	}
}

Input* Input::GetInstance()
{
	if (Input::Instance == nullptr)
	{
		Input::Instance = new Input();

		Input::Instance->autorelease();
	}

	return Input::Instance;
}

Input::Input()
{
	this->refreshRequested = false;
}

Input::~Input()
{
}

void Input::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void Input::initializeListeners()
{
	super::initializeListeners();
	
	this->addGlobalEventListener(EventListenerCustom::create(InputEvents::EventKeyJustPressedInternal, [=](EventCustom* eventCustom)
	{
		InputEvents::KeyboardEventArgs* args = static_cast<InputEvents::KeyboardEventArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->onKeyPressed(args->keycode);
		}
	}));
	
	this->addGlobalEventListener(EventListenerCustom::create(InputEvents::EventKeyJustReleasedInternal, [=](EventCustom* eventCustom)
	{
		InputEvents::KeyboardEventArgs* args = static_cast<InputEvents::KeyboardEventArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->onKeyReleased(args->keycode);
		}
	}));

	this->addGlobalEventListener(EventListenerCustom::create(InputEvents::EventMouseMoveInternal, [=](EventCustom* eventCustom)
	{
		InputEvents::MouseEventArgs* args = static_cast<InputEvents::MouseEventArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			Input::MouseState.canClick = false;
			Input::MouseState.mouseCoords = args->mouseCoords;
			Input::MouseState.isDragging = Input::MouseState.isLeftClicked
				&& (std::abs(Input::MouseState.mouseInitialCoords.x - args->mouseCoords.x) >= Input::MinDragDistance
					|| std::abs(Input::MouseState.mouseInitialCoords.y - args->mouseCoords.y) >= Input::MinDragDistance);

			InputEvents::TriggerMouseMove(Input::MouseState);
			InputEvents::TriggerMouseRefresh(Input::MouseState);
		}
	}));

	this->addGlobalEventListener(EventListenerCustom::create(InputEvents::EventMouseDownInternal, [=](EventCustom* eventCustom)
	{
		InputEvents::MouseEventArgs* args = static_cast<InputEvents::MouseEventArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			Input::MouseState.mouseInitialCoords = args->mouseInitialCoords;
			Input::MouseState.isLeftClicked = true;

			InputEvents::TriggerMouseDown(Input::MouseState);
			InputEvents::TriggerMouseRefresh(Input::MouseState);
		}
	}));

	this->addGlobalEventListener(EventListenerCustom::create(InputEvents::EventMouseUpInternal, [=](EventCustom* eventCustom)
	{
		InputEvents::MouseEventArgs* args = static_cast<InputEvents::MouseEventArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			Input::MouseState.isLeftClicked = false;
			Input::MouseState.isDragging = false;

			InputEvents::TriggerMouseUp(Input::MouseState);
			InputEvents::TriggerMouseRefresh(Input::MouseState);
		}
	}));

	this->addGlobalEventListener(EventListenerCustom::create(InputEvents::EventMouseScrollInternal, [=](EventCustom* eventCustom)
	{
		InputEvents::MouseEventArgs* args = static_cast<InputEvents::MouseEventArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			Input::MouseState.scrollDelta = args->scrollDelta;

			InputEvents::TriggerMouseScroll(Input::MouseState);
			InputEvents::TriggerMouseRefresh(Input::MouseState);
		}
	}));
	
	this->addGlobalEventListener(EventListenerCustom::create(InputEvents::EventClickableMouseOver, [=](EventCustom* eventCustom)
	{
		Input::MouseState.canClick = true;

		InputEvents::TriggerMouseRefresh(Input::MouseState);
	}));
	
	this->addGlobalEventListener(EventListenerCustom::create(InputEvents::EventClickableMouseOut, [=](EventCustom* eventCustom)
	{
		InputEvents::TriggerMouseRefresh(Input::MouseState);
	}));
	
	this->addGlobalEventListener(EventListenerCustom::create(InputEvents::EventMouseRequestRefresh, [=](EventCustom* eventCustom)
	{
		this->refreshRequested = true;
	}));
	

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_CTRL, InputEvents::KeyCode::KEY_ALT, InputEvents::KeyCode::KEY_SHIFT}, [=](InputEvents::KeyboardEventArgs*)
	{
		Input::MouseState.canClick = false;

		InputEvents::TriggerMouseMove(Input::MouseState);
		InputEvents::TriggerMouseRefresh(Input::MouseState);
	});

	this->whenKeyReleased({ InputEvents::KeyCode::KEY_CTRL, InputEvents::KeyCode::KEY_ALT, InputEvents::KeyCode::KEY_SHIFT}, [=](InputEvents::KeyboardEventArgs*)
	{
		Input::MouseState.canClick = false;
		
		InputEvents::TriggerMouseMove(Input::MouseState);
		InputEvents::TriggerMouseRefresh(Input::MouseState);
	});
}

void Input::update(float dt)
{
	super::update(dt);

	if (this->refreshRequested)
	{
		this->refreshRequested = false;
		
		Input::MouseState.canClick = false;
		
		InputEvents::TriggerMouseMove(Input::MouseState);
		InputEvents::TriggerMouseRefresh(Input::MouseState);
	}
}

InputEvents::MouseEventArgs Input::GetMouseEvent()
{
	return Input::MouseState;
}

void Input::onKeyPressed(InputEvents::KeyCode keyCode)
{
	Input::PressedKeysPrevious = Input::PressedKeys;
	Input::PressedKeys[(int)keyCode] = true;

	// Check if previously not pressed or if previously up
	if (!Input::PressedKeysPrevious.contains((int)keyCode) || !Input::PressedKeysPrevious[(int)keyCode])
	{
		InputEvents::TriggerKeyJustPressed(InputEvents::KeyboardEventArgs(keyCode));
	}
}

void Input::onKeyReleased(InputEvents::KeyCode keyCode)
{
	Input::PressedKeysPrevious = Input::PressedKeys;
	Input::PressedKeys[(int)keyCode] = false;

	InputEvents::TriggerKeyJustReleased(InputEvents::KeyboardEventArgs(keyCode));
}

InputEvents::KeyCode Input::GetActiveModifiers()
{
	InputEvents::KeyCode modifiers = InputEvents::KeyCode::KEY_NONE;

	if (Input::IsPressed(InputEvents::KeyCode::KEY_SHIFT))
	{
		modifiers = (InputEvents::KeyCode)((int)modifiers | (int)InputEvents::KeyCode::KEY_SHIFT);
	}

	if (Input::IsPressed(InputEvents::KeyCode::KEY_ALT))
	{
		modifiers = (InputEvents::KeyCode)((int)modifiers | (int)InputEvents::KeyCode::KEY_ALT);
	}

	if (Input::IsPressed(InputEvents::KeyCode::KEY_CTRL))
	{
		modifiers = (InputEvents::KeyCode)((int)modifiers | (int)InputEvents::KeyCode::KEY_CTRL);
	}

	return modifiers;
}

bool Input::IsPressed(InputEvents::KeyCode keyCode)
{
	if (Input::PressedKeys.contains((int)keyCode))
	{
		return Input::PressedKeys[(int)keyCode];
	}

	return false;
}

bool Input::IsReleased(InputEvents::KeyCode keyCode)
{
	if (Input::PressedKeys.contains((int)keyCode))
	{
		return !Input::PressedKeys[(int)keyCode];
	}

	return true;
}
