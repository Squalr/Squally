#pragma once

#include "cocos2d.h"
#include <memory>
#include <string>

using namespace std;
using namespace cocos2d;

class PostProcess : public cocos2d::Layer
{
public:
	struct Impl
	{
	public:
		Impl(PostProcess* parent);
		~Impl();
		GLProgram * glProgram;
		RenderTexture* renderTexture;
		Sprite* sprite;

	private:
		PostProcess * mParent;
	};

	virtual bool init(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	void draw(cocos2d::Layer* layer);
	static PostProcess* create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

private:
	PostProcess();
	virtual ~PostProcess();

	std::unique_ptr<Impl> mpImpl;
};
