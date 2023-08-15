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
#include <ctype.h> /* tolower */

#define APP_NAME "TCT 1.20"

void httpd_close();

/* Log Output */
static void print_log(const char* log, int log_length) {
  printf("[LOG-%i] %s", log_length, log);
}

/* Keyboard Event Callback */
static void on_key_event(uint8_t keycode) {
  if (keycode == LIBCR_KEY_GOL1) {
    /* Bila Tombol GOL1 Ditekan, Tampilkan Message */
    printf("---> TOMBOL GOL1 DITEKAN\n");
  } else {
    printf("---> TOMBOL DENGAN KODE #%i DITEKAN\n", keycode);
  }
}

/* Print Help untuk Example */
void print_help() {
  printf("\n");
  printf("INPUT UNTUK MELAKUKAN ACTION\n");
  printf("----------------------------\n");
  printf("1-5. Ubah Golongan         0. Clear Golongan\n");
  printf("A-E. Ubah Golongan AVC     Z. Clear Golongan AVC\n");
  printf("S.   SOP / EOP             M. Ubah Message\n");
  printf("L.   Ubah LLB              T. Tarif, no-resi & saldo\n");
  printf("H.   Print Help            Q. QUIT\n\n");
}

/* Main Function */
int main(int argc, char** argv) {
  /* Set Log Callback */
  libcr_set_log_cb(print_log, LIBCR_LOGLEVEL_INFO);

  /* Set keyboard event callback */
  libcr_set_keyboard_cb(on_key_event);

  /* Set Informasi Aplikasi TCT */
  libcr_set_info(1, 2, LIBCR_GARDU_MULTI, LIBCR_GERBANG_EXIT, "PASTEUR 1",
                 "PURBALEUNYI");

  /* Mulai Service */
  libcr_init(APP_NAME, LIBCR_DEFAULT_PORT);

  /* Print Help */
  print_help();

  /* Variabel awal */
  int active = 1;

  /* Variabel ubah menu */
  int sop = 0;
  int msg = 0;
  int llb = 0;
  int trf = 0;

  /* Tunggu Key */
  while (active) {
    /* Trap keyboard input */
    int c = tolower(getc(stdin));
    switch (c) {
      case 'q':
        /* Quit */
        active = 0;
        break;
      case 'h':
        /* Print Help */
        print_help();
        break;
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
        /* Set Golongan 1-5 */
        libcr_set_golongan(c - '0');
        break;
      case '0':
        /* Clear Golongan */
        libcr_set_golongan(LIBCR_GOL_CLEAR);
        break;
      case 'a':
      case 'b':
      case 'c':
      case 'd':
      case 'e':
        /* Set Golongan AVC 1-5 */
        libcr_set_golongan_avc(c - 'a' + 1);
        break;
      case 'z':
        /* Clear Golongan AVC */
        libcr_set_golongan_avc(LIBCR_GOL_CLEAR);
        break;
      case 's':
        /* Contoh Update Perioda */
        sop = sop ? 0 : 1;
        if (sop == 1) {
          /* Set SOP (Shift 1, Perioda 4) */
          libcr_set_data_perioda(1002, 2001, 1, 4);
        } else {
          /* Set EOP */
          libcr_set_data_perioda(0, 0, 0, 0);
        }
        break;
      case 'm':
        /* Contoh Set Message */
        if (++msg > 3) msg = 0;
        if (msg == 1)
          libcr_set_message("TENTUKAN GOLONGAN KENDARAAN");
        else if (msg == 2)
          libcr_set_message("TRANSAKSI BERHASIL. MENUNGGU DETEKSI");
        else if (msg == 3)
          libcr_set_message("TAP KARTU OPERASIONAL UNTUK SOP");
        else
          libcr_set_message(NULL);
        break;
      case 'l':
        /* Contoh Update LLB */
        llb = llb == LIBCR_LLB_GREEN ? LIBCR_LLB_RED : LIBCR_LLB_GREEN;
        libcr_set_llb(llb);
        break;
      case 't':
        /* Contoh Set Tarif / Saldo / Nomor Resi */
        if (++msg > 5) msg = 0;
        if (msg == 1)
          libcr_set_tarif(3500);
        else if (msg == 2)
          libcr_set_saldo(54000);
        else if (msg == 3)
          libcr_set_noresi(521);
        else if (msg == 4) {
          libcr_set_tarif(1250);
          libcr_set_saldo(75000);
        } else if (msg == 5) {
          libcr_set_tarif(6000);
          libcr_set_noresi(48690);
          libcr_set_saldo(LIBCR_SALDO_NONE);
        } else {
          libcr_set_tarif(LIBCR_TARIF_NONE);
          libcr_set_noresi(LIBCR_NORESI_NONE);
          libcr_set_saldo(LIBCR_SALDO_NONE);
        }
        break;
    }
  }

  printf("Tutup Aplikasi\n");
  libcr_close();

  return 0;
}
