#ifndef LV_PAGE_MGR_H
#define LV_PAGE_MGR_H
/* Includes --------------------------------------------------------------------------------------*/
#include <stdbool.h>
#include "lv_mgr_defs.h"
#include "lvgl/lvgl.h"
/* Define ----------------------------------------------------------------------------------------*/
/* Exported macro --------------------------------------------------------------------------------*/
#define LV_MGR_PAGE_REG(_interfce)                                                         \
	lv_mgr_page_cfg_t page##_interfce##_cfg __attribute__((__section__(".lv.mgr.page"))) = { \
		.interfce = &_interfce,                                                        \
	}

/* Exported typedef ------------------------------------------------------------------------------*/

typedef struct lv_mgr_page_interface {
	int32_t id;
	char *name;
	lv_obj_t *(*create)(lv_obj_t *parent);
	void (*enter)(void);
	/* page 是将要切换的页面，time是输出值为动画所需时间 */
	void (*enter_anim)(lv_obj_t *page, uint32_t *time);
	void (*exit)(void);
	void (*exit_anim)(lv_obj_t *page, uint32_t *time);
	void (*destroy)(void);
} lv_mgr_page_interface_t;

typedef struct lv_mgr_page_cfg {
	lv_mgr_page_interface_t *interfce;
} lv_mgr_page_cfg_t;

/* Exported constants ----------------------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------------------------*/

/**
 * @brief 初始化
 */
lv_mgr_status lv_mgr_page_init(void);

/**
 * @brief 进入页面
 */
lv_mgr_status lv_mgr_page_push(int32_t page_id, bool anim);

/**
 * @brief 推出页面
 */
lv_mgr_status lv_mgr_page_pop(bool anim);

/**
 * @brief 返回当前页面id
 */
int32_t lv_mgr_page_get_id(void);

/**
 * @brief 判断当前页面是否是主界面
 */
bool lv_mgr_page_is_root(void);

/**
 * @brief 判断当前是否有过度动画
 */
bool lv_mgr_page_is_anim(void);

#endif // LV_PAGE_MGR_H
