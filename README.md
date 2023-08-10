# JMTO Control Room Service Library (LibCR)

**`LibCR`** merupakan library untuk menyediakan **service** komunikasi data antar aplikasi **Toll Collector**
dengan aplikasi **Control-Room JMTO**. Library akan mengurus semua proses komunikasi, dari mulai inisialisasi
`port server`, protokol komunikasi, hingga kontrol pengiriman data.

Aplikasi **Toll Collector** hanya perlu menyisipkan **library**, melakukan **inisialisasi** dan selanjutnya melakukan
*provide* informasi-informasi yang dibutuhkan oleh **Control-Room** dengan menggunakan fungsi-fungsi yang
telah tersedia.

Untuk penerimaan `data/event` dari **Control-Room**, aplikasi **Toll Collector** dapat melakukan
*registrasi* fungsi `callback`, baik itu untuk mendapatkan `event keyboard` ataupun `event cst`.

Library tersedia untuk `Linux` dalam `3` arsitektur, diantaranya:
* `amd64` - Intel/AMD x86 dengan 64bit
* `aarch64` - ARM 64bit
* `armv7` - ARM 32bit

Sedangkan untuk `QNX/NTO` hanya disediakan arsitektur `i386` (Intel/AMD x86 dengan 32bit)

## Library
Library dibangun sebagai library untuk `C/C++` yang dapat digunakan pada environment `gcc`.

File library terdiri dari 2 jenis extension `*.a` (pada direktori `lib`) atau `*.o` (pada direktori `obj`).
Aplikasi **Toll Collector** dapat memilih salah-satu format sesuai dengan kebutuhannya.

Berikut adalah nama-nama file binary untuk library beserta keterangan arsitektur dan platformnya:
* `libcr-amd64.a` / `libcr-amd64.o` - Linux x86 64bit
* `libcr-aarch64.a` / `libcr-aarch64.o` - Linux ARM 64bit
* `libcr-armv7.a` / `libcr-armv7.o` - Linux ARMv7
* `libcr-i386-qnx.a` / `libcr-i386-qnx.o` - QNX/NTO x86 32bit

## Test Program
Test program dapat dilihat pada file `example/testlibcr.c`, dan dapat di-build dengan `build_test.sh` (Hanya untuk Linux). Berikut command untuk melakukan build sesuai dengan arsitektur yang dituju:

``` bash
# Build untuk x86 64bit
./build_test.sh

# Build untuk arm-64
./build_test.sh aarch64

# Build untuk arm-v7 32bit
./build_test.sh armv7
```

----

# Referensi Library

---
## Struktur Data

### `libcr_cstdata_t`
Struktur data mifare yang akan dikirimkan pada event tap kartu pada CST.
terdiri dari block 1 sampai 3. Block 0 tidak akan dikirimkan.

``` c
typedef struct {
  uint8_t status;     /* Status pembacaan kartu. Lihat LIBCR_CSTSTATUS_* */
  uint8_t sector_id;  /* ID Sektor */
  uint8_t block1[16]; /* 16byte data pada block 1 (relatif-sektor) */
  uint8_t block2[16]; /* 16byte data pada block 2 (relatif-sektor) */
  uint8_t block3[16]; /* 16byte data pada block 3 (relatif-sektor) */
} libcr_cstdata_t;
```




---
## Callback Functions

### `*libcr_keyboard_cb()`
Callback interface untuk menerima event keyboard dari ControlRoom. 
#### Arguments
- `keycode` : Kode keyboard yang ditekan. Lihat `LIBCR_KEY_*`
 
#### Return Value
- `void` tidak perlu memberikan return

``` c
typedef void (*libcr_keyboard_cb)(uint8_t keycode);
```

### `*libcr_cst_cb()`
Callback interface untuk menerima event tap CST 
#### Arguments
- `uuid` : Hex String (null terminated) untuk UUID kartu yang di tap
- `data` : Data kartu yang di tap di control room
- `data_length` : Jumlah data/sektor yang didapat
 
#### Return Value
- `void` tidak perlu memberikan return

``` c
typedef void (*libcr_cst_cb)(const char* uuid, const libcr_cstdata_t* data,
                             size_t data_length);
```

### `*libcr_log_cb()`
Callback interface untuk logging 
#### Arguments
- `log` : String log
- `log_length` : Panjang string log
 
