#include <modules.h>

static struct self_t self;

MODULE(XORG);

static void init(void) {
    INIT_MOD(DONT_POLL);
}

/* Check we're on X */
static int check(void) {
    state.display = getenv("DISPLAY");
    state.xauthority = getenv("XAUTHORITY");
    return !state.display || !state.xauthority;
}

static void destroy(void) {
    /* Skeleton function needed for modules interface */
}

static int callback(void) {
    /* Skeleton function needed for modules interface */
    return 0;
}
