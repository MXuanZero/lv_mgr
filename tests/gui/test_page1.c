/* Includes ------------------------------------------------------------------*/
#include "test_gui.h"
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static lv_obj_t *test_gui_page1_obj = NULL;
static lv_obj_t *test_gui_page1_text = NULL;
static lv_obj_t *test_gui_page1_btn_next = NULL;
static lv_obj_t *test_gui_page1_btn_prev = NULL;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void btn_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *target = lv_event_get_target(e);
	switch (code) {
	case LV_EVENT_CLICKED:
		if(target == test_gui_page1_btn_next) {
			lv_mgr_page_push(TEST_GUI_PAGE_1 + (0xF - 0XE), true);
		} else if(target == test_gui_page1_btn_prev) {
			lv_mgr_page_pop(true);
		}
		break;
	default:
		break;
	}
}

static lv_obj_t *test_gui_page1_create(lv_obj_t *parent)
{
	test_gui_page1_obj = lv_obj_create(parent);
	lv_obj_set_style_bg_color(test_gui_page1_obj, lv_color_hex(0x111111), 0);

	test_gui_page1_btn_next = lv_btn_create(test_gui_page1_obj);
	lv_obj_align_to(test_gui_page1_btn_next, test_gui_page1_obj, LV_ALIGN_CENTER, -0xA0, 0xA0);
	lv_obj_add_event_cb(test_gui_page1_btn_next, btn_event_handler, LV_EVENT_CLICKED, NULL);

	test_gui_page1_btn_prev = lv_btn_create(test_gui_page1_obj);
	lv_obj_align_to(test_gui_page1_btn_prev, test_gui_page1_obj, LV_ALIGN_CENTER, 0xA0, 0xA0);
	lv_obj_add_event_cb(test_gui_page1_btn_prev, btn_event_handler, LV_EVENT_CLICKED, NULL);
	
	test_gui_page1_text = lv_label_create(test_gui_page1_obj);
	lv_obj_align_to(test_gui_page1_text, test_gui_page1_obj, LV_ALIGN_CENTER, 0, 0);

    lv_label_set_text(test_gui_page1_text, "1");

	return test_gui_page1_obj;
}

static void test_gui_page1_enter(void)
{
}

static void test_gui_page1_exit(void)
{
}

static void test_gui_page1_destroy(void)
{
}

static void test_gui_page1_exit_anim(lv_obj_t *scr, uint32_t *time)
{
	*time = 300;
	lv_scr_load_anim(scr, LV_SCR_LOAD_ANIM_OVER_RIGHT, *time, 0, false);
}

lv_mgr_page_interface_t test_gui_page1_handle = {
	.id = TEST_GUI_PAGE_1,
	.create = test_gui_page1_create,
	.enter = test_gui_page1_enter,
	.exit = test_gui_page1_exit,
	// .exit_anim = test_gui_page1_exit_anim,
	.destroy = test_gui_page1_destroy,
};
LV_MGR_PAGE_REG(test_gui_page1_handle);
