#include <raylib.h>

int
main(void)
{
	const int screen_width = 800;
	const int screen_height = 450;

	InitWindow(screen_width, screen_height, "Reverse Narrator");
	SetTargetFPS(20);

	Texture2D screen_background = LoadTexture("images/1.png");

	enum { CHAPTER_MENU, CHAPTER_0, CHAPTER_1, CHAPTER_MAX };
	const char *chapter_text[CHAPTER_MAX] = {"chapter 0", "chapter 1"};
	int chapter_selection = CHAPTER_MENU;

	Texture2D chapter0_slide0 = LoadTexture("images/2.png");
	Texture2D chapter0_slide1 = LoadTexture("images/3.png");

	float slide_alpha = 0.0f;

	enum { MENU_START, MENU_EXIT, MENU_MAX };
	const char *menu_options[MENU_MAX] = {"start", "exit"};
	int menu_selection = MENU_START;

	while (!WindowShouldClose()) {
		slide_alpha += 0.1f * GetFrameTime();
		if (slide_alpha > 1.0f)
			slide_alpha = 1.0f;

		if (IsKeyPressed(KEY_DOWN)) {
			menu_selection++;
			if (menu_selection >= MENU_MAX) {
				menu_selection = 0;
			}
		}

		if (IsKeyPressed(KEY_UP)) {
			menu_selection--;
			if (menu_selection < 0) {
				menu_selection = MENU_MAX - 1;
			}
		}

		if (IsKeyPressed(KEY_ESCAPE)) {
			chapter_selection = CHAPTER_MENU;
		}

		if (IsKeyPressed(KEY_ENTER)) {
			switch (menu_selection) {
			case MENU_START:
				chapter_selection = CHAPTER_0;
				break;
			case MENU_EXIT:
				goto _EXIT;
			default:
				goto _EXIT;
			}
		}

		BeginDrawing();
		ClearBackground(BLACK);
		switch (chapter_selection) {
		case CHAPTER_MENU: {
			DrawTextureEx(screen_background, (Vector2){0, 0}, 0, 0.3, WHITE);
			DrawTextEx(GetFontDefault(), "RE//VERSE Narrator", (Vector2){360, 30}, 20, 10, WHITE);
			for (int i = 0; i < MENU_MAX; ++i) {
				int font_size = 15;
				if (menu_selection == i) {
					font_size = 19;
				}
				DrawTextEx(GetFontDefault(), menu_options[i], (Vector2){380, 100 + 30 * i}, font_size,
					   10, WHITE);
			}
			break;
		}
		case CHAPTER_0: {
			DrawTextEx(GetFontDefault(), chapter_text[CHAPTER_0], (Vector2){20, 20}, 20, 10, WHITE);
			DrawTextureEx(chapter0_slide0, (Vector2){0, 0}, 0, 0.3, Fade(WHITE, slide_alpha));
			DrawTextureEx(chapter0_slide1, (Vector2){400, 0}, 0, 0.3, Fade(WHITE, slide_alpha));
			break;
		}
		default:
			goto _EXIT;
		}
		EndDrawing();
	}

_EXIT:
	UnloadTexture(chapter0_slide0);
	UnloadTexture(chapter0_slide1);
	UnloadTexture(screen_background);
	CloseWindow();

	return 0;
}
