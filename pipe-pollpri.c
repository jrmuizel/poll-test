#include <stdio.h>
#include <unistd.h>
#include <sys/poll.h>

int main() {
	struct pollfd fds[1];
	int ret;

        int filedes[2];
        pipe(filedes);
        write(filedes[1], "M", 1);

        fds[0].fd = filedes[0];
	fds[0].events = POLLIN | POLLPRI;

	ret = poll(fds, 1,1000);

        if (ret > 0) {
                if (fds[0].revents & POLLIN)
                        printf ("pipe is readable %x\n", fds[0].revents);
        }

	return 0;

}
