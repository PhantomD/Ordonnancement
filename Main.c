#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct Machine Machine;
typedef struct Job Job ;




struct Machine {
    int id;
    float Si; //Début
    float Ti; //Fin
    /** Entre Si et Ti on ne peut rien faire **/
};

struct Job {
    int id;
    float* duree;
    float ci  ; //date de fin;
};


/**
 * @brief affichage
 * @param jobs
 * @param machines
 * @param n_j nombre de jobs
 * @param n_m nombre de machines
 */
void affichage(Job* jobs, Machine* machines, int n_j, int n_m){
    int i, j ;

    printf("****affichage ******\n");

    for (i = 0 ; i < n_j ; i++){  // affichage jobs
        Job jo = jobs[i];

        printf("job : id = %d , duree = [ ", jo.id);
        for(j = 0 ; j < n_m ; j++){ // affichage durée
            printf("%f, ",jo.duree[i]);
        }
        printf("] \n");
    }

    for (i = 0 ; i < n_m ; i++){  // affichage machines
        Machine machine = machines[i];
        printf("machine id = %d, Si = %f, Ti = %f \n", machine.id, machine.Si, machine.Ti);

    }

    printf("**********\n");
}


/**
 * @brief f fonction objective
 * @param jobs tableau des jobs
 * @param i nombre de jobs
 * @return
 */
int f(Job* jobs, int i){

    int res = 0, j;

    for(j=0; j < i ; j++){
        res+= jobs[j].ci;
    }
    return res ;
}






int main(){

    int j = 1; //Jobs
    int m = 2; //Machines
    int* tab = malloc(m*j*sizeof(int)); // tableau final à ordonnancer
    Job* jobs = malloc(j*sizeof(Job));
    Machine* machines = malloc(m*sizeof(Machine));

    srand(time(NULL));

    //instanciation
    int i,k;

    for (i = 1 ; i <= j ; i++){  // instanciation jobs
        Job jo ;
        jo.id = 5;
        jo.duree = malloc(sizeof(int)*m);
        for(k = 0 ; k < m ; k++){ // instanciations durées pour chaque job
            jo.duree[k] = rand();
        }
        jobs[i-1] = jo;
    }

    for (i = 1 ; i <= m ; i++){ //instanciation machine
        Machine machine ;
        machine.id = i;
        machine.Si = rand();
        machine.Ti = rand();
        machines[i-1]= machine ;
    }

    affichage(jobs, machines, j , m);


    // libération mémoire
    free(tab);

    for (i = 0 ; i < j ; i++){ // libération job
        free(jobs[i].duree);
    }

    free(jobs);
    free(machines);
    return 0;


}
