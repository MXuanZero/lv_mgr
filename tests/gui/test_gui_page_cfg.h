#ifndef TEST_GUI_PAGE_CFG_H
#define TEST_GUI_PAGE_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------------*/
#include "gui/mgr/lv_mgr_page.h"
/* Exported variables ------------------------------------------------------------------------------*/
extern lv_mgr_page_interface_t test_gui_page1_handle;
extern lv_mgr_page_interface_t test_gui_page2_handle;
extern lv_mgr_page_interface_t test_gui_page3_handle;
extern lv_mgr_page_interface_t test_gui_page4_handle;
extern lv_mgr_page_interface_t test_gui_page5_handle;

static lv_mgr_page_cfg_t lv_mgr_page_cfg_list[] = {
	{ .inf = &test_gui_page1_handle }, { .inf = &test_gui_page2_handle },
	{ .inf = &test_gui_page3_handle }, { .inf = &test_gui_page4_handle },
	{ .inf = &test_gui_page5_handle }, { .inf = NULL }, // END
};

#ifdef __cplusplus
}
#endif

#endif /* TEST_GUI_PAGE_CFG_H */