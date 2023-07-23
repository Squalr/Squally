#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class DrawNode;
}

template <class T> class LazyNode;
class NormalFadeHud;
class TriangleFadeHud;
class TvFadeHud;

class FadeHud : public Hud
{
public:
	static FadeHud* create();
	
	enum class FadeHudType
	{
		Normal,
		Triangles,
		Tv,
	};

	void runAnim(FadeHud::FadeHudType fadeHudType);
	void resetAnims();

	static const float AnimationTimeBudget;

protected:
	FadeHud();
	virtual ~FadeHud();
	
	void pause() override;

private:
	typedef Hud super;

	LazyNode<NormalFadeHud>* normalFadeHud = nullptr;
	LazyNode<TriangleFadeHud>* triangleFadeHud = nullptr;
	LazyNode<TvFadeHud>* tvFadeHud = nullptr;
	cocos2d::DrawNode* resetScreen = nullptr;
};
