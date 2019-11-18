#include <semaphore.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <pthread.h>

#define CROSSING_TIME 1										// number of seconds to cross rope
#define AVERAGE_CREATION_TIME 2								// average (mean) number of seconds between baboons' arrivals at rope
#define BABOONS_TO_CROSS 5									// number of baboons that will need to cross rope during simulation

sem_t crossers_mut;											// semaphore - controls access to crossers
sem_t rope_mut;												// semaphore - controls eastbound access to rope
sem_t write_mut;											// semaphore - controls access to std::cout
int crossers = 0;											// number of eastbound baboons (negative indicates number of westbound baboons)

void cross_rope(int crosser){
	string direction;
	/*
	Ver quíen cruza, por defecto cruzan los que vienen
	desde el este.
	*/
	if (crosser > 0)
		direction = "Eastbound";
	else{
		direction = "Westbound";
		crosser = -crosser;									
	}
	/*
	espera el semaforo write.
	*/
	sem_wait(&write_mut);									
	cout << direction << " baboon crossing the rope...\t" << crosser << " " << direction << " baboon(s) are currently crossing." << std::endl;
	sem_post(&write_mut);									
	sleep(CROSSING_TIME);									
}

void *eastbound_baboon(void*){
	bool done = false;
	int crossers_copy;
	/*
	
	*/
	while (!done){
		sem_wait(&crossers_mut);							
		if (crossers >= 0){
			++crossers;										
			crossers_copy = crossers;						
			if (crossers == 1)
				sem_wait(&rope_mut);						
			sem_post(&crossers_mut);						
			cross_rope(crossers_copy);						
			sem_wait(&crossers_mut);						
			--crossers;										
			if (crossers == 0)
				sem_post(&rope_mut);						
			done = true;									
		}
		else
			sleep(0);
		sem_post(&crossers_mut);							
	}
	return 0;
}

void *westbound_baboon(void*){
	bool done = false;
	int crossers_copy;
	while (!done){
		sem_wait(&crossers_mut);							
		if (crossers <= 0){
			--crossers;										
			crossers_copy = crossers;
			if (crossers == -1)
				sem_wait(&rope_mut);						
			sem_post(&crossers_mut);						
			cross_rope(crossers_copy);						
			sem_wait(&crossers_mut);						
			++crossers;										
			if (crossers == 0)
				sem_post(&rope_mut);						
			done = true;
		}
		else
			sleep(0);
		sem_post(&crossers_mut);							
	}
	return 0;
}

int main(){
	sem_init(&crossers_mut, 0, 1);							
	sem_init(&rope_mut, 0, 1);								
	sem_init(&write_mut, 0, 1);								
	pthread_t baboons[BABOONS_TO_CROSS];					
	srand(time(NULL));										
	for (int i = 0; i < BABOONS_TO_CROSS; ++i){
															
		sleep(-AVERAGE_CREATION_TIME * log((double)rand()/((double)RAND_MAX + 1)));
		double direction = (double)rand()/(double)RAND_MAX;	
		if (direction < .5){								
			pthread_create(&baboons[i], NULL, eastbound_baboon, (void *)i);
		}
		else												
			pthread_create(&baboons[i], NULL, westbound_baboon, (void *)i);
	}


	for (int i = 0; i < BABOONS_TO_CROSS; ++i){
		pthread_join(baboons[i], NULL);
	}
	return 0;
}
