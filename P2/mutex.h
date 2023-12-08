#ifndef __mutex_h
#define __mutex_h
 
#include <pthread.h>
 
class Mutex
{
public:
	Mutex() {}
	~Mutex() {}
 
	void lock() { pthread_mutex_lock(&mut); }
	bool try_lock() { return (pthread_mutex_trylock(&mut) == 0);} // true when succeeds.
	void unlock()   {pthread_mutex_unlock(&mut);} 
	void CCliente() {pthread_cond_signal(&cond_cliente);}
	void CBarbeiro(){pthread_cond_signal(&cond_barbeiro);} 
	void WCliente() {pthread_cond_wait(&cond_cliente, &mut);}
	void WBarbeiro(){pthread_cond_wait(&cond_barbeiro, &mut);} 
        
    
 
private:
	pthread_mutex_t mut;
	pthread_cond_t cond_barbeiro;
	pthread_cond_t cond_cliente;
};
 
#endif
