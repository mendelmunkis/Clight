#include <sys/signalfd.h>
#include <signal.h>
#include <modules.h>

static struct self_t self = {
    .standalone = 1,
};


MODULE(SIGNAL);

/*
 * Set signals handler for SIGINT and SIGTERM (using a signalfd)
 */
static void init(void) {
    sigset_t mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGTERM);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    int fd = signalfd(-1, &mask, 0);
    INIT_MOD(fd);
}

static int check(void) {
    return 0; /* Skeleton function needed for modules interface */
}

static void destroy(void) {
    /* Skeleton function needed for modules interface */
}

/*
 * if received an external SIGINT or SIGTERM,
 * just switch the quit flag to 1 and print to stdout.
 */
static int callback(void) {
    struct signalfd_siginfo fdsi;
    ssize_t s;

    s = read(main_p[self.idx].fd, &fdsi, sizeof(struct signalfd_siginfo));
    if (s != sizeof(struct signalfd_siginfo)) {
        ERROR("an error occurred while getting signalfd data.\n");
    }
    INFO("received signal %d. Leaving.\n", fdsi.ssi_signo);
    state.quit = NORM_QUIT;
    return 0;
}

