#include <stdio.h>
#include <stdlib.h>
#include "mutex.h"
#include "thread.h"
#include <unistd.h>

#define NUM_CADEIRAS 5
#define NUM_CLIENTES 10 

int clientes_esperando = 0;


Mutex mutex;

int barbeiro(int i) {
    while(1) {
         
        mutex.lock();                                                                                                                    //lock

        if (clientes_esperando == 0) {
            printf("O barbeiro está dormindo...\n");
	        mutex.WBarbeiro();                                                                                                          //wait barbeiro	
            mutex.unlock();                                                                                                             //unlock
        } else {
            clientes_esperando--;
            printf("O barbeiro está cortando o cabelo de um cliente. Clientes esperando: %d\n", clientes_esperando);
            mutex.CCliente();                                                                                                           //signal Cliente
            mutex.unlock();                                                                                                             //unlock
        }

        //cortando o cabelo
        sleep(3);
         
    }
    
    return 0;
    
}

int cliente(int i) {
     
        mutex.lock();                                                                                                                   //lock

    if (clientes_esperando < NUM_CADEIRAS) {
        clientes_esperando++;
        printf("Cliente entrou na barbearia. Clientes esperando: %d\n", clientes_esperando);
	    mutex.CBarbeiro();	                                                                                                            //signal barbeiro
        mutex.WCliente();                                                                                                               //wait cliente
        mutex.unlock();                                                                                                                 //unlock
    } else {
        printf("A barbearia está cheia. Cliente foi embora.\n");
        mutex.unlock();                                                                                                                 //unlock
    }
    
    return 0;
  
}

int main() {
    Thread * clientes[NUM_CLIENTES];
    Thread * barb;

    // Inicializa o barbeiro
    barb = new Thread(&barbeiro,0);
    
    // Inicializa os clientes
    for (int i = 0; i < 10; ++i) {
        clientes[i] = new Thread(&cliente, i);
        sleep(1); // Simula chegada de clientes em intervalos
    }

    // Aguarda o término das threads
    barb->join(NULL);
    for (int i = 0; i < 10; ++i) {
        clientes[i]->join(NULL);
    }

    return 0;
}
