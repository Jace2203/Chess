#include "Graphic.h"

GLFWwindow* set_up()
{
	GLFWwindow* window;

	// Initialize the library
	if (!glfwInit())
		return nullptr;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess Game", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return nullptr;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);
	
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;

	return window;
}

void GetMousePosition(GLFWwindow* window, double* x, double* y)
{
	glfwGetCursorPos(window, x, y);
}

void menu1_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double x, y;
		GetMousePosition(window, &x, &y);
		y = (double)SCREEN_HEIGHT - y;
		if ((y >= 192) && (y <= 242))
		{
			Game::setValue(0);
		}
		else if ((y >= 86) && (y <= 138))
		{
			Game::setValue(1);
		}
	}
}

void menu2_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double x, y;
		GetMousePosition(window, &x, &y);
		y = SCREEN_HEIGHT - y;
		if ((y >= 193) && (y <= 243))
		{
			Game::setValue(0);
		}
		else if ((y >= 87) && (y <= 137))
		{
			Game::setValue(1);
		}
	}
}

void game_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double x, y;
		GetMousePosition(window, &x, &y);
		y = SCREEN_HEIGHT - y;
		if ((x >= 280) && (x <= 840) && (y >= 35) && (y <= 595))
		{
			Pos temp((x - 280) / 70, (y - 35) / 70);
			if (Game::Update_Move(temp))
			{
				((ChessNotation*)m_ChessNotation)->ReadIn(Game::getChessBoard()->start_pos, Game::getChessBoard()->end_pos, Game::getChessBoard()->castling, Game::getChessBoard()->captured_type);
				Game::ResetValues();
				Game::getChessBoard()->end_pos = Game::getChessBoard()->NULL_POS;
			}
		}
		else if ((x >= 1080) && (y >= 590))
		{
			Game::setValue(0);
		}
	}
}

void prom_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double x, y;
		GetMousePosition(window, &x, &y);
		y = SCREEN_HEIGHT - y;
		if ((x >= 385) && (x <= 735) && (y >= 280) && (y <= 350))
		{
			Game::setValue((x - 385) / 70 + 1);
		}
	}
}

void after_mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double x, y;
		GetMousePosition(window, &x, &y);
		y = SCREEN_HEIGHT - y;
		if (y >= 590)
		{
			if (x >= 1080)
			{
				Game::setValue(0);
			}
			else if (x >= 1040)
			{
				Game::setValue(1);
			}
			else if (x >= 1000)
			{
				Game::setValue(2);
			}
			else if (x >= 960)
			{
				Game::setValue(3);
			}
		}
	}
}