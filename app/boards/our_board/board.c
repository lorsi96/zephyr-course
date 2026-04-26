#include <zephyr/init.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(board, LOG_LEVEL_INF);

static int board_our_board_init(void) {
    LOG_INF("Board Initialized!");
	return 0;
}

SYS_INIT(board_our_board_init, PRE_KERNEL_1, 0);
