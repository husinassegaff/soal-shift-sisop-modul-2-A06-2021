# Soal-shift-sisop-modul-2-A06-2021
Jawaban soal praktikum Sistem Operasi modul 2.

**Anggota kelompok**:
```
- Richard Asmarakandi       05111940000017
- Muhammad Rafki Mardi      0511194000054
- Husin Muhammad Assegaff   05111940000127
```
---
## Tabel Konten
- [Soal 1](#soal-1)
  - [Soal 1.a](#soal-1a)
  - [Soal 1.b](#soal-1b)
  - [Soal 1.c](#soal-1c)
  - [Soal 1.d](#soal-1d)
  - [Soal 1.e](#soal-1e)
  - [Soal 1.f](#soal-1f)

- [Soal 2](#soal-2)
  - [Soal 2.a](#soal-2a)
  - [Soal 2.b](#soal-2b)
  - [Soal 2.c](#soal-2c)
  - [Soal 2.d](#soal-2d)
  - [Soal 2.e](#soal-2e)

- [Soal 3](#soal-3)
  - [Soal 3.a](#soal-3a)
  - [Soal 3.b](#soal-3b)
  - [Soal 3.c](#soal-3c)
  - [Soal 3.d](#soal-3d)
  - [Soal 3.e](#soal-3e)

## Soal 1
**[Source Code Soal 1](https://github.com/husinassegaff/soal-shift-sisop-modul-2-A06-2021/blob/main/soal1/soal1.c)**

**Deskripsi:**\
Steven ingin membuat Stevany terkagum dengan menjadi ahli dalam matkul SISOP. Hal yang dilakukan Steven adalah membuat sebuah `program` yang akan menghasilkan File zip berisikan foto, video, dan musik kegemaran Stevany dihari ulang tahunnya.

Untuk mewujudkan hal tersebut Steven ingin agar program tersebut berkerja secara bertahap dalam dua fase.

- Fase pertama, enam jam sebelum ulang tahun Stevany, program `daemon` melakukan secara berurut - urut :
    
    - Membuat direktory dengan nama `Musyik`, `Fylm` dan `Pyoto`.
    - Mengunduh file `.zip` dari link yang disertakan.
    - Mengekstrak `.zip` yang sudah diunduh.
    - Memindahkan file yang ada ada di folder hasil ekstrak ke direktory yang sudah di buat.

- Fase kedua, saat tahun Stevany, program `daemon` melakukan secara berurut - urut :

    - Menzip ketiga direktory yg dibuat ke nama `Lope_you_Stevany.zip`
    - Menghapus direktory yang ada, sehingga menyisakan zip.

**Catatan:**
- Ulang Tahun Stevany : 09 April Pukul 22.22 WIB
- Program berjalan secara `daemon`.
- Tidak boleh menggunakan fungsi `system()`, `mkdir()`, dan `rename()`.
- Tidak boleh pake `cron`.

**_Prequisite_:**

- Karena program harus berjalan secara `daemon`, digunakan template dari [modul 2](https://github.com/arsitektur-jaringan-komputer/Modul-Sisop/blob/master/2021/Modul2/README.md#3-implementasi-daemon).
- Tahapan :
    - Fork _parent process_ dan kill parent proces
    - Mengubah _permission_ interaksi programm daemon dengan program yang ada di _working directory_.
    - Agar dapat berjalan, _child process_ membuat session ID sendiri agar dapat berjalan tanpa _parent_.
    - Mengubah tempat program `daemon` bekerja.
    - Menutup deskripsi standar file alias interaksi ke terminal.
    - Membuat loop utama sebagai tempat program yang ingin kita `daemon`-kan.
- _Library_ yang digunakan berupa

```c
#include <stdio.h>      // library standar
#include <sys/types.h>  // penghasil proses
#include <sys/stat.h>   // Akses atribut informasi
#include <stdlib.h>     // kontrol proses
#include <fcntl.h>      // kontrol file
#include <errno.h>      // kontrol error
#include <unistd.h>     // interaksi dengan POSIX
#include <syslog.h>     // kontrol log dan event
#include <string.h>     // untuk manipulasi string
#include <time.h>       // untuk interaksi terhadap waktu sistem
#include <sys/wait.h>   // agar program tidak terhenti pasca exec ()
#include <dirent.h>     // untuk interaksi terhadap direktory dan isinya
```
- Penyelesaian permintaan soal dilakukan di loop utama.
```c
...   
  while (1) {
    // Tulis program kalian di sini

    sleep(1);
  }
}
...
```
note: 

tanda `...` merupakan kode program yang tidak ditampilkan untuk memudahkan pembacaan.
- Program `daemon` memiliki `sleep(1)` yang berarti akan berjalan setiap satu detik.
- Karena program memiliki trigger berupa waktu, digunakan fungsi dan tipe data dari _library_ `time.h` yakni,
```c
...
time_t rawtime;
struct tm * timeinfo;
int i, stat;
time ( &rawtime );
timeinfo = localtime ( &rawtime );
...
```
note: 

tanda `...` merupakan kode program yang tidak ditampilkan untuk memudahkan pembacaan.

- Variabel `time_t` nantinya akan menyimpan nilai waktu.
- Fungsi `time()` mengembalikan lama waktu sejak 1 Januari 1970 dalam detik.
- Untuk `localtime()` mengembalikan waktu dalam bentuk pointer yang telah terbagi informasi waktnya (detik, menit, hari, tanggal dan seterusnya).
- Dengan `sleep(1)` setiap detih, program akan mengambil nilai waktu tiap satu detik dan dicek ke sebuak _conditional statement_.
- Untuk membagi perintah ke dua periode (enam jam sebelum waktu ulang tahun dan saat ulang tahun) digunakan `if` dan `else if` _conditional statement_
```c
...
// Enam jam sebelum ulang tahun, 9 April 2021 16:22:00
if(timeinfo->tm_mon == 3 && timeinfo->tm_mday== 9 && timeinfo->tm_hour== 16 && timeinfo->tm_min==22 && timeinfo->tm_sec==0){
    ...
}// Waktu ulang tahun, 9 April 2021 16:22:00
else if (timeinfo->tm_mon == 3 && timeinfo->tm_mday== 9 && timeinfo->tm_hour== 22 && timeinfo->tm_min==22 && timeinfo->tm_sec==0){
    ...
}
...
```

note: 

tanda `...` merupakan kode program yang tidak ditampilkan untuk memudahkan pembacaan.

- Karena setiap proses, jika tidak ditangani, akan mengakhiri program digunakan template ini supaya proses tidak langsung menutup program.
```c
...
if ((pid = fork()) == 0){
    //proses
}else{
    waidpid(pid,&stat,0);
    if(WIFEXITED(pid))
    //proses selanjutnya
}
...
```
- Pada kode diatas, kondisi `if` melakukan `fork()` terhadap `daemon`.
- Setelah proses selesai akan dibuat sebuah inisiasi tunggu proses yang baru saja di `fork` dengan nilai tunggu `stat`.
- Pada `WIFEXITED(pid)` memberitahu jika proses `fork(pid)` sudah selesai lakukan perintah selanjutnya.
- Untuk periode pertama, strategi yang dilakukan dalam penyelesaian soal ini adalah dengan iterasi 3 kali yang mana tiap iterasi , secara bertahap, melakukan permintaan `a` hingga `d`.
- Untuk mewujudkan hal ini, kita kembali ke kode di atas, kita melakukan _nested_ 
```c
...
for (i=0; i<3; i++)
{
    if ((pid = fork()) == 0){
        if ((pid = fork()) == 0){
            if ((pid = fork()) == 0){
                //proses a
            }else{
                waidpid(pid,&stat,0);
                if(WIFEXITED(pid))
                //proses b
            }
        }else{
            waidpid(pid,&stat,0);
            if(WIFEXITED(pid))
            //proses c
            else{
                waidpid(pid,&stat,0);
                if(WIFEXITED(pid))
                //proses d
            }
        }
    }
}
...
```

*Soal 1.a hingga 1.d berjalan saat kondisi waktu adalah 9 April dan waktu pukul 16:22:00.*

### Soal 1.a

**Deskripsi:**\
Pada periode pertama, yakni enam jam sebelum ulang tahun Stevany program membuat sebuah direktory bernama `Musyik`, `Fylm` dan `Pyoto`.

**Pembahasan:**

```c
...
char n[3][20]={
    "Musyik",
    "Pyoto",
    "Fylm"
};
...
for (i=0; i<3; i++)
{
    if (...){
        if (...){
            if((pid=fork())==0){
                // proses a
                char *argv[] = {"mkdir",n[i], NULL};
                execv("/bin/mkdir", argv);
            }else
            ...
        }else
        ...
    }else
    ...
}
```

- Proses dilakukan di `proses a`.
- Dibantu array string `n[i][]` untuk menyimpan nama direktory yang akan dibuat.
- Menggunakan `execv(tipe,argumen)` dan pointer string `argv[]`.
- Melaksanakan perintah pembuatan direktori `mkdir` dengan tipe `/bin/mkdir`.
- Tiap iterasi akan membuat direktory sesuai urutan array string.

**Kendala :**\
Tidak ada.

### Soal 1.b
**Deskripsi:**\
Mengunduh file dengan `wget` dari link yang disertakan pada modul soal.

**Pembahasan:**

```c
...
char link[3][100]={
    "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
    "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
    "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"
};
char rn[3][20]={
    "Musyik.zip",
    "Pyoto.zip",
    "Fylm.zip"
};
...
for (i=0; i<3; i++)
{
    if (...){
        if (...){
            if((pid=fork())==0){
                ...
            }else{
                waitpid(pid,&stat,0);
                if (WIFEXITED(stat))
                {
                    char *argv[] = {"wget", "--no-check-certificate",link[i],"-O",rn[i], NULL};
                    execv("/usr/bin/wget", argv);
                }
            }
        }
        ...
    }
    ...
}
```

- Proses dilakukan di `proses b`.
- Dibantu array string `link[i][]` untuk link _download_ dan `rn[i][]` untuk penamaan hasil `wget`.
- Menggunakan `execv(tipe,argumen)` dan pointer string `argv[]`.
- Melaksanakan perintah pengunduhan `wget` dengan tipe `/usr/bin/wget`.
- Opsi `--no-check-certification`
- Opsi `-o` untuk memberikan nama `rn[i][]` dari hasil `wget` nantinya.
- Tiap iterasi akan mengunduh file secara berurut sesuai dengan array (MUSIK, FOTO, FILM).

**Kendala :**\
Tidak ada.

### Soal 1.c
**Deskripsi:**\
Ekstrak file `.zip` yang sudah diunduh melalui `wget`.

**Pembahasan:**

```c
...
char link[3][100]={
    "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download",
    "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download",
    "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download"
};
...
char n1[3][20]={
    "MUSIK",
    "FOTO",
    "FILM"
};
...
for (i=0; i<3; i++)
{
    if (...){
        if (...){
            if((pid=fork())==0){
                ...
            }else{
                ...
            }
        }else{
            waitpid(pid,&stat,0);
            if (WIFEXITED(stat))
            {
                if((pid=fork())==0)
                {
                    char *argv[] = {"unzip",rn[i], NULL};
                    execv("/usr/bin/unzip", argv);
                }else
                ...
            }
        }
    }else
    ...
}

```

- Proses dilakukan di `proses c`.
- Dibantu array string `n1[i][]`.
- Menggunakan `execv(tipe,argumen)` dan pointer string `argv[]`.
- Melaksanakan `unzip`, dengan tipe `/usr/bin/unzip`.

**Kendala :**\
Tidak ada.

### Soal 1.d
**Deskripsi:**\
Memindahkan file dari direktori hasil ekstrak file `.zip` ke direktory yang dibuat dengan `mkdir`.

**Pembahasan:**

```c
...
char n1[3][20]={
    "MUSIK",
    "FOTO",
    "FILM"
};
char n[3][20]={
    "Musyik",
    "Pyoto",
    "Fylm"
};
...
DIR *dp;
struct dirent *ep;
...
for (i=0; i<3; i++)
{
    if (...){
        if (...){
            if((pid=fork())==0){
                ...
            }else{
                ...
            }
        }else{
            waitpid(pid,&stat,0);
            if (WIFEXITED(stat))
            {
                if((pid=fork())==0){
                    ...
                }else{
                    waitpid(pid,&stat,0);
                    if (WIFEXITED(stat))
                    {
                        getcwd(path, sizeof(path));
                        strcat(path,"/");
                        strcpy(target,"");
                        strcpy(target,path);
                        strcat(target,n[i]);
                        strcat(path,n1[i]);
                        dp = opendir(path);
                        while ((ep = readdir (dp))) {
                            strcpy(file,"");
                            strcpy(file,path);
                            if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0){
                                if ((pid = fork()) == 0)
                                {
                                        strcat(file,"/");
                                        strcat(file,ep->d_name);
                                        char *argv[] = {"mv",file, target, NULL};
                                        execv("/bin/mv", argv);      
                                }else{
                                    waitpid(pid, &stat,0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }else
    ...
}

```

- Proses dilakukan di `proses d`.
- Menggunakan tipe data dari `DIR` dengan pointer `*dp` untuk menunjuk direktori tersebut.
- `struct dirent` `*ep` sebagai penunjuk entitas dalam direktori.
- Fungsi `getcwd()` sebagai fungsi untuk mengambil `path` tempat program `daemon` berjalan.
- `path` kemudian disalin ke `target` karna perpindahan masih terhadap jalur relatif sama.
- String `path` kemudian ditambahkan nama direktori `n1[i][]`yang filenya akan dipindahkan melalui `strcat()`.
- String `target` kemudian ditambahkan nama `n[i][]` direktori tujuan penyimpanan `strcat()`.
- Dengan bantuan _library_ `dirent.h` kita menggunakan fungsi `opendir()` untuk mengakses konten direktori.
- Kemudian dengan fungsi `while(ep = readdir(dp))` diiterasi setiap file yang ada di dalam direktory dengan bantuan struct `ep`.
- `ep ->d_name` mewakili nama dari sebuah file, karna hanya file yang dipindahkan digunakan `if` _condition_ dan string yang ditunjuk `ep->d_name` akan disalin ke string `file` sebagai target file yang akan dipindahkan.
- Menggunakan `execv(tipe,argumen)` dan pointer string `argv[]`.
- Printah move berupa `mv` yang mempunyai tipe `/bin/mv`.
- Kegiatan akan berulang sebanyak tiga kali.

**Kendala :**\
Tidak ada.

```
Ringkasan proses periode pertama

Jika waktu == 9 April, 16:22:00, maka,
    mkdir → wget → unzip → move
selesai.
```
**Bukti Periode Pertama:**

![Bukti1A](soal1/)

*Soal 1.a hingga 1.d berjalan saat kondisi waktu adalah 9 April dan waktu pukul 22:22:00.*

### Soal 1.e
**Deskripsi:**\
Menzip tiga direktory yang sebelumnya sudah diisikan file file sesuai kategori namanya.

**Pembahasan:**
```c
char n[3][20]={
    "Musyik",
    "Pyoto",
    "Fylm"
};
...
else if (timeinfo->tm_mon == 3 && timeinfo->tm_mday== 9 && timeinfo->tm_hour== 22 && timeinfo->tm_min==22 && timeinfo->tm_sec==0){

        // komponen zip
        
        if ((pid = fork()) == 0)
        {    
            char *argv[] = {"zip","-r","Lopyu_Stevany.zip",n[0],n[1],n[2], NULL};
            execv("/usr/bin/zip", argv);
        }else{
            waitpid(pid,&stat,0);
            ...
        }
    }
    ...
```

- Menggunakan `execv(tipe,argumen)` dan pointer string `argv[]`.
- Printah move berupa `zip` yang mempunyai tipe `/usr/bin/zip`.
- Opsi `-r` dilakukan untuk melakukan `zip` terhadap lebih dari satu direktori `n[0]`,`n[1]`, dan `n[2]`.

**Kendala :**\
Tidak ada.

### Soal 1.f
**Deskripsi:**\
Menghapus direktory yang tersisa, menyisakan file `.zip`

**Pembahasan:**
```c
char n[3][20]={
    "Musyik",
    "Pyoto",
    "Fylm"
};
char n1[3][20]={
    "MUSIK",
    "FOTO",
    "FILM"
};
...
else if (timeinfo->tm_mon == 3 && timeinfo->tm_mday== 9 && timeinfo->tm_hour== 22 && timeinfo->tm_min==22 && timeinfo->tm_sec==0){

        // komponen zip
        
        if ((pid = fork()) == 0)
        {    
            ...
        }else{
            waitpid(pid,&stat,0);
            char *argv[] = {"rm","-r",n[0],n[1],n[2],n1[0],n1[1],n1[2], NULL};
            execv("/bin/rm", argv);
        }
    }
    ...
```

- Menggunakan `execv(tipe,argumen)` dan pointer string `argv[]`.
- Printah move berupa `rm` yang mempunyai tipe `/bin/rm`.
- Opsi `-r` dilakukan untuk menghapus direktori mulai dari kontennya, barulah direktori itu sendiri.

**Bukti Periode Dua    :**

![Bukti1B](soal1/)

**Kendala :**\
Tidak ada.

---
## Soal 2 
**[Source Code Soal 2](https://github.com/husinassegaff/soal-shift-sisop-modul-2-A06-2021/blob/main/soal2/soal2.c)**

**Deskripsi:**\
deskripsi.

### Soal 2.a
**Deskripsi:**\
deskripsi.

**Pembahasan:**
```c
//kode
```

- 
-
-

```
hasil
```
**Bukti   :**

![Bukti2A](soal2/Bukti2A.png)

**Kendala :**\
kendala.

### Soal 2.b

**Deskripsi:**\
deskripsi.

**Pembahasan:**
```c
//kode
```

- 
-
-

```
hasil
```
**Bukti   :**

![Bukti2B](soal2/Bukti2B.png)

**Kendala :**
kendala.

### Soal 2.c

**Deskripsi:**\
deskripsi.

**Pembahasan:**
```c
//kode
```

- 
-
-

```
hasil
```

**Bukti :**

![Bukti2C](soal2/Bukti2c.png)

**Kendala :**\
Kendala.

### Soal 2.d

**Deskripsi:**\
deskripsi.

**Pembahasan:**
```c
//kode
```

- 
-
-

```
hasil
```

**Bukti :**

![Bukti2D](soal2/Bukti2D.png)

**Kendala :**\
Kendala.

### Soal 2.e

**Deskripsi:**\
deskripsi.

**Pembahasan:**
```c
//kode
```

- 
-
-

```
hasil
```

**Bukti :**

![Bukti2E](soal2/Bukti2E.png)

**Kendala :**\
Kendala.

---
## Soal 3 

**[Source Code Soal 3](https://https://github.com/husinassegaff/soal-shift-sisop-modul-2-A06-2021/blob/main/soal3/soal3.c)**

### Soal 3.a

**Deskripsi:**\
deskripsi.

**Pembahasan:**
```c
//kode
```

- 
-
-

```
hasil
```

**Bukti :**

![Bukti3A](soal3/Bukti3A.PNG)

**Kendala :**\
Kendala.

### Soal 3.b

**Deskripsi:**\
deskripsi.

**Pembahasan:**
```c
//kode
```

- 
-
-

```
hasil
```
**Bukti :**

![Bukti3B](soal3/Bukti3B.PNG)

**Kendala :**\
kendala.

### Soal 3.c

**Deskripsi:**\
deskripsi.

**Pembahasan:**
```c
//kode
```

- 
-
-

```
hasil
```

**Bukti :**

![Bukti3C](soal3/Bukti3C.png)

**Kendala :**\
kendala

### Soal 3.d

**Deskripsi:**\
deskripsi.

**Pembahasan:**
```c
//kode
```

- 
-
-

```
hasil
```

**Bukti :**

![Bukti3D](soal3/Bukti3D.png)

**Kendala :**\
kendala.

### Soal 3.e

**Deskripsi:**\
deskripsi.

**Pembahasan:**
```c
//kode
```

- 
-
-

```
hasil
```

**Bukti :**

![Bukti3E](soal3/Bukti3E.png)

**Kendala :**\
Kendala.
