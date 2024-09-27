/* Includes --------------------------------------------------------------------------------------*/
#include <stdio.h>
#include "win_param.h"
#include "json-c/json.h"
/* Private define --------------------------------------------------------------------------------*/
#define LVGL_JSON_FILE "lvgl_win.json"
/* Private macro ---------------------------------------------------------------------------------*/
/* Private typedef -------------------------------------------------------------------------------*/
/* Private function prototypes -------------------------------------------------------------------*/
/* Private variables -----------------------------------------------------------------------------*/
static json_object *json_obj = NULL;
static json_object *json_win_pos = NULL;
/* Private functions -----------------------------------------------------------------------------*/

void win_param_init(void)
{
	json_object *jobj, *jpos, *jobj_x, *jobj_y;
	jobj = json_object_from_file(LVGL_JSON_FILE);
	if (jobj == NULL) {
		jobj = json_object_new_object();
		if(jobj == NULL) {
			goto JOBJ_EXIT;
		}
	}

	jpos = json_object_object_get(jobj, "pos");
	if (jpos == NULL) {
		jpos = json_object_new_object();
		if(jpos == NULL) {
			goto JPOS_EXIT;
		}
		json_object_object_add(jobj, "pos", jpos);
	}

	jobj_x = json_object_object_get(jpos, "x");
	if(jobj_x == NULL) {
		jobj_x = json_object_new_int(50);
		if(jobj_x == NULL) {
			goto JOBJ_X;
		}
		json_object_object_add(jpos, "x", jobj_x);
	}

	jobj_y = json_object_object_get(jpos, "y");
	if(jobj_y == NULL)
	{
		jobj_y = json_object_new_int(50);
		if(jobj_y == NULL) {
			goto JOBJ_Y;
		}
		json_object_object_add(jpos, "y", jobj_y);
	}

	json_obj = jobj;
	json_win_pos = jpos;
	json_object_to_file_ext(LVGL_JSON_FILE, json_obj, JSON_C_TO_STRING_PRETTY);
	return;

	json_object_put(jobj_y);
JOBJ_Y:
	json_object_put(jobj_x);
JOBJ_X:
	json_object_put(jpos);
JPOS_EXIT:
	json_object_put(jobj);
JOBJ_EXIT:
	return;
}

enum win_param_status win_param_pos_set(int x, int y)
{
	if (json_win_pos == NULL) {
		return PARAM_ERROR;
	}
	json_object_set_int(json_object_object_get(json_win_pos, "x"), x);
	json_object_set_int(json_object_object_get(json_win_pos, "y"), y);
	json_object_to_file_ext(LVGL_JSON_FILE, json_obj, JSON_C_TO_STRING_PRETTY);
	return PARAM_OK;
}

enum win_param_status win_param_pos_get(int *x, int *y)
{
	if (json_win_pos == NULL) {
		return PARAM_ERROR;
	}
	*x = json_object_get_int(json_object_object_get(json_win_pos, "x"));
	*y = json_object_get_int(json_object_object_get(json_win_pos, "y"));
	return PARAM_OK;
}

void win_pos_param_exit(void)
{
	json_object_put(json_obj);
}