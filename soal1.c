/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman
 * Modul            : 04 - Dynamic Structures
 * Hari, Tanggal    : Senin, 4 Mei 2026       
 * Nama/NIM         : Dzaky Raihan Nugraha/13224062
 * Deskripsi        : Membuat sistem tambah belakang, tambah depan, hapus, dan find gerbong dalam KAM (Kereta Api Minecraft)
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct gerbong {
    int pendataan;
    struct gerbong* next;
}gerbong;

void awazDepan (gerbong** utama, int a){
    gerbong* gerbongBaru=(gerbong*)malloc(sizeof(gerbong));
    gerbongBaru->pendataan=a; //untuk membuat gerbong baru

    gerbongBaru->next=*utama; //gerbong barunya nunjukin ke utama(depan)
    *utama=gerbongBaru;
}

void awazBelakang (gerbong** utama, int a){
    gerbong* gerbongBaru=(gerbong*)malloc(sizeof(gerbong));
    gerbongBaru->pendataan=a;
    gerbongBaru->next=NULL; //paling belakang berarti nextnya bakal kosong gitu

    if(*utama==NULL){
        *utama=gerbongBaru; 
        return; //incase ternyata masih kosong, berarti yang baru ditambahin dari utama (depan)
    }

    //in case ternyata udah ada gerbongnya
    gerbong* temp=*utama;
    while(temp->next!=NULL){
        temp=temp->next;
    }

    temp->next=gerbongBaru; //nyambungin gerbong terakhir dengan gerbong baru yang ditambah di belakang
}

void awazDel (gerbong** utama, int a){
    if(*utama==NULL){ //maknanya kalo kosong ya gausah hapus apa apa
        return;    
    }

    if((*utama)->pendataan==a){ //incase ternyata yang dihapus itu gerbong pertama
        gerbong* temp=*utama;
        *utama=(*utama)->next;
        free(temp);
        return;
    }

    //bagian nyari gerbong yang datanya x
    gerbong* tertentu=*utama;

    //kalo udah di ujung atau gerbang yang dicari adalah gerbong tertentu (x-nya)
    while(tertentu->next!=NULL && tertentu->next->pendataan!=a){
        tertentu=tertentu->next;
    }

    //kalau gerbong ditemuin
    if(tertentu->next!=NULL){
        gerbong* temp=tertentu->next;
        tertentu->next=tertentu->next->next; //-> ditulis 2x soalnya untuk lewatin gerbong yang dihapus
        free(temp);
    }
}

void temuGerbong (gerbong* utama, int a){
    int position=0; //mulai urutin dari 0 untuk nyari (lama sih, tapi yaudah gtw lagi)
    gerbong* tertentu=utama;

    //searching dari awal sampai akhir gerbong
    while(tertentu!=NULL){
        if(tertentu->pendataan==a){
            printf("FOUND %d\n", position);
            return; //kalo udah ketemu yang GET OUTTTTTT
        }
        tertentu=tertentu->next;
        position++;
    }
    //ternyata gak ada gitu ya
    printf("NOT FOUND\n");
}

void dispGerbong(gerbong* utama){
    //kalo kosong
    if(utama==NULL){
        printf("LIST EMPTY\n");
        return;
    }

    //kalo isinya ada
    printf("LIST");
    gerbong* tertentu=utama;
    while(tertentu!=NULL){
        printf(" %d", tertentu->pendataan);
        tertentu=tertentu->next;
    }
    printf("\n");
}

int main() {
    //operasi Q
    int Q=0;
    scanf("%d", &Q);

    //anggap kereta masih kosong
    gerbong* utama=NULL;

    //looping sebanyak Q
    for (int i=0; i<Q; i++){
        int op; //jenis operasinya 1 2 3 ato 4
        int x; //angkanya
        //membaca jenis op, x
        scanf("%d %d", &op, &x);

        if(op==1){ //opsi 1 tambah depan 
            awazDepan(&utama, x);
        }

        else if(op==2){ //opsi 2 tambah belakang
            awazBelakang(&utama, x);
        }

        else if(op==3){ // opsi 3 hapus hapus
            awazDel(&utama, x);
        }

        else if (op==4){ //opsi 4 find gerbong
            temuGerbong(utama, x);
        }
    }
    //print semua gerbongnya
    dispGerbong(utama);
    return 0;
}
