#ifndef TEST_GUI_H
#define TEST_GUI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------------*/
#include "gui/mgr/lv_mgr_page.h"
/* Define ----------------------------------------------------------------------------------------*/
/* Exported macro --------------------------------------------------------------------------------*/
/* Exported typedef ------------------------------------------------------------------------------*/
typedef enum test_gui_page_id {
	TEST_GUI_PAGE_1 = 0x100,
	TEST_GUI_PAGE_2,
	TEST_GUI_PAGE_3,
	TEST_GUI_PAGE_4,
	TEST_GUI_PAGE_5,
	TEST_GUI_PAGE_6,
	TEST_GUI_PAGE_7,
	TEST_GUI_PAGE_8,
	TEST_GUI_PAGE_9,
} test_gui_page_id;
/* Exported constants ----------------------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------------------------*/

void test_gui_init(void);

#ifdef __cplusplus
}
#endif

#endif /* TEST_GUI_H */