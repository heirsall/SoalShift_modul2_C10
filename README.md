# SoalShift_modul2_C10
SoalShift modul 2 Sistem Operasi kelompok C10.

# 1
 Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

Pada Nomor ini yang perlu dilakukan pertama perlu untuk membuka direktory

`folder = opendir("/home/zahrul/modul2/");`

 Selanjutnya 
``
if (folder)
    {
        while ((dir = readdir(folder)) != NULL) //Untuk membaca direktori
        {
	    int len = (int) strlen(dir->d_name); //Untuk mendapatkan panjang char setiap nama file

	    char *name = dir->d_name;

	   	if(name[len-1] == 'g')	//menyeleksi pada 4 char terakhir apakah mengandung .png
        	if(name[len-2] == 'n' ) 
		if(name[len-3] == 'p' )
		if(name[len-4] == '.'){
	    	
		char nFile[1024];

		strcpy(nFile, "/home/zahrul/modul2/gambar/"); //untuk mengkopi string dimasukan ke variabel nFile

		strcat(nFile, name); //menyambungkan string isi nFile dengan namafile
		
		len = (int)strlen(nFile);

		nFile[len-4] = '\0'; //menghapus string .png pada file
		
		strcat(nFile, "_grey.png"); //menyambungkan isi string nFile dengan _grey.png

						if(fork()==0){

		 execlp("mv", "mv",name,nFile,(char*) NULL); //melakukan rename dan move 


		}
	    }
	    }
``
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
    int inipipe[4]; 	---------------->untuk pipe yang nanti diperlukan
    char hasil[1024];

    child_id1 = fork();	-------------->melakukan fork pertama

    if(child_id1 == 0){
      execl("/usr/bin/unzip","unzip", "campur2.zip", NULL); ------>untuk unzip
    }else{


	
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

          dup2(inipipe[1], STDOUT_FILENO); ---------> menyimpan hasil ls 
          close(inipipe[1]); 
      execlp("ls","ls","/home/zahrul/praktikum2/baru/campur2",(char*) NULL); -------> Melakukan ls
      
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
		 execlp("grep", "grep",".txt$",(char*) NULL);-------> Melakukan grep yang menyeleksi file beresktensi .txt 
             
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
# 4
Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan: 
dilarang menggunakan crontab
Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, ds


