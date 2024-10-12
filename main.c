#include <stdio.h>
#include <stdlib.h>
#define CMAX 10

int choix, x;
 int solde;

typedef struct SClient {
    int Code_cli;
    char Nom[CMAX];
    char Prenom[CMAX];
} SClient;

int comparer (const void* a, const void* b)
{
    const SClient *c1 = a;
    const SClient *c2 = b;
    return strcmp(c1->Nom,c2->Nom);

}


typedef struct Date {
    int Jour;
    int Mois;
    int Annee;
} Date;

typedef struct SCompte {
    int code_cpt;
    int code_cli;
    struct Date d_compte;
    int somme;
} SCompte;

SClient clients[20];
SCompte comptes[20];

void menu() {
    printf("1- Gestion des clients\n");
    printf("2- Gestion des comptes\n");
    printf("3- Gestion des operations\n");
    printf("4- Quitter le programme\n");
    printf("Choisir le menu : ");
    scanf("%d", &choix);
    sous_menu(choix);
}

void sous_menu(int a) {
    if (a == 1) {
        printf("1-Ajouter\n");
        printf("2-Modifier\n");
        printf("3-Suprimer\n");
        printf("4-Afficher\n");
        printf("5-Retour\n");
        printf("Choisir un sous menu : ");
        scanf("%d", &x);
        gerer_client(x);
    } else if (a == 2) {
        printf("1-Ajouter\n");
        printf("2-Rechercher\n");
        printf("3-Afficher la liste\n");
        printf("4-Suprimer\n");
        printf("5-Retour\n");
        printf("Choisir un sous menu : ");
        scanf("%d", &x);
        gere_compte(x);
    } else if (a == 3) {
        printf("1-Retrait\n");
        printf("2-Viremeny\n");
        printf("Choisir un sous menu : ");
        scanf("%d", &x);
         gere_operation(x);
    } else if (a == 4) {
        exit(0);  // Exit the program when option 4 is chosen
    } else {
        printf("Mauvais choix\n");
        menu();  // Return to the menu in case of a wrong choice
    }
}

