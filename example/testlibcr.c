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
  libcr_set_info(1, 2, "PASTEUR 1", LIBCR_GARDU_MULTI, LIBCR_GERBANG_EXIT);

  libcr_init(LIBCR_DEFAULT_PORT);

  sleep(20);

  libcr_close();

  return 0;
}
