#include "KSequence.h"

using namespace cocos2d;

KSequence* KSequence::create(std::vector<EventKeyboard::KeyCode> sequence, std::function<void()> callback, bool interruptable)
{
	KSequence* instance = new KSequence(sequence, callback, interruptable);

	instance->autorelease();

	return instance;
}

KSequence::KSequence(std::vector<EventKeyboard::KeyCode> sequence, std::function<void()> callback, bool interruptable)
{
	this->sequence = sequence;
	this->callback = callback;
	this->interruptable = interruptable;
	this->completed = false;
	this->currentIndex = 0;
}

KSequence::~KSequence()
{
}

void KSequence::onEnter()
{
	super::onEnter();
}

void KSequence::initializeListeners()
{
	super::initializeListeners();

	this->whenKeyPressed(
	{
		EventKeyboard::KeyCode::KEY_A,
		EventKeyboard::KeyCode::KEY_B,
		EventKeyboard::KeyCode::KEY_C,
		EventKeyboard::KeyCode::KEY_D,
		EventKeyboard::KeyCode::KEY_E,
		EventKeyboard::KeyCode::KEY_F,
		EventKeyboard::KeyCode::KEY_G,
		EventKeyboard::KeyCode::KEY_H,
		EventKeyboard::KeyCode::KEY_I,
		EventKeyboard::KeyCode::KEY_J,
		EventKeyboard::KeyCode::KEY_K,
		EventKeyboard::KeyCode::KEY_L,
		EventKeyboard::KeyCode::KEY_M,
		EventKeyboard::KeyCode::KEY_N,
		EventKeyboard::KeyCode::KEY_O,
		EventKeyboard::KeyCode::KEY_P,
		EventKeyboard::KeyCode::KEY_Q,
		EventKeyboard::KeyCode::KEY_R,
		EventKeyboard::KeyCode::KEY_S,
		EventKeyboard::KeyCode::KEY_T,
		EventKeyboard::KeyCode::KEY_U,
		EventKeyboard::KeyCode::KEY_V,
		EventKeyboard::KeyCode::KEY_W,
		EventKeyboard::KeyCode::KEY_X,
		EventKeyboard::KeyCode::KEY_Y,
		EventKeyboard::KeyCode::KEY_Z,
	}, [=](InputEvents::InputArgs* args)
	{
		this->processInput(args->keycode);
	});
}

void KSequence::processInput(EventKeyboard::KeyCode keycode)
{
	if (this->completed || this->sequence.size() <= 0)
	{
		return;
	}

	if (this->sequence[this->currentIndex] == keycode)
	{
		this->currentIndex++;

		if (this->currentIndex >= int(this->sequence.size()))
		{
			this->completed = true;

			if (this->callback != nullptr)
			{
				this->callback();
			}
		}
	}
	else if (this->interruptable)
	{
		this->currentIndex = 0;
	}
}
