#include "KSequence.h"

using namespace cocos2d;

KSequence* KSequence::create(std::vector<InputEvents::KeyCode> sequence, std::function<void()> callback, bool interruptable)
{
	KSequence* instance = new KSequence(sequence, callback, interruptable);

	instance->autorelease();

	return instance;
}

KSequence::KSequence(std::vector<InputEvents::KeyCode> sequence, std::function<void()> callback, bool interruptable)
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
		InputEvents::KeyCode::KEY_A,
		InputEvents::KeyCode::KEY_B,
		InputEvents::KeyCode::KEY_C,
		InputEvents::KeyCode::KEY_D,
		InputEvents::KeyCode::KEY_E,
		InputEvents::KeyCode::KEY_F,
		InputEvents::KeyCode::KEY_G,
		InputEvents::KeyCode::KEY_H,
		InputEvents::KeyCode::KEY_I,
		InputEvents::KeyCode::KEY_J,
		InputEvents::KeyCode::KEY_K,
		InputEvents::KeyCode::KEY_L,
		InputEvents::KeyCode::KEY_M,
		InputEvents::KeyCode::KEY_N,
		InputEvents::KeyCode::KEY_O,
		InputEvents::KeyCode::KEY_P,
		InputEvents::KeyCode::KEY_Q,
		InputEvents::KeyCode::KEY_R,
		InputEvents::KeyCode::KEY_S,
		InputEvents::KeyCode::KEY_T,
		InputEvents::KeyCode::KEY_U,
		InputEvents::KeyCode::KEY_V,
		InputEvents::KeyCode::KEY_W,
		InputEvents::KeyCode::KEY_X,
		InputEvents::KeyCode::KEY_Y,
		InputEvents::KeyCode::KEY_Z,
	}, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->processInput(args->keycode);
	});
}

void KSequence::processInput(InputEvents::KeyCode keycode)
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
