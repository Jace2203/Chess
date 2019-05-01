#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "graphic/Renderer.h"

#include "graphic/VertexBuffer.h"
#include "graphic/VertexBufferLayout.h"
#include "graphic/IndexBuffer.h"
#include "graphic/VertexArray.h"
#include "graphic/Shader.h"
#include "graphic/Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

extern int* m_ChessNotation;

enum Mode
{
	MENU1 = 1, MENU2, GAME, PROM, AFTER
};

enum Type
{
	none = -1, king, queen, bishop, knight, rook, pawn, passing
};

enum Color
{
	black = -1, white = 1
};

static void invert(Color* c)
{
	*c = Color(int(*c) * -1);
}

static Color invert(Color c)
{
	return Color(int(c) * -1);
}

static std::ostream& operator<<(std::ostream& stream, Color c)
{
	if (c == white)
		stream << "White:";
	else
		stream << "Black:";
	return stream;
}

struct Pos
{
	int x, y;

	Pos() = default;
	Pos(int i) { x = i % 8; y = (i - x) / 8; }
	Pos(int i, int j) { x = i; y = j; }

	int ToNum() { return x + y * 8; }

	bool operator==(Pos& other) { return (x == other.x) && (y == other.y); }
	bool operator!=(Pos& other) {  return !(*this == other); }
};