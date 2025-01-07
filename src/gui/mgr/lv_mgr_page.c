/* Includes --------------------------------------------------------------------------------------*/
#include "lv_mgr_page.h"
#include "lvgl/src/misc/lv_mem.h"
#include <stdio.h>
/* Private define --------------------------------------------------------------------------------*/
/* Private macro ---------------------------------------------------------------------------------*/
#define STACK_TOP (stack.head)
#define STACK_SEC (stack.second)
#define STACK_ROOT (stack.tail)
#define STACK_SIZE (stack.size)
#define PAGE_INTERFACE(page) ((lv_mgr_page_interface_t *)*(uintptr_t *)(page))
/* Private typedef -------------------------------------------------------------------------------*/
typedef struct lv_mgr_page_handle {
	lv_mgr_page_interface_t *interface; // 由于存在宏PAGE_INTERFACE，因此interface一定要在第一个！
	lv_obj_t *obj;
	lv_page_status state;
} lv_mgr_page_t;

typedef struct lv_mgr_page_item {
	lv_mgr_page_t *page;
	struct lv_mgr_page_item *prev;
	struct lv_mgr_page_item *next;
} lv_mgr_page_item_t;

typedef struct lv_mgr_page_stack {
	int32_t size;
	struct lv_mgr_page_item *head;
	struct lv_mgr_page_item *second;
	struct lv_mgr_page_item *tail;
} lv_mgr_page_stack_t;

typedef struct lv_mgr_page {
	int32_t page_sum;
	lv_mgr_page_t handles[0];
} lv_mgr_page_array_t;
/* Private function prototypes -------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
#if 0
extern lv_mgr_page_cfg_t __lv_mgr_page_cfg_start__;
extern lv_mgr_page_cfg_t __lv_mgr_page_cfg_end__;
#else

#define LV_MGR_PAGE_CFG_LIST_SIZE (sizeof(lv_mgr_page_cfg_list) / sizeof(lv_mgr_page_cfg_list[0]))
#define __lv_mgr_page_cfg_start__ lv_mgr_page_cfg_list[0]
#define __lv_mgr_page_cfg_end__ lv_mgr_page_cfg_list[LV_MGR_PAGE_CFG_LIST_SIZE - 1]

#if 0
extern lv_mgr_page_interface_t app_master_handle;
extern lv_mgr_page_interface_t gui_start_up_handle;

lv_mgr_page_cfg_t lv_mgr_page_cfg_list[] = {
	{ .inf = &app_master_handle },
	{ .inf = &gui_start_up_handle },
	{ .inf = NULL }, // END
};

#else
#include "tests/gui/test_gui_page_cfg.h"
#endif
#endif

static lv_mgr_page_array_t *mgr;
static lv_mgr_page_stack_t stack = { 0 };
static bool page_anim = false;
/* Private functions -----------------------------------------------------------------------------*/
static void lv_mgr_page_active(lv_mgr_page_t *page)
{
	lv_mgr_page_interface_t *interface = page->interface;
	if (page->state < LV_PAGE_STATE_CREATED) {
		page->obj = interface->create(NULL);
		interface->enter();
		page->state = LV_PAGE_STATE_ACTIVE;
	} else if (page->state < LV_PAGE_STATE_ACTIVE) {
		interface->enter();
		page->state = LV_PAGE_STATE_ACTIVE;
	}
}

static void lv_mgr_page_inactive(lv_mgr_page_t *page)
{
	lv_mgr_page_interface_t *interface = page->interface;
	if (page->state > LV_PAGE_STATE_INACTIVE) {
		interface->exit();
		page->state = LV_PAGE_STATE_INACTIVE;
	}
}

static void lv_mgr_page_delay_destroy(lv_mgr_page_t *page)
{
	page->state = LV_PAGE_STATE_ACTIVE_BG;
}

