#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
    FILE *yaz;
    char *kelime,*hash[487], *p, dosya[29];
    int i, j, h1, t, max=0, debug=0, tercih = 1;
    int ascii = 'a',asci, nkey, ara;
    if(strcmp(argv[1], "DEBUG") == 0)
	debug = 1;

    else if(strcmp(argv[1], "NORMAL") == 0)
	debug = 0;

    printf("hash tablosu oluşturulmasını istiyorsanız 1 e basınız\n");
    printf("hash tablosu oluşturulmasını istemiyorsanız 0 a basınız\n");
    printf("Tercihiniz :");
    scanf("%d", &tercih);
    if(tercih != 0 && tercih != 1) {
	printf("yanlis tercih program sonlandı\n");
	exit(1);
    }
    if (tercih == 0){
	printf("hash tablosunun okunacagi dosya adını uzantısıyla birlikte giriniz :");
        scanf("%s", dosya);
    }
    for(j=0; j<487; j++){
	hash[j] = NULL;
    }
    if( tercih == 1){
        yaz = fopen("smallDictionary.txt","r");
        if(yaz == NULL){
	    puts("dosya acılamıyor");
	    exit(1);
        }
        do{
	    kelime = (char *)malloc(15*sizeof(char));   // dosyadan kelimeler tek tek okunup hashlenip tabloya yerleştiriliyor.
            i=fscanf(yaz,"%s",kelime);
	    h1 = hashf(kelime,487, debug);
	    if (hash[h1] == NULL){
	        hash[h1] = kelime;
	        if(debug == 1)
	            printf("%s yerlestigi indis %d\n",kelime, h1);
	    }
	    else{					// cakisma olmasi durumunda else devreye giriyor.
	        if(debug==1)
	            printf("%s, %d cakisma oldu rehas yapiliyor\n", kelime, h1);
	        j = 0;
	        t = 1;
	        while( j < 487 ) {       
	            nkey = rehash(h1, 487, t, debug);
		    if(hash[nkey] == NULL){
		        hash[nkey] = kelime;
		        if(debug == 1)
                            printf("%s rehashden sonra yerlestigi indis %d\n",kelime, nkey);
		        break;
		    }
		    else{
		        if( debug == 1)
			    printf("%d yine cakisma oldu tekrar rehash yapiliyor.\n",nkey);		
		    }
		    j++;
		    t++;
	        }
	        if(t>max)     //en fazla kac kez rehash yapıldıgını tutuyor
		    max = t;
	    }	
        }
        while( i != EOF);
    }

    if( tercih == 0){ 		// kullanıcının istegi uzerine hash tablosunu dosyadan okunuyor.
        yaz = fopen( dosya, "r" );
	if(yaz == NULL){
	    puts("dosya acılamıyor");
	    exit(1);
        }
        kelime = (char *)malloc(15*sizeof(char));
        i=fscanf(yaz,"%s",kelime);
	for(j = 0; i != EOF; j++){
	    hash[j] = kelime;
	}
    }	    
    fclose(yaz);
    free(kelime);	
    query(hash, max, debug); // kullanıcının aradıgı kelimeyi isteyip islemler yapan fonksiyon
    
    return 0;
    }



int hashf(char *kelime, int m, int debug){
    
    int h1, j = 1, key=0;
    int ascii = 'a',asci;
    for(j=1; kelime[j] != '\0'; j++){   // kelimenin key i olusturuluyor.
            asci = kelime[j];
	    key += (asci - ascii)*26*j ;    
	}
    h1 = key % m;
    if( debug == 1)
	printf("key = %d, m = %d, adres = %d\n", key, m, h1);
    return h1;
}
int rehash(int h1, int size, int t, int debug){

    int offset, nkey, r = 479;
    offset = r - (h1 % r);
    nkey = (h1 + t*offset) % size;
    if( debug == 1)
	printf("offset = %d, R = %d, adres = %d\n", offset, r, nkey);

    return nkey;

}

int query(char *hash[], int max, int debug){
    int h1, equal=0, j, t = 0, k=0, y, nkey, counter=0, oldkey=489;
    char *p,aranan[15], e;
    char b[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','r','s','t','u','v','w','x','y','z','q'};
    printf("aradiginiz kelimeyi giriniz :");
    scanf("%s", aranan);
    h1 = hashf(aranan, 487, debug);
    p = hash[h1];
    if ( p == NULL ){   //kelimeye bakılan indisli yer NULL ise kelime yok demektir. Harf değiştirme kısmına gecis yap.
        printf("1 göze bakıldı\n");
	goto ara;
    }
    if(strcmp(p, aranan) == 0){
	    printf("bulundu = %d\n",h1);
    }
    else{
	t = 0;
	for(j=0; j<max; j++){
	    nkey = rehash(h1, 487, t, debug);
	    if ( nkey == oldkey ){
		printf("kelime bulunamadi\n");
		j = max;
	    }
	    oldkey = nkey;
	    p = hash[nkey];
	    if( p == NULL)    //aranan eleman null a eşitse segmentation fault hatası almamak için kontrol koydum.
		continue;
	    if(strcmp(p, aranan) == 0){
		printf("bulundu : %d\n", nkey);
		equal++;
		break;
	    }
	    counter++;
	    t++;	
	}
	if(debug == 1)
	    printf("%d göze bakıldı\n", counter+1);
  
    }
    ara:
    if( equal == 0){
	
	for(j = 0; aranan[j] != '\0'; j++){       // kelime bulunamadıysa harfleri degistirilerek tabloda aranıyor.
	    e = aranan[j];
	    for(t = 0; b[t] != '\0'; t++){
		aranan[j] = b[t];
		h1 = hashf(aranan,487, 0);
		p = hash[h1];
		if(p == NULL)
		    continue;
		if(strcmp(p, aranan) == 0)
		    printf("sunu mu demek istediniz : %s\n",aranan);
       			
		else{
		    y = 0;
		    for(k=0; k<max; k++){
	    		nkey = rehash(h1, 487, y, 0);
	    		p = hash[nkey];
			if( p == NULL)
			    continue;
 	    		if(strcmp(p, aranan) == 0){
			    printf("sunu mu demek istediniz : %s\n",aranan);
			    break;
		        }
		        
		        y++;
		    
		    }
                }


	    }
	    aranan[j] = e;    	
    	}   
    }
	
    return 0;
}
