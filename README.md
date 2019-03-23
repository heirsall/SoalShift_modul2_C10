# SoalShift_modul2_C10
SoalShift modul 2 Sistem Operasi kelompok C10.

# 1
 Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

Pada pertama adalah membuat Program deamon agar program dapat berjalan berulang-ulang

Setelah program daemon terbuat kita mulai ke programnya

    `` 
	DIR *folder;
    struct dirent *dir;
    folder = opendir("/home/zahrul/modul2/");
    ``
    
Pada Syntaq diatas pertama adalah inisialisasi `DIR *folder`  yang digunakan untuk membuka direktori
dan `struct dirent *dir` untuk nanti digunakan membaca direktori

		if (folder)
   			 {
        		while ((dir = readdir(folder)) != NULL)
        		{
			    int len = (int) strlen(dir->d_name);
				char *name = dir->d_name;
			
			



Pada kode diatas adalah mengcedek folder dan perulangan membaca isi dari folder
` int len = (int) strlen(dir->d_name);` Digunakan untuk mencari panjang string dari nama file 
`  	if(name[len-1] == 'g')
        	if(name[len-2] == 'n' )
		if(name[len-3] == 'p' )
		if(name[len-4] == '.'){`
Diatas adalah untuk mengecek apakah file berformat `.png`
`char nFile[1024];` Inisialisasi char untuk nama file nanti

`strcpy(nFile, "/home/zahrul/modul2/gambar/");` 

Mengisi nfile dengean string "/home/zahrul/modul2/gambar/" 

`strcat(nFile, name);` Menyambung nfile dengan nama file asli
sehingga menjadi "/home/zahrul/modul2/gambar/*namafile.png*"

`len = (int)strlen(nFile);` Menghitung panjang string dari nFile
`nFile[len-4] = '\0';` Menghapus char pada indeks panjang karakter - 4 dan lanjutannya 
			Sehingga menjadi "/home/zahrul/modul2/gambar/*namafile*"
`strcat(nFile, "_grey.png");` Menyambung nFile dengan _grey.png sehingga menjadi
				"/home/zahrul/modul2/gambar/*namafile_grey.png*"
 `execlp("mv", "mv",name,nFile,(char*) NULL); ` Untuk meng mv file ke lokasi tujuan dengan nama baru



# 2
Soal 2 diminta untuk menghapus file <i>elen.ku</i> yang berada di direktori <i>hatiku</i> dengan menjalankan proses Daemon, namun untuk mengahapus file <i>elen.ku</i> terdapat sebuah masalah untuk akses permissionnya sehingga dibuat akses baru dengan kode permission "0777".

1. Membaca tempat elen.ku ini
```
    char *tempat = "/home/tieria21/hatiku/elen.ku";
```
2. Membuat variabel deklrasi file dan PID nya
```
stat(tempat, &elen);

    struct stat elen;
    struct x *a;
    struct y *b;

    a = getpwuid(elen.st_uid);
    b = getgrgid(elen.st_gid);
```
3. Untuk permissionnya dibaca
```
char perm[]="0777";
    int c;

    c = strtol(perm,0,8);    
    chmod(tempat, c);
```
4. Lalu menghapus dengan format www-data nya
```
if(strcmp(own->pw_name, "www-data")==0 && strcmp(grp->gr_name, "www-data")==0) 
        remove(tempat);

    sleep(3);
```
5. Untuk menjalan kan programmnya setelah di compile
```
sudo chown www-data:www-data /home/[user]/hatiku/elen.ku
```
Hasilnya file <i>elen.ku</i> akan terhapus

# 3
Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
Gunakan fork dan exec.
Gunakan minimal 3 proses yang diakhiri dengan exec.
Gunakan pipe
Pastikan file daftar.txt dapat diakses dari text editor

``

		#include <stdlib.h>
		#include <sys/types.h>
		#include <sys/stat.h>
		#include <fcntl.h>
		#include <errno.h>
		#include <stdio.h>
		#include <sys/wait.h>
		#include <string.h>
		#include <dirent.h>
		#include <unistd.h>

	int main()
	{
    pid_t child_id1;
    int status;
    int inipipe[4]; 	------->untuk pipe yang nanti diperlukan
    char hasil[1024];

    child_id1 = fork();	-------------->melakukan fork pertama

    if(child_id1 == 0){
      execl("/usr/bin/unzip","unzip", "campur2.zip", NULL); ------>untuk unzip
    }
    else{


	
    	pid_t child_id2;
        int p2;
        
	while(wait(&status)>0);

        pipe(inipipe); -----------> membuat pipe1
        pipe(inipipe+2);----------> membuat pipe2

        child_id2 = fork();
        if(child_id2==0){

          close(inipipe[0]);
          close(inipipe[2]);
          close(inipipe[3]);

          dup2(inipipe[1], STDOUT_FILENO); -----> menyimpan hasil ls 
          close(inipipe[1]); 
      execlp("ls","ls","/home/zahrul/praktikum2/baru/campur2",(char*) NULL); --> Melakukan ls
      
        }
		else{
	
	
    		pid_t child_id3;
  	          child_id3 = fork();
        
	    if(child_id3==0){

			  
	              close(inipipe[1]);
	              dup2(inipipe[0],STDIN_FILENO); ---------------> membaca hasil ls  
	              close(inipipe[0]);

	              close(inipipe[2]);
	              dup2(inipipe[3],STDOUT_FILENO); --------------> untuk menyimpan hasil grep
	              close(inipipe[3]);
		 execlp("grep", "grep",".txt$",(char*) NULL);---> Melakukan grep yang menyeleksi file beresktensi .txt 
             
            }else{

              close(inipipe[1]);
              close(inipipe[0]);
              close(inipipe[3]);
 
	             int cetak = read(inipipe[2],hasil,sizeof(hasil));------>mengambil hasil grep

              close(inipipe[2]);
              FILE* file;
              file = fopen("daftar.txt","w+");
             fprintf(file," Berikut Berupa File berformat .txt :\n%.*s\n",cetak,hasil);---->memasukan hasil ls grep ke file
             printf("Berikut Berupa File berformat .txt :\n%.*s\n",cetak,hasil); ----> untuk mencetak hasil ls grep
	
              fclose(file);
           	 }
            
        	}
	    }
	}
``



	`execl("/usr/bin/unzip","unzip", "campur2.zip", NULL);`
Untuk Unzip


	``execlp("ls","ls","/home/zahrul/praktikum2/baru/campur2",(char*) NULL);``

Untuk ls

	``execlp("grep",".txt$",(char*) NULL);``

Untuk melakukan grep,yaitu menyaring yang berformat .txt

# 4
Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan: 
dilarang menggunakan crontab
Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, ds

``
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include <time.h>
//template from modul 2 daemon
int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/zahrul/praktikum2/4j/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int nomer=1;
  while(1) 
  {
	struct stat title;
    FILE *filenak;

    char folder[]="makan_enak.txt";
    
    stat(folder, &title);
    time_t wakses = title.st_atime; 
    time_t wakprogjal = time(NULL); 
    double time = difftime(wakprogjal, wakses)
    if(time)<=30) 
    {
	char wakses[100];
      sprintf(wakses, "%d.txt", nomer);

      char folder2[]="makan_sehat";
      
	strcat(folder2, wakses);
                  

      filenak = fopen(folder2, "w"); 

      fclose(filenak);
      nomer=nomer+1;
    }
    sleep(5);
  }
  
  exit(EXIT_SUCCESS);
}