static void lv_mgr_page_remove(lv_mgr_page_t *page)
{
	lv_mgr_page_interface_t *interface = page->interface;
	if (page->state > LV_PAGE_STATE_INACTIVE) {
		interface->exit();
		interface->destroy();
		page->state = LV_PAGE_STATE_IDLE;
	} else if (page->state > LV_PAGE_STATE_DESTROYED) {
		interface->destroy();
		page->state = LV_PAGE_STATE_IDLE;
	}
}

void lv_mgr_page_enter_anim_ready(lv_timer_t *timer)
{
	page_anim = false;
}

void lv_mgr_page_exit_anim_ready(lv_timer_t *timer)
{
	lv_mgr_page_t *handle = timer->user_data;
	lv_mgr_page_remove(handle);
	if (handle->obj != NULL) {
		lv_obj_del(handle->obj);
	}
	page_anim = false;
}

lv_mgr_status lv_mgr_page_init(void)
{
	lv_mgr_page_cfg_t *cfg_arr;
	uint32_t cnt = 0;
	uint8_t *end = (uint8_t *)&__lv_mgr_page_cfg_end__;
	uint8_t *start = (uint8_t *)&__lv_mgr_page_cfg_start__;
	int32_t page_sum = (int32_t)((end - start) / sizeof(lv_mgr_page_cfg_t));
	LV_ASSERT(page_sum != 0);

	mgr = lv_mem_alloc(page_sum * sizeof(lv_mgr_page_t) + sizeof(lv_mgr_page_array_t));
	if (mgr == NULL) {
		return LV_MGR_ERROR;
	}
	memset(mgr, 0, page_sum * sizeof(lv_mgr_page_t) + sizeof(lv_mgr_page_array_t));
	for (cfg_arr = &__lv_mgr_page_cfg_start__; cfg_arr != &__lv_mgr_page_cfg_end__;
	     cfg_arr++, cnt++) {
		mgr->handles[cnt].interface = cfg_arr->inf;
		LV_LOG_INFO("page[%d] name: %s", cnt, cfg_arr->page->name);
	}

	if (cnt != page_sum) {
		lv_mem_free(mgr);
		LV_ASSERT(page_sum == cnt);
		return LV_MGR_ERROR;
	}
	mgr->page_sum = page_sum;

	return LV_MGR_OK;
}

static lv_mgr_page_t *lv_mgr_page_find(int32_t page_id)
{
	int32_t cnt = mgr->page_sum;
	lv_mgr_page_t *handles = mgr->handles;

	if (page_id == -1) {
		return NULL;
	}
	for (int32_t i = 0; i < cnt; i++) {
		lv_mgr_page_t *page = &handles[i];
		if (page_id == PAGE_INTERFACE(page)->id) {
			return &handles[i];
		}
	}
	return NULL;
}

lv_mgr_status lv_mgr_page_push(int32_t page_id, bool anim)
{
	lv_mgr_page_t *target = lv_mgr_page_find(page_id);
	if (target == NULL) {
		return LV_MGR_NOT_FOUND_PAGE;
	}

	lv_mgr_page_interface_t *interface = target->interface;
	if (STACK_TOP != NULL && lv_mgr_page_get_id() == interface->id) {
		return LV_MGR_OK;
	}

	if (target->state == LV_PAGE_STATE_DESTROYED) {
		LV_LOG_WARN("if not free page");
		return LV_MGR_ERROR;
	}

	if (STACK_ROOT != NULL) {
		if (PAGE_INTERFACE(STACK_ROOT->page)->id == page_id) {
			return LV_MGR_OK;
		}
	}

	lv_mgr_page_item_t *item = lv_mem_alloc(sizeof(lv_mgr_page_item_t));
	if (item == NULL) {
		return LV_MGR_ALLOC_ERROR;
	}

	memset(item, 0, sizeof(lv_mgr_page_item_t));
	item->page = target;
	if (STACK_SIZE == 0) {
		item->prev = NULL;
		item->next = NULL;
		STACK_TOP = item;
		STACK_ROOT = item;
	} else {
		lv_mgr_page_inactive(STACK_TOP->page);
		item->next = NULL;
		item->prev = STACK_TOP;
		STACK_TOP->next = item;
		STACK_TOP = item;
		STACK_SEC = STACK_TOP->prev;
	}
	STACK_SIZE++;

	lv_mgr_page_active(target);
	if (interface->enter_anim && anim) {
		uint32_t time = 0;
		lv_timer_t *timer;
		page_anim = true;
		interface->enter_anim(target->obj, &time);
		timer = lv_timer_create(lv_mgr_page_enter_anim_ready, time + 40, STACK_TOP->page);
		lv_timer_set_repeat_count(timer, 1);
	} else {
		lv_scr_load(target->obj);
	}
	return LV_MGR_OK;
}

