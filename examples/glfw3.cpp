#include <iostream>
#include <cstdlib>

#include <GLFW/glfw3.h>

#include "nano_font.h"

namespace {

namespace window_property {
	int x = 50;
	int y = 50;
	int width = 640;
	int height = 480;
}

void ErrorCallback(int error, const char* description)
{
	std::cerr << "Error: " << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLFWwindow* OpenWindow(const std::string &title)
{
	glfwWindowHint(GLFW_DECORATED, GL_FALSE);

	auto window = glfwCreateWindow(window_property::width, window_property::height, title.c_str(), nullptr, nullptr);
	if (!window) {
		return nullptr;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetWindowPos(window, window_property::x, window_property::y);

	return window;
}

}

class Renderer {
public:
	Renderer() {
		CreateTexture();
	}

	void Draw(const std::string &message, int x, int y, float scale) {
		int width, height;
		glfwGetFramebufferSize(glfwGetCurrentContext(), &width, &height);

		glViewport(0, 0, width, height);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.f, 1.f, 0.f, 1.f, 0, 1);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture_handle);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		for(const auto &code: message) {
			auto index = nano_font::ToIndex(code);
			DrawCode(index, static_cast<float>(x), static_cast<float>(y), scale);
			x += static_cast<int>((nano_font::property::width + 1) * scale);
		}
	}

private:
	void DrawCode(char index, float position_x, float position_y, float scale) {
		glBegin(GL_QUADS);

		GLfloat width = static_cast<float>(nano_font::property::width) / window_property::width * scale;
		GLfloat height = static_cast<float>(nano_font::property::height) / window_property::height * scale;
		GLfloat x = position_x / window_property::width;
		GLfloat y = (window_property::height - position_y) / window_property::height - height;

		GLfloat texcoord = 1.f / nano_font::property::font_count;
		glTexCoord2f(index * texcoord, 0.f);
		glVertex2f(x, y);

		glTexCoord2f((index + 1) * texcoord, 0.f);
		glVertex2f(x + width, y);

		glTexCoord2f((index + 1) * texcoord, 1.f);
		glVertex2f(x + width, y + height);

		glTexCoord2f(index * texcoord, 1.f);
		glVertex2f(x, y + height);

		glEnd();
	}

	void CreateTexture() {
		namespace property = nano_font::property;
		texture.width = property::width * property::font_count;
		texture.height = property::height;

		auto pixels = nano_font::Make(texture);

		glGenTextures(1, &texture_handle);
		glBindTexture(GL_TEXTURE_2D, texture_handle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	nano_font::Texture texture;
	GLuint texture_handle;
};

int main(int argc, char** argv) {

	glfwSetErrorCallback(ErrorCallback);

	if (!glfwInit()) {
		std::exit(EXIT_FAILURE);
	}

	auto window = OpenWindow("nano font");
	if (!window) {
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window, KeyCallback);

	auto renderer = Renderer();

	while (!glfwWindowShouldClose(window)) {
		renderer.Draw("hello world", 30, 30, 2.f);
		renderer.Draw("please press ESC key to close", 30, 60, 2.f);

		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	glfwTerminate();
	std::exit(EXIT_SUCCESS);
}

