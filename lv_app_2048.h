#include "lv_app_2048_check.h"
#include "lv_app_2048_set_tile.h"
#include "lv_app_2048_anim.h"

void lv_app_2048_record_gesture(lv_event_t *e)
{
  // lv_obj_t *screen = (lv_obj_t *)lv_event_get_current_target(e);
  last_gesture_dir = lv_indev_get_gesture_dir(lv_indev_active());
}

void lv_app_2048_record_score_tile_click(lv_event_t *e)
{
  if (!isPlaying)
  {
    score_tile_clicked = true;
  }
}

static void lv_app_2048_new_tile(int i)
{
  popnew_objs.anim_count = 0;

  bool has_empty = true;
  while (has_empty)
  {
    has_empty = false;
    for (int y = 0; y < 4; y++)
    {
      for (int x = 0; x < 4; x++)
      {
        if (tile_val[y][x] == 0)
        {
          has_empty = true;
          int r = random(80);
          if (r <= 4)
          {
            int new_value = (r == 4) ? 4 : 2;
#ifdef DEBUG_MODE
            Serial.printf("new: [%d,%d] = %d\n", x, y, new_value);
#endif
            lv_obj_t *new_tile = lv_obj_create(board);
            tile_obj[y][x] = new_tile;
            tile_val[y][x] = new_value;
            lv_obj_remove_flag(new_tile, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_border_width(new_tile, 0, LV_PART_MAIN);
            lv_obj_set_size(new_tile, 0, 0);
            lv_obj_align(new_tile, LV_ALIGN_CENTER, (x * tile_size_m) + tile_offset, (y * tile_size_m) + tile_offset);
            lv_obj_t *new_label = lv_label_create(new_tile);
            lv_obj_align(new_label, LV_ALIGN_CENTER, 0, 0);
            lv_app_2048_set_tile(new_tile, new_label, new_value);

            lv_app_2048_pop_obj(x, y);

            if (popnew_objs.anim_count == i)
            {
              return;
            }
          }
        }
      }
    }
  }
}

static void lv_app_2048_display_score()
{
  if (curr_score > best_score)
  {
    best_score = curr_score;
  }

  lv_label_set_text_fmt(score_label, "%d", curr_score);
  lv_obj_set_style_text_font(score_label, lv_app_2048_get_font(score_tile_w, curr_score), LV_PART_MAIN);
  lv_label_set_text_fmt(best_label, "%d", best_score);
  lv_obj_set_style_text_font(best_label, lv_app_2048_get_font(score_tile_w, best_score), LV_PART_MAIN);
}

static bool lv_app_2048_handle_gesture()
{
  if (last_gesture_dir == LV_DIR_NONE)
  {
    return false;
  }

  // init value
  lv_app_2048_anim_reset();
  move_objs.dir = last_gesture_dir;

  int last_merged_idx;
  lv_obj_t *tmp_tile[4];
  switch (last_gesture_dir)
  {
  case LV_DIR_LEFT:
#ifdef DEBUG_MODE
    Serial.println("LV_DIR_LEFT");
#endif
    if ((movable & LEFT_MOVABLE_BIT) == 0)
    {
      last_gesture_dir = LV_DIR_NONE;
      return false;
    }
    for (int y = 0; y < 4; y++) // loop rows from top to bottom
    {
      last_handle_idx = -1; // init to outside value
      last_merged_idx = -1; // init to outside value

      for (int x = 0; x < 4; x++) // loop cells for each row from left to right
      {
        if (tile_val[y][x] > 0) // if cell not empty
        {
          if ((last_handle_idx == last_merged_idx)                 // not merge first tile or just merged tile
              || (tile_val[y][x] != tile_val[y][last_handle_idx])) // not same number, not merge
          {
            if (x > (last_handle_idx + 1)) // require move
            {
#ifdef DEBUG_MODE
              Serial.printf("move: [%d,%d] -> [%d,%d]\n", x, y, last_handle_idx + 1, y);
#endif
              lv_app_2048_move_obj(x, y, last_handle_idx + 1, y, x, x - (last_handle_idx + 1));
            }
            last_handle_idx++;
          }
          else // same number, merge
          {
#ifdef DEBUG_MODE
            Serial.printf("merge: [%d,%d], [%d,%d]\n", x, y, last_handle_idx, y);
#endif
            lv_app_2048_merge_objs(x, y, last_handle_idx, y, x, x - last_handle_idx);
            last_merged_idx = last_handle_idx;
          }
        }
      }
    }
    break;
  case LV_DIR_RIGHT:
#ifdef DEBUG_MODE
    Serial.println("LV_DIR_RIGHT");
#endif
    if ((movable & RIGHT_MOVABLE_BIT) == 0)
    {
      last_gesture_dir = LV_DIR_NONE;
      return false;
    }
    for (int y = 0; y < 4; y++) // loop rows from top to bottom
    {
      last_handle_idx = 4; // init to outside value
      last_merged_idx = 4; // init to outside value

      for (int x = 3; x > -1; x--) // loop cells for each row from right to left
      {
        if (tile_val[y][x] > 0) // if cell not empty
        {
          if ((last_handle_idx == last_merged_idx)                 // first tile or previous handled tile just merged, not merge
              || (tile_val[y][x] != tile_val[y][last_handle_idx])) // not same number, not merge
          {
            if (x < (last_handle_idx - 1)) // require move
            {
#ifdef DEBUG_MODE
              Serial.printf("move: [%d,%d] -> [%d,%d]\n", x, y, last_handle_idx - 1, y);
#endif
              lv_app_2048_move_obj(x, y, last_handle_idx - 1, y, x, (last_handle_idx - 1) - x);
            }
            last_handle_idx--;
          }
          else // same number, merge
          {
#ifdef DEBUG_MODE
            Serial.printf("merge: [%d,%d], [%d,%d]\n", x, y, last_handle_idx, y);
#endif
            lv_app_2048_merge_objs(x, y, last_handle_idx, y, x, last_handle_idx - x);
            last_merged_idx = last_handle_idx;
          }
        }
      }
    }
    break;
  case LV_DIR_TOP:
#ifdef DEBUG_MODE
    Serial.println("LV_DIR_TOP");
#endif
    if ((movable & TOP_MOVABLE_BIT) == 0)
    {
      last_gesture_dir = LV_DIR_NONE;
      return false;
    }
    for (int x = 0; x < 4; x++) // loop columns from left to right
    {
      last_handle_idx = -1; // init to outside value
      last_merged_idx = -1; // init to outside value

      for (int y = 0; y < 4; y++) // loop cells for each column from top to bottom
      {
        if (tile_val[y][x] > 0) // if cell not empty
        {
          if ((last_handle_idx == last_merged_idx)                 // first tile or previous handled tile just merged, not merge
              || (tile_val[y][x] != tile_val[last_handle_idx][x])) // not same number, not merge
          {
            if (y > (last_handle_idx + 1)) // require move
            {
#ifdef DEBUG_MODE
              Serial.printf("move: [%d,%d] -> [%d,%d]\n", x, y, x, last_handle_idx + 1);
#endif
              lv_app_2048_move_obj(x, y, x, last_handle_idx + 1, y, y - (last_handle_idx + 1));
            }
            last_handle_idx++;
          }
          else // same number, merge
          {
#ifdef DEBUG_MODE
            Serial.printf("merge: [%d,%d], [%d,%d]\n", x, y, x, last_handle_idx);
#endif
            lv_app_2048_merge_objs(x, y, x, last_handle_idx, y, y - last_handle_idx);
            last_merged_idx = last_handle_idx;
          }
        }
      }
    }
    break;
  case LV_DIR_BOTTOM:
#ifdef DEBUG_MODE
    Serial.println("LV_DIR_BOTTOM");
#endif
    if ((movable & BOTTOM_MOVABLE_BIT) == 0)
    {
      last_gesture_dir = LV_DIR_NONE;
      return false;
    }
    for (int x = 0; x < 4; x++) // loop columns from left to right
    {
      last_handle_idx = 4; // init to outside value
      last_merged_idx = 4; // init to outside value

      for (int y = 3; y > -1; y--) // loop cells for each column from bottom to top
      {
        if (tile_val[y][x] > 0) // if cell not empty
        {
          if ((last_handle_idx == last_merged_idx)                 // first tile or previous handled tile just merged, not merge
              || (tile_val[y][x] != tile_val[last_handle_idx][x])) // not same number, not merge
          {
            if (y < (last_handle_idx - 1)) // require move
            {
#ifdef DEBUG_MODE
              Serial.printf("move: [%d,%d] -> [%d,%d]\n", x, y, x, last_handle_idx - 1);
#endif
              lv_app_2048_move_obj(x, y, x, last_handle_idx - 1, y, (last_handle_idx - 1) - y);
            }
            last_handle_idx--;
          }
          else // same number, merge
          {
#ifdef DEBUG_MODE
            Serial.printf("merge: [%d,%d], [%d,%d]\n", x, y, x, last_handle_idx);
#endif
            lv_app_2048_merge_objs(x, y, x, last_handle_idx, y, last_handle_idx - y);
            last_merged_idx = last_handle_idx;
          }
        }
      }
    }
    break;
  }

  lv_app_2048_display_score();
  last_gesture_dir = LV_DIR_NONE;
  return true;
}

static void lv_app_2048_redraw_board_value()
{
  for (int y = 0; y < 4; y++)
  {
    for (int x = 0; x < 4; x++)
    {
      int value = tile_val[y][x];

      if (value)
      {
        lv_obj_t *cur_tile = lv_obj_create(board);
        tile_obj[y][x] = cur_tile;
        lv_obj_remove_flag(cur_tile, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_set_style_border_width(cur_tile, 0, LV_PART_MAIN);
        lv_obj_set_size(cur_tile, tile_size, tile_size);
        lv_obj_align(cur_tile, LV_ALIGN_CENTER, (x * tile_size_m) + tile_offset, (y * tile_size_m) + tile_offset);

        lv_obj_t *tile_label = lv_label_create(cur_tile);
        lv_obj_align(tile_label, LV_ALIGN_CENTER, 0, 0);

        lv_app_2048_set_tile(cur_tile, tile_label, value);
      }
      else
      {
        if (tile_obj[y][x])
        {
          lv_obj_delete(tile_obj[y][x]);
          tile_obj[y][x] = NULL;
        }
      }
    }
  }
}

static void lv_app_2048(lv_obj_t *scr)
{
  w = lv_obj_get_width(scr);
  h = lv_obj_get_height(scr);
  margin = w / 32;
  if (margin < 4)
  {
    margin = 4;
  }
  board_size = w;
  board_y = (w - h) / 2;
  board_size4 = board_size / 4;
  tile_size = board_size4 - margin;

  int h6 = h / 6;
  if (tile_size > h6)
  {
    tile_size = h6;
  }
  tile_size_m = tile_size + ((board_size4 - tile_size) / 2);
  tile_size_m2 = tile_size_m / 2;
  tile_offset = tile_size_m2 - tile_size_m - tile_size_m;

  lv_obj_set_style_bg_color(scr, lv_color_hex(0x000000), LV_PART_MAIN);
  lv_obj_remove_flag(scr, LV_OBJ_FLAG_SCROLLABLE);

  lv_obj_t *title_tile = lv_obj_create(scr);
  lv_obj_remove_flag(title_tile, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(title_tile, lv_color_hex(TILE_2048), LV_PART_MAIN);
  lv_obj_set_style_border_width(title_tile, 0, LV_PART_MAIN);
  lv_obj_set_size(title_tile, tile_size, tile_size);
  lv_obj_set_pos(title_tile, 0, 0);

  lv_obj_t *title_label = lv_label_create(title_tile);
  lv_obj_align(title_label, LV_ALIGN_CENTER, 0, 0);
  lv_app_2048_set_tile(title_tile, title_label, 2048);

  score_tile_w = ((w - tile_size - tile_size_m2) / 2) - margin;
  score_tile = lv_obj_create(scr);
  lv_obj_remove_flag(score_tile, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(score_tile, lv_color_hex(BOARD_BG), LV_PART_MAIN);
  lv_obj_set_style_border_width(score_tile, 0, LV_PART_MAIN);
  lv_obj_set_size(score_tile, score_tile_w, tile_size);
  lv_obj_set_pos(score_tile, w - score_tile_w - margin - score_tile_w, 0);
  lv_obj_add_event_cb(score_tile, lv_app_2048_record_score_tile_click, LV_EVENT_CLICKED, NULL);

  lv_obj_t *score_title_label = lv_label_create(score_tile);
  lv_label_set_text(score_title_label, "SCORE");
  lv_obj_set_style_text_color(score_title_label, lv_color_hex(SCORE_TEXT), LV_PART_MAIN);
  lv_obj_set_style_text_font(score_title_label, &lv_font_montserrat_18, LV_PART_MAIN);
  lv_obj_align(score_title_label, LV_ALIGN_CENTER, 0, -24);

  score_label = lv_label_create(score_tile);
  lv_obj_set_style_text_color(score_label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
  lv_obj_align(score_label, LV_ALIGN_CENTER, 0, tile_size / 6);

  lv_obj_t *best_tile = lv_obj_create(scr);
  lv_obj_remove_flag(best_tile, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(best_tile, lv_color_hex(BOARD_BG), LV_PART_MAIN);
  lv_obj_set_style_border_width(best_tile, 0, LV_PART_MAIN);
  lv_obj_set_size(best_tile, score_tile_w, tile_size);
  lv_obj_set_pos(best_tile, w - score_tile_w, 0);

  lv_obj_t *best_title_label = lv_label_create(best_tile);
  lv_label_set_text(best_title_label, "BEST");
  lv_obj_set_style_text_color(best_title_label, lv_color_hex(SCORE_TEXT), LV_PART_MAIN);
  lv_obj_set_style_text_font(best_title_label, &lv_font_montserrat_18, LV_PART_MAIN);
  lv_obj_align(best_title_label, LV_ALIGN_CENTER, 0, -24);

  best_label = lv_label_create(best_tile);
  lv_obj_set_style_text_color(best_label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
  lv_obj_align(best_label, LV_ALIGN_CENTER, 0, tile_size / 6);

  lv_app_2048_display_score();

  lv_obj_t *remark_label = lv_label_create(scr);
  lv_label_set_text(remark_label, "Join the numbers and get to the 2048 tile!");
  lv_obj_set_style_text_color(remark_label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
  lv_obj_set_style_text_font(remark_label, &lv_font_montserrat_18, LV_PART_MAIN);
  lv_obj_set_pos(remark_label, 0, tile_size + 16);

  board = lv_obj_create(lv_scr_act());
  lv_obj_remove_flag(board, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(board, lv_color_hex(BOARD_BG), LV_PART_MAIN);
  lv_obj_set_style_border_width(board, 0, LV_PART_MAIN);
  lv_obj_set_size(board, board_size, board_size);
  lv_obj_align(board, LV_ALIGN_CENTER, 0, -board_y);

  for (int y = 0; y < 4; y++)
  {
    for (int x = 0; x < 4; x++)
    {
      lv_obj_t *cur_tile = lv_obj_create(board);
      lv_obj_remove_flag(cur_tile, LV_OBJ_FLAG_SCROLLABLE);
      lv_obj_set_style_bg_color(cur_tile, lv_color_hex(TILE_BG), LV_PART_MAIN);
      lv_obj_set_style_border_width(cur_tile, 0, LV_PART_MAIN);
      lv_obj_set_size(cur_tile, tile_size, tile_size);
      lv_obj_align(cur_tile, LV_ALIGN_CENTER, (x * tile_size_m) + tile_offset, (y * tile_size_m) + tile_offset);
    }
  }

  lv_obj_add_event_cb(board, lv_app_2048_record_gesture, LV_EVENT_GESTURE, NULL);
  lv_obj_remove_flag(board, LV_OBJ_FLAG_GESTURE_BUBBLE);

    // init vales
  score_tile_clicked = false;
  isPlaying = true;

#ifdef DEBUG_MODE
  lv_app_2048_redraw_board_value();
#else
  lv_app_2048_new_tile(2);
  lv_app_2048_start_anim();
#endif
}

static bool lv_app_2048_loop()
{
  if (isPlaying)
  {
    lv_app_2048_check_movable();
    if (movable)
    {
      if (lv_app_2048_handle_gesture())
      {
        lv_app_2048_new_tile(1);
        lv_app_2048_start_anim();
#ifdef DEBUG_MODE
        lv_app_2048_check_tile_val();
#endif
        return true;
      }
    }
    else
    {
      Serial.println("not movable");
      isPlaying = false;
      lv_obj_set_style_bg_color(score_tile, lv_color_hex(TILE_64), LV_PART_MAIN);
    }
  }
  else /* !isPlaying */
  {
    if (score_tile_clicked)
    {
      // start a new game
      lv_obj_set_style_bg_color(score_tile, lv_color_hex(BOARD_BG), LV_PART_MAIN);

      // init value
      for (int y = 0; y < 4; y++)
      {
        for (int x = 0; x < 4; x++)
        {
          tile_val[y][x] = 0;
        }
      }
      curr_score = 0;

      lv_app_2048_redraw_board_value();

      // init vales
      score_tile_clicked = false;
      isPlaying = true;
      lv_app_2048_anim_reset();

      lv_app_2048_new_tile(2);
      lv_app_2048_start_anim();
      return true;
    }
  }

  return false;
}
