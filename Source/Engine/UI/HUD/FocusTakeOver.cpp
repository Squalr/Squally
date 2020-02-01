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

void FocusTakeOver::disableBackground()
{
	this->focusBackground->setVisible(false);
}

void FocusTakeOver::focus(std::vector<Node*> nodes, Transition transition)
{
	this->unfocus(Transition::Instant);

	for (auto next : nodes)
	{
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
			this->focusBackground->runAction(FadeTo::create(0.25f, 196));
			break;
		}
		case Transition::Instant:
		{
			this->focusBackground->setOpacity(196);
			break;
		}
	}
}

void FocusTakeOver::unfocus(Transition transition)
{
	for (auto next : this->hijackedNodes)
	{
		Node* node = next.first;
		Node* parent = std::get<0>(next.second);
		int childIndex = std::get<1>(next.second);

		GameUtils::changeParent(node, parent, true, true, childIndex);
	}

	this->hijackedNodes.clear();
	this->repeatFocusedNodes.clear();

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
		GameUtils::changeParent(next, this->hijackContainer, true);
	}
}

void FocusTakeOver::softUnfocus()
{
	for (auto next : this->hijackedNodes)
	{
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
