/* Includes ------------------------------------------------------------------*/
#include "mgr/lv_mgr_page.h"
#include "start_up.h"
#include "gui_pages.h"
/* Private define ------------------------------------------------------------*/
#define STRAT_UP_LOGO_TEXT "T-Clock"
#define COLOR_ORANGE lv_color_hex(0xff931e)
#define COLOR_RED lv_color_hex(0xff0000)
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static lv_anim_t gui_start_up_cont_anim;
static lv_anim_t gui_start_up_logo_anim;
static lv_anim_t gui_start_up_exit_anim;
static lv_anim_timeline_t *gui_start_up_anim;
lv_obj_t *label_logo;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
static void gui_start_up_cont_anim_cb(void *var, int32_t v)
{
	lv_obj_set_style_width(var, (lv_coord_t)v, 0);
}

static void gui_start_up_logo_anim_cb(void *var, int32_t v)
{
	lv_obj_set_y(var, (lv_coord_t)v);
}

static void gui_start_up_exit_anim_cb(void *var, int32_t v)
{
	lv_obj_set_style_opa(var, (lv_coord_t)v, 0);
}

static void gui_start_up_ready_cb(struct _lv_anim_t *anim)
{
	lv_mgr_page_pop(true);
}

static lv_obj_t *gui_start_up_create(lv_obj_t *parent)
{
	lv_obj_t *gui_start_up_obj = lv_obj_create(parent);
	lv_obj_set_style_bg_color(gui_start_up_obj, lv_color_hex(0xFFFFFF), 0);

	lv_obj_t *cont = lv_obj_create(gui_start_up_obj);
	lv_obj_remove_style_all(cont);
	lv_obj_set_size(cont, 115, 40);
	lv_obj_set_style_border_color(cont, COLOR_RED, 0);
	lv_obj_set_style_border_side(cont, LV_BORDER_SIDE_BOTTOM, 0);
	lv_obj_set_style_border_width(cont, 3, 0);
	lv_obj_set_style_border_post(cont, true, 0);
	lv_obj_center(cont);

	label_logo = lv_label_create(cont);
	lv_obj_set_style_text_font(label_logo, &lv_font_montserrat_26, 0);
	lv_obj_set_style_text_color(label_logo, lv_color_black(), 0);
	lv_label_set_text(label_logo, STRAT_UP_LOGO_TEXT);
	lv_obj_center(label_logo);

	/* cont anim */
	lv_anim_init(&gui_start_up_cont_anim);
	lv_anim_set_var(&gui_start_up_cont_anim, cont);
	lv_anim_set_values(&gui_start_up_cont_anim, 0,
			   lv_obj_get_style_width(cont, 0));
	lv_anim_set_time(&gui_start_up_cont_anim, 550);
	lv_anim_set_exec_cb(&gui_start_up_cont_anim, gui_start_up_cont_anim_cb);
	lv_anim_set_path_cb(&gui_start_up_cont_anim, lv_anim_path_ease_in_out);

	/* logo anim */
	lv_anim_init(&gui_start_up_logo_anim);
	lv_anim_set_var(&gui_start_up_logo_anim, label_logo);
	lv_anim_set_values(&gui_start_up_logo_anim,
			   lv_obj_get_style_height(cont, 0) + 3,
			   lv_obj_get_y(label_logo) + 3);
	lv_anim_set_time(&gui_start_up_logo_anim, 600);
	lv_anim_set_exec_cb(&gui_start_up_logo_anim, gui_start_up_logo_anim_cb);
	lv_anim_set_path_cb(&gui_start_up_logo_anim, lv_anim_path_ease_in_out);
	lv_anim_set_ready_cb(&gui_start_up_logo_anim, gui_start_up_ready_cb);

	/* exit */
	lv_anim_init(&gui_start_up_exit_anim);
	lv_anim_set_var(&gui_start_up_exit_anim, cont);
	lv_anim_set_values(&gui_start_up_exit_anim, LV_OPA_100, LV_OPA_0);
	lv_anim_set_time(&gui_start_up_exit_anim, 500);
	lv_anim_set_exec_cb(&gui_start_up_exit_anim, gui_start_up_exit_anim_cb);
	lv_anim_set_path_cb(&gui_start_up_exit_anim, lv_anim_path_ease_in_out);
	lv_anim_set_ready_cb(&gui_start_up_exit_anim, gui_start_up_ready_cb);

	/* anim timeline */
	gui_start_up_anim = lv_anim_timeline_create();
	lv_anim_timeline_add(gui_start_up_anim, 0, &gui_start_up_cont_anim);
	lv_anim_timeline_add(gui_start_up_anim, 400, &gui_start_up_logo_anim);

	// lv_anim_timeline_add(gui_start_up_anim, 1700, &gui_start_up_exit_anim);
	lv_anim_timeline_start(gui_start_up_anim);

	return gui_start_up_obj;
}

static void gui_start_up_enter(void)
{

}

static void gui_start_up_exit(void)
{
	printf("start_up_destroy\n");
}

static void gui_start_up_scr_exit_anim(lv_obj_t *scr, uint32_t *time)
{
	*time = 300;
	lv_scr_load_anim(scr, LV_SCR_LOAD_ANIM_OVER_RIGHT, *time, 0, false);
}

static void gui_start_up_destroy(void)
{
	lv_anim_timeline_del(gui_start_up_anim);
	lv_obj_del(label_logo);
}

lv_mgr_page_interface_t gui_start_up_handle = {
	.id = LV_PAGE_START_UP,
	.create = gui_start_up_create,
	.enter = gui_start_up_enter,
	.exit = gui_start_up_exit,
	.exit_anim = gui_start_up_scr_exit_anim,
	.destroy = gui_start_up_destroy,
};
LV_MGR_PAGE_REG(gui_start_up_handle);