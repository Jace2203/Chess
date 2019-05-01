#pragma once

#include "deco.h"
#include "Chessboard.h"
#include "ChessNotation.h"
#include "Game.h"

#define SCREEN_WIDTH 1120
#define SCREEN_HEIGHT 630

GLFWwindow* set_up();

void GetMousePosition(GLFWwindow* window, double* x, double* y);
void menu1_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void menu2_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void game_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void prom_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void after_mouse_button_callback(GLFWwindow* window, int button, int action, int mods);