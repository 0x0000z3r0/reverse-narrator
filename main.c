#include <raylib.h>

int
main(void)
{
  const int screen_width = 800;
  const int screen_height = 450;
  
  InitWindow(screen_width, screen_height, "Reverse Narrator");
  SetTargetFPS(20);

  Texture2D screen_background = LoadTexture("images/1.png"); 

  const char *menu_options[] = { "start", "exit" };
  const int menu_options_max = sizeof (menu_options) / sizeof (menu_options[0]);
  int menu_selection = 0;
  
  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_DOWN)) {
      menu_selection++;
      if (menu_selection >= menu_options_max) {
          menu_selection = 0;
      }
    }

    if (IsKeyPressed(KEY_UP)) {
      menu_selection--;
      if (menu_selection < 0) {
          menu_selection = menu_options_max - 1;
      }
    }
    
    if (IsKeyPressed(KEY_ENTER)) {
      if (menu_selection == 1) {
        goto _EXIT;
      }
    }

    BeginDrawing();
    ClearBackground(BLACK); 
    DrawTextureEx(screen_background, (Vector2){ 0, 0 }, 0, 0.3, WHITE);
    DrawTextEx(GetFontDefault(), "RE//VERSE Narrator", (Vector2){ 360, 30 }, 20, 10, WHITE);
    for (int i = 0; i < menu_options_max; ++i) {
      int font_size = 15;
      if (menu_selection == i) {
        font_size = 18;
      }
      DrawTextEx(GetFontDefault(), menu_options[i], (Vector2){ 380, 100 + 30 * i }, font_size, 10, WHITE);
    }
    EndDrawing();
  }
  
_EXIT:
  UnloadTexture(screen_background);
  CloseWindow();
  
  return 0;
}

