#include <stdio.h>
struct uye
{
char isim[100];
float hesap;
int havale;
}yapi[2];

int main(){
    FILE *fp, *yaz;
    int b;
    fp = fopen("dosyam.txt","r"); //okunacak dosya açılıyor
    for(b=0; b<2; b++){ 		 // dosyadan iki kayıt okunuyor ve struct yapısının icine yerleştiriliyor.
	fscanf(fp, "%s %f %d", &yapi[b].isim, &yapi[b].hesap, &yapi[b].havale);
    }
    
    yaz = fopen("yaz.txt","w"); // yazılacak dosya açılıyor.
    for(b=0; b<2; b++){  	// struct türündeki listesinden iki kayıt okunup dosyaya yazılıyor.
        fprintf(yaz, "%s %f %d\n",yapi[b].isim, yapi[b].hesap, yapi[b].havale);
    }

    fclose(fp);
    fclose(yaz);
    return 0;
}
