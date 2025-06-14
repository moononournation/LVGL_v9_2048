#define SCORE_TEXT 0xC8BEB5
#define TILE_TEXT1 0x847369
#define TILE_TEXT2 0xFFF8F0
#define BOARD_BG 0x837970
#define TILE_BG 0x938980
#define TILE_2 0xEFE2DA
#define TILE_4 0xEBE1C6
#define TILE_8 0xF5B079
#define TILE_16 0xF69562
#define TILE_32 0xF67B59
#define TILE_64 0xF45E3D
#define TILE_128 0xEACF74
#define TILE_256 0xEBCA63
#define TILE_512 0xEEC655
#define TILE_1024 0xF1C247
#define TILE_2048 0xF4BE39
#define TILE_4096 0x79B0F5
#define TILE_8192 0x6295F6
#define TILE_16384 0x597BF6
#define TILE_32768 0x3D5EF4
#define TILE_65536 0x2141F2

const lv_font_t *lv_app_2048_get_font(int w, int v)
{
  int digit_count;
  if (v >= 1000000000)
  {
    digit_count = 10;
  }
  else if (v >= 100000000)
  {
    digit_count = 9;
  }
  else if (v >= 10000000)
  {
    digit_count = 8;
  }
  else if (v >= 1000000)
  {
    digit_count = 7;
  }
  else if (v >= 100000)
  {
    digit_count = 6;
  }
  else if (v >= 10000)
  {
    digit_count = 5;
  }
  else if (v >= 1000)
  {
    digit_count = 4;
  }
  else if (v >= 100)
  {
    digit_count = 3;
  }
  else if (v >= 10)
  {
    digit_count = 2;
  }
  else
  {
    digit_count = 1;
  }

  w -= margin;
  w *= 5;
  w /= digit_count;
  w /= 3;
  if (w > 48)
  {
    return &lv_font_montserrat_48;
  }
  else if (w > 46)
  {
    return &lv_font_montserrat_46;
  }
  else if (w > 44)
  {
    return &lv_font_montserrat_44;
  }
  else if (w > 42)
  {
    return &lv_font_montserrat_42;
  }
  else if (w > 40)
  {
    return &lv_font_montserrat_40;
  }
  else if (w > 38)
  {
    return &lv_font_montserrat_38;
  }
  else if (w > 36)
  {
    return &lv_font_montserrat_36;
  }
  else if (w > 34)
  {
    return &lv_font_montserrat_34;
  }
  else if (w > 32)
  {
    return &lv_font_montserrat_32;
  }
  else if (w > 30)
  {
    return &lv_font_montserrat_30;
  }
  else if (w > 28)
  {
    return &lv_font_montserrat_28;
  }
  else if (w > 26)
  {
    return &lv_font_montserrat_26;
  }
  else if (w > 24)
  {
    return &lv_font_montserrat_24;
  }
  else if (w > 22)
  {
    return &lv_font_montserrat_22;
  }
  else if (w > 20)
  {
    return &lv_font_montserrat_20;
  }
  else if (w > 18)
  {
    return &lv_font_montserrat_18;
  }
  else if (w > 16)
  {
    return &lv_font_montserrat_16;
  }
  else if (w > 14)
  {
    return &lv_font_montserrat_14;
  }
  else if (w > 12)
  {
    return &lv_font_montserrat_12;
  }
  else if (w > 10)
  {
    return &lv_font_montserrat_10;
  }
  else
  {
    return &lv_font_montserrat_8;
  }
}

static void lv_app_2048_set_tile(lv_obj_t *tile, lv_obj_t *label, int value)
{
  lv_label_set_text_fmt(label, "%d", value);
  lv_obj_set_style_text_font(label, lv_app_2048_get_font(tile_size, value), LV_PART_MAIN);

  switch (value)
  {
  case 2:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_2), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT1), LV_PART_MAIN);
    break;
  case 4:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_4), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT1), LV_PART_MAIN);
    break;
  case 8:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_8), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  case 16:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_16), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  case 32:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_32), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  case 64:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_64), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  case 128:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_128), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  case 256:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_256), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  case 512:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_512), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  case 1024:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_1024), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  case 2048:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_2048), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  case 4096:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_4096), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  case 8192:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_8192), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  case 16384:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_16384), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  case 32768:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_32768), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  default: // 65536
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_65536), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    break;
  }
}
