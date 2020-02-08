#include "FocusTakeOver.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCNode.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/SceneEvents.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

FocusTakeOver * FocusTakeOver::create()
{
	FocusTakeOver* instance = new FocusTakeOver();

	instance->autorelease();

	return instance;
}

FocusTakeOver::FocusTakeOver()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->hijackedNodes = std::vector<HijackData>();
	this->focusBackground = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
	this->hijackContainer = Node::create();
	this->takeOverOpacity = 196;
	this->hasFocus = false;
	this->isRepeatFocused = false;

	this->addChild(this->focusBackground);
	this->addChild(this->hijackContainer);
}

FocusTakeOver::~FocusTakeOver()
{
}

void FocusTakeOver::onEnter()
{
	super::onEnter();

	this->focusBackground->setOpacity(0);
}

void FocusTakeOver::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* beforeSceneChangeListener = EventListenerCustom::create(
		SceneEvents::EventBeforeSceneChange,
		[=](EventCustom* EventCustom)
		{
			// Important to restore any hijacked nodes before scene changes
			this->unfocus();
		}
	);

	this->addEventListenerIgnorePause(beforeSceneChangeListener);
}

void FocusTakeOver::setTakeOverOpacity(GLubyte takeOverOpacity)
{
	this->takeOverOpacity = takeOverOpacity;
}

void FocusTakeOver::focus(std::vector<Node*> nodes, Transition transition)
{
	this->unfocus(Transition::None);

	for (auto next : nodes)
	{
		if (next == nullptr)
		{
			continue;
		}

		Node* parent = next->getParent();
		
		cocos2d::Vector<Node*> children = parent->getChildren();
		int childIndex = 0;
		auto search = std::find(children.begin(), children.end(), next);

		if (search != children.end())
		{
			childIndex = std::distance(children.begin(), search);
		}

		this->hijackedNodes.push_back(HijackData(next, parent, childIndex));
	}

	// Sort in lowest-to-highest child index so that they are restored in the correct order
	std::sort(this->hijackedNodes.begin(), this->hijackedNodes.end(), [](FocusTakeOver::HijackData& a, FocusTakeOver::HijackData& b)
	{ 
		return a.originalIndex < b.originalIndex;
	});

	// Change the parents of the focus targets (do this as a post-step to keep an accurate child index)
	for (auto next : this->hijackedNodes)
	{
		GameUtils::changeParent(next.node, this->hijackContainer, true);
	}

	switch(transition)
	{
		default:
		{
			break;
		}
		case Transition::Fade:
		{
			this->focusBackground->runAction(FadeTo::create(0.25f, this->takeOverOpacity));
			break;
		}
		case Transition::Instant:
		{
			this->focusBackground->setOpacity(this->takeOverOpacity);
			break;
		}
	}

	this->hasFocus = false;
}

void FocusTakeOver::unfocus(Transition transition)
{
	for (auto next : this->hijackedNodes)
	{
		GameUtils::changeParent(next.node, next.originalParent, true, true, next.originalIndex);
	}

	switch(transition)
	{
		default:
		{
			break;
		}
		case Transition::Fade:
		{
			this->focusBackground->runAction(FadeTo::create(0.25f, 0));
			break;
		}
		case Transition::Instant:
		{
			this->focusBackground->setOpacity(0);
			break;
		}
	}

	this->hijackedNodes.clear();
	this->hasFocus = false;
}

bool FocusTakeOver::isFocused()
{
	return this->hasFocus;
}

void FocusTakeOver::repeatFocus(std::vector<cocos2d::Node*> nodes)
{
	this->focus(nodes, Transition::Fade);

	this->isRepeatFocused = true;

	this->softUnfocus();
}

void FocusTakeOver::refocus()
{
	for (auto next : this->hijackedNodes)
	{
		GameUtils::changeParent(next.node, this->hijackContainer, true);
	}
}

void FocusTakeOver::softUnfocus()
{
	for (auto next : this->hijackedNodes)
	{
		GameUtils::changeParent(next.node, next.originalParent, true, true, next.originalIndex);
	}
}

void FocusTakeOver::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags)
{
	if (this->isRepeatFocused)
	{
		this->refocus();

		super::visit(renderer, parentTransform, parentFlags);

		this->softUnfocus();
	}
	else
	{
		super::visit(renderer, parentTransform, parentFlags);
	}
}