``
# 5
Di soal 5 kita diminta untuk menyimpan file log yang berasal dari "/var/log/syslog" dalam sebuah folder yang bernamakan waktu simpan di setiap menitnya sampai berjumlah 30 dalam 1 folder lalu terus berlanjut membuat folder baru berisikan file log juga. Lalu juga kita diminta untuk membuat program untuk menghentika jalannya proses membuat file log tersebut.

1. Mendeklarasikan waktu dan akses mengambil data waktu dari sistem
```
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
```
2. Untuk membuat folder yang bernamakan sesuai dengan waktu dari sistem, dan juga mengisikan data nama waktu dengan folder
```
  int a = 1;
  DIR *sip;

  char waktu[30];
  char folder[50]="/home/tieria21/modul2/log/";
  snprintf(waktu, sizeof waktu, "%02d:%02d:%04d-%02d:%02d",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900,tm.tm_hour,tm.tm_min);
  strcat(folder,waktu);
```
3. Fork untuk membuat proses baru membuat folder, dan program parent melanjutkan proses selanjutnya
```
  if(fork()==0){
    execlp("mkdir","mkdir","-p",folder,NULL);
  }
  else{
    while(wait(&status)>0);
  }
```
4. Didalam program utama kita mendeklrasikan variabel untuk mengambil waktu dan prograrm menjalankan fungsi untuk membuat file dalam folder log dengan format waktu yang disesuaikan sebanyak 30 dalam 1 menit.

```
  while(1) {
    // main program here
    sip = opendir(folder);

    if(a>=2 || !sip){
    a = 1;
    t = time(NULL);
    tm = *localtime(&t);
    
    memset(folder,0,sizeof(folder));
    strcpy(folder, "/home/tieria21/modul2/log/");
    snprintf(waktu, sizeof waktu, "%02d:%02d:%04d-%02d:%02d",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900,tm.tm_hour,tm.tm_min);
    strcat(folder,waktu);
    
    if(!fork())
    {
      execlp("mkdir","mkdir","-p",folder,NULL);
    }
    else
    {
      while(wait(&status)>0);
    }  
  }
```
5. Dalam eksekusi terakhir, fork untuk membuat proses baru yang menjalankan membuat file akhir sesuai format yang diminta dan memasukkan isian dari "/var/log/syslog"
```
    if(fork()==0){
      char log[30];
      snprintf(log, sizeof log, "/log%d.log", a);
      strcat(folder, log);
      execlp("cp", "cp", "/var/log/syslog", folder, NULL);
    }
    closedir(sip);
    
    a++;

    sleep(60);
  } exit(EXIT_SUCCESS);
}
```
