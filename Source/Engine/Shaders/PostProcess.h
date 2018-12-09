#pragma once
#include <memory>
#include <string>

#include "cocos/2d/CCLayer.h"

namespace cocos2d
{
	class GLProgram;
	class RenderTexture;
	class Sprite;
}

class PostProcess : public cocos2d::Layer
{
public:
	// Redefine this, not all compilers can find the std:: implementation
	template<typename T, typename... Args>
	std::unique_ptr<T> make_unique(Args&&... args)
	{
		return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
	}

	struct Impl
	{
		public:
			Impl(PostProcess* parent);
			~Impl();
			cocos2d::GLProgram * glProgram;
			cocos2d::RenderTexture* renderTexture;
			cocos2d::Sprite* sprite;

		private:
			PostProcess * mParent;
	};

	virtual bool init(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);
	void draw(cocos2d::Layer* layer);
	void draw(cocos2d::Node* node);
	static PostProcess* create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

private:
	PostProcess();
	virtual ~PostProcess();

	std::unique_ptr<Impl> mpImpl;
};
