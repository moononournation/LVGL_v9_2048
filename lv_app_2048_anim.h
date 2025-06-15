struct AnimObj
{
  int32_t val;
  int32_t steps;
  lv_obj_t *obj;
};

struct MergeObj
{
  int32_t val;
  lv_obj_t *from;
  lv_obj_t *to;
};

struct AnimObjs
{
  lv_dir_t dir;
  int anim_count;
  AnimObj anim[12];
  int tobe_merge_count;
  MergeObj tobe_merge[8];
};

AnimObjs move_objs;
lv_anim_t move_anim;
AnimObjs growshrink_objs;
lv_anim_t growshrink_anim;
AnimObjs popnew_objs;
lv_anim_t popnew_anim;

static void lv_app_2048_anim_reset()
{
  move_objs.anim_count = 0;
  move_objs.tobe_merge_count = 0;
  growshrink_objs.anim_count = 0;
  popnew_objs.anim_count = 0;
}

static void lv_app_2048_anim_size_cb(void *var, int32_t v)
{
  AnimObjs *objs = (AnimObjs *)var;
  for (int i = 0; i < objs->anim_count; i++)
  {
    int32_t val = objs->anim[i].val + v;
    lv_obj_set_size(objs->anim[i].obj, val, val);
  }
}

static void lv_app_2048_anim_x_cb(void *var, int32_t v)
{
  AnimObjs *objs = (AnimObjs *)var;
  for (int i = 0; i < objs->anim_count; i++)
  {
    int32_t val = objs->anim[i].val + (v * objs->anim[i].steps);
    lv_obj_set_x(objs->anim[i].obj, val);
  }
}

static void lv_app_2048_anim_y_cb(void *var, int32_t v)
{
  AnimObjs *objs = (AnimObjs *)var;
  for (int i = 0; i < objs->anim_count; i++)
  {
    int32_t val = objs->anim[i].val + (v * objs->anim[i].steps);
    lv_obj_set_y(objs->anim[i].obj, val);
  }
}

static void lv_app_2048_anim_complete_cb(lv_anim_t *anim)
{
  AnimObjs *objs = (AnimObjs *)anim->var;
  lv_obj_t *label;
  if (objs->tobe_merge_count > 0)
  {
    for (int i = 0; i < objs->tobe_merge_count; i++)
    {
      lv_obj_delete(objs->tobe_merge[i].to);
      label = lv_obj_get_child(objs->tobe_merge[i].from, 0);
      lv_app_2048_set_tile(objs->tobe_merge[i].from, label, objs->tobe_merge[i].val);
    }
  }
}

static void lv_app_2048_start_anim()
{
  if (move_objs.anim_count > 0)
  {
    lv_anim_init(&move_anim);
    lv_anim_set_var(&move_anim, &move_objs);
    lv_anim_set_exec_cb(&move_anim, ((move_objs.dir == LV_DIR_LEFT) || (move_objs.dir == LV_DIR_RIGHT)) ? lv_app_2048_anim_x_cb : lv_app_2048_anim_y_cb);
    lv_anim_set_values(&move_anim, 0, ((move_objs.dir == LV_DIR_LEFT) || (move_objs.dir == LV_DIR_TOP)) ? (1 - tile_size_m) : (tile_size_m - 1));
    lv_anim_set_time(&move_anim, 200);
    lv_anim_set_completed_cb(&move_anim, lv_app_2048_anim_complete_cb);
    lv_anim_start(&move_anim);

    if (growshrink_objs.anim_count > 0)
    {
      lv_anim_init(&growshrink_anim);
      lv_anim_set_var(&growshrink_anim, &growshrink_objs);
      lv_anim_set_exec_cb(&growshrink_anim, lv_app_2048_anim_size_cb);
      lv_anim_set_values(&growshrink_anim, 0, tile_size / 4);
      lv_anim_set_delay(&growshrink_anim, 200);
      lv_anim_set_time(&growshrink_anim, 100);
      lv_anim_set_playback_time(&growshrink_anim, 100);
      lv_anim_set_repeat_count(&growshrink_anim, 1);
      lv_anim_start(&growshrink_anim);
    }
  }
  if (popnew_objs.anim_count > 0)
  {
    lv_anim_init(&popnew_anim);
    lv_anim_set_var(&popnew_anim, &popnew_objs);
    lv_anim_set_exec_cb(&popnew_anim, lv_app_2048_anim_size_cb);
    lv_anim_set_values(&popnew_anim, 0, tile_size);
    lv_anim_set_delay(&popnew_anim, 200);
    lv_anim_set_time(&popnew_anim, 200);
    lv_anim_set_path_cb(&popnew_anim, lv_anim_path_overshoot);
    lv_anim_start(&popnew_anim);
  }
}

static void lv_app_2048_move_obj(int from_x, int from_y, int to_x, int to_y, int v, int steps)
{
  // move
  move_objs.anim[move_objs.anim_count].val = (v * tile_size_m) + tile_offset;
  move_objs.anim[move_objs.anim_count].steps = steps;
  move_objs.anim[move_objs.anim_count].obj = tile_obj[from_y][from_x];
  move_objs.anim_count++;

  // set tile
  tile_obj[to_y][to_x] = tile_obj[from_y][from_x];
  tile_val[to_y][to_x] = tile_val[from_y][from_x];
  tile_obj[from_y][from_x] = NULL;
  tile_val[from_y][from_x] = 0;
}

static void lv_app_2048_merge_objs(int from_x, int from_y, int to_x, int to_y, int v, int steps)
{
  // move
  move_objs.anim[move_objs.anim_count].val = (v * tile_size_m) + tile_offset;
  move_objs.anim[move_objs.anim_count].steps = steps;
  move_objs.anim[move_objs.anim_count].obj = tile_obj[from_y][from_x];
  move_objs.anim_count++;

  // merge
  int merge_val = tile_val[from_y][from_x] + tile_val[to_y][to_x];
  curr_score += merge_val;
  move_objs.tobe_merge[move_objs.tobe_merge_count].val = merge_val;
  move_objs.tobe_merge[move_objs.tobe_merge_count].from = tile_obj[from_y][from_x];
  move_objs.tobe_merge[move_objs.tobe_merge_count].to = tile_obj[to_y][to_x];
  move_objs.tobe_merge_count++;

  // growshrink
  growshrink_objs.anim[growshrink_objs.anim_count].obj = tile_obj[from_y][from_x];
  growshrink_objs.anim[growshrink_objs.anim_count].val = tile_size;
  growshrink_objs.anim_count++;

  // set tile
  tile_obj[to_y][to_x] = tile_obj[from_y][from_x];
  tile_val[to_y][to_x] = merge_val;
  tile_obj[from_y][from_x] = NULL;
  tile_val[from_y][from_x] = 0;
}

static void lv_app_2048_pop_obj(int x, int y)
{
  popnew_objs.anim[popnew_objs.anim_count].obj = tile_obj[y][x];
  popnew_objs.anim[popnew_objs.anim_count].val = 0;
  popnew_objs.anim_count++;
}