#include <raylib.h>
#include <stdlib.h>
#include <string.h>

static int
cmp_file_paths(const void *a, const void *b)
{
	const char *path_a = *(const char **)a;
	const char *path_b = *(const char **)b;
	return strcmp(path_a, path_b);
}

int
main(void)
{
	const int screen_width = 900;
	const int screen_height = 450;

	InitWindow(screen_width, screen_height, "Reverse Narrator");
	SetTargetFPS(20);

	Texture2D screen_background = LoadTexture("assets/background.png");

	enum { CHAPTER_MENU, CHAPTER_0, CHAPTER_1, CHAPTER_MAX };
	const char *chapter_text[CHAPTER_MAX] = {"", "chapter 0", "chapter 1"};
	int chapter_selection = CHAPTER_MENU;

	FilePathList chapter0_files = LoadDirectoryFilesEx("assets/chapter0", ".png", false);
	qsort(chapter0_files.paths, chapter0_files.count, sizeof(char *), cmp_file_paths);

	struct chapter_context {
		Texture2D slides[6];
		float slides_alpha[6];
		Vector2 slides_postions[6];
		float slides_scale[6];
		int slides_count;
	};

	struct chapter_context chapter0_context;
	memset(&chapter0_context, 0, sizeof(chapter0_context));
	chapter0_context.slides_count = chapter0_files.count;
	for (int i = 0; i < chapter0_context.slides_count; ++i) {
		chapter0_context.slides[i] = LoadTexture(chapter0_files.paths[i]);
	}
	chapter0_context.slides_postions[0].x = 5.0f;
	chapter0_context.slides_postions[0].y = 10.0f;
	chapter0_context.slides_scale[0] = 0.285f;
	chapter0_context.slides_postions[1].x = 300.0f;
	chapter0_context.slides_postions[1].y = 10.0f;
	chapter0_context.slides_scale[1] = 0.285f;
	chapter0_context.slides_postions[2].x = 600.0f;
	chapter0_context.slides_postions[2].y = 10.0f;
	chapter0_context.slides_scale[2] = 0.285f;
	chapter0_context.slides_postions[3].x = 5.0f;
	chapter0_context.slides_postions[3].y = 10.0f;
	chapter0_context.slides_scale[3] = 0.285f;
	chapter0_context.slides_postions[4].x = 300.0f;
	chapter0_context.slides_postions[4].y = 10.0f;
	chapter0_context.slides_scale[4] = 0.285f;
	chapter0_context.slides_postions[5].x = 600.0f;
	chapter0_context.slides_postions[5].y = 10.0f;
	chapter0_context.slides_scale[5] = 0.285f;

	UnloadDirectoryFiles(chapter0_files);

	float *slide_alpha = NULL;

	enum { MENU_START, MENU_EXIT, MENU_MAX };
	const char *menu_options[MENU_MAX] = {"start", "exit"};
	int menu_selection = MENU_START;

	while (!WindowShouldClose()) {
		if (slide_alpha != NULL) {
			*slide_alpha += 0.35f * GetFrameTime();
			if (*slide_alpha > 1.0f)
				*slide_alpha = 1.0f;
		}

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

		if (IsKeyPressed(KEY_M)) {
			chapter_selection = CHAPTER_MENU;
		}

		if (IsKeyPressed(KEY_S)) {
			if (slide_alpha != NULL) {
				*slide_alpha = 1.0f;
			}
		}

		if (IsKeyPressed(KEY_ENTER)) {
			switch (menu_selection) {
			case MENU_START:
				if (slide_alpha != NULL) {
					*slide_alpha = 0.0f;
				}
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
			const int hint_offset = 410;
			DrawTextEx(GetFontDefault(), "[M] go to menu", (Vector2){310, hint_offset}, 10, 5, WHITE);
			DrawTextEx(GetFontDefault(), "[S] skip the animation", (Vector2){310, hint_offset + 10}, 10, 5,
				   WHITE);
			DrawTextEx(GetFontDefault(), "[Esc] exit the game", (Vector2){310, hint_offset + 20}, 10, 5,
				   WHITE);
			break;
		}
		case CHAPTER_0: {
			if (slide_alpha == NULL) {
				slide_alpha = &chapter0_context.slides_alpha[0];
			} else if (*slide_alpha >= 1.0f) {
				if (slide_alpha <= &chapter0_context.slides_alpha[chapter0_context.slides_count - 1]) {
					++slide_alpha;
				}
			}
			DrawTextEx(GetFontDefault(), chapter_text[CHAPTER_0], (Vector2){20, 20}, 20, 10, WHITE);
			for (int i = 0; i < chapter0_files.count; ++i) {
				DrawTextureEx(chapter0_context.slides[i], chapter0_context.slides_postions[i], 0,
					      chapter0_context.slides_scale[i],
					      Fade(WHITE, chapter0_context.slides_alpha[i]));
			}

			break;
		}
		default:
			goto _EXIT;
		}
		EndDrawing();
	}

_EXIT:
	for (int i = 0; i < chapter0_files.count; ++i) {
		UnloadTexture(chapter0_context.slides[i]);
	}
	UnloadTexture(screen_background);
	CloseWindow();

	return 0;
}