void gerer_client(int a) {
    if (a == 1) {  // Add Client
       struct SClient client;
        FILE *file;
        printf("Code client: ");
        scanf("%d", &client.Code_cli);
        printf("Nom: ");
        scanf("%s", client.Nom);  // No need for & with arrays
        printf("Prenom: ");
        scanf("%s", client.Prenom);

        file = fopen("client.txt", "a");
        fwrite(&client, sizeof(client), 1, file);

        if (fwrite != 0) {
            printf("Client ajouté avec succès\n");
        } else {
            printf("Erreur\n");
        }
        fclose(file);

    } else if (a == 2) {  // Modify Client
        SClient client, nvClient;
        FILE *file;

        printf("Code Client à modifier: ");
        scanf("%d", &nvClient.Code_cli);
        printf("Nouveau nom: ");
        scanf("%s", nvClient.Nom);
        printf("Nouveau prenom: ");
        scanf("%s", nvClient.Prenom);

        file = fopen("client.txt", "r");
        int nbClient = 0;
        while (fread(&client, sizeof(SClient), 1, file)) {
            clients[nbClient] = client;
            nbClient++;
        }
        fclose(file);
        remove("client.txt");

        FILE *nf = fopen("ny.txt", "a");
        for (int i = 0; i < nbClient; i++) {
            if (clients[i].Code_cli == nvClient.Code_cli) {
                fwrite(&nvClient, sizeof(SClient), 1, nf);
            } else {
                fwrite(&clients[i], sizeof(SClient), 1, nf);
            }
        }
        fclose(nf);
        rename("ny.txt", "client.txt");

    } else if (a == 3) {  // Delete Client
        struct SClient client;
        int code;
        FILE *file;

        printf("Code Client à supprimer: ");
        scanf("%d", &code);

        file = fopen("client.txt", "r");
        int nbClient = 0;
        while (fread(&client, sizeof(SClient), 1, file)) {
            clients[nbClient] = client;
            nbClient++;
        }
        fclose(file);
        remove("client.txt");

        FILE *nf = fopen("ny.txt", "a");
        for (int i = 0; i < nbClient; i++) {
            if (clients[i].Code_cli != code) {
                fwrite(&clients[i], sizeof(SClient), 1, nf);
            }
        }
        fclose(nf);
        rename("ny.txt", "client.txt");

    } else if (a == 4) {  // Display Clients
        SClient client;
        FILE *file = fopen("client.txt", "r");
        int nbClient = 0;
        while (fread(&client, sizeof(SClient), 1, file)) {
            clients[nbClient] = client;
            nbClient++;
        }
        fclose(file);
        qsort(clients, nbClient,sizeof(SClient),comparer);

        for (int c = 0; c < nbClient; c++) {
            printf("\nCode client: %d", clients[c].Code_cli);
            printf("\nNom: %s %s\n", clients[c].Nom, clients[c].Prenom);
        }

    } else if (a == 5)
        menu();  // Return to the main menu

}
void gere_compte(int a)
{

    if(a==1)
    {
           // Add Client
        struct SCompte compte;
        struct SCompte compte0;

        FILE *file;
        FILE *f1;
        printf("Code compte: ");
        scanf("%d", &compte.code_cpt);

        f1=fopen("compte.txt","r");


        int found=0;


        while(fread(&compte0,sizeof(struct SCompte),1,f1 && found ==0)) {
            if (compte0.code_cpt == compte.code_cpt)
            {

                  found = 1;
            }
        }
        if(found==1)
            printf("code  existant\n");
            return 0;





        printf("Code Client: ");
        scanf("%d", &compte.code_cli);  // No need for & with arrays
        printf("Jour : ");
        scanf("%d", &compte.d_compte.Jour);
        printf("Mois: ");
        scanf("%d", &compte.d_compte.Mois);
        printf("Année: ");
        scanf("%d", &compte.d_compte.Annee);
        printf("Somme :");
        scanf("%d",&compte.somme);

        file = fopen("compte.txt", "a");
        fwrite(&compte, sizeof(compte), 1, file);

        if (fwrite != 0)
            printf("Compte ajoute avec succees\n");
         else
            printf("Erreur\n");
    }
    else if (a==2)
    {
        struct SCompte compte;
        int code;
        FILE*file;

        printf("Code compte : ");
        scanf("%d",&code);

        file=fopen("compte.txt","r");
        int found=0;


        while(fread(&compte,sizeof(struct SCompte),1,file && found ==0)) {
            if (compte.code_cpt == code)
            {
                printf("\n Code compte : %d",compte.code_cpt);
                 printf("\n Code client : %d",compte.code_cli);
                  printf("\n Code creation %d / %d / %d",compte.d_compte.Jour, compte.d_compte.Mois,compte.d_compte.Annee);
                  printf("\n Somme %d",compte.somme);
                  found = 1;
            }
        }
        if(found==0)
            printf("code non existant\n");

        fclose(file);

    }
      else if (a==3)
    {
        struct SCompte compte;
        FILE*file;


        file=fopen("compte.txt","r");


        while(fread(&compte,sizeof(struct SCompte),1,file)) {

                printf("\n Code compte : %d",compte.code_cpt);
                 printf("\n Code client : %d",compte.code_cli);
                  printf("\n Code creation %d / %d / %d",compte.d_compte.Jour, compte.d_compte.Mois,compte.d_compte.Annee);
                  printf("\n Somme %d",compte.somme);
                  printf("\n----------------------------------");

        }


        fclose(file);

    }
     else if (a == 4) {  // Delete Client
        struct SCompte compte;
        int code;
        FILE *file;

        printf("Code Compte à supprimer: ");
        scanf("%d", &code);

        file = fopen("compte.txt", "r");
        int nbCompte = 0;
        while (fread(&compte, sizeof(SCompte), 1, file)) {
            comptes[nbCompte] = compte;
            nbCompte++;
        }
        fclose(file);
        remove("compte.txt");

        FILE *nf = fopen("ny.txt", "a");
        for (int i = 0; i < nbCompte; i++)
            {
            if (comptes[i].code_cpt != code)
                fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
            }
        fclose(nf);
        rename("ny.txt", "compte.txt");
        }
        else if (a==5)
        menu();

}
void  gere_operation(int a)
{
    if(a==1)
    {
        struct SCompte compte;
        int code,m;
        FILE *file;

        printf("Code Compte : ");
        scanf("%d", &code);

         file = fopen("compte.txt", "r");

        int nb = 0;

        while (fread(&compte, sizeof(struct SCompte), 1, file)) {
            comptes[nb] = compte;
            nb++;
        }
        fclose(file);
        remove("compte.txt");

        FILE *nf;
        nf = fopen("ny.txt", "a");
        for (int i = 0; i < nb; i++)
            {
                 if (comptes[i].code_cpt == code)
                    {

                  do{
                        printf("montant :");
                        scanf("%d",&m);
                        if(m>500)
                            printf("le montant ne doit pas depasser 500 DT");
                         solde = comptes[i].somme - m;
                        if(solde<250)
                            printf("le solde ne doit pas etre inf a 250 DT ");

                        }while(m>500 || solde<250);
                        comptes[i].somme=comptes[i].somme-m;
                         printf("\n Code compte : %d",compte.code_cpt);
                         printf("\n Code client : %d",compte.code_cli);
                         printf("\n Code creation %d / %d / %d",compte.d_compte.Jour, compte.d_compte.Mois,compte.d_compte.Annee);
                         printf("\n Somme %d",compte.somme);
                         printf("\n----------------------------------");

                      }
                fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
            }
        fclose(nf);
        rename("ny.txt", "compte.txt");

    }
    else if(a==2)
    {
          struct SCompte compte;
        int code1,code2,m;
        FILE *file;

        printf("Code Compte de depart : ");
        scanf("%d", &code1);

        printf("Code Compte d arrivee : ");
        scanf("%d", &code2);

         file = fopen("compte.txt", "r");

        int nb = 0;

        while (fread(&compte, sizeof(struct SCompte), 1, file)) {
            comptes[nb] = compte;
            nb++;
        }
        fclose(file);
        remove("compte.txt");

        FILE *nf;
        nf = fopen("ny.txt", "a");
        for (int i = 0; i < nb; i++)
            {
                 if (comptes[i].code_cpt == code1)
                    {

                        do{
                            printf("montant :");
                            scanf("%d",&m);
                            if(m>500)
                                printf("\n le montant ne doit pas depasser 500 DT");
                            solde = comptes[i].somme - m;
                            if(solde<250)
                                printf("\n le solde ne doit pas etre inf a 250 DT ");

                            }while(m>500 || solde<250);
                        comptes[i].somme=comptes[i].somme - m;
                         printf("\n  compte depart :");
                         printf("\n Code compte : %d",comptes[i].code_cpt);
                         printf("\n Code client : %d",comptes[i].code_cli);
                         printf("\n my Somme :%d",comptes[i].somme);
                         printf("\n Date creation %d / %d / %d",compte.d_compte.Jour, compte.d_compte.Mois,compte.d_compte.Annee);
                         printf("\n----------------------------------");

                      }
                      else if(comptes[i].code_cpt == code2)
                      {
                          comptes[i].somme = comptes[i].somme + m;
                          printf("compte d arrivée :");
                           printf("\n code compte %d",comptes[i].code_cpt);
                            printf("\n code client %d",comptes[i].code_cli);
                             printf("\n my somme : %d",comptes[i].somme);
                              printf("\n Date creation %d / %d / %d",compte.d_compte.Jour , compte.d_compte.Mois , compte.d_compte.Jour);
                               printf("\n-------------------------------");
                      }
                fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
            }
        fclose(nf);
        rename("ny.txt", "compte.txt");

    }
    }



int main() {
    menu();
    return 0;
}
