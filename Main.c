#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>



typedef struct Machine Machine;
typedef struct Job Job ;
typedef struct Horaire Horaire ;
typedef struct Element Element;
typedef Element* llist;
typedef struct Liste Liste;


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

struct Horaire{
    float debut;
    float fin;
    int id;
    bool attente;
};



struct Element
{
    int nombre;
    Element *suivant;
};


struct Liste
{
    Element *premier;
    Element *dernier;
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
            printf("%f, ",jo.duree[j]);
        }
        printf("] \n");
    }

    for (i = 0 ; i < n_m ; i++){  // affichage machines
        Machine machine = machines[i];
        printf("machine id = %d, Si = %f, Ti = %f \n", machine.id, machine.Si, machine.Ti);

    }

    printf("**********\n");
}


int count(void **tab)
{
      int i;

     for (i = 0; tab[i]; i++)
            ;
     return (i);
}

void affichageTableauOrdonnance(Horaire** tab, int job, int machine, Machine* machines, int* nbJobMachine){
    int i, j ;
    printf("****affichage tableau ******\n");
    for (i = 0 ; i < machine ; i++){
        Machine m = machines[i];
        printf("Machine : id = %d \n", m.id);
        for(j = 0 ; j < nbJobMachine[i]; j++){
            Horaire horaire = tab[i][j];
            if(horaire.attente)
                printf("Horaire de %.2f h à %.2f h en attente \n",horaire.debut,horaire.fin);
            else
                printf("Travail sur l'Horaire de %.2f h a %.2f h sur le job %d \n",horaire.debut,horaire.fin,horaire.id);
        }
        printf("\n");
    }

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

void tricroissant( int tab[], int tab_size)
{
  int i=0;
  int tmp=0;
  int j=0;

  for(i = 0; i < tab_size; i++)
    {
      for(j = i+1; j < tab_size; j++)
        {
          if(tab[j] < tab[i])
            {
              tmp = tab[i];
              tab[i] = tab[j];
              tab[j] = tmp;
            }
        }
    }
}

void tridecroissant(Job* jobs)
{
  int i=0, tmp=0, j=0;
  for(i = 0; i < sizeof(jobs); i++)
    {
        Job jtmp = jobs[i];
        if(jtmp.duree[i] < jtmp.duree[i+1])
            {
              tmp = jtmp.duree[i];
              jtmp.duree[i] = jtmp.duree[j];
              jtmp.duree[j] = tmp;
            }
        }

}

void swap(int a, int b){
    int tmp;
    tmp = a;
    a = b;
    b = tmp;
}

Liste *initialisation()
{
    Liste *liste = malloc(sizeof(*liste));
    Element *element = malloc(sizeof(*element));
    if (liste == NULL || element == NULL)
    {
        exit(EXIT_FAILURE);
    }
    element->nombre = NULL;
    element->suivant = NULL;
    liste->premier = NULL;
    return liste;
}

void afficherListe(Liste *liste)
{
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    Element *actuel = liste->premier;
    while (actuel != NULL)
    {
        printf("%d -> ", actuel->nombre);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

void insertion(Liste *liste, int nvNombre)
{
    Element *nouveau = malloc(sizeof(*nouveau));
    if (liste == NULL || nouveau == NULL)
    {
        exit(EXIT_FAILURE);
    }
    nouveau->nombre = nvNombre;
    nouveau->suivant = liste->premier;
    liste->premier = nouveau;
}

/**
 * @brief heuristique_NEH
 * Il s'agit d'un algorithme constructif qui sélectionne le job le plus long parmi les jobs non encore placés et essaie de l’insérer dans toutes
 *les  positions  possibles  de  la  séquence  partielle  en   cours  de  construction.  Elle  choisit  enfin  la
 *séquence  qui  augmente  le  moins  la  durée  de  l’ordonnancement  partiel  formé  par  les  jobs  déjà placés.
 */


 Horaire** heuristique_NEH(Job* jobs, Machine* machines, Horaire** tab, int job, int machine){

    int i = 0, j = 0, k = 0, duree_job = 0, tmp = 0, nb_job = 0 ;
    //Liste liste_jobs = NULL;
    Liste *liste_jobs = initialisation();

    for(i = 0; i < job; i++)
    {
        Job jtmp = jobs[i];
        while(machine != nb_job)
        {
            nb_job++;
            for(j = 0 ; j < sizeof(jobs)+1 ; j++)
            {
                if(jtmp.duree[j] < jtmp.duree[j-1])
                {
                    tmp = jtmp.duree[j];
                    jtmp.duree[j] = jtmp.duree[j-1];
                    jtmp.duree[j-1] = tmp;
                }
                if(nb_job ==  machine){
                printf("%f    ",jtmp.duree[j]); /****** Affiche dans ordre croissant, pour afficher dans l'ordre decroissant dans la liste ********/
                insertion(liste_jobs, jtmp.duree[j]);

                }
            }

        }
    }
    afficherListe(liste_jobs); /********* affiche la liste des jobs dans l'ordre décroissant de leur durée *************/
 }
   /* tridecroissant(jobs, job);
    for(int b = 0; b < jobs.length; b++) liste_job.add(jobs[b]);
    for(int i = 0; i < N; i++)
        {
            Cpmax = 9999999;
            for(int k = 1; k < i; k++)
            {

Placer le job Ji à la position k dans la séquence partielle sans changer la position relative des autres jobs déjà placés.
Calculer le Cmax de l’ordonnancement partiel formé.

                if(Cmax< Cpmax)
                {
                    Best_k = k;
                    Cpmax = Cmax;
                }
            }
        }
*/



/**
 * @brief heuristique_TSS
 * Heuristique partant d'une solution partielle et choissant le meilleur job suivant, selon certaines conditions
 */
Horaire** heuristique_TSS(Job* jobs, Machine* machines, Horaire** tab, int job, int machine, int* nbJobMachine){
    int i,j,k,t,g;
    for(i = 0; i< machine; i++){
        nbJobMachine[i] = 0;
    }
    float pause =0;
    float somtpsin =0;
    float somtpsex= 0;
    float dureeajoute = 0;
    float cpmax = 0;
    int jobplace = 0;
    int crt = 50000;
    int crtj;
    for(i = 0 ; i < job ; i++){
        // on place le job Ji
        for(j = 0 ; j< machine ; j++){
            for(k = 0 ; k<j ;k++){
                Job jtmp = jobs[i];
                pause += jtmp.duree[k];
            }
            if(j==0){
                Horaire htmp;
                Job jtmp = jobs[i];
                htmp.debut = 0;
                htmp.attente = false;
                htmp.fin = jtmp.duree[j] + htmp.debut;
                htmp.id = jtmp.id;
                tab[j][nbJobMachine[j]] = htmp;
                nbJobMachine[j]++;
            }
            else{
                 Horaire htmp;
                 htmp.attente = true;
                 htmp.debut=0;
                 htmp.fin = pause +  htmp.debut;
                 pause = 0;
                 tab[j][nbJobMachine[j]] = htmp;
                 nbJobMachine[j]++;
                 Job jtmp = jobs[i];
                 Horaire htmpprec = tab[j][0];
                 htmp.debut = htmpprec.fin;
                 htmp.attente = false;
                 htmp.fin = jtmp.duree[j] + htmp.debut;
                 htmp.id = jtmp.id;
                 tab[j][nbJobMachine[j]]  = htmp;
                 nbJobMachine[j]++;
            }
        }
        while(job - 1 - jobplace > 0){
            for(t = 1 ;t<job - jobplace; t++){
                somtpsex = 0;
                somtpsin = 0;
                cpmax = 0;
                Job jtmp = jobs[t];
                for(j = 0 ; j<machine; j++){
                    pause = 0;
                    for(k = 0 ; k<j ;k++){
                        pause += jtmp.duree[k];
                    }

                    for(g=0 ; g<nbJobMachine[j]; g++){
                        Horaire htmp = tab[j][g];
                        if(htmp.attente)
                            somtpsin += htmp.fin - htmp.debut;
                        else
                            somtpsex += htmp.fin - htmp.debut;
                    }
                    Horaire htmp = tab[j][nbJobMachine[j]-1];
                    dureeajoute = jtmp.duree[j] + htmp.fin + pause;
                    somtpsin+= pause;
                    somtpsex+=jtmp.duree[j];
                    if(dureeajoute>cpmax){
                        cpmax = dureeajoute;
                    }
                }
                if((cpmax + somtpsin - somtpsex) < crt){
                    crt = (cpmax + somtpsin - somtpsex);
                    crtj = t;
                }
            }
            for(j = 0 ; j< machine ; j++){
                pause = 0;
                for(k = 0 ; k<j ;k++){
                    Job jtmp = jobs[crtj];
                    pause += jtmp.duree[k];
                }
                if(j==0){
                    Horaire htmp;
                    Horaire htmpprec = tab[j][nbJobMachine[j]-1];
                    Job jtmp = jobs[crtj];
                    htmp.debut = htmpprec.fin;
                    htmp.attente = false;
                    htmp.fin = jtmp.duree[j] + htmp.debut;
                    htmp.id = jtmp.id;
                    tab[j][nbJobMachine[j]] = htmp;
                    nbJobMachine[j]++;
                }
                else{
                     Horaire htmp;
                     Horaire htmpprec = tab[j][nbJobMachine[j]-1];
                     htmp.attente = true;
                     htmp.debut=htmpprec.fin;
                     htmp.fin = pause +  htmp.debut;
                     pause = 0;
                     tab[j][nbJobMachine[j]] = htmp;
                     nbJobMachine[j]++;
                     Job jtmp = jobs[crtj];
                     htmpprec = tab[j][nbJobMachine[j]-1];
                     htmp.debut = htmpprec.fin;
                     htmp.attente = false;
                     htmp.fin = jtmp.duree[j] + htmp.debut;
                     htmp.id = jtmp.id;
                     tab[j][nbJobMachine[j]]  = htmp;
                     nbJobMachine[j]++;
                }
            }
            jobplace++;
           // A FAIRE  jobs = supprimerElement(jobs, crtj, j);
        }

    }
    return tab;

}

/**
 * @brief allocfloat2
 * @param nb1 premiere dimension
 * @param nb2 deuxieme dimension
 * @return
 * Permet d'allouer de la mémoire pour un tableau a deux dimensions
 */
int **allocfloat2(int nb1, int nb2)
{
  int **p;
  int i;

  p = (int **) malloc(sizeof(int *) * nb1);
  if(p == NULL) {
    fprintf(stderr,"erreur malloc 2\n");
    exit(EXIT_FAILURE);
  }

  for(i=0;i<nb1;i++) {
    p[i] = malloc(sizeof(Horaire) * nb2);
    if(p[i] == NULL) {
      fprintf(stderr,"erreur malloc 3\n");
      exit(EXIT_FAILURE);
    }
  }
  return(p);
}




int main(){

    int j = 2; //Jobs
    int m = 4; //Machines
    Horaire** tab = allocfloat2(m,j*2); // tableau final à ordonnancer  j*2 = nb job + pause entre job
    Job* jobs = malloc(j*sizeof(Job));
    Machine* machines = malloc(m*sizeof(Machine));

    srand(time(NULL));

    //instanciation
    int i,k;

    for (i = 1 ; i <= j ; i++){  // instanciation jobs
        Job jo ;
        jo.id = i;
        jo.duree = malloc(sizeof(int)*m);
        for(k = 0 ; k < m ; k++){ // instanciations durées pour chaque job
            jo.duree[k] = rand()%(10-1)+1;
        }
        jobs[i-1] = jo;
    }

    for (i = 1 ; i <= m ; i++){ //instanciation machine
        Machine machine ;
        machine.id = i;
        machine.Si = rand()%(20-1)+1;
        machine.Ti = rand()%(20-(int)(machine.Si+1))+(int)(machine.Si+1);
        machines[i-1]= machine ;
    }


   affichage(jobs, machines, j , m);
   int* nbJobMachine = malloc(m*sizeof(int));
   tab = heuristique_TSS(jobs,machines,tab,j,m,nbJobMachine);
   //affichageTableauOrdonnance(tab,j,m,machines,nbJobMachine);

    tab = heuristique_NEH(jobs, machines,tab,j,m);
    //affichageTableauOrdonnance(tab,j,m,machines,nbJobMachine);

    // libération mémoire
    free(tab);

    for (i = 0 ; i < j ; i++){ // libération job
        free(jobs[i].duree);
    }

    free(jobs);
    free(machines);
    return 0;


}

