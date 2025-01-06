#ifndef SRC_PORT_WIN_PARAM_H
#define SRC_PORT_WIN_PARAM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes --------------------------------------------------------------------------------------*/
#include "stdbool.h"
/* Define ----------------------------------------------------------------------------------------*/
/* Exported macro --------------------------------------------------------------------------------*/
/* Exported typedef ------------------------------------------------------------------------------*/
typedef enum win_param_status {
    PARAM_OK = 0,
    PARAM_ERROR,
} win_param_status_e;
/* Exported constants ----------------------------------------------------------------------------*/
/* Exported functions ----------------------------------------------------------------------------*/

void win_param_init(void);
win_param_status_e win_param_pos_set(int x, int y);
win_param_status_e win_param_pos_get(int *x, int *y);
void win_pos_param_exit(void);

#ifdef __cplusplus
}
#endif

#endif //SRC_PORT_WIN_PARAM_H
