
#include<stdio.h>
#include<stdlib.h>
#include <time.h>


/**
fonksiyon kullancıdan istedigi algoritmayi secmesini sorar
secilen algoritmayi çalistirir.

*/
int main(){
    int tercih,uzunluk;
    int i,j,aranan,tmp,bas=0;
    printf(" ozyineli fonksiyon icin 1 giriniz\n ozyinesiz fonksiyon icin 2 giriniz \n tercihiniz :");
    scanf("%d",&tercih);
    
    if(tercih==1 || tercih==2){
	printf("eleman sayisini giriniz:");
	scanf("%d",&uzunluk);
	printf("aradiginiz elemani giriniz:");
	scanf("%d",&aranan);            
	int *p = (int *)malloc(uzunluk*sizeof(int));
	srand(time(NULL));
	for(i=0;i<uzunluk;i++){          //dizinin içi rastgele dolduruldu.
     	    p[i]=rand()%(2*uzunluk)+1;   //en büyük eleman dizi uzunluğunun iki katı olacak şekilde kısıtlandı
	}
	for(i=0;i<uzunluk;i++){		//dizide elemanlarının unique olması sağlandı
            for(j=0;j<uzunluk;j++){
                if(i != j){
		    while(p[i]==p[j]){
		        p[i]=rand()%(2*uzunluk)+1;
		    }
                    
         	}
    	    }
	}
        //sıralama
	for(j=0; j<uzunluk; j++)  	// dizi elemanları kabarcık sıralama ile sıralandı
        for(i=0; i<uzunluk; i++){
	    if(p[i]>p[i+1]){
		tmp = p[i];
		p[i] = p[i+1];
		p[i+1] = tmp;
	    }
	}


        if(tercih==1){		//klavyeden 1 girisi yapildiysa ozyineli fonksiyon cagrisi yapildi.
	    time_t start,stop;
	    time(&start);
	    ozyineli(p,aranan,uzunluk,bas);
            printf("ozyineli fonksiyonu sectiniz!\n");
	    time(&stop);
	    printf("runtime : %f seconds\n", (double)difftime(stop,start)); // calisma suresi
	} 
        
        else if(tercih==2){	//klavyeden 2 girisi yapildiysa ozyinesiz fonksiyon cagrisi yapildi.
	    clock_t tic = clock();
	    ozyinesiz(p,aranan,uzunluk);
	    printf("ozyinesiz fonksiyonu sectiniz!\n");
	    clock_t toc = clock();
	    printf("runtime : %f seconds\n", (double)(toc-tic)/CLOCKS_PER_SEC); // calisma suresi
	}
    }
    else
        printf("yanlis girdi!");

    return 0;
}
/**
 fonksiyon ozyineli bir şekilde aranan elemanı bineary search algoritmasıyla arıyor.
 @param mid dizinin ortadaki elemanının indisi
*/
int ozyineli(int *ptr, int srch, int end, int start){
    int mid = (start + end)/2;
    if(ptr[mid]==srch){		//sayi bulunduysa ekrana indisini yazdır.
	 printf("sayi bulundu. indisi : %d\n",mid);
        return 0;
    }

    
    if(end<start){		// sayi bulunamadiysa haber ver.
	printf("sayi bulunamadi\n");
	return 0;
    }
    else{
	if(ptr[mid]>srch)	//ozyineleme cagrisi	
	    return ozyineli(ptr,srch,mid-1,start);
	else
	    return ozyineli(ptr,srch,end,mid+1);
	}
}

/**
 fonksiyon ozyinesiz çalışarak aranan elemanı bineary search algoritmasıyla arıyor.
 @param orta dizinin ortadaki elemanının indisi
 @param start dizinin başlangıç indisi
*/
int ozyinesiz(int *ptr, int srch, int end){		
    int orta,start=0;
    while(end>=start){
	
	orta = (end + start) / 2;
	if(orta==srch){					//aranan eleman bulunduysa ekrana indisi yazdir.
	    printf("bulundu. indisi = %d\n",orta);
	    return 0;
	}
        if(ptr[orta] > srch)			//aranan eleman dizinin ortanca elemanindan kucukse dizinin sol tarafında arama yapmaya gec
	    end = orta - 1;
	
	else if(ptr[orta] < srch)	   //aranan eleman dizinin ortanca elemanindan buyukse dizinin sag tarafında arama yapmaya gec
	    start = orta + 1;
    }
    printf("deger bulunamadi\n");		//deger bulunamadiysa haber ver.
   
    return 0;
}

