#include "Texture.h"

Engine::Texture::Texture(const char* image_path, int image_type) {
	stbi_set_flip_vertically_on_load(true);

	int ImageWidth, ImageHeight, NumberOfChannels;
	m_Bytes = stbi_load(image_path, &ImageWidth, &ImageHeight, &NumberOfChannels, 0);

	check(glGenTextures(1, &m_Texture));
	check(glActiveTexture(GL_TEXTURE0));
	check(glBindTexture(GL_TEXTURE_2D, m_Texture));

	check(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	check(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));

	check(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	check(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	check(glTexImage2D(GL_TEXTURE_2D, 0, image_type, ImageWidth, ImageHeight, 0, image_type, GL_UNSIGNED_BYTE, m_Bytes));

	check(glGenerateMipmap(GL_TEXTURE_2D));

	check(glBindTexture(GL_TEXTURE_2D, 0));

	stbi_image_free(m_Bytes);
}

void Engine::Texture::Bind() {
	check(glBindTexture(GL_TEXTURE_2D, m_Texture));
}

void Engine::Texture::Unbind() {
	check(glBindTexture(GL_TEXTURE_2D, 0));
}