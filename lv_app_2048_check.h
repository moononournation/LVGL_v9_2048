static int w, h, margin;
static int board_size, board_y, board_size_4;
static int tile_size_m, tile_size_m2, tile_size, tile_offset;
static lv_obj_t *board;
static lv_obj_t *tile_obj[4][4];
#ifdef DEBUG_MODE
static int tile_val[4][4] = {
    {2, 2, 4, 8},
    {16, 32, 64, 128},
    {256, 512, 1024, 2048},
    {4096, 8192, 16384, 32768}};
#else
static int tile_val[4][4] = {0};
#endif
static lv_dir_t last_gesture_dir = LV_DIR_NONE;
static int last_handle_idx;

static bool lv_app_2048_check_h_movable(lv_dir_t dir)
{
  for (int y = 0; y < 4; y++)
  {
    if (dir == LV_DIR_LEFT)
    {
      if (((tile_val[y][0] == 0) && (tile_val[y][1] > 0)) || ((tile_val[y][1] == 0) && (tile_val[y][2] > 0)) || ((tile_val[y][2] == 0) && (tile_val[y][3] > 0)))
      {
        return true;
      }
    }
    else if (dir == LV_DIR_RIGHT)
    {
      if (((tile_val[y][3] == 0) && (tile_val[y][2] > 0)) || ((tile_val[y][2] == 0) && (tile_val[y][1] > 0)) || ((tile_val[y][1] == 0) && (tile_val[y][0] > 0)))
      {
        return true;
      }
    }
    for (int x = 0; x < 3; x++)
    {
      if ((tile_val[y][x] > 0) && (tile_val[y][x] == tile_val[y][x + 1]))
      {
        return true;
      }
    }
  }
  return false;
}

static bool lv_app_2048_check_v_movable(lv_dir_t dir)
{
  for (int x = 0; x < 4; x++)
  {
    if (dir == LV_DIR_TOP)
    {
      if (((tile_val[0][x] == 0) && (tile_val[1][x] > 0)) || ((tile_val[1][x] == 0) && (tile_val[2][x] > 0)) || ((tile_val[2][x] == 0) && (tile_val[3][x] > 0)))
      {
        return true;
      }
    }
    else if (dir == LV_DIR_BOTTOM)
    {
      if (((tile_val[3][x] == 0) && (tile_val[2][x] > 0)) || ((tile_val[2][x] == 0) && (tile_val[1][x] > 0)) || ((tile_val[1][x] == 0) && (tile_val[0][x] > 0)))
      {
        return true;
      }
    }
    for (int y = 0; y < 3; y++)
    {
      if ((tile_val[y][x] > 0) && (tile_val[y][x] == tile_val[y + 1][x]))
      {
        return true;
      }
    }
  }
  return false;
}

static void lv_app_2048_check_tile_val()
{
  for (int y = 0; y < 4; y++)
  {
    Serial.printf("%d, %d, %d, %d\n", tile_val[y][0], tile_val[y][1], tile_val[y][2], tile_val[y][3]);
  }
}
