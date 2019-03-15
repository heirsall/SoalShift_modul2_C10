# SoalShift_modul2_C10
SoalShift modul 2 Sistem Operasi kelompok C10.

# 1
 Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

Pada Nomor ini yang perlu dilakukan pertama perlu untuk membuka direktory

`folder = opendir("/home/zahrul/modul2/");`

 Selanjutnya 
 ``if (folder)
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
