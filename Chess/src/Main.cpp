#include <iostream>

#include <Windows.h>

#include "deco.h"
#include "Graphic.h"
#include "Chessboard.h"
#include "Game.h"
#include "ChessNotation.h"

#define SCREEN_WIDTH 1120
#define SCREEN_HEIGHT 630
#define AI_DEPTH 3

ChessBoard* Game::m_ChessBoard;
int* m_ChessNotation;
Mode Game::m_Mode;
int Game::m_Value;
bool Game::m_Win;
bool Game::m_Draw;
Pos Game::m_Pos;

int main()
{
	int timer = 0;

	ChessBoard chessboard;
	chessboard.init();
	Game::setChessBoard(&chessboard);
	Game::setMode(MENU1);
	Game::setValue(-1);
	Game::setWin(false);
	Game::setDraw(false);
	Game::setPos(Pos(-1, -1));

	ChessNotation chessnotation;
	m_ChessNotation = (int*)&chessnotation;

	bool single = true;
	Color AI_color = Color(rand() % 2);

	// Window Part
	GLFWwindow* window = set_up();
	glfwSetMouseButtonCallback(window, menu1_mouse_button_callback);

	Texture white_king_texture("res/textures/white_king.png");
	Texture white_queen_texture("res/textures/white_queen.png");
	Texture white_bishop_texture("res/textures/white_bishop.png");
	Texture white_knight_texture("res/textures/white_knight.png");
	Texture white_rook_texture("res/textures/white_rook.png");
	Texture white_pawn_texture("res/textures/white_pawn.png");
	Texture black_king_texture("res/textures/black_king.png");
	Texture black_queen_texture("res/textures/black_queen.png");
	Texture black_bishop_texture("res/textures/black_bishop.png");
	Texture black_knight_texture("res/textures/black_knight.png");
	Texture black_rook_texture("res/textures/black_rook.png");
	Texture black_pawn_texture("res/textures/black_pawn.png");

	Texture board("res/textures/chessboard.png");
	Texture cover("res/textures/cover.png");
	Texture left("res/textures/left.png");
	Texture right("res/textures/right.png");
	Texture save("res/textures/save.png");
	Texture gear("res/textures/gear.png");
	Texture pic("res/textures/sample.png");

	Texture single_word("res/textures/single.png");
	Texture multi_word("res/textures/multi.png");
	Texture new_word("res/textures/new.png");
	Texture import_word("res/textures/import.png");

	Texture list_bg("res/textures/list_bg.png");

	Texture zero("res/textures/notation/0.png");
	Texture one("res/textures/notation/1.png");
	Texture two("res/textures/notation/2.png");
	Texture three("res/textures/notation/3.png");
	Texture four("res/textures/notation/4.png");
	Texture five("res/textures/notation/5.png");
	Texture six("res/textures/notation/6.png");
	Texture seven("res/textures/notation/7.png");
	Texture eight("res/textures/notation/8.png");
	Texture a("res/textures/notation/a.png");
	Texture b("res/textures/notation/b.png");
	Texture c("res/textures/notation/c.png");
	Texture d("res/textures/notation/d.png");
	Texture e("res/textures/notation/e.png");
	Texture f("res/textures/notation/f.png");
	Texture g("res/textures/notation/g.png");
	Texture h("res/textures/notation/h.png");
	Texture dash("res/textures/notation/dash.png");

	float positions[] = {
		-35.0f, -35.0f, 0.0f, 0.0f,
		35.0f, -35.0f, 1.0f, 0.0f,
		35.0f,  35.0f, 1.0f, 1.0f,
		-35.0f,  35.0f, 0.0f, 1.0f
	};

	float board_size[] = {
		-280.0f, -280.0f, 0.0f, 0.0f,
		280.0f, -280.0f, 1.0f, 0.0f,
		280.0f,  280.0f, 1.0f, 1.0f,
		-280.0f,  280.0f, 0.0f, 1.0f
	};

	float pic_size[] = {
		-125.0f, -125.0f, 0.0f, 0.0f,
		125.0f, -125.0f, 1.0f, 0.0f,
		125.0f,  125.0f, 1.0f, 1.0f,
		-125.0f,  125.0f, 0.0f, 1.0f
	};

	float single_size[] = {
		-145.0f, -26.5f, 0.0f, 0.0f,
		145.0f, -26.5f, 1.0f, 0.0f,
		145.0f,  26.5f, 1.0f, 1.0f,
		-145.0f,  26.5f, 0.0f, 1.0f
	};

	float multi_size[] = {
		-196.0f, -26.5f, 0.0f, 0.0f,
		196.0f, -26.5f, 1.0f, 0.0f,
		196.0f,  26.5f, 1.0f, 1.0f,
		-196.0f,  26.5f, 0.0f, 1.0f
	};

	float new_size[] = {
		-156.3f, -25.5f, 0.0f, 0.0f,
		156.3f, -25.5f, 1.0f, 0.0f,
		156.3f,  25.5f, 1.0f, 1.0f,
		-156.3f,  25.5f, 0.0f, 1.0f
	};

	float import_size[] = {
		-123.0f, -25.5f, 0.0f, 0.0f,
		123.0f, -25.5f, 1.0f, 0.0f,
		123.0f,  25.5f, 1.0f, 1.0f,
		-123.0f,  25.5f, 0.0f, 1.0f
	};

	float icon_size[] = {
		-20.0f, -20.0f, 0.0f, 0.0f,
		20.0f, -20.0f, 1.0f, 0.0f,
		20.0f,  20.0f, 1.0f, 1.0f,
		-20.0f,  20.0f, 0.0f, 1.0f
	};

	float list_size[] = {
		-100.0f, -260.0f, 0.0f, 0.0f,
		100.0f, -260.0f, 1.0f, 0.0f,
		100.0f,  260.0f, 1.0f, 1.0f,
		-100.0f,  260.0f, 0.0f, 1.0f
	};

	float notation_size[] = {
		-11.5f, -13.75f, 0.0f, 0.0f,
		11.5f, -13.75f, 1.0f, 0.0f,
		11.5f,  13.75f, 1.0f, 1.0f,
		-11.5f,  13.75f, 0.0f, 1.0f
	};

	unsigned int indicies[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray piece_va;
	VertexBuffer piece_vb(positions, 4 * 4 * sizeof(float));
	VertexBufferLayout piece_layout;
	piece_layout.Push<float>(2);
	piece_layout.Push<float>(2);
	piece_va.AddBuffer(piece_vb, piece_layout);

	VertexArray board_va;
	VertexBuffer board_vb(board_size, 4 * 4 * sizeof(float));
	VertexBufferLayout board_layout;
	board_layout.Push<float>(2);
	board_layout.Push<float>(2);
	board_va.AddBuffer(board_vb, board_layout);

	VertexArray pic_va;
	VertexBuffer pic_vb(pic_size, 4 * 4 * sizeof(float));
	VertexBufferLayout pic_layout;
	pic_layout.Push<float>(2);
	pic_layout.Push<float>(2);
	pic_va.AddBuffer(pic_vb, pic_layout);

	VertexArray single_va;
	VertexBuffer single_vb(single_size, 4 * 4 * sizeof(float));
	VertexBufferLayout single_layout;
	single_layout.Push<float>(2);
	single_layout.Push<float>(2);
	single_va.AddBuffer(single_vb, single_layout);

	VertexArray multi_va;
	VertexBuffer multi_vb(multi_size, 4 * 4 * sizeof(float));
	VertexBufferLayout multi_layout;
	multi_layout.Push<float>(2);
	multi_layout.Push<float>(2);
	multi_va.AddBuffer(multi_vb, multi_layout);

	VertexArray new_va;
	VertexBuffer new_vb(new_size, 4 * 4 * sizeof(float));
	VertexBufferLayout new_layout;
	new_layout.Push<float>(2);
	new_layout.Push<float>(2);
	new_va.AddBuffer(new_vb, new_layout);

	VertexArray import_va;
	VertexBuffer import_vb(import_size, 4 * 4 * sizeof(float));
	VertexBufferLayout import_layout;
	import_layout.Push<float>(2);
	import_layout.Push<float>(2);
	import_va.AddBuffer(import_vb, import_layout);

	VertexArray icon_va;
	VertexBuffer icon_vb(icon_size, 4 * 4 * sizeof(float));
	VertexBufferLayout icon_layout;
	icon_layout.Push<float>(2);
	icon_layout.Push<float>(2);
	icon_va.AddBuffer(icon_vb, icon_layout);

	VertexArray list_va;
	VertexBuffer list_vb(list_size, 4 * 4 * sizeof(float));
	VertexBufferLayout list_layout;
	list_layout.Push<float>(2);
	list_layout.Push<float>(2);
	list_va.AddBuffer(list_vb, list_layout);

	VertexArray notation_va;
	VertexBuffer notation_vb(notation_size, 4 * 4 * sizeof(float));
	VertexBufferLayout notation_layout;
	notation_layout.Push<float>(2);
	notation_layout.Push<float>(2);
	notation_va.AddBuffer(notation_vb, notation_layout);

	IndexBuffer ib(indicies, 6);

	Shader shader("res/shaders/Basic.shader");

	Renderer renderer;

	glm::mat4 proj = glm::ortho(0.0f, (float)SCREEN_WIDTH, 0.0f, (float)SCREEN_HEIGHT, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	shader.Unbind();

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));
	
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();
		glClearColor(1.0f, 1.0f, 0.5f, 1.0f);

		if (Game::getMode() == MENU1)
		{
			shader.Bind();
			pic.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(560, 455, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(pic_va, ib, shader);
			}

			single_word.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(560, 218, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(single_va, ib, shader);
			}

			multi_word.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(560, 112, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(multi_va, ib, shader);
			}
			shader.Unbind();

			if (Game::getValue() == 0)
			{
				Game::setValue(-1);
				Game::setMode(MENU2);
				single = true;
				// kick on minimax
				glfwSetMouseButtonCallback(window, menu2_mouse_button_callback);
				
			}
			else if (Game::getValue() == 1)
			{
				Game::setValue(-1);
				Game::setMode(MENU2);
				single = false;
				glfwSetMouseButtonCallback(window, menu2_mouse_button_callback);
			}
		}
		else if (Game::getMode() == MENU2)
		{
			shader.Bind();
			pic.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(560, 455, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(pic_va, ib, shader);
			}

			new_word.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(560, 218, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(new_va, ib, shader);
			}

			import_word.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(560, 112, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(import_va, ib, shader);
			}
			shader.Unbind();

			if (Game::getValue() == 0)
			{
				Game::setValue(-1);
				Game::setMode(GAME);
				glfwSetMouseButtonCallback(window, game_mouse_button_callback);
			}
			else if (Game::getValue() == 1)
			{
				Game::setValue(-1);
				if (chessnotation.ReadFromFile())
				{
					Game::setMode(GAME);
					glfwSetMouseButtonCallback(window, game_mouse_button_callback);
				}
				else
				{
					Game::setMode(MENU1);
					chessboard.init();
					glfwSetMouseButtonCallback(window, menu1_mouse_button_callback);
				}
			}
		}
		else if (Game::getMode() == GAME)
		{
			if (single && chessboard.color == AI_color)
			{
				int temp;
				if (AI_color == white)
				{
					temp = chessboard.Minimax_Min(AI_color, AI_DEPTH);
				}
				else
				{
					temp = chessboard.Minimax_Max(AI_color, AI_DEPTH);
				}
				Game::Update_Move(Pos(temp / 1000, (temp % 1000) / 100));
				Game::Update_Move(Pos((temp % 100) / 10, (temp % 10)));
				Game::ResetValues();
			}

			shader.Bind();
			board.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(560, 315, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(board_va, ib, shader);
			}

			gear.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1100, 610, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(icon_va, ib, shader);
			}
			shader.Unbind();

			Pos temp = chessboard.start_pos;
			if (temp != chessboard.NULL_POS)
			{
				shader.Bind();
				cover.Bind();
				shader.SetUniform1i("u_Texture", 0);
				{
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((temp.x + 1) * 70 + 245, (temp.y + 1) * 70, 0));
					glm::mat4 mvp = proj * view * model;
					shader.SetUniformMat4f("u_MVP", mvp);

					renderer.Draw(piece_va, ib, shader);
				}
				shader.Unbind();
			}

			int* pieces = (int*)chessboard.getPieces();
			for (int j = 0; j < 8; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					Pieces piece = *(Pieces*)((int*)pieces[i + j * 8]);
					if (piece.color == white)
					{
						switch (piece.type)
						{
						case king:
						{
							shader.Bind();
							white_king_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 245, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case queen:
						{
							shader.Bind();
							white_queen_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 245, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case bishop:
						{
							shader.Bind();
							white_bishop_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 245, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case knight:
						{
							shader.Bind();
							white_knight_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 245, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case rook:
						{
							shader.Bind();
							white_rook_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 245, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case pawn:
						{
							shader.Bind();
							white_pawn_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 245, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						default: break;
						}
					}
					else
					{
						switch (piece.type)
						{
						case king:
						{
							shader.Bind();
							black_king_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 245, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case queen:
						{
							shader.Bind();
							black_queen_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 245, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case bishop:
						{
							shader.Bind();
							black_bishop_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 245, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case knight:
						{
							shader.Bind();
							black_knight_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 245, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case rook:
						{
							shader.Bind();
							black_rook_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 245, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case pawn:
						{
							shader.Bind();
							black_pawn_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 245, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						default: break;
						}
					}
				}
			}

			if (Game::getValue() == 0)
			{
				Game::setValue(-1);
				Game::setMode(MENU1);
				chessboard.init();
				glfwSetMouseButtonCallback(window, menu1_mouse_button_callback);
			}

			if (Game::getWin())
			{
				MessageBox(NULL, chessboard.color == white ? "White Win" : "Black Win", chessboard.color == white ? "White Win" : "Black Win", MB_OK);
				Game::setMode(AFTER);
				glfwSetMouseButtonCallback(window, after_mouse_button_callback);
			}
		}
		else if (Game::getMode() == PROM)
		{
			glfwSetMouseButtonCallback(window, prom_mouse_button_callback);

			shader.Bind();
			if (chessboard.color == black)
			{
				white_queen_texture.Bind();
				shader.SetUniform1i("u_Texture", 0);
				{
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(420, 315, 0));
					glm::mat4 mvp = proj * view * model;
					shader.SetUniformMat4f("u_MVP", mvp);

					renderer.Draw(piece_va, ib, shader);
				}

				white_bishop_texture.Bind();
				shader.SetUniform1i("u_Texture", 0);
				{
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(490, 315, 0));
					glm::mat4 mvp = proj * view * model;
					shader.SetUniformMat4f("u_MVP", mvp);

					renderer.Draw(piece_va, ib, shader);
				}

				white_knight_texture.Bind();
				shader.SetUniform1i("u_Texture", 0);
				{
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(560, 315, 0));
					glm::mat4 mvp = proj * view * model;
					shader.SetUniformMat4f("u_MVP", mvp);

					renderer.Draw(piece_va, ib, shader);
				}

				white_rook_texture.Bind();
				shader.SetUniform1i("u_Texture", 0);
				{
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(630, 315, 0));
					glm::mat4 mvp = proj * view * model;
					shader.SetUniformMat4f("u_MVP", mvp);

					renderer.Draw(piece_va, ib, shader);
				}

				white_pawn_texture.Bind();
				shader.SetUniform1i("u_Texture", 0);
				{
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(700, 315, 0));
					glm::mat4 mvp = proj * view * model;
					shader.SetUniformMat4f("u_MVP", mvp);

					renderer.Draw(piece_va, ib, shader);
				}
			}
			else
			{
				black_queen_texture.Bind();
				shader.SetUniform1i("u_Texture", 0);
				{
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(420, 315, 0));
					glm::mat4 mvp = proj * view * model;
					shader.SetUniformMat4f("u_MVP", mvp);

					renderer.Draw(piece_va, ib, shader);
				}

				black_bishop_texture.Bind();
				shader.SetUniform1i("u_Texture", 0);
				{
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(490, 315, 0));
					glm::mat4 mvp = proj * view * model;
					shader.SetUniformMat4f("u_MVP", mvp);

					renderer.Draw(piece_va, ib, shader);
				}

				black_knight_texture.Bind();
				shader.SetUniform1i("u_Texture", 0);
				{
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(560, 315, 0));
					glm::mat4 mvp = proj * view * model;
					shader.SetUniformMat4f("u_MVP", mvp);

					renderer.Draw(piece_va, ib, shader);
				}

				black_rook_texture.Bind();
				shader.SetUniform1i("u_Texture", 0);
				{
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(630, 315, 0));
					glm::mat4 mvp = proj * view * model;
					shader.SetUniformMat4f("u_MVP", mvp);

					renderer.Draw(piece_va, ib, shader);
				}

				black_pawn_texture.Bind();
				shader.SetUniform1i("u_Texture", 0);
				{
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(700, 315, 0));
					glm::mat4 mvp = proj * view * model;
					shader.SetUniformMat4f("u_MVP", mvp);

					renderer.Draw(piece_va, ib, shader);
				}
			}
			shader.Unbind();

			if (Game::getValue() > -1)
			{
				chessboard.Promotion(Game::getPos(), Type(Game::getValue()));
				Game::setValue(-1);
				Game::setMode(GAME);
				glfwSetMouseButtonCallback(window, game_mouse_button_callback);
			}
		}
		else if (Game::getMode() == AFTER)
		{
			shader.Bind();
			board.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(365, 315, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(board_va, ib, shader);
			}

			gear.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1100, 610, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(icon_va, ib, shader);
			}

			save.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1060, 610, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(icon_va, ib, shader);
			}

			right.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1020, 610, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(icon_va, ib, shader);
			}

			left.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(980, 610, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(icon_va, ib, shader);
			}
			shader.Unbind();

			int* pieces = (int*)chessboard.getPieces();
			for (int j = 0; j < 8; j++)
			{
				for (int i = 0; i < 8; i++)
				{
					Pieces piece = *(Pieces*)((int*)pieces[i + j * 8]);
					if (piece.color == white)
					{
						switch (piece.type)
						{
						case king:
						{
							shader.Bind();
							white_king_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 50, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case queen:
						{
							shader.Bind();
							white_queen_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 50, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case bishop:
						{
							shader.Bind();
							white_bishop_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 50, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case knight:
						{
							shader.Bind();
							white_knight_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 50, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case rook:
						{
							shader.Bind();
							white_rook_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 50, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case pawn:
						{
							shader.Bind();
							white_pawn_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 50, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						default: break;
						}
					}
					else
					{
						switch (piece.type)
						{
						case king:
						{
							shader.Bind();
							black_king_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 50, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case queen:
						{
							shader.Bind();
							black_queen_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 50, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case bishop:
						{
							shader.Bind();
							black_bishop_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 50, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case knight:
						{
							shader.Bind();
							black_knight_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 50, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case rook:
						{
							shader.Bind();
							black_rook_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 50, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						case pawn:
						{
							shader.Bind();
							black_pawn_texture.Bind();
							shader.SetUniform1i("u_Texture", 0);
							{
								glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3((i + 1) * 70 + 50, (j + 1) * 70, 0));
								glm::mat4 mvp = proj * view * model;
								shader.SetUniformMat4f("u_MVP", mvp);

								renderer.Draw(piece_va, ib, shader);
							}
							shader.Unbind();
							break;
						};
						default: break;
						}
					}
				}
			}

			shader.Bind();
			list_bg.Bind();
			shader.SetUniform1i("u_Texture", 0);
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(950, 295, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);

				renderer.Draw(list_va, ib, shader);
			}
			shader.Unbind();

			int start;
			int end = chessnotation.length;
			
			start = end - 14;
			if (start < 0)
				start = 0;

			shader.Bind();
			for (int i = start; i < end; i++)
			{
				bool flag = false;
				int j = 0;
				if (int(chessnotation.list[i][j]) >= int('A') && int(chessnotation.list[i][j]) <= int('Z'))
				{
					j += 1;
					flag = true;
				}

				for (j; j < chessnotation.list_length[i]; j++)
				{
					switch (chessnotation.list[i][j])
					{
					case '0': zero.Bind(); break;
					case '1': one.Bind(); break;
					case '2': two.Bind(); break;
					case '3': three.Bind(); break;
					case '4': four.Bind(); break;
					case '5': five.Bind(); break;
					case '6': six.Bind(); break;
					case '7': seven.Bind(); break;
					case '8': eight.Bind(); break;
					case 'a': a.Bind(); break;
					case 'b': b.Bind(); break;
					case 'c': c.Bind(); break;
					case 'd': d.Bind(); break;
					case 'e': e.Bind(); break;
					case 'f': f.Bind(); break;
					case 'g': g.Bind(); break;
					case 'h': h.Bind(); break;
					case '-': dash.Bind(); break;
					}
					shader.SetUniform1i("u_Texture", 0);
					{
						glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(900 + ((j - (flag ? 2 : 1)) * 26), 495 - ((i - 1) * 37), 0));
						glm::mat4 mvp = proj * view * model;
						shader.SetUniformMat4f("u_MVP", mvp);

						renderer.Draw(notation_va, ib, shader);
					}
				}
			}
			shader.Unbind();

			if (Game::getValue() == 0)
			{
				Game::setValue(-1);
				Game::setMode(MENU1);
				Game::setWin(false);
				chessnotation.clear();
				chessboard.init();
				glfwSetMouseButtonCallback(window, menu1_mouse_button_callback);
			}
			else if (Game::getValue() == 1)
			{
				chessnotation.WriteOutFile();
			}
			else if (Game::getValue() == 2 && timer == 0)
			{
				timer = 100;
				glfwSetMouseButtonCallback(window, NULL);
				chessnotation.forward();
			}
			else if (Game::getValue() == 3 && timer == 0)
			{
				timer = 100;
				glfwSetMouseButtonCallback(window, NULL);
				chessnotation.backward();
			}

			if (timer == 1)
				glfwSetMouseButtonCallback(window, after_mouse_button_callback);
		}

		if (timer != 0)
			timer -= 1;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}