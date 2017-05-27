#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
using namespace std;


pthread_mutex_t mutex;
pthread_cond_t cond_var;
pthread_mutex_init(&mutex,NULL);
pthread_cond_init(&cond_var,NULL);



bool chopstick[6]=1; // I use indexes 1 to 5 in order to clarify the simulation of the problem
                     // value 1 means the chopstick is free. value 0 means the chopstick is being used.

void thinking(int duration, int philosopherNumber){
	cout<<"The philosopher "<<philosopherNumber<<" is gonna think for a while!"<<endl;
	sleep(duartion);
}


void eating(){
	cout<<"The philosopher "<<philosopherNumber<<" wishes to eat dinner!"<<endl;
	pickup_forks(philosopherNumber);
	return_forks(philosopherNumber);
	pthread_exit(0);
}

void pickup_forks(int philosopherNumber){ //The philosopher wishes to eat
	pthread_mutex_lock($mutex);
	while (!(chopstick[philosopherNumber] && chopstick[(philosopherNumber+1)%5])) {
		pthread_cond_wait(&mutex, &cond_var);
	cout<<"The philosopher "<<philosopherNumber<<" picked up both of the chopsticks!"<<endl;
	pthread_mutex_unlock(&mutex);
	}

}


void return_forks(int philosopherNumber){ //The philosopher has finished eating
	pthread_mutex_lock($mutex);
	chopstick[philosopherNumber]=1;
	chopstick[(philosopherNumber+1)%5]=1;
	pthread_cond_signal(&cond_var);
	cout<<"The philosopher "<<philosopherNumber<<" returned both of the chopsticks!"<<endl;
	pthread_mutex_unlock(&mutex);
	thinking();
}

int main(){

	srand(time(NULL));

	pthread_t philosopher[6]; // I use indexes 1 to 5 in order to clarify the simulation of the problem

	for(int i=1; i<6; i++){
		pthread_create(&philosopher[i], NULL, thinking((rand()%3)+1, i), NULL); // Sleep between 1 and 3 seconds
		pthread_join(&philosopher[i],NULL);
	}

	return 0;
}