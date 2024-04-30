#include<cs50.h>
#include<string.h>
#include<stdio.h>
#define MAX_CANDIDATES 9
#define MAX_VOTERS 100
typedef struct{
    string name;
    int votes;
    bool eliminated;
}candidate;

int preferences[MAX_VOTERS][MAX_CANDIDATES];   //matriz 
candidate candidates[MAX_CANDIDATES];

int voter_count;
int candidate_count;

bool vote(int voter, int rank, string names);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
int main(int argc, string argv[])
{

    if(argc < 2)
    {
        printf("./runoff Enter candidate");
        return 1;
    }

    if(argc+1 > MAX_CANDIDATES)
    {
        printf("Enter below %i candidates", MAX_CANDIDATES);
        return 2;
    }

 candidate_count = argc-1;
for(int i = 0; i<candidate_count;i++)
{
  candidates[i].name = argv[i+1];
  candidates[i].votes = 0;               //setea nombres con el command line argument y pone lo demas default
  candidates[i].eliminated = false;
}


     voter_count = get_int("Number of voters ");
    if(voter_count > MAX_VOTERS)
    {
      printf("Enter below %i number of voters", MAX_VOTERS);
    }


    for (int i = 0; i < voter_count; i++)
    {
                                                                //recorre la matriz con un nested

        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(i, j, name))                        //llama a la funcion de votos al mismo tiempo que checkea si son validos o no
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
                                                    
        printf("\n");
}


 while(true){
    tabulate();

    bool won = print_winner();
        if (won)
        {
            break;
        }
        int min = find_min();
        bool tie = is_tie(min);
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        eliminate(min);

        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;          //resetea los votos a 0 
        }
    }
    return 0;
 }





bool vote(int voter, int rank, string name)
{
for (int i = 0; i<candidate_count;i++)
{
   if (strcmp(candidates[i].name,name) == 0)     // se fija si el nombre esta en candidatos 
   {
    preferences [voter][rank] = i; //guarda los votos desde voter [0] por preferencia [1 2 3] hasta el voter final
                                   //usando los i,j que recibieron del nested loop de arriba
    return true;
   }
}

return false;
}

void tabulate(void)
{
    for (int i = 0; i < voter_count;i++)
    {

        for(int j = 0; j < candidate_count;j++)
        {
            if(candidates[preferences[i][j]].eliminated == false) // si el candidato no esta eliminado
        {
            candidates[preferences[i][j]].votes++; //añadimos el total vote count a cada candidato
            break;
        }


        }
    }
}

bool print_winner(void)
{

    for(int i = 0; i < candidate_count ; i++)
    {

    if(candidates[i].votes > (voter_count/2)) // si tiene mas de la mitad de los votos gana automaticamnete
    {
        printf("%s\n", candidates[i].name);
        return true;
    }
    }
return false;


}
int find_min(void)
{
    int minimum = voter_count;

    for (int i = 0; i<candidate_count;i++)
    {
           if(candidates[i].votes<minimum && candidates[i].eliminated == false)
           {
            minimum = candidates[i].votes;
           }
    }return minimum;

}
bool is_tie(int min)
{
    int still_run = 0; // si no esta eliminado
    int counter = 0;
   for (int i = 0; i<candidate_count;i++)
   {
      if(!candidates[i].eliminated)
      {
        still_run++;
      }
      if (candidates[i].votes == min)
      {
        counter++; // 
      }
    }
      if(still_run == counter)
      {
        return true;      // si todos los candidatos sin eliminar tienen el minimo de votos 
      }
    {
   }
   return false;
}

void eliminate(int min)
{
    for (int i = 0; i<candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if(candidates[i].votes == min)
            {
                candidates[i].eliminated = true;
            }

        }
    }return;
}
