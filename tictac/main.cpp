#include "include/raylib.h"
#include <iostream>

const int WIDTH = 600;
const int HEIGHT = 400;
const int SIZE = 9;
const char *WINDOW_TITLE = "Tic Tac Toe";
const char *SCREEN_TEXT = "BEST TIC TAC TOE X(YOU) O(COMPUTER)";

enum Play
{
	EMPTY,
	X,
	O,
};

struct GameState
{
	Rectangle rec;
	Play play = Play::EMPTY;
	Color color = BEIGE;

	bool update(Play p, Vector2 point)
	{
		if (play == Play::EMPTY && CheckCollisionPointRec(point, rec))
		{
			play = p;
			return true;
		}
		return false;
	}

	void draw()
	{
		DrawRectangleRec(rec, color);
		float x = rec.x + rec.width / 2 - 15;
		float y = rec.y + rec.height / 2 - 20;
		if (play == Play::EMPTY)
			return;
		DrawText(
				(play == Play::X) ? "X" : "O",
				x,	// pos X
				y,	// pos y
				45, // Font size
				WHITE);
	}
};

void init_game_state(GameState board[SIZE])
{
	float x = 120;
	float st_x = x;
	float st_y = 10;
	float width = 70;
	float height = 80;
	for (int i = 0; i < SIZE; ++i)
	{
		if (i % 3 == 0)
		{
			st_x = x;
			st_y += (height + 2);
		}
		board[i] = GameState{Rectangle{st_x, st_y, width, height}};
		st_x += (width + 2);
	}
}

// Dumb gpt move
int get_ai_move(GameState board[SIZE])
{
	for (int i = 0; i < SIZE; ++i)
	{
		if (board[i].play == Play::EMPTY)
			return i;
	}
}

bool is_game_in_progress(GameState board[SIZE])
{
	for (int i = 0; i < SIZE; ++i)
	{
		if (board[i].play == Play::EMPTY)
			return true;
	}
	return false;
}

/*
0 1 2
3 4 5
6 7 8
*/
Play check_winner(GameState board[SIZE])
{
	Color win_color = MAROON;
	// Check columns
	for (int i = 0; i < 3; ++i)
	{
		if ((board[i].play != Play::EMPTY) && (board[i].play == board[i + 3].play) && (board[i + 3].play == board[i + 6].play))
		{
			board[i].color = win_color;
			board[i + 3].color = win_color;
			board[i + 6].color = win_color;
			return board[i].play;
		}
	}

	// Check rows
	int i = 0;
	while (i <= 6)
	{
		if ((board[i].play != Play::EMPTY) && (board[i].play == board[i + 1].play) && (board[i + 1].play == board[i + 2].play))
		{
			board[i].color = win_color;
			board[i + 1].color = win_color;
			board[i + 2].color = win_color;
			return board[i].play;
		}
		i = i + 3;
	}

	// Check diagonals
	if ((board[0].play != Play::EMPTY) && (board[0].play == board[4].play) && (board[4].play == board[8].play))
	{
		board[0].color = win_color;
		board[4].color = win_color;
		board[8].color = win_color;
		return board[0].play;
	}

	if ((board[2].play != Play::EMPTY) && (board[2].play == board[4].play) && (board[4].play == board[6].play))
	{
		board[2].color = win_color;
		board[4].color = win_color;
		board[6].color = win_color;
		return board[2].play;
	}
	return Play::EMPTY;
}

int main(void)
{
	GameState board[SIZE];
	init_game_state(board);
	InitWindow(WIDTH, HEIGHT, WINDOW_TITLE);
	bool ai_turn = false;
	bool game_in_progress = true;
	Sound music;

	InitAudioDevice();
	if (IsAudioDeviceReady())
	{
		std::cout << "Audio device is ready" << std::endl;
		Wave wav = LoadWave("tictac/resources/fun.wav");
		music = LoadSoundFromWave(wav);
		PlaySound(music);
	}

	while (!WindowShouldClose())
	{
		if (!IsSoundPlaying(music))
		{
			PlaySound(music);
		}

		BeginDrawing();
		ClearBackground(LIGHTGRAY);

		// Draw decoration
		int st = 10;
		int width = WIDTH - 2 * st;
		int height = HEIGHT - 2 * st;

		for (int i = 0; i < 6; ++i)
		{
			DrawRectangleLines(st, st, width, height, BLUE);
			st += 1;
			width -= 2;
			height -= 2;
		}
		// End of decoration

		Play winner = check_winner(board);
		game_in_progress = (winner == Play::EMPTY) && is_game_in_progress(board);

		// Status Text
		if (!game_in_progress)
		{

			DrawText(
					"PRESS R TO\n\nRESTART",
					360, // pos X
					180, // pos y
					30,	 // Font size
					MAROON);
			int key_pressed = GetCharPressed();
			if (key_pressed == 'R' || key_pressed == 'r')
			{
				init_game_state(board);
				ai_turn = false;
				game_in_progress = true;
			}

			const char *win_text = (winner == Play::X) ? "YOU WON!!!" : "YOU LOST!!!";
			DrawText(
					win_text,
					160,
					350,
					25,
					LIME);
		}

		// Draw board
		for (int i = 0; i < SIZE; ++i)
		{
			board[i].draw();
		}
		// End of board

		if (game_in_progress && !ai_turn)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				Vector2 pos = GetMousePosition();
				for (int i = 0; i < SIZE; ++i)
				{
					if (board[i].update(Play::X, pos))
					{
						board[i].draw();
						ai_turn = true;
						break;
					}
				}
			}
		}
		else if (game_in_progress && ai_turn)
		{
			WaitTime(0.5);
			int idx = get_ai_move(board);
			board[idx].play = Play::O;
			ai_turn = false;
		}

		DrawText(
				SCREEN_TEXT,
				120, // pos X
				20,	 // pos y
				15,	 // Font size
				LIME);
		DrawCircle(GetTouchX(), GetTouchY(), 8, LIME);
		EndDrawing();
	}
	CloseAudioDevice();
	CloseWindow();
	return 0;
}
