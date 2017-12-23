#include "Window.h"

Window::Window()
{
}

Window::~Window()
{
	AudioEngine::end();
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
	GLViewImpl* glview;

	switch (ConfigManager::LoadResolution())
	{
	case ConfigManager::ResolutionSetting::R1080x768:
		glview = GLViewImpl::createWithRect(this->windowTitle, Rect(0, 0, ConfigManager::Resolution1024x768->width, ConfigManager::Resolution1024x768->height));
		break;
	case ConfigManager::ResolutionSetting::R1920x1080:
		glview = GLViewImpl::createWithRect(this->windowTitle, Rect(0, 0, ConfigManager::Resolution1920x1080->width, ConfigManager::Resolution1920x1080->height));
		break;
	case ConfigManager::ResolutionSetting::FullScreen:
	default:
		glview = GLViewImpl::createWithFullScreen(this->windowTitle);
		break;
	}

	glview->setDesignResolutionSize(glview->getFrameSize().width, glview->getFrameSize().height, ResolutionPolicy::NO_BORDER);
	director->setOpenGLView(glview);
	glview->setCursorVisible(false);

	// Debugging: Turn on display FPS
	// director->setDisplayStats(true);

	// Start the game
	Game* game = new Game();

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void Window::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();
	AudioEngine::pauseAll();
}

// This function will be called when the app is active again
void Window::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();
	AudioEngine::resumeAll();
}
