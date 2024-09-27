#ifndef LV_MGR_DEFS_H
#define LV_MGR_DEFS_H
/* Includes --------------------------------------------------------------------------------------*/
#include <stdint.h>
/* Define ----------------------------------------------------------------------------------------*/
/* Exported macro --------------------------------------------------------------------------------*/
/* Exported typedef ------------------------------------------------------------------------------*/
typedef enum {
	LV_MGR_OK,
	LV_MGR_ERROR,
	LV_MGR_ALLOC_ERROR,
	LV_MGR_NOT_FOUND_PAGE,
	LV_MGR_NOT_INIT,
} lv_mgr_status;


typedef enum {
	LV_PAGE_STATE_IDLE = 0, /* Not in use */
	LV_PAGE_STATE_DESTROYED, /* Not active and having been destroyed */
	LV_PAGE_STATE_CREATED, /* Created */
	LV_PAGE_STATE_INACTIVE, /* Not active */
	LV_PAGE_STATE_ACTIVE_BG, /* Active but at the background */
	LV_PAGE_STATE_ACTIVE, /* Active and at the foreground */
} lv_page_status;
/* Exported constants ----------------------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------------------------*/
#endif // LV_MGR_DEFS_H
