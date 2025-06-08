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

static void lv_app_2048_set_tile(lv_obj_t *tile, lv_obj_t *label, int value)
{
  lv_label_set_text_fmt(label, "%d", value);

  switch (value)
  {
  case 2:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_2), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT1), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, LV_PART_MAIN);
    break;
  case 4:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_4), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT1), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, LV_PART_MAIN);
    break;
  case 8:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_8), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, LV_PART_MAIN);
    break;
  case 16:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_16), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, LV_PART_MAIN);
    break;
  case 32:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_32), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, LV_PART_MAIN);
    break;
  case 64:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_64), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_48, LV_PART_MAIN);
    break;
  case 128:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_128), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_44, LV_PART_MAIN);
    break;
  case 256:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_256), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_44, LV_PART_MAIN);
    break;
  case 512:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_512), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_44, LV_PART_MAIN);
    break;
  case 1024:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_1024), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_32, LV_PART_MAIN);
    break;
  case 2048:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_2048), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_32, LV_PART_MAIN);
    break;
  case 4096:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_4096), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_32, LV_PART_MAIN);
    break;
  case 8192:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_8192), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_32, LV_PART_MAIN);
    break;
  case 16384:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_16384), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_30, LV_PART_MAIN);
    break;
  case 32768:
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_32768), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_30, LV_PART_MAIN);
    break;
  default: // 65536
    lv_obj_set_style_bg_color(tile, lv_color_hex(TILE_65536), LV_PART_MAIN);
    lv_obj_set_style_text_color(label, lv_color_hex(TILE_TEXT2), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_30, LV_PART_MAIN);
    break;
  }
}