#### Return Value
- `void` tidak perlu memberikan return

``` c
typedef void (*libcr_log_cb)(const char* log, int log_length);
```




---
## Functions

### `libcr_init()`
Inisialisasi dan mulai service control room. Hanya panggil sekali ketika program dimulai, dan jalankan `libcr_close` ketika program selesai. 
#### Arguments
- `port` : Port TCP yang akan digunakan (Rekomendasi `LIBCR_DEFAULT_PORT`)
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_init(
    int port
);
```

### `libcr_close()`
Hentikan service control room. 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_close();
```

### `libcr_set_info()`
Set detail informasi gardu. Disarankan informasi awal ini telah di-set sebelum menjalankan `libcr_init()`. 
#### Arguments
- `kode_gerbang` : Kode gerbang (1-99)
- `kode_gardu` : Kode gardu (1-99)
- `nama_gardu` : Nama gardu (contoh: KALIHUTIP UTAMA 1)
- `tipe_gardu` : Tipe gardu (contoh: OPEN, EXIT, ENTRANCE, OPEN-ENTRANCE)
- `port` : Port TCP yang akan digunakan (Rekomendasi `LIBCR_DEFAULT_PORT`)
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_set_info(
    uint8_t kode_gerbang,
    uint8_t kode_gardu,
    const char* nama_gardu,
    const char* tipe_gardu
);
```

### `libcr_is_active()`
Cek apakah service control room berjalan 
#### Return Value
- `LIBCR_OK` bila aktif, `LIBCR_ERR_NOSERVICE` bila non-aftif

``` c
int libcr_is_active();
```

### `libcr_set_keyboard_cb()`
Set callback untuk penerima event keyboard 
#### Arguments
- `callback` : Fungsi callback. Isi NULL bila nonaktif
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_set_keyboard_cb(
    libcr_keyboard_cb callback
);
```

### `libcr_set_cst_cb()`
Set callback untuk penerima event cst 
#### Arguments
- `callback` : Fungsi callback. Isi NULL bila nonaktif
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_set_cst_cb(
    libcr_cst_cb callback
);
```

### `libcr_set_log_cb()`
Set callback untuk penerima message log 
#### Arguments
- `callback` : Fungsi callback. Isi NULL bila nonaktif
- `loglevel` : Lihat `LIBCR_LOGLEVEL_*`
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_set_log_cb(
    libcr_log_cb callback,
    uint8_t loglevel
);
```

### `libcr_cst_reg_sector()`
Tambah registrasi request sektor mifare. Sektor yang telah teregistrasi akan dibaca CST Control Room ketika kartu mifare di-tap, dan data akan dikirimkan melalui callback yang telah diset dengan fungsi `libcr_set_cst_cb`.

 Registrasi multiple sektor dapat dilakukan dengan menjalankan fungsi ini kembali dengan argument `sector_id` yang berbeda.

 Bila fungsi ini dipanggil kembali dengan `sector_id` sebelumnya telah teregistrasi, maka data `keytype` dan `key` pada registrasi sector tersebut akan ditimpa.

 **Jumlah maksimal** sector yang dapat diregistrasi adalah sebanyak `5 sektor`. 
#### Arguments
- `sector_id` : ID sektor mifare yang akan dibaca
- `keytype` : Lihat `LIBCR_CST_KEY_TYPE_*`
- `key` : Hex string mifare key untuk sektor yang dimaksud
- `sector_id` : ID sektor mifare yang akan dibaca
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_cst_reg_sector(
    uint8_t sector_id,
    uint8_t keytype,
    const char* key
);
```

### `libcr_cst_unreg_sector()`
Hapus registrasi request sektor mifare yang sebelumnya pernah diregistrasi menggunakan fungsi `libcr_cst_reg_sector`. 
#### Arguments
- `sector_id` : ID sektor mifare yang akan hapus
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_cst_unreg_sector(
    uint8_t sector_id
);
```

### `libcr_cst_num_sector()`
Dapatkan jumlah sektor yang sudah direquest 
#### Return Value
- `Error Code.` atau jumlah sektor yang sudah di request (&gt;=0)

``` c
int libcr_cst_num_sector();
```

