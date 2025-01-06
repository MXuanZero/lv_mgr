/* Includes ------------------------------------------------------------------*/
#include "page/gui_pages.h"
#include "mgr/lv_mgr_page.h"
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void gui_init(void)
{
	lv_mgr_page_init();
	lv_mgr_page_push(LV_PAGE_MASTER, false);
	lv_mgr_page_push(LV_PAGE_START_UP, false);
}
