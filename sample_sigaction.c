/* Andre Augusto Giannotti Scota (a2gs)
 * andre.scota@gmail.com
 *
 * A sample of sigaction(2) usage.
 *
 * MIT License
 *
 */

/* sample_sigaction.c
 * A sample of sigaction(2) usage.
 *
 *  Who     | When       | What
 *  --------+------------+----------------------------
 *   a2gs   | 19/01/2019 | Creation
 *          |            |
 */


/* *** INCLUDES ************************************************************************ */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>


/* *** FUNCTIONS *********************************************************************** */
void functionHandle(int signum, siginfo_t *si, void *context)
{
	fprintf(stderr, "Signal sent: signum: [%d] / si_signo: [%d]\n", signum, si->si_signo);

	if(si->si_pid != 0 || si->si_uid != 0)
		fprintf(stderr, "Signal sent by kill(2) and sigqueue(3): process: [%d] and userId: [%u]\n", si->si_pid, si->si_uid);

	fprintf(stderr, "------------------------------\n");
	fprintf(stderr, "For regular signals: ");

	if     (si->si_code == SI_USER   ) fprintf(stderr, "SI_USER: kill(2).\n");
	else if(si->si_code == SI_KERNEL ) fprintf(stderr, "SI_KERNEL: Sent by the kernel.\n");
	else if(si->si_code == SI_QUEUE  ) fprintf(stderr, "SI_QUEUE: sigqueue(3).\n");
	else if(si->si_code == SI_TIMER  ) fprintf(stderr, "SI_TIMER: POSIX timer expired.\n");
	else if(si->si_code == SI_MESGQ  ) fprintf(stderr, "SI_MESGQ: POSIX message queue state changed; see mq_notify(3).\n");
	else if(si->si_code == SI_ASYNCIO) fprintf(stderr, "SI_ASYNCIO: AIO completed.\n");
	else if(si->si_code == SI_SIGIO  ) fprintf(stderr, "SI_SIGIO: Queued SIGIO.\n");
	else if(si->si_code == SI_TKILL  ) fprintf(stderr, "SI_TKILL: tkill(2) or tgkill(2).\n");
	else                               fprintf(stderr, "Unknow\n");
	fprintf(stderr, "------------------------------\n");

	switch(signum){
		case SIGHUP:
			break;

		case SIGINT:
			break;

		case SIGQUIT:
			break;

		case SIGILL:
			fprintf(stderr, "SIGILL: ");

			if     (si->si_code == ILL_ILLOPC) fprintf(stderr, "ILL_ILLOPC: Illegal opcode.\n");
			else if(si->si_code == ILL_ILLOPN) fprintf(stderr, "ILL_ILLOPN: Illegal operand.\n");
			else if(si->si_code == ILL_ILLADR) fprintf(stderr, "ILL_ILLADR: Illegal addressing mode.\n");
			else if(si->si_code == ILL_ILLTRP) fprintf(stderr, "ILL_ILLTRP: Illegal trap.\n");
			else if(si->si_code == ILL_PRVOPC) fprintf(stderr, "ILL_PRVOPC: Privileged opcode.\n");
			else if(si->si_code == ILL_PRVREG) fprintf(stderr, "ILL_PRVREG: Privileged register.\n");
			else if(si->si_code == ILL_COPROC) fprintf(stderr, "ILL_COPROC: Coprocessor error.\n");
			else if(si->si_code == ILL_BADSTK) fprintf(stderr, "ILL_BADSTK: Internal stack error.\n");
			else                               fprintf(stderr, "Unknow\n");

			break;

		case SIGABRT: /* SIGIOT */
			break;

		case SIGFPE:
			fprintf(stderr, "SIGFPE/SIGIOT: ");

			if     (si->si_code == FPE_INTDIV) fprintf(stderr, "FPE_INTDIV: Integer divide by zero.\n");
			else if(si->si_code == FPE_INTOVF) fprintf(stderr, "FPE_INTOVF: Integer overflow.\n");
			else if(si->si_code == FPE_FLTDIV) fprintf(stderr, "FPE_FLTDIV: Floating-point divide by zero.\n");
			else if(si->si_code == FPE_FLTOVF) fprintf(stderr, "FPE_FLTOVF: Floating-point overflow.\n");
			else if(si->si_code == FPE_FLTUND) fprintf(stderr, "FPE_FLTUND: Floating-point underflow.\n");
			else if(si->si_code == FPE_FLTRES) fprintf(stderr, "FPE_FLTRES: Floating-point inexact result.\n");
			else if(si->si_code == FPE_FLTINV) fprintf(stderr, "FPE_FLTINV: Floating-point invalid operation.\n");
			else if(si->si_code == FPE_FLTSUB) fprintf(stderr, "FPE_FLTSUB: Subscript out of range.\n");
			else                               fprintf(stderr, "Unknow\n");

			exit(0);

			break;

		case SIGKILL: /* cannot be caught, blocked, or ignored */
			break;

		case SIGSTOP: /* cannot be caught, blocked, or ignored */
			break;

		case SIGSEGV:
			fprintf(stderr, "SIGSEGV: ");

			if     (si->si_code == SEGV_MAPERR) fprintf(stderr, "SEGV_MAPERR: Address not mapped to object.\n");
			else if(si->si_code == SEGV_ACCERR) fprintf(stderr, "SEGV_ACCERR: Invalid permissions for mapped object.\n");
			else if(si->si_code == SEGV_BNDERR) fprintf(stderr, "SEGV_BNDERR: Failed address bound checks.\n");
			else if(si->si_code == SEGV_PKUERR) fprintf(stderr, "SEGV_PKUERR: Access was denied by memory protection keys.\n");
			else                                fprintf(stderr, "Unknow\n");

			break;

		case SIGPIPE:
			break;

		case SIGALRM:
			break;

		case SIGTERM:
			break;

		case SIGUSR1:
			break;

		case SIGUSR2:
			break;

		case SIGCHLD: /* SIGCLD */
			fprintf(stderr, "SIGCHLD/SIGCLD: ");

			if     (si->si_code == CLD_EXITED   ) fprintf(stderr, "CLD_EXITED: Child has exited.\n");
			else if(si->si_code == CLD_KILLED   ) fprintf(stderr, "CLD_KILLED: Child was killed.\n");
			else if(si->si_code == CLD_DUMPED   ) fprintf(stderr, "CLD_DUMPED: Child terminated abnormally.\n");
			else if(si->si_code == CLD_TRAPPED  ) fprintf(stderr, "CLD_TRAPPED: Traced child has trapped.\n");
			else if(si->si_code == CLD_STOPPED  ) fprintf(stderr, "CLD_STOPPED: Child has stopped.\n");
			else if(si->si_code == CLD_CONTINUED) fprintf(stderr, "CLD_CONTINUED: Stopped child has continued.\n");
			else                                  fprintf(stderr, "Unknow\n");

			break;

		case SIGCONT:
			break;

		case SIGTSTP:
			break;

		case SIGTTIN:
			break;

		case SIGTTOU:
			break;

		case SIGBUS:
			fprintf(stderr, "SIGBUS: ");

			if     (si->si_code == BUS_ADRALN)    fprintf(stderr, "BUS_ADRALN: Invalid address alignment.\n");
			else if(si->si_code == BUS_ADRERR)    fprintf(stderr, "BUS_ADRERR: Nonexistent physical address.\n");
			else if(si->si_code == BUS_OBJERR)    fprintf(stderr, "BUS_OBJERR: Object-specific hardware error.\n");
			else if(si->si_code == BUS_MCEERR_AR) fprintf(stderr, "BUS_MCEERR_AR: Hardware memory error consumed on a machine check; action required.\n");
			else if(si->si_code == BUS_MCEERR_AO) fprintf(stderr, "BUS_MCEERR_AO: Hardware memory error detected in process but not consumed; action optional.\n");
			else                                  fprintf(stderr, "Unknow\n");

			break;

		case SIGPOLL: /* SIGIO */
			fprintf(stderr, "SIGPOLL/SIGIO: ");

			if     (si->si_code == POLL_IN ) fprintf(stderr, "POLL_IN: Data input available.\n");
			else if(si->si_code == POLL_OUT) fprintf(stderr, "POLL_OUT: Output buffers available.\n");
			else if(si->si_code == POLL_MSG) fprintf(stderr, "POLL_MSG: Input message available.\n");
			else if(si->si_code == POLL_ERR) fprintf(stderr, "POLL_ERR: I/O error.\n");
			else if(si->si_code == POLL_PRI) fprintf(stderr, "POLL_PRI: High priority input available.\n");
			else if(si->si_code == POLL_HUP) fprintf(stderr, "POLL_HUP: Device disconnected.\n");
			else                             fprintf(stderr, "Unknow\n");

			break;

		case SIGPROF:
			break;

		case SIGSYS:
			/*
			fprintf(stderr, "SIGSYS: ");

			if (si->si_code == SYS_SECCOMP) fprintf(stderr, "SYS_SECCOMP: Triggered by a seccomp(2) filter rule.\n");
			else                            fprintf(stderr, "Unknow\n");
			*/

			break;

		case SIGTRAP:
			fprintf(stderr, "SIGTRAP: ");

			if     (si->si_code == TRAP_BRKPT ) fprintf(stderr, "TRAP_BRKPT: Process breakpoint.\n");
			else if(si->si_code == TRAP_TRACE ) fprintf(stderr, "TRAP_TRACE: Process trace trap.\n");
			/*
			else if(si->si_code == TRAP_BRANCH) fprintf(stderr, "TRAP_BRANCH: Process taken branch trap.\n");
			else if(si->si_code == TRAP_HWBKPT) fprintf(stderr, "TRAP_HWBKPT: Hardware breakpoint/watchpoint.\n");
			*/
			else                                fprintf(stderr, "Unknow\n");
			break;

		case SIGURG:
			break;

		case SIGVTALRM:
			break;

		case SIGXCPU:
			break;

		case SIGXFSZ:
			break;

		/*
		case SIGEMT:
			break;
		*/

		case SIGSTKFLT:
			break;

		case SIGPWR:
			break;

		/*
		case SIGINFO:
			break;
		*/

		/*
		case SIGLOST:
			break;
		*/

		case SIGWINCH:
			fprintf(stderr, "SIGWINCH: Window resize signal.\n");
			break;

		/*
		case SIGUNUSED:
			break;
		*/

		default:
			break;
	}

	return;
}

