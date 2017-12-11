#include "Window.h"

Window::Window()
{
}

Window::~Window()
{
	SimpleAudioEngine::end();
}

// If you want a different context, modify the value of glContextAttrs it will affect all platforms
void Window::initGLContextAttrs()
{
	// Set OpenGL context attributes: red, green, blue, alpha, depth, stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}

// If you want to use the package manager to install more packages, don't modify or remove this function
static int register_all_packages()
{
	return 0; // Flag for packages manager
}

bool Window::applicationDidFinishLaunching()
{
	Director* director = Director::getInstance();
	GLView* glview = director->getOpenGLView();

	if (!glview) {
		glview = GLViewImpl::createWithFullScreen("Squalr Tutorial");
		//glview = GLViewImpl::createWithRect("Squalr Tutorial", Rect(0, 0, this->mediumResolutionSize->width, this->mediumResolutionSize->height));
		director->setOpenGLView(glview);
		glview->setCursorVisible(false);
	}

	// Turn on display FPS
	director->setDisplayStats(true);

	// Set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);

	// Set the design resolution
	glview->setDesignResolutionSize(this->designResolutionSize->width, this->designResolutionSize->height, ResolutionPolicy::NO_BORDER);
	Size frameSize = glview->getFrameSize();

	// If the frame's height is larger than the height of medium size.
	if (frameSize.height > this->mediumResolutionSize->height)
	{
		director->setContentScaleFactor(MIN(this->largeResolutionSize->height / this->designResolutionSize->height, this->largeResolutionSize->width / this->designResolutionSize->width));
	}
	// If the frame's height is larger than the height of small size.
	else if (frameSize.height > this->smallResolutionSize->height)
	{
		director->setContentScaleFactor(MIN(this->mediumResolutionSize->height / this->designResolutionSize->height, this->mediumResolutionSize->width / this->designResolutionSize->width));
	}
	// If the frame's height is smaller than the height of medium size.
	else
	{
		director->setContentScaleFactor(MIN(this->smallResolutionSize->height / this->designResolutionSize->height, this->smallResolutionSize->width / this->designResolutionSize->width));
	}

	register_all_packages();

	// Start the game
	Game* game = new Game();

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void Window::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	SimpleAudioEngine::getInstance()->pauseAllEffects();
}

// This function will be called when the app is active again
void Window::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	SimpleAudioEngine::getInstance()->resumeAllEffects();
}
