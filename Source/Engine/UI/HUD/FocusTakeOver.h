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

	enum class Transition
	{
		None,
		Instant,
		Fade,
	};

	void setTakeOverOpacity(GLubyte takeOverOpacity);
	void unfocus(Transition transition = Transition::Fade);
	bool isFocused();

	// Captures nodes, but does not return them to their prior owner. Updating the position of focused nodes will cause visual issues. Very performant.
	void focus(std::vector<cocos2d::Node*> nodes, Transition transition = Transition::Fade);

	// Captures nodes, and continuously places them in their original position. Performant, but assumes the position of the captured nodes isn't updated elsewhere.
	void positionFreezeFocus(std::vector<cocos2d::Node*> nodes);

	// Captures nodes, but returns nodes to their prior owner every draw frame. Caller has nothing to worry about, but this has serious performance issues.
	void repeatFocus(std::vector<cocos2d::Node*> nodes);

protected:
	FocusTakeOver();
	virtual ~FocusTakeOver();

	void onEnter() override;
	void initializeListeners() override;
	void update(float dt) override;
	void pause() override;

	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags) override;

private:
	typedef Hud super;
	
	void refocus();
	void softUnfocus();

	struct HijackData
	{
		cocos2d::Node* node;
		cocos2d::Node* originalParent;
		int originalIndex;
		cocos2d::Vec3 originalCoords;

		HijackData(cocos2d::Node* node, cocos2d::Node* originalParent, int originalIndex, cocos2d::Vec3 originalCoords)
			: node(node), originalParent(originalParent), originalIndex(originalIndex), originalCoords(originalCoords) { }
	};

	enum class FocusMode
	{
		None,
		Normal,
		Freeze,
		Repeat
	};

	GLubyte takeOverOpacity;
	cocos2d::LayerColor* focusBackground;
	cocos2d::Node* hijackContainer;
	std::vector<HijackData> hijackedNodes;
	FocusMode focusMode;
};