### `libcr_set_trxstate()`
Set state transaksi saat ini. Selalu panggil ketika selesai SOP, mulai EOP, transaksi berhasil dan terjadi deteksi 
#### Arguments
- `trxstate` : State transaksi saat ini. Lihat `LIBCR_TRXSTATE_*`
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_set_trxstate(
    uint8_t trxstate
);
```

### `libcr_set_golongan()`
Set golongan saat ini. Selalu panggil ketika golongan kendaraan berubah. Set `LIBCR_GOL_CLEAR` untuk clear golongan. 
#### Arguments
- `golongan` : Golongan kendaraan (1-5), atau `LIBCR_GOL_CLEAR`
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_set_golongan(
    int8_t golongan
);
```

### `libcr_set_golongan_avc()`
Set golongan yang didapatkan avc. Selalu panggil ketika golongan avc berubah. Set `LIBCR_GOL_CLEAR` untuk clear golongan avc. 
#### Arguments
- `golongan` : Golongan avc (1-5), atau `LIBCR_GOL_CLEAR`
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_set_golongan_avc(
    uint8_t golongan
);
```

### `libcr_set_tarif()`
Set tarif saat ini. Selalu panggil ketika tarif berubah. Set `LIBCR_TARIF_NONE` untuk clear tarif. 
#### Arguments
- `tarif` : Tarif dalam integer, atau `LIBCR_TARIF_NONE`
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_set_tarif(
    int32_t tarif
);
```

