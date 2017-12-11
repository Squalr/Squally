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

	glview = GLViewImpl::createWithFullScreen("Squalr Tutorial");
	// glview = GLViewImpl::createWithRect("Squalr Tutorial", Rect(0, 0, this->mediumResolutionSize->width, this->mediumResolutionSize->height));

	glview->setDesignResolutionSize(glview->getFrameSize().width, glview->getFrameSize().height, ResolutionPolicy::NO_BORDER);
	director->setOpenGLView(glview);
	glview->setCursorVisible(false);

	// Turn on display FPS
	director->setDisplayStats(true);

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
