/* Includes ------------------------------------------------------------------*/
#include "mgr/lv_mgr_page.h"
#include "gui_master.h"
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static lv_obj_t *gui_master_obj = NULL;
static const char *page_map[] = { "Action1", "Action2", "" };
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void btnm_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code) {
	case LV_EVENT_CLICKED:
		lv_obj_t *obj = lv_event_get_target(e);
		uint32_t id = lv_btnmatrix_get_selected_btn(obj);
		switch (id) {
		case (0): {
			break;
		}
		default:
			break;
		}
		break;
	default:
		break;
	}
}

static lv_obj_t *gui_master_create(lv_obj_t *parent)
{
	gui_master_obj = lv_obj_create(parent);
	lv_obj_set_style_bg_color(gui_master_obj, lv_color_hex(0x111111), 0);

	/* button */
	lv_obj_t *btnm = lv_btnmatrix_create(gui_master_obj);
	lv_obj_set_style_border_side(btnm, LV_BORDER_SIDE_NONE, 1);

	lv_btnmatrix_set_map(btnm, page_map);

	lv_btnmatrix_set_one_checked(btnm, true);
	lv_obj_set_size(btnm, LV_PCT(100), LV_PCT(10));

	lv_obj_set_style_border_width(btnm, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(btnm, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(btnm, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(btnm, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(btnm, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(btnm, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(btnm, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(btnm, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(btnm, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(btnm, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(btnm, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

	lv_obj_set_style_border_width(btnm, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(btnm, lv_color_hex(0x000000), LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(btnm, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_radius(btnm, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(btnm, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(btnm, lv_color_hex(0xeeeeee), LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(btnm, LV_GRAD_DIR_NONE, LV_PART_ITEMS | LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(btnm, 0, LV_PART_ITEMS | LV_STATE_DEFAULT);

	lv_obj_add_event_cb(btnm, btnm_event_handler, LV_EVENT_ALL, NULL);

	return gui_master_obj;
}

static void gui_master_enter(void)
{
}

static void gui_master_exit(void)
{
}

static void gui_master_destroy(void)
{
}

lv_mgr_page_interface_t app_master_handle = {
	.id = LV_PAGE_MASTER,
	.create = gui_master_create,
	.enter = gui_master_enter,
	.exit = gui_master_exit,
	.destroy = gui_master_destroy,
};
LV_MGR_PAGE_REG(app_master_handle);
