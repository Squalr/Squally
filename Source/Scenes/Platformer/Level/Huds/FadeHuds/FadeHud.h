#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class DrawNode;
}

template <class T> class LazyNode;
class NormalFadeHud;
class TriangleFadeHud;

class FadeHud : public Hud
{
public:
	static FadeHud* create();
	
	enum class FadeHudType
	{
		Normal,
		Triangles,
	};

	void runAnim(FadeHud::FadeHudType fadeHudType);
	void resetAnims();

	static const float AnimationTimeBudget;

protected:
	FadeHud();
	virtual ~FadeHud();

private:
	typedef Hud super;

	LazyNode<NormalFadeHud>* normalFadeHud;
	LazyNode<TriangleFadeHud>* triangleFadeHud;

	cocos2d::DrawNode* resetScreen;
};
