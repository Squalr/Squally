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

	void setTakeOverOpacity(GLubyte takeOverOpacity);
	void focus(std::vector<cocos2d::Node*> nodes, Transition transition = Transition::Fade);
	void unfocus(Transition transition = Transition::Fade);
	bool isFocused();
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
	bool hasFocus;

	struct HijackData
	{
		cocos2d::Node* node;
		cocos2d::Node* originalParent;
		int originalIndex;

		HijackData(cocos2d::Node* node, cocos2d::Node* originalParent, int originalIndex) : node(node), originalParent(originalParent), originalIndex(originalIndex) { }
	};

	GLubyte takeOverOpacity;
	cocos2d::LayerColor* focusBackground;
	cocos2d::Node* hijackContainer;
	std::vector<HijackData> hijackedNodes;
	bool isRepeatFocused;
};
