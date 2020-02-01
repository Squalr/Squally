#pragma once
#include <vector>

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class LayerColor;
	class Node;
}

class FocusTakeOver : public Hud
{
public:
	static FocusTakeOver* create();

	enum Transition
	{
		None,
		Instant,
		Fade,
	};

	void focus(std::vector<cocos2d::Node*> nodes, Transition transition = Transition::Fade);
	void unfocus(Transition transition = Transition::Fade);
	void repeatFocus(std::vector<cocos2d::Node*> nodes);

protected:
	FocusTakeOver();
	virtual ~FocusTakeOver();

	void onEnter() override;
	void initializeListeners() override;

	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

private:
	typedef Hud super;
	
	void refocus();
	void softUnfocus();

	std::vector<cocos2d::Node*> repeatFocusedNodes;
	cocos2d::LayerColor* focusBackground;
	cocos2d::Node* hijackContainer;
	std::map<cocos2d::Node*, std::tuple<cocos2d::Node*, int>> hijackedNodes;
};