lv_mgr_status lv_mgr_page_pop(bool anim)
{
	if (STACK_TOP == STACK_ROOT || STACK_TOP == NULL) {
		return LV_MGR_OK;
	}

	lv_mgr_page_t *top_page = STACK_TOP->page;
	lv_mgr_page_interface_t *top_page_interface = top_page->interface;
	if (top_page_interface->exit_anim && anim) {
		uint32_t time = 0;
		page_anim = true;
		top_page_interface->exit_anim(STACK_SEC->page->obj, &time);
		if (time != 0) {
			lv_timer_t *timer;
			timer = lv_timer_create(lv_mgr_page_exit_anim_ready, time + 40, top_page);
			lv_timer_set_repeat_count(timer, 1);
			lv_mgr_page_delay_destroy(top_page);
		} else {
			lv_mgr_page_remove(top_page); // 执行exit不执行destroy
			lv_scr_load(STACK_SEC->page->obj);
			lv_obj_del(top_page->obj);
		}
		lv_mem_free((void *)STACK_TOP);
	} else {
		lv_mgr_page_remove(top_page);
		lv_scr_load(STACK_SEC->page->obj);
		lv_obj_del(top_page->obj);
		lv_mem_free(STACK_TOP);
	}

	STACK_TOP = STACK_SEC;
	STACK_TOP->next = NULL;
	STACK_SEC = STACK_SEC->prev;
	STACK_SIZE--;

	lv_mgr_page_active(STACK_TOP->page);
	return LV_MGR_OK;
}

lv_mgr_status lv_mgr_page_pop_n(uint32_t n, bool anim)
{
	if (STACK_TOP == STACK_ROOT || STACK_TOP == NULL) {
		return LV_MGR_OK;
	}
	if (n >= STACK_SIZE || n < 1) {
		return LV_MGR_ERROR;
	}

	anim = false; // 多页面退出暂不支持动画

	uint32_t pop_cnt = 0;
	lv_obj_t *cur_scr_obj = STACK_TOP->page->obj;
	lv_mgr_page_remove(STACK_TOP->page);
	lv_mem_free(STACK_TOP);
	STACK_TOP = STACK_SEC;

	while ((++pop_cnt < n) && (STACK_TOP != NULL) && (STACK_TOP != STACK_ROOT)) {
		STACK_SEC = STACK_TOP->prev;
		lv_mgr_page_remove(STACK_TOP->page);
		lv_obj_del(STACK_TOP->page->obj);
		lv_mem_free(STACK_TOP);
		STACK_TOP = STACK_SEC;
		STACK_SIZE--;
	}
	STACK_SEC = STACK_TOP->prev;
	lv_mgr_page_active(STACK_TOP->page);

	lv_scr_load(STACK_TOP->page->obj);
	if (cur_scr_obj) {
		lv_obj_del(cur_scr_obj);
	}

	return LV_MGR_OK;
}

lv_mgr_status lv_mgr_page_pop_to_root(bool anim)
{
	return lv_mgr_page_pop_n(STACK_SIZE - 1, anim);
}

int32_t lv_mgr_page_get_id(void)
{
	if (STACK_TOP == NULL) {
		return -1;
	}
	return PAGE_INTERFACE(STACK_TOP->page)->id;
}

bool lv_mgr_page_is_root(void)
{
	LV_ASSERT(NULL == STACK_ROOT || NULL == STACK_TOP);
	return STACK_TOP == STACK_ROOT;
}

bool lv_mgr_page_is_anim(void)
{
	return page_anim;
}
