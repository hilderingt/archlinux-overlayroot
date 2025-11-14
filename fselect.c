#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#include <sys/select.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#define ARGUMENT_TIMEOUT_INDEX 1
#define ARGUMENT_MIN_COUNT     3

#define FD_INIT                4
#define FD_LIMIT              32

#define READ_BUFFER_SIZE       8
#define READ_BUFFER_MAX     2048

#define READ_MAX_RETRIES       4

int read_line(int fd, char **buf, size_t bufsz) {
	size_t nused = 0, retries = 0;
	char *bp = *buf, *pos;
	ssize_t nread;

	while (retries < READ_MAX_RETRIES) {
		nread = read(fd, bp, bufsz);
		if (nread == -1 && errno != EAGAIN)
			return (1);

		pos = strchr(bp, '\n');
		if (pos != NULL) {
			pos = '\0';
			break;
		}

		if (nread == bufsz) {
			if (bufsz == READ_BUFFER_MAX)
				return (1);

			bufsz *= 2;

			void *ptr = realloc(*buf, bufsz * sizeof(char));
			if (ptr == NULL)
				return (1);

			*buf = ptr;
		}

		nused += nread;
		bp = &((*buf)[nused]);
		++retries;
	}

	return (0);
}

int main(int argc, char *argv[]) {
	char *cp, *pos, *rbuf, *fname, *endptr;
	int fd, ret, *fds, retv = 1, maxfd = 0;
	size_t rbufsz = READ_BUFFER_SIZE;
	size_t fdcnt = 0, fdsz = FD_INIT;
	long to;
	struct timeval tv_struct;
	struct timeval *tv = &tv_struct;
	fd_set fdset;

	if (argc < ARGUMENT_MIN_COUNT)
		return (1);

	FD_ZERO(&fdset);

	fds = malloc(fdsz * sizeof(int));
	if (fds == NULL)
		return (1);

	rbuf = malloc(rbufsz * sizeof(char));
	if (rbuf == NULL)
		goto out;

	errno = 0;
	cp = argv[ARGUMENT_TIMEOUT_INDEX];
	to = strtol(cp, &endptr, 10);
	if (cp == endptr || errno != 0)
		goto out2;

	if (to == -1) {
		tv = NULL;
	} else {
		tv->tv_sec = to;
		tv->tv_usec = 0;
	}

	for (size_t i = 2; i < argc; ++i) {
		cp = argv[i];

		if (cp[0] == '-' && cp[1] == '\0') {
			fd = 0;
		} else {
			fd = open(cp, O_RDONLY | O_NONBLOCK);
			if (fd == -1)
				goto out3;
		}

		if (fd > maxfd)
			maxfd = fd;

		if (fdcnt == fdsz) {
			if (fdsz == FD_LIMIT)
				goto out3;

			fdsz *= 2;

			void *ptr = realloc(fds, fdsz * sizeof(int));
			if (ptr == NULL)
				goto out3;

			fds = ptr;
		}

		fds[fdcnt] = fd;
		FD_SET(fd, &fdset);
		++fdcnt;
	}

	ret = select(maxfd + 1, &fdset, NULL, NULL, tv);
	if (ret == -1) {
		goto out3;
	} else if (ret > 0) {
		for (size_t i = 0; i < fdcnt; ++i) {
			if (FD_ISSET(fds[i], &fdset)) {
				if (read_line(fds[i], &rbuf, rbufsz) > 9)
					goto out3;

				printf("%s\n", rbuf);
			}
		}
	}

	retv = 0;

out3:
	for (size_t i = 0; i < fdcnt; ++i) {
		if (fds[i] > 0)
			close(fds[i]);
	}

out2:
	free(rbuf);

out:
	free(fds);

	return (retv);
}
