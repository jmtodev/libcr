/*
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
 * Filename    : libcr.h
 * Description : lib control room header
 *
 * + This is part of libentrance
 * + 2023 - Author(s): Ahmad Amarullah
 *
 */

#ifndef __libcr_h__
#define __libcr_h__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

/**
 * DEFINE State Transaksi
 */
#define LIBCR_DEFAULT_PORT 8280 /* Port Default LibCR (8280) */

/**
 * DEFINE State Transaksi
 */
#define LIBCR_TRXSTATE_NOREADY 0 /* Belum SOP / Bukan dalam mode transaksi */
#define LIBCR_TRXSTATE_READY 1   /* Siap Transaksi (sebelum transaksi) */
#define LIBCR_TRXSTATE_TRANS 2   /* Proses Transaksi s/d sebelum deteksi */

/**
 * DEFINE Tarif
 */
#define LIBCR_TARIF_NONE -1 /* Tidak ada tarif */

/**
 * DEFINE State LLB
 */
#define LIBCR_LLB_NONE -1 /* Tidak ada info llb */
#define LIBCR_LLB_RED 0   /* llb merah */
#define LIBCR_LLB_GREEN 1 /* llb hijau */

/**
 * DEFINE Golongan
 */
#define LIBCR_GOL_CLEAR 0 /* Clear/Cancel Golongan */
#define LIBCR_GOL_1 1     /* Golongan 1 / BUS */
#define LIBCR_GOL_2 2     /* Golongan 2 */
#define LIBCR_GOL_3 3     /* Golongan 3 */
#define LIBCR_GOL_4 4     /* Golongan 4 */
#define LIBCR_GOL_5 5     /* Golongan 5 */

/**
 * DEFINE Keycode
 */
#define LIBCR_KEY_GOL1 1   /* GOL1 */
#define LIBCR_KEY_GOL2 2   /* GOL2 */
#define LIBCR_KEY_GOL3 3   /* GOL3 */
#define LIBCR_KEY_GOL4 4   /* GOL4 */
#define LIBCR_KEY_GOL5 5   /* GOL5 */
#define LIBCR_KEY_TEST 6   /* TEST PRINT */
#define LIBCR_KEY_REG 7    /* REG */
#define LIBCR_KEY_BSP 8    /* BACKSPACE */
#define LIBCR_KEY_CAN 9    /* CANCEL */
#define LIBCR_KEY_RESET 10 /* RESET */
#define LIBCR_KEY_MENU 11  /* MENU */
#define LIBCR_KEY_LLA 12   /* LLA */
#define LIBCR_KEY_EXT1 13  /* Extra Key 1 (example: left) */
#define LIBCR_KEY_EXT2 14  /* Extra Key 2 (example: right) */
#define LIBCR_KEY_EXT3 15  /* Extra Key 3 (example: up) */
#define LIBCR_KEY_EXT4 16  /* Extra Key 4 (example: down) */
#define LIBCR_KEY_EXT5 17  /* Extra Key 5 (example: alb/dns) */
#define LIBCR_KEY_EXT6 18  /* Extra Key 6 - unavailable */
#define LIBCR_KEY_EXT7 19  /* Extra Key 7 - unavailable */
#define LIBCR_KEY_NUM0 20  /* NUMBER 0 */
#define LIBCR_KEY_NUM1 21  /* NUMBER 1 */
#define LIBCR_KEY_NUM2 22  /* NUMBER 2 */
#define LIBCR_KEY_NUM3 23  /* NUMBER 3 */
#define LIBCR_KEY_NUM4 24  /* NUMBER 4 */
#define LIBCR_KEY_NUM5 25  /* NUMBER 5 */
#define LIBCR_KEY_NUM6 26  /* NUMBER 6 */
#define LIBCR_KEY_NUM7 27  /* NUMBER 7 */
#define LIBCR_KEY_NUM8 28  /* NUMBER 8 */
#define LIBCR_KEY_NUM9 29  /* NUMBER 9 */

/**
 * DEFINE CST Mifare Key Type
 */
