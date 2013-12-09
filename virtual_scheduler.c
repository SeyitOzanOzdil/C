/**


Program rastgele uzunluğunu berlirlediği bekleme kuyruğunu rastgele oluşturulan processlerle dolduruyor. İkinci aşamada programın rastgele 1 yada 0 üretmesi sonucu bekleme kuyruğunun sonuna yeni bir process ekliyor. Daha sonra bekleme kuyruğundaki verileri schedule ediyor.
kuyrukta process kalmayana kadar ikinci aşamadan itibaren anlattığım işlemleri tekrarlıyor. Her tekrar sırasında bekleme kuyruğu, işlenen ve işlenemeyen processlerin kuyruğu ekrana yazdırılıyor.

@yazan

İsim:          Seyit Ozan Özdil

E-Mail:        seyit.ozdil55@gmail.com

Compiler used: GCC

Operating System: Linux

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
    typedef struct{         //process tanımı
        int processId;
        int lifeCycle;
        int priority;
        int ttl;
	int location;
    }PROCESS;

PROCESS *waiting_queue;                 
PROCESS *terminated, *tmp, *non_terminated;
int tindex = 0, ntindex = 0, total_Lc = 0;

/**
 fonksiyon kuyrukları oluşturuyor, bekleme kuyruğunda eleman kalmayana kadar schedulerı çağırıp her adımda kuyrukları ekrana yazdıracak fonksiyonu çağırıyor.    

*/
int main(){

    srand(time(NULL));
    int nmbr_proc, add, nump, fixed, index, avgLc, counter=0;
    nmbr_proc = 5 + rand() % 6;       //process sayısı 
    nump = nmbr_proc;                 //process sayısını tutan değişken     
    fixed = nmbr_proc+1;              //process sayısını tutan değişken 
    waiting_queue = (PROCESS *)malloc((nmbr_proc+2) * sizeof(PROCESS)); // bekleme kuyruğu  
    terminated = (PROCESS *)malloc((nmbr_proc*3) * sizeof(PROCESS));    // işlenen kuyruğu 
    non_terminated = (PROCESS *)malloc((nmbr_proc*3) * sizeof(PROCESS)); // işlenemeyen kuyruğu
    create_proc(0, nmbr_proc);  //processler yaratılıyor                      
    show_lists(nump, fixed);           //kuyruklar ekrana basılıyor
    while(nmbr_proc > 0){       //kuyruk boşlana kadar kuyruktaki processleri schedule et 
	add = rand() % 2;
        if(add == 1){           //eğer rastgele sayı 1 gelirse bekelem kuyruğuna 1 process ekle
	    create_proc(nmbr_proc, nmbr_proc+1);
	    nmbr_proc++;
	    nump++;                     
	    show_lists(nump, fixed);
	}

        nmbr_proc = scheduler(nmbr_proc); // schedule et
        show_lists(nump, fixed);
    }
    
    avgLc = total_Lc / (tindex);  //işlenen listesinin lifecycle ortalamasını al
    printf("average lifeCycle of the terminated processes : %d\n", avgLc);
    free(waiting_queue);
    free(terminated);
    free(non_terminated);
    return 0;
}
/**
 kuyurkları ekrana yazdıran fonksiyon
 @param i indis olarak kullanılıyor.
*/
int show_lists(int np, int fixed_lng){  
    int i;
    for(i=0; i<fixed_lng; i++){ // bekleme kuyruğu sabit uzunluklu 
	printf("wq[%d] : %d, lc:%d, ttl:%d\n",i ,waiting_queue[i].processId, waiting_queue[i].lifeCycle,waiting_queue[i].ttl);
    }

    for(i=0; i<np; i++){
	printf(" t[%d] : %d\n",i ,terminated[i].processId);
    }

    for(i=0; i<np; i++){
	printf("nt[%d] : %d\n",i ,non_terminated[i].processId);
    }
    printf("---------------\n");
    return 0;
}
/**
 kuyruğa istenen indisten, belirlenen eleman sayısı kadar process ekleniyor.
 @param j indis olarak kullanılıyor.
 @param next_procId oluşturulan processlerin process Id lerini belirlemede kullanılıyor 
*/
int create_proc(int start, int nump){ // processleri yaratan fonksiyon
    int j;
    static next_procId=1;
    for(j=start; j<nump; j++){
	waiting_queue[j].processId = next_procId;
	waiting_queue[j].lifeCycle = 1;
	waiting_queue[j].priority  = 1 + rand() % 3;   
	waiting_queue[j].ttl       = 5 + rand() % 6;
	waiting_queue[j].location  = j;
	next_procId = waiting_queue[j].processId+1;
    }
    return 0;
}

/**
 bekleme kuyruğundaki processleri schedule edip işlenen yada işlenemeyen listesine ekliyor.
 @param k indis olarak kullanılıyor.
 @param t indis olarak kullanılıyor.
 @param p indis olarak kullanılıyor.
 @param location processlerin kuyruktaki güncel yerlerini tutuyor.
 @param maxp bekleme kuyruğundaki processlerin en yüksek öncelikli olanının öncelik değerini tutuyor.
*/
int scheduler(int nop){  
    int k, t, location; 
    int maxp=4, p;
    
    for(k=0; k<nop; k++){      // bekleme kuyruğunda en yüksek öncelikli process seçilir (1 en yüksek öncelik)
	if(waiting_queue[k].priority < maxp){
	    maxp = waiting_queue[k].priority;
	    location = waiting_queue[k].location;
	}
    }
    
    for(t=0; t<nop; t++){   //aynı öncelikli processlerden lifecycle ı yüksek olan seçilir
	if(t != location && waiting_queue[t].priority == maxp){
	    if(waiting_queue[t].lifeCycle > waiting_queue[location].lifeCycle){
		maxp = waiting_queue[t].priority;
	        location = waiting_queue[t].location;
	    }
	    
	     else if(waiting_queue[t].lifeCycle == waiting_queue[location].lifeCycle){  //lc ları da eşitsen ttl'i küçük olan
	        if(waiting_queue[t].ttl < waiting_queue[location].ttl){
		    maxp = waiting_queue[t].priority;
	    	    location = waiting_queue[t].location;
		}
	    }
	}
	
	   
    }

    if(waiting_queue[location].lifeCycle > waiting_queue[location].ttl){ // lifecycle ttl den büyükse işlenemeyen kuyruğuna ekle
	non_terminated[ntindex] = waiting_queue[location];
	ntindex++;
    }

    else{
	terminated[tindex] = waiting_queue[location]; //lifecycle ttl den küçükse işlenen kuyruğuna ekle
	total_Lc += terminated[tindex].lifeCycle ; // kuyruktaki toplam lifecycle hesaplamak için
	tindex++;
	
    }

    for(p=location; p<nop; p++){
	waiting_queue[p] = waiting_queue[p+1]; //schedule ettikten sonra ilgili proc. listenden çıkartılıyor 
	waiting_queue[p].location -= 1;       //listeyi çıkan elemanın yerini doldurarak kaydır
    }
    nop--;  //eleman sayısını azalt

    for(p=0; p<nop; p++){
	waiting_queue[p].lifeCycle++; // bekleme kuyruğunda kalanların lc lerini 1 arttır
    }

    return nop;
}
