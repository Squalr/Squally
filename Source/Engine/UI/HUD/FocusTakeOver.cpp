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

	this->hijackedNodes = std::map<Node*, std::tuple<Node*, int>>();
	this->focusBackground = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
	this->hijackContainer = Node::create();
	this->takeOverOpacity = 196;
	this->hasFocus = false;

	this->hijackContainer->setCascadeColorEnabled(false);
	this->hijackContainer->setCascadeOpacityEnabled(false);

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

		this->hijackedNodes[next] = std::tuple<Node*, int>(parent, childIndex);

		GameUtils::changeParent(next, this->hijackContainer, true);
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
		if (next.first == nullptr)
		{
			continue;
		}

		Node* node = next.first;
		Node* parent = std::get<0>(next.second);
		int childIndex = std::get<1>(next.second);

		GameUtils::changeParent(node, parent, true, true, childIndex);
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
	this->repeatFocusedNodes.clear();
	this->hasFocus = false;
}

bool FocusTakeOver::isFocused()
{
	return this->hasFocus;
}

void FocusTakeOver::repeatFocus(std::vector<cocos2d::Node*> nodes)
{
	this->focus(nodes, Transition::Fade);

	this->repeatFocusedNodes = nodes;

	this->softUnfocus();
}

void FocusTakeOver::refocus()
{
	for (auto next : this->repeatFocusedNodes)
	{
		if (next == nullptr)
		{
			continue;
		}

		GameUtils::changeParent(next, this->hijackContainer, true);
	}
}

void FocusTakeOver::softUnfocus()
{
	for (auto next : this->hijackedNodes)
	{
		if (next.first == nullptr)
		{
			continue;
		}

		Node* node = next.first;
		Node* parent = std::get<0>(next.second);
		int childIndex = std::get<1>(next.second);

		GameUtils::changeParent(node, parent, true, true, childIndex);
	}
}

void FocusTakeOver::visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags)
{
	if (this->repeatFocusedNodes.empty())
	{
		super::visit(renderer, parentTransform, parentFlags);
	}
	else
	{
		this->refocus();

		super::visit(renderer, parentTransform, parentFlags);

		this->softUnfocus();
	}
}
