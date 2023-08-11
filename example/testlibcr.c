/*******************************************************************************
 * Copyright (C) 2023 JMTO (https://jmto.co.id/)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *______________________________________________________________________________
 *
 * Filename    : testlibcr.c
 * Description : Example program libcr
 *
 * + This is part of libcr
 * + 2023 - Author(s): Ahmad Amarullah
 *
 */

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
