#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>

int
main (void)
{
  struct utsname os_info;
  struct sysinfo s_info;
  char *user, *shell;
  long uptime_hours, uptime_mins;

  user = getenv ("USER");
  shell = getenv ("SHELL");
  uname (&os_info);
  sysinfo (&s_info);

  uptime_hours = s_info.uptime / 3600;
  uptime_mins = (s_info.uptime % 3600) / 60;

  printf (
      "  \033[34m.-.\033[0m      \033[1;34m%s\033[0m@\033[1;34m%s\033[0m\n",
      user ? user : "user", os_info.nodename);
  printf ("  \033[34m(o o)\033[0m     -----------\n");
  printf ("  \033[34m| v |\033[0m     \033[1;34mOS:\033[0m     %s %s\n",
          os_info.sysname, os_info.machine);
  printf (" \033[34m/|   |\\\033[0m    \033[1;34mKernel:\033[0m %s\n",
          os_info.release);
  printf (" \033[34m~ ~ ~ ~\033[0m    \033[1;34mUptime:\033[0m %ldh %ldm\n",
          uptime_hours, uptime_mins);
  printf ("            \033[1;34mShell:\033[0m  %s\n",
          shell ? shell : "unknown");
  printf ("            \033[1;34mMemory:\033[0m %ld / %ld MB\n",
          (s_info.totalram - s_info.freeram) / 1024 / 1024,
          s_info.totalram / 1024 / 1024);

  return 0;
}
