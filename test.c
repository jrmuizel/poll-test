#include <stdio.h>
#include <unistd.h>
#include <sys/poll.h>

#define TIMEOUT 5

int main (void)
{
	struct pollfd fds[2];
	int ret;

	/* watch stdin for input */
	fds[0].fd = STDIN_FILENO;
	fds[0].events = POLLIN | POLLPRI;

        int filedes[2];
        pipe(filedes);
	/* watch stdout for ability to write */
	fds[1].fd = filedes[0];
	fds[1].events = POLLIN | POLLPRI;
        //write(filedes[1], "M", 1);

	ret = poll(fds, 2, TIMEOUT * 1000);

	if (ret == -1) {
		perror ("poll");
		return 1;
	}

	if (!ret) {
		printf ("%d seconds elapsed.\n", TIMEOUT);
		return 0;
	}

	if (fds[0].revents & POLLIN)
		printf ("stdin is readable %x\n", fds[0].revents);

	if (fds[1].revents & POLLIN)
		printf ("pipe is readable %x\n", fds[1].revents);

	return 0;

}