### `libcr_set_llb()`
Set status llb saat ini. Selalu panggil ketika state llb berubah. Set `LIBCR_LLB_NONE` bila tidak akan mengirimkan status perubahan llb. 
#### Arguments
- `llb` : Lihat `LIBCR_LLB_*`
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_set_llb(
    int8_t llb
);
```

### `libcr_set_message()`
Set message yang akan ditampilkan di control room saat ini. Dapat digunakan sebagai sarana informasi untuk CS, misalnya:
 - TENTUKAN GOLONGAN KENDARAAN
 - TAP KARTU OPERASIONAL UNTUK SOP
 - MASUKAN PIN: 123_
 - TRANSAKSI BERHASIL. MENUNGGU DETEKSI

 Isi dengan `NULL` bila akan mengosongkan pesan. 
#### Arguments
- `message` : Message yang akan tampil (max 256 karakter).
 
#### Return Value
- `Error Code.` Lihat `LIBCR_OK` atau `LIBCR_ERR_*`

``` c
int libcr_set_message(
    const char* message
);
```




---
## Constants

### State Transaksi
| NAME | VALUE | Keterangan |
| ------ | ------ | ------ |
|`LIBCR_DEFAULT_PORT`|`8280`|Port Default LibCR (8280)|
### State Transaksi
| NAME | VALUE | Keterangan |
| ------ | ------ | ------ |
|`LIBCR_TRXSTATE_NOREADY`|`0`|Belum SOP / Bukan dalam mode transaksi|
|`LIBCR_TRXSTATE_READY`|`1`|Siap Transaksi (sebelum transaksi)|
|`LIBCR_TRXSTATE_TRANS`|`2`|Proses Transaksi s/d sebelum deteksi|
### Tarif
| NAME | VALUE | Keterangan |
| ------ | ------ | ------ |
|`LIBCR_TARIF_NONE`|`-1`|Tidak ada tarif|
### State LLB
| NAME | VALUE | Keterangan |
| ------ | ------ | ------ |
|`LIBCR_LLB_NONE`|`-1`|Tidak ada info llb|
|`LIBCR_LLB_RED`|`0`|llb merah|
|`LIBCR_LLB_GREEN`|`1`|llb hijau|
### Golongan
| NAME | VALUE | Keterangan |
| ------ | ------ | ------ |
|`LIBCR_GOL_CLEAR`|`0`|Clear/Cancel Golongan|
|`LIBCR_GOL_1`|`1`|Golongan 1 / BUS|
|`LIBCR_GOL_2`|`2`|Golongan 2|
|`LIBCR_GOL_3`|`3`|Golongan 3|
|`LIBCR_GOL_4`|`4`|Golongan 4|
|`LIBCR_GOL_5`|`5`|Golongan 5|
### Keycode
| NAME | VALUE | Keterangan |
| ------ | ------ | ------ |
|`LIBCR_KEY_GOL1`|`1`|GOL1|
|`LIBCR_KEY_GOL2`|`2`|GOL2|
|`LIBCR_KEY_GOL3`|`3`|GOL3|
|`LIBCR_KEY_GOL4`|`4`|GOL4|
|`LIBCR_KEY_GOL5`|`5`|GOL5|
|`LIBCR_KEY_TEST`|`6`|TEST PRINT|
|`LIBCR_KEY_REG`|`7`|REG|
|`LIBCR_KEY_BSP`|`8`|BACKSPACE|
|`LIBCR_KEY_CAN`|`9`|CANCEL|
|`LIBCR_KEY_RESET`|`10`|RESET|
|`LIBCR_KEY_MENU`|`11`|MENU|
|`LIBCR_KEY_LLA`|`12`|LLA|
|`LIBCR_KEY_EXT1`|`13`|Extra Key 1 (example: left)|
|`LIBCR_KEY_EXT2`|`14`|Extra Key 2 (example: right)|
|`LIBCR_KEY_EXT3`|`15`|Extra Key 3 (example: up)|
|`LIBCR_KEY_EXT4`|`16`|Extra Key 4 (example: down)|
|`LIBCR_KEY_EXT5`|`17`|Extra Key 5 (example: alb/dns)|
|`LIBCR_KEY_EXT6`|`18`|Extra Key 6 - unavailable|
|`LIBCR_KEY_EXT7`|`19`|Extra Key 7 - unavailable|
|`LIBCR_KEY_NUM0`|`20`|NUMBER 0|
|`LIBCR_KEY_NUM1`|`21`|NUMBER 1|
|`LIBCR_KEY_NUM2`|`22`|NUMBER 2|
|`LIBCR_KEY_NUM3`|`23`|NUMBER 3|
|`LIBCR_KEY_NUM4`|`24`|NUMBER 4|
|`LIBCR_KEY_NUM5`|`25`|NUMBER 5|
|`LIBCR_KEY_NUM6`|`26`|NUMBER 6|
|`LIBCR_KEY_NUM7`|`27`|NUMBER 7|
|`LIBCR_KEY_NUM8`|`28`|NUMBER 8|
|`LIBCR_KEY_NUM9`|`29`|NUMBER 9|
### CST Mifare Key Type
| NAME | VALUE | Keterangan |
| ------ | ------ | ------ |
|`LIBCR_CST_KEY_TYPE_A`|`0`|Mifare Key Type-A|
|`LIBCR_CST_KEY_TYPE_B`|`1`|Mifare Key Type-B|
### CST Read Sector Status
| NAME | VALUE | Keterangan |
| ------ | ------ | ------ |
|`LIBCR_CSTSTATUS_OK`|`0`|Pembacaan berhasil|
|`LIBCR_CSTSTATUS_ERR_AUTH`|`1`|Auth Sector Gagal|
|`LIBCR_CSTSTATUS_ERR_READ`|`2`|Proses baca setelah auth gagal|
### Log Level
| NAME | VALUE | Keterangan |
| ------ | ------ | ------ |
|`LIBCR_LOGLEVEL_NONE`|`0`|Jangan lakukan log|
|`LIBCR_LOGLEVEL_ERROR`|`1`|Log ketika ada error|
|`LIBCR_LOGLEVEL_WARNING`|`2`|Log ketika ada error+warning|
|`LIBCR_LOGLEVEL_INFO`|`3`|Log ketika ada error+warning+informasi|
|`LIBCR_LOGLEVEL_MORE`|`4`|Log dengan informasi lengkap|
|`LIBCR_LOGLEVEL_VERBOSE`|`5`|Log secara mendetail|
### Error Code
| NAME | VALUE | Keterangan |
| ------ | ------ | ------ |
|`LIBCR_OK`|`0`|Tidak terjadi error|
|`LIBCR_ERR_ARG`|`-1`|Argumen yang disertakan tidak valid|
|`LIBCR_ERR_INIT`|`-2`|Init service gagal|
|`LIBCR_ERR_REINIT`|`-3`|Service sebelumnya masih berjalan|
|`LIBCR_ERR_NOSERVICE`|`-4`|Service belum dijalankan (di-init)|
|`LIBCR_ERR_NOSECTORID`|`-5`|Sector-id mifare belum terdaftar|



