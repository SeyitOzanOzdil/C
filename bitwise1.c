/**
 program girilen sayının binary gösteriminde  kaç tane 1 var hesaplar
*/

#include<stdio.h>

int main(){
    int sayi, tmp, counter=0;
    printf("bir sayı giriniz :");
    scanf("%d", &sayi);

    while(sayi>0){
	tmp = sayi&1;
	if(tmp == 1)
	    counter++;
	sayi>>=1;
    }
    printf("girilen sayının binary gösterimindeki 1 sayisi : %d\n",  counter);	
    return 0;
}