int main(int argc, char *argv[])
{
	int pauseRet = 0;
	struct sigaction new_action, old_action;

	/* Cleanup new_action */
	new_action.sa_flags = 0;
	new_action.sa_flags = SA_SIGINFO; /* SA_NOCLDSTOP|SA_NOCLDWAIT|SA_NODEFER|SA_ONSTACK|SA_RESETHAND|SA_RESTART|SA_RESTORER */
	new_action.sa_sigaction = functionHandle;
	/* new_action.sa_handler = functionHandle;   do not set because sa_flags and sa_sigaction are set */
	sigemptyset(&new_action.sa_mask);

	fprintf(stderr, "PID: [%d]\n", getpid());

	sigaction(SIGINT, NULL, &old_action); /* Get actual status of SIGINT */
	if(old_action.sa_handler != SIG_IGN) /* if SIGINT is not (already) SIG_IGN ... */
		sigaction(SIGINT, &new_action, NULL); /* ... connect SIGINT to new_action->sa_sigaction */

	sigaction(SIGHUP, NULL, &old_action);
	if(old_action.sa_handler != SIG_IGN)
		sigaction(SIGHUP, &new_action, NULL);

	sigaction(SIGTERM, NULL, &old_action);
	if(old_action.sa_handler != SIG_IGN)
		sigaction(SIGTERM, &new_action, NULL);

	sigaction(SIGFPE, NULL, &old_action);
	if(old_action.sa_handler != SIG_IGN)
		sigaction(SIGFPE, &new_action, NULL);

	sigaction(SIGWINCH, NULL, &old_action); /* Well used by ncurses (just change terminal/window size to test) */
	if(old_action.sa_handler != SIG_IGN)
		sigaction(SIGWINCH, &new_action, NULL);

	pauseRet = pause();
	if(pauseRet == -1)
		fprintf(stderr, "pause(2) returned: [%s]\n", strerror(errno));

	/* or simple test to SIGFPE:
	pauseRet = 4/0;
	*/

	return(0);
}
