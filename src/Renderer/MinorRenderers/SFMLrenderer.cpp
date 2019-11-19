#include "SFMLrenderer.hpp"
#include <GL/glew.h>

namespace ph {

void SFMLRenderer::submit(const sf::Drawable* object)
{
	mSubmitedObjects.emplace_back(object);
}

unsigned SFMLRenderer::getNumberOfSubmitedObjects() const
{
	return mSubmitedObjects.size();
}

void SFMLRenderer::flush(sf::RenderWindow& window)
{
	if(mSubmitedObjects.empty()) {
		return;
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);

	sf::View view;
	view.setCenter(0, 0);
	view.setSize(640, 480);
	window.setView(view);

	window.pushGLStates();
	window.resetGLStates();

	for(const auto* object : mSubmitedObjects)
		window.draw(*object);

	window.popGLStates();

	mSubmitedObjects.clear();
}

}