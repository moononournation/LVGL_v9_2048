#define RIGHT_MOVABLE_BIT 0b0001
#define BOTTOM_MOVABLE_BIT 0b0010
#define TOP_MOVABLE_BIT 0b0100
#define LEFT_MOVABLE_BIT 0b1000

static int w, h, margin;
static int score_tile_w, board_size, board_y, board_size4;
static int tile_size_m, tile_size_m2, tile_size, tile_offset;
static lv_obj_t *score_label;
static lv_obj_t *best_label;
static lv_obj_t *board;
static lv_obj_t *tile_obj[4][4];
#ifdef DEBUG_MODE
static int tile_val[4][4] = {
    {2, 2, 4, 8},
    {16, 32, 64, 128},
    {256, 512, 1024, 2048},
    {4096, 8192, 16384, 32768}};
static int curr_score = 130992;
static int best_score = 130992;
#else
static int tile_val[4][4] = {0};
static int curr_score = 0;
static int best_score = 4092;
#endif
static lv_dir_t last_gesture_dir = LV_DIR_NONE;
static byte movable;
static int last_handle_idx;

static void lv_app_2048_check_movable()
{
  movable = 0;
  // loop rows
  for (int y = 0; y < 4; y++)
  {
    if (((tile_val[y][0] == 0) && (tile_val[y][1] > 0)) || ((tile_val[y][1] == 0) && (tile_val[y][2] > 0)) || ((tile_val[y][2] == 0) && (tile_val[y][3] > 0)))
    {
      movable |= LEFT_MOVABLE_BIT;
    }
    if (((tile_val[y][3] == 0) && (tile_val[y][2] > 0)) || ((tile_val[y][2] == 0) && (tile_val[y][1] > 0)) || ((tile_val[y][1] == 0) && (tile_val[y][0] > 0)))
    {
      movable |= RIGHT_MOVABLE_BIT;
    }
    for (int x = 0; x < 3; x++)
    {
      if ((tile_val[y][x] > 0) && (tile_val[y][x] == tile_val[y][x + 1]))
      {
        movable |= LEFT_MOVABLE_BIT | RIGHT_MOVABLE_BIT;
      }
    }
  }
  // loop columns
  for (int x = 0; x < 4; x++)
  {
    if (((tile_val[0][x] == 0) && (tile_val[1][x] > 0)) || ((tile_val[1][x] == 0) && (tile_val[2][x] > 0)) || ((tile_val[2][x] == 0) && (tile_val[3][x] > 0)))
    {
      movable |= TOP_MOVABLE_BIT;
    }
    if (((tile_val[3][x] == 0) && (tile_val[2][x] > 0)) || ((tile_val[2][x] == 0) && (tile_val[1][x] > 0)) || ((tile_val[1][x] == 0) && (tile_val[0][x] > 0)))
    {
      movable |= BOTTOM_MOVABLE_BIT;
    }
    for (int y = 0; y < 3; y++)
    {
      if ((tile_val[y][x] > 0) && (tile_val[y][x] == tile_val[y + 1][x]))
      {
        movable |= TOP_MOVABLE_BIT | BOTTOM_MOVABLE_BIT;
      }
    }
  }
}

static void lv_app_2048_check_tile_val()
{
  for (int y = 0; y < 4; y++)
  {
    Serial.printf("%d, %d, %d, %d\n", tile_val[y][0], tile_val[y][1], tile_val[y][2], tile_val[y][3]);
  }
}
