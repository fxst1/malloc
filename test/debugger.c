#include <sys/ptrace.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
extern int errno;

pid_t				child;

void 				backtrace()
{
	errno = 0;
	system("./show_dbg");
//	ptrace(PTRACE_TRACEME, child, 0L, 0L);
}

void 				signal_segsegv(int n)
{
	write(1, "Segfault\n", 9);
	backtrace();
	exit(1);
	(void)n;
}

void 				signal_segkill(int n)
{
	write(1, "Segkill\n", 8);
	exit(1);
	(void)n;
}

int					main(int argc, char **argv)
{
	int				status;
	char			path[1024] = {0};

	if (argc <= 1)
	{
		write(1, "Usage : command\n", 16);
		return (1);
	}

	if (!access(argv[1], X_OK))
	{
		strcpy(path, argv[1]);
	}
	else
	{
		strcat(path, "/bin/");
		strcat(path, argv[1]);
	}

	write(1, "Path: ", 6);
	write(1, path, strlen(path));
	write(1, "\n", 6);

	if (!(child = fork()))
	{
		write(1, "Child\n", 6);
		signal(SIGSEGV, signal_segsegv);
		signal(SIGKILL, signal_segkill);
		execvp(path, argv + 1);
		exit(0);
	}
	else if (child > 0)
	{
		setpgid(child, 0);
		write(1, "Parent\n", 7);
		wait(&status);
		if (WIFSIGNALED(status))
		{
		    // It was terminated by a signal
    		if (WTERMSIG(status) == SIGSEGV)
    		{
				signal_segsegv(1);
        		// It was terminated by a segfault
    		}
		}
	}
	return (0);
}
