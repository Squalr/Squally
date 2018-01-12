#include "PostProcess.h"

PostProcess* PostProcess::create(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
	PostProcess* postProcess = new  PostProcess();

	if (postProcess && postProcess->init(vertexShaderFile, fragmentShaderFile))
	{
		postProcess->autorelease();

		return postProcess;
	}
	else
	{
		CC_SAFE_DELETE(postProcess);
		return nullptr;
	}
}

PostProcess::PostProcess() : mpImpl(make_unique<PostProcess::Impl>(this))
{

}

PostProcess::~PostProcess()
{
	this->mpImpl->renderTexture->release();
	this->setAnchorPoint(Point::ZERO);
	this->setPosition(Point::ZERO);
}

bool PostProcess::init(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->mpImpl->glProgram = GLProgram::createWithFilenames(vertexShaderFile, fragmentShaderFile);
	this->mpImpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_POSITION);
	this->mpImpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_COLOR);
	this->mpImpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
	this->mpImpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD1, GLProgram::VERTEX_ATTRIB_TEX_COORD1);
	this->mpImpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD2, GLProgram::VERTEX_ATTRIB_TEX_COORD2);
	this->mpImpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD3, GLProgram::VERTEX_ATTRIB_TEX_COORD3);
	this->mpImpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_NORMAL, GLProgram::VERTEX_ATTRIB_NORMAL);
	this->mpImpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_WEIGHT, GLProgram::VERTEX_ATTRIB_BLEND_WEIGHT);
	this->mpImpl->glProgram->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_BLEND_INDEX, GLProgram::VERTEX_ATTRIB_BLEND_INDEX);
	this->mpImpl->glProgram->link();
	this->mpImpl->glProgram->updateUniforms();

	this->mpImpl->renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height);
	this->mpImpl->renderTexture->retain();

	this->mpImpl->sprite = Sprite::createWithTexture(this->mpImpl->renderTexture->getSprite()->getTexture());
	this->mpImpl->sprite->setTextureRect(Rect(0, 0, this->mpImpl->sprite->getTexture()->getContentSize().width, this->mpImpl->sprite->getTexture()->getContentSize().height));
	this->mpImpl->sprite->setAnchorPoint(Point::ZERO);
	this->mpImpl->sprite->setPosition(Point::ZERO);
	this->mpImpl->sprite->setFlippedY(true);
	this->mpImpl->sprite->setGLProgram(this->mpImpl->glProgram);

	this->addChild(this->mpImpl->sprite);

	return true;
}

void PostProcess::draw(cocos2d::Layer* layer)
{
	this->mpImpl->renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);

	layer->visit();
	// In case you decide to replace Layer* with Node*,
	// since some 'Node' derived classes do not have visit()
	// member function without an argument:
	//auto renderer = Director::getInstance()->getRenderer();
	//auto& parentTransform = Director::getInstance()->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	//layer->visit(renderer, parentTransform, true);

	this->mpImpl->renderTexture->end();

	this->mpImpl->sprite->setTexture(this->mpImpl->renderTexture->getSprite()->getTexture());
}

PostProcess::Impl::Impl(PostProcess* parent) : mParent(parent)
{

}

PostProcess::Impl::~Impl() = default;
