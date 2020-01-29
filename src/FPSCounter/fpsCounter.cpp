#include "fpsCounter.hpp"
#include "Renderer/renderer.hpp"
#include <cstdio>

namespace ph {

FPSCounter::FPSCounter()
	:mClock()
	,mFPS(0)
	,mFramesFromLastSecond(0)
	,mIsActive(false)
{
}

void FPSCounter::handleEvent(Event phEvent)
{
	if(auto* e = std::get_if<sf::Event>(&phEvent))
		if(e->type == sf::Event::KeyPressed && e->key.code == sf::Keyboard::F2)
			mIsActive = !mIsActive;
}

void FPSCounter::update()
{
	if(mClock.getElapsedTime().asSeconds() >= 1) {
		mFPS = mFramesFromLastSecond;
		mClock.restart();
		mFramesFromLastSecond = 0;
	}
	else
		++mFramesFromLastSecond;

	if(mIsActive) {
		char outputText[16];
		sprintf_s(outputText, "%s%u", "FPS: ", mFPS);
		Renderer::submitDebugText(outputText, "LiberationMono-Bold.ttf", 50.f, 2.f, 2.f, sf::Color::Yellow);
	}
}

}