#define LIBCR_CST_KEY_TYPE_A 0 /* Mifare Key Type-A */
#define LIBCR_CST_KEY_TYPE_B 1 /* Mifare Key Type-B */

/**
 * DEFINE Log Level
 */
#define LIBCR_LOGLEVEL_NONE 0    /* Jangan lakukan log */
#define LIBCR_LOGLEVEL_ERROR 1   /* Log ketika ada error */
#define LIBCR_LOGLEVEL_WARNING 2 /* Log ketika ada error+warning */
#define LIBCR_LOGLEVEL_INFO 3    /* Log ketika ada error+warning+informasi */
#define LIBCR_LOGLEVEL_MORE 4    /* Log dengan informasi lengkap */
#define LIBCR_LOGLEVEL_VERBOSE 5 /* Log secara mendetail */

/**
 * DEFINE Error Code
 */
#define LIBCR_OK 0              /* Tidak terjadi error */
#define LIBCR_ERR_ARG -1        /* Argumen yang disertakan tidak valid */
#define LIBCR_ERR_INIT -2       /* Init service gagal */
#define LIBCR_ERR_REINIT -3     /* Service sebelumnya masih berjalan */
#define LIBCR_ERR_NOSERVICE -4  /* Service belum dijalankan (di-init) */
#define LIBCR_ERR_NOSECTORID -5 /* Sector-id mifare belum terdaftar */

/**
 * STRUCT `libcr_cstdata_t`
 * Struktur data mifare yang akan dikirimkan pada event tap kartu pada CST.
 * terdiri dari block 1 sampai 3. Block 0 tidak akan dikirimkan.
 */
typedef struct {
  char uuid[16];      /* HEX String UUID Kartu */
  uint8_t sector_id;  /* ID Sektor */
  uint8_t block1[16]; /* 16byte data pada block 1 (relatif-sektor) */
  uint8_t block2[16]; /* 16byte data pada block 2 (relatif-sektor) */
  uint8_t block3[16]; /* 16byte data pada block 3 (relatif-sektor) */
} libcr_cstdata_t;

/**
 * Callback interface untuk menerima event keyboard dari ControlRoom.
 * @param keycode Kode keyboard yang ditekan. Lihat <b>LIBCR_KEY_*</b>
 * @return <b>void</b> tidak perlu memberikan return
 */
typedef void (*libcr_keyboard_cb)(uint8_t keycode);

/**
 * Callback interface untuk menerima event tap CST
 * @param data Data kartu yang di tap di control room
 * @param data_length Jumlah data/sektor yang didapat
 * @return <b>void</b> tidak perlu memberikan return
 */
typedef void (*libcr_cst_cb)(const libcr_cstdata_t* data, size_t data_length);

/**
 * Callback interface untuk logging
 * @param log String log
 * @param log_length Panjang string log
 * @return <b>void</b> tidak perlu memberikan return
 */
typedef void (*libcr_log_cb)(const char* log, int log_length);

/**
 * Inisialisasi dan mulai service control room. Hanya panggil sekali ketika
 * program dimulai, dan jalankan <b>libcr_close</b> ketika program selesai.
 * @param kode_gerbang Kode gerbang (1-99)
 * @param kode_gardu Kode gardu (1-99)
 * @param nama_gardu Nama gardu (contoh: KALIHUTIP UTAMA 1)
 * @param tipe_gardu Tipe gardu (contoh: OPEN, EXIT, ENTRANCE, OPEN-ENTRANCE)
 * @param port Port TCP yang akan digunakan (Rekomendasi `LIBCR_DEFAULT_PORT`)
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_init(uint8_t kode_gerbang, uint8_t kode_gardu, const char* nama_gardu,
               const char* tipe_gardu, int port);

/**
 * Hentikan service control room.
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_close();

/**
 * Cek apakah service control room berjalan
 * @return <b>LIBCR_OK</b> bila aktif, <b>LIBCR_ERR_NOSERVICE</b> bila non-aftif
 */
int libcr_is_active();

