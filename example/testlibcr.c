#include <libcr.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void httpd_close();

/* Log Output */
static void print_log(const char* log, int log_length) {
  printf("[LOG-%i] %s", log_length, log);
}

int main(int argc, char** argv) {
  libcr_set_log_cb(print_log, LIBCR_LOGLEVEL_VERBOSE);

  libcr_init(1, 2, "PASTEUR 1", "OPEN", LIBCR_DEFAULT_PORT);

  sleep(10);

  libcr_close();

  return 0;
}