/**
 * Set callback untuk penerima event keyboard
 * @param callback Fungsi callback. Isi NULL bila nonaktif
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_set_keyboard_cb(libcr_keyboard_cb callback);

/**
 * Set callback untuk penerima event cst
 * @param callback Fungsi callback. Isi NULL bila nonaktif
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_set_cst_cb(libcr_cst_cb callback);

/**
 * Set callback untuk penerima message log
 * @param callback Fungsi callback. Isi NULL bila nonaktif
 * @param loglevel Lihat <b>LIBCR_LOGLEVEL_*</b>
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_set_log_cb(libcr_log_cb callback, uint8_t loglevel);

/**
 * Tambah request sektor mifare yang akan dibaca ketika kartu mifare di tap.
 * Fungsi dapat dipanggil berkali-kali untuk memerintahkan read multi-sektor.
 * Bila sector_id pernah di-add sebelumnya, maka data key sector tersebut akan
 * ditimpa. Max sector yang direquest sebanyak 5 sektor.
 * @param sector_id ID sektor mifare yang akan dibaca
 * @param keytype Lihat <b>LIBCR_CST_KEY_TYPE_*</b>
 * @param key Hex string mifare key untuk sektor yang dimaksud
 * @param sector_id ID sektor mifare yang akan dibaca
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_cst_add_sector(uint8_t sector_id, uint8_t keytype, const char* key);

/**
 * Hapus request sektor mifare yang akan dibaca ketika kartu mifare di tap.
 * @param sector_id ID sektor mifare yang akan hapus
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_cst_remove_sector(uint8_t sector_id);

/**
 * Dapatkan jumlah sektor yang sudah direquest
 * @return <b>Error Code.</b> atau jumlah sektor yang sudah di request (&gt;=0)
 */
int libcr_cst_num_sector();

/**
 * Set state transaksi saat ini. Selalu panggil ketika selesai SOP, mulai EOP,
 * transaksi berhasil dan terjadi deteksi
 * @param trxstate State transaksi saat ini. Lihat <b>LIBCR_TRXSTATE_*</b>
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_set_trxstate(uint8_t trxstate);

/**
 * Set golongan saat ini. Selalu panggil ketika golongan kendaraan berubah.
 * Set <b>LIBCR_GOL_CLEAR</b> untuk clear golongan.
 * @param golongan Golongan kendaraan (1-5), atau <b>LIBCR_GOL_CLEAR</b>
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_set_golongan(int8_t golongan);

/**
 * Set golongan yang didapatkan avc. Selalu panggil ketika golongan avc berubah.
 * Set <b>LIBCR_GOL_CLEAR</b> untuk clear golongan avc.
 * @param golongan Golongan avc (1-5), atau <b>LIBCR_GOL_CLEAR</b>
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_set_golongan_avc(uint8_t golongan);

/**
 * Set tarif saat ini. Selalu panggil ketika tarif berubah.
 * Set <b>LIBCR_TARIF_NONE</b> untuk clear tarif.
 * @param tarif Tarif dalam integer, atau <b>LIBCR_TARIF_NONE</b>
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_set_tarif(int32_t tarif);

/**
 * Set status llb saat ini. Selalu panggil ketika state llb berubah.
 * Set <b>LIBCR_LLB_NONE</b> bila tidak akan mengirimkan status perubahan llb.
 * @param llb Lihat <b>LIBCR_LLB_*</b>
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_set_llb(int8_t llb);

/**
 * Set message yang akan ditampilkan di control room saat ini. Dapat digunakan
 * sebagai sarana informasi untuk CS, misalnya:<br>
 * - TENTUKAN GOLONGAN KENDARAAN<br>
 * - TAP KARTU OPERASIONAL UNTUK SOP<br>
 * - MASUKAN PIN: 123_<br>
 * - TRANSAKSI BERHASIL. MENUNGGU DETEKSI<br><br>
 * Isi dengan `NULL` bila akan mengosongkan pesan.
 * @param message Message yang akan tampil (max 256 karakter).
 * @return <b>Error Code.</b> Lihat <b>LIBCR_OK</b> atau <b>LIBCR_ERR_*</b>
 */
int libcr_set_message(const char* message);

/* [END-DOC] */
/* end of extern for cpp */
#ifdef __cplusplus
}
#endif
#endif /* __libentrance_h__ */