#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include<stdbool.h>
#include<math.h>

/* portul folosit */
#define PORT 2018
#define MAX_GEN 11
#define MAX_SUGGESTION 10
#define MAX_SEARCH_RESULTS 1000
#define BUFFER_LENGTH 512
const char IP[]="127.0.0.1";
char username[21],password[33]; 

/* codul de eroare returnat de anumite apeluri */
extern int errno;
int client,utilizator_id;

//initializare database handler , statement query
sqlite3 *db;
sqlite3_stmt *res; 



void send_book(int book_id)
{
char Titlu[30],Autor[63],An_aparitie[10],ISBN[17],Gen[30],Rezumat[10000];
int size_toSend,size_Sent,return_Value,rating;
char *sql = "SELECT CARTI.TITLU,AUTORI.NUME,AUTORI.PRENUME,CARTI.AN_APARITIE,CARTI.ISBN,CARTI.RATING,GENURI.NUME_GEN,CARTI.REZUMAT FROM CARTI JOIN AUTORI ON AUTORI.AUTOR_ID=CARTI.AUTOR_ID JOIN GENURI ON CARTI.GEN_ID=GENURI.GEN_ID WHERE CARTI.CARTE_ID=?";
int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    if (rc == SQLITE_OK) 
    {
        sqlite3_bind_int(res, 1, book_id);
    }


    int step;
    while((step = sqlite3_step(res))!=SQLITE_DONE)
    {
       if(step == SQLITE_ROW) 
        { 
          strcpy(Titlu,sqlite3_column_text(res, 0));
          strcpy(Autor,sqlite3_column_text(res, 1));
          strcat(Autor," ");
          strcat(Autor,sqlite3_column_text(res, 2));
          strcpy(An_aparitie,sqlite3_column_text(res, 3));
          strcpy(ISBN,sqlite3_column_text(res, 4));
          rating=atoi(sqlite3_column_text(res, 5));
          strcpy(Gen,sqlite3_column_text(res, 6));
          strcpy(Rezumat,sqlite3_column_text(res,7));

        }
    }
Autor[strlen(Autor)]='\0';
Titlu[strlen(Titlu)]='\0';
 An_aparitie[strlen(An_aparitie)]='\0';
 ISBN[strlen(ISBN)]='\0';
 Gen[strlen(Gen)]='\0';
 Rezumat[strlen(Rezumat)]='\0';

printf("%s %s %s %s %s %s %d \n",Autor,Titlu,An_aparitie,ISBN,Gen,Rezumat,rating);
fflush(stdout);



send(client,&book_id,sizeof(int),0);

 size_toSend=strlen(Titlu)+1;
    send(client,&size_toSend,sizeof(int),0);
  
    size_Sent=0;
    while(size_Sent<size_toSend)
    {
      return_Value=send(client,Titlu+size_Sent,size_toSend-size_Sent, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la send");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected" );
        break;
      }
      size_Sent+=return_Value;
    }
    
 size_toSend=strlen(Autor)+1;
    send(client,&size_toSend,sizeof(int),0);
  
    size_Sent=0;
    while(size_Sent<size_toSend)
    {
      return_Value=send(client,Autor+size_Sent,size_toSend-size_Sent, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la send");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected" );
        break;
      }
      size_Sent+=return_Value;
    }


     size_toSend=strlen(An_aparitie)+1;
    send(client,&size_toSend,sizeof(int),0);
  
    size_Sent=0;
    while(size_Sent<size_toSend)
    {
      return_Value=send(client,An_aparitie+size_Sent,size_toSend-size_Sent, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la send");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected" );
        break;
      }
      size_Sent+=return_Value;
    }

     size_toSend=strlen(ISBN)+1;
    send(client,&size_toSend,sizeof(int),0);
  
    size_Sent=0;
    while(size_Sent<size_toSend)
    {
      return_Value=send(client,ISBN+size_Sent,size_toSend-size_Sent, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la send");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected" );
        break;
      }
      size_Sent+=return_Value;
    }

    send(client,&rating,sizeof(int),0);



     size_toSend=strlen(Gen)+1;
    send(client,&size_toSend,sizeof(int),0);
  
    size_Sent=0;
    while(size_Sent<size_toSend)
    {
      return_Value=send(client,Gen+size_Sent,size_toSend-size_Sent, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la send");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected" );
        break;
      }
      size_Sent+=return_Value;
    }

     size_toSend=strlen(Rezumat)+1;
    send(client,&size_toSend,sizeof(int),0);
  
    size_Sent=0;
    while(size_Sent<size_toSend)
    {
      return_Value=send(client,Rezumat+size_Sent,size_toSend-size_Sent, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la send");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected" );
        break;
      }
      size_Sent+=return_Value;
    }
}

void create_search_vector(int* suggestion_vector,int* nr_cautari)
{

char *sql = "SELECT UTILIZATORI.NR_CAUTARI,CAUTARI.GEN_ID FROM UTILIZATORI JOIN CAUTARI ON CAUTARI.UTILIZATOR_ID=UTILIZATORI.UTILIZATOR_ID  WHERE UTILIZATORI.UTILIZATOR_ID=?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }


  if (rc == SQLITE_OK) 
  {
        sqlite3_bind_int(res, 1, utilizator_id);

  }

    int step;
    while((step = sqlite3_step(res))!=SQLITE_DONE)
    {
       if(step == SQLITE_ROW) 
        { 
            suggestion_vector[atoi(sqlite3_column_text(res, 1))]++;
            *nr_cautari=atoi(sqlite3_column_text(res, 0));
        }
    }
}


void get_books(int GEN_ID,int bookNumber,int *suggestion_vector,int *pozitie)
{
  char *sql = "SELECT * FROM(SELECT CARTE_ID FROM CARTI WHERE GEN_ID=?) LIMIT ? OFFSET 0";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    if (rc == SQLITE_OK) 
    {
        sqlite3_bind_int(res, 1, GEN_ID);
        sqlite3_bind_int(res, 2, bookNumber);

    }
    int step;
    while((step = sqlite3_step(res))!=SQLITE_DONE)
    {
       if(step == SQLITE_ROW) 
        { 
            suggestion_vector[*pozitie]=atoi(sqlite3_column_text(res, 0));
            *pozitie=*pozitie+1;
        }
    }  
}

int get_random_book(int pozitie,int *suggestion_vector)
{
  char *sql = "SELECT CARTE_ID FROM CARTI";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    int step;
    while((step = sqlite3_step(res))!=SQLITE_DONE)
    {
       if(step == SQLITE_ROW) 
        { 
            int ok=1;
            for(int i=0;i<=pozitie;i++)
            {
              if(suggestion_vector[i]==atoi(sqlite3_column_text(res, 0))) { ok=0;}
            }
            if(ok==1)
            {
              return atoi(sqlite3_column_text(res, 0));
            }
        }
    }
    return 0;  
}

void create_suggestion_vector(int *search_vector,int *suggestion_vector,int nr_cautari)
{
    int pozitie=0,nr_books;double percentage;
    for(int i=1;i<=MAX_GEN;i++)
    {
        if(search_vector[i]>0)
        {
          percentage=search_vector[i]/nr_cautari;
          nr_books=floor(percentage*MAX_SUGGESTION);
          get_books(i,nr_books,suggestion_vector,&pozitie);
        }
    }
    while(pozitie<MAX_SUGGESTION)
    {
      suggestion_vector[pozitie]=get_random_book(pozitie,suggestion_vector);
      pozitie++;
    }
}

void send_sugestii()
{
  int search_vector[MAX_GEN],nr_cautari,suggestion_vector[MAX_GEN];
  for(int i=0;i<MAX_GEN;i++)
  {
    search_vector[i]=0;
    suggestion_vector[i]=0;
  }
  create_search_vector(search_vector,&nr_cautari);
  create_suggestion_vector(search_vector,suggestion_vector,nr_cautari);
  for(int i=0;i<10;i++)
  {
    send_book(suggestion_vector[i]);
  }
}

void search_by_Titlu(int *number,int *search_results,char *text_toSearch)
{
  char *sql = "SELECT CARTE_ID FROM CARTI WHERE LOWER(TITLU) LIKE '%' || ? || '%' ";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    if (rc == SQLITE_OK) 
    {
      sqlite3_bind_text(res, 1, text_toSearch,strlen(text_toSearch),0);

    }
    int step;
    while((step = sqlite3_step(res))!=SQLITE_DONE)
    {
       if(step == SQLITE_ROW) 
        { 
            search_results[*number]=atoi(sqlite3_column_text(res, 0));
            *number=*number+1;
        }
    }  
}

void search_by_Autor(int *number,int *search_results,char *text_toSearch)
{
  char *sql = "SELECT CARTE_ID FROM CARTI JOIN AUTORI ON CARTI.AUTOR_ID=AUTORI.AUTOR_ID WHERE LOWER(AUTORI.NUME_COMPLET) LIKE '%' || ? || '%' ";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    if (rc == SQLITE_OK) 
    {
      sqlite3_bind_text(res, 1, text_toSearch,strlen(text_toSearch),0);

    }
    int step;
    while((step = sqlite3_step(res))!=SQLITE_DONE)
    {
       if(step == SQLITE_ROW) 
        { 
            search_results[*number]=atoi(sqlite3_column_text(res, 0));
            *number=*number+1;
        }
    }  
}

void search_by_Gen(int *number,int *search_results,char *text_toSearch)
{
  char *sql = "SELECT CARTE_ID FROM CARTI JOIN GENURI ON CARTI.GEN_ID=GENURI.GEN_ID WHERE LOWER(GENURI.NUME_GEN) LIKE '%' || ? || '%' ";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    if (rc == SQLITE_OK) 
    {
      sqlite3_bind_text(res, 1, text_toSearch,strlen(text_toSearch),0);

    }
    int step;
    while((step = sqlite3_step(res))!=SQLITE_DONE)
    {
       if(step == SQLITE_ROW) 
        { 
            search_results[*number]=atoi(sqlite3_column_text(res, 0));
            *number=*number+1;
        }
    }  
}

void search_by_Subgen(int *number,int *search_results,char *text_toSearch)
{

  char *sql = "SELECT CARTE_ID FROM CARTI JOIN SUBGENURI ON CARTI.SUBGEN_ID=SUBGENURI.SUBGEN_ID WHERE LOWER(SUBGENURI.NUME_SUBGEN) LIKE '%' || ? || '%' ";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    if (rc == SQLITE_OK) 
    {
      sqlite3_bind_text(res, 1, text_toSearch,strlen(text_toSearch),0);

    }
    int step;
    while((step = sqlite3_step(res))!=SQLITE_DONE)
    {
       if(step == SQLITE_ROW) 
        { 
            search_results[*number]=atoi(sqlite3_column_text(res, 0));
            *number=*number+1;
        }
    }  
}

void send_search_results()
{
  int option_size,size_Received,size_to_recv,return_Value,text_toSearch_size,search_number=0,search_results[MAX_SEARCH_RESULTS];
  char option[10],text_toSearch[30];
  recv(client,&option_size,sizeof(int),0);
  size_Received=0;
  size_to_recv=option_size;
    while(size_Received<size_to_recv)
    {
      return_Value=recv(client,option+size_Received,size_to_recv-size_Received, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la recv\n");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected\n" );
        break;
      }
      size_Received+=return_Value;
    }
    option[option_size]='\0';

  recv(client,&text_toSearch_size,sizeof(int),0);
  size_Received=0;
  size_to_recv=text_toSearch_size;
    while(size_Received<size_to_recv)
    {
      return_Value=recv(client,text_toSearch+size_Received,size_to_recv-size_Received, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la recv\n");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected\n" );
        break;
      }
      size_Received+=return_Value;
    }
    text_toSearch[text_toSearch_size]='\0';
    
    printf("Utilizatorul %s a cautat %s dupa %s \n",username,text_toSearch,option);

    if(strcmp(option,"Titlu")==0)
    {
    search_by_Titlu(&search_number,search_results,text_toSearch);
    send(client,&search_number,sizeof(int),0);
    for(int i=0;i<search_number;i++)
      {
        send_book(search_results[i]);
      }
    printf("\n");
    }
    if(strcmp(option,"Autor")==0)
    {
    search_by_Autor(&search_number,search_results,text_toSearch);
    send(client,&search_number,sizeof(int),0);
    for(int i=0;i<search_number;i++)
      {
        send_book(search_results[i]);
      }
    printf("\n");
    } 
    if(strcmp(option,"Gen")==0)
    {
    search_by_Gen(&search_number,search_results,text_toSearch);
    send(client,&search_number,sizeof(int),0);
    for(int i=0;i<search_number;i++)
      {
        send_book(search_results[i]);
      }
     printf("\n");
    }
    if(strcmp(option,"Subgen")==0)
    {
    search_by_Subgen(&search_number,search_results,text_toSearch);
    send(client,&search_number,sizeof(int),0);
    for(int i=0;i<search_number;i++)
      {
        send_book(search_results[i]);
      }
      printf("\n");
    }
}


void send_download()
{
  int book_id,size_toSend,size_Sent,return_Value;
  const char *file_location;
  char buffer[BUFFER_LENGTH];
  recv(client,&book_id,sizeof(int),0);

char *sql = "SELECT FILE_LOCATION FROM CARTI WHERE CARTE_ID=?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    if (rc == SQLITE_OK) 
    {
      sqlite3_bind_int(res, 1, book_id);
    }
    int step;
    while((step = sqlite3_step(res))!=SQLITE_DONE)
    {
       if(step == SQLITE_ROW) 
        { 
            file_location=sqlite3_column_text(res, 0);
        }
    }  

 char *file_name;
 char file_location_copy[1000];
 strcpy(file_location_copy,file_location);
 char *pch = strtok (file_location_copy,"/");
  while (pch != NULL)
  {
    file_name=pch;
    pch = strtok (NULL, "/");
  }    

printf("Se initiaza transferul fisierului %s catre utilizatorul %s\n",file_name,username);
fflush(stdout);

 size_toSend=strlen(file_name)+1;
 send(client,&size_toSend,sizeof(int),0);
  
    size_Sent=0;
    while(size_Sent<size_toSend)
    {
      return_Value=send(client,file_name+size_Sent,size_toSend-size_Sent, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la send");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected" );
        break;
      }
      size_Sent+=return_Value;
    }
    bool valid_download=0;
    FILE *file_descriptor = fopen(file_location,"r");
		if(file_descriptor == NULL)
		    {
        printf("Fisierul %s nu a putut fi deschis\n\n",file_name);
        send(client,&valid_download,sizeof(bool),0);
		    }
    else
    {
        valid_download=1;
        send(client,&valid_download,sizeof(bool),0);
        bzero(buffer, BUFFER_LENGTH); 
		    int file_block_size; 
		    while((file_block_size = fread(buffer, sizeof(char), BUFFER_LENGTH, file_descriptor))>0)
		    {
		        if(send(client, buffer, file_block_size, 0) < 0)
		        {
		            printf("Fisierul %s nu a putut fi trimis\n\n",file_name);
                break;
		        }
		        bzero(buffer, BUFFER_LENGTH);
		    }
        printf("Fisierul %s a fost trimis cu succes catre %s\n\n",file_name,username);
    }


}

void update_log()
{
  int book_id,utilizator_id,nr_cautari,gen_id;
  recv(client,&book_id,sizeof(int),0);
  
  char *sql = "SELECT UTILIZATOR_ID,NR_CAUTARI FROM UTILIZATORI WHERE NUME_CONT=?";
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    if (rc == SQLITE_OK) 
    {
      sqlite3_bind_text(res, 1, username,strlen(username),0);
    }
    int step;
    while((step = sqlite3_step(res))!=SQLITE_DONE)
    {
       if(step == SQLITE_ROW) 
        { 
            utilizator_id=atoi(sqlite3_column_text(res, 0));
            nr_cautari=atoi(sqlite3_column_text(res, 1));
        }
    } 

    sql = "SELECT GEN_ID FROM CARTI WHERE CARTE_ID=?";
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    if (rc == SQLITE_OK) 
    {
      sqlite3_bind_int(res, 1, book_id);
    }
    while((step = sqlite3_step(res))!=SQLITE_DONE)
    {
       if(step == SQLITE_ROW) 
        { 
            gen_id=atoi(sqlite3_column_text(res, 0));
        }
    } 

    sql = "INSERT INTO CAUTARI(UTILIZATOR_ID,CARTE_ID,GEN_ID) VALUES (?,?,?)"; 
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    if (rc == SQLITE_OK) 
    {
      sqlite3_bind_int(res, 1, utilizator_id);
      sqlite3_bind_int(res, 2, book_id);
      sqlite3_bind_int(res, 3, gen_id);
    }
     while((step = sqlite3_step(res))!=SQLITE_DONE); 

     sql = "UPDATE UTILIZATORI SET NR_CAUTARI=? WHERE UTILIZATOR_ID=?"; 
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    if (rc == SQLITE_OK) 
    {
      sqlite3_bind_int(res, 1, nr_cautari+1);
      sqlite3_bind_int(res, 2, utilizator_id);
    }
     while((step = sqlite3_step(res))!=SQLITE_DONE);
}

bool create_account(char *surname,char *name,char *account,char *password)
{
    int step;
    char *sql = "INSERT INTO UTILIZATORI(PAROLA,NUME,PRENUME,NUME_CONT) VALUES (?,?,?,?)"; 
    int rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) 
    {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }
    if (rc == SQLITE_OK) 
    {
    sqlite3_bind_text(res, 1, password,strlen(password),0);
    sqlite3_bind_text(res, 2, surname,strlen(surname),0);
    sqlite3_bind_text(res, 3, name,strlen(name),0);
    sqlite3_bind_text(res, 4, account,strlen(account),0);
    }
     while((step = sqlite3_step(res))==SQLITE_DONE)
     {
       printf("Contul %s a fost creat cu succes!",account);
       return 1;
     }
     return 0;
}


void register_account()
{
int size,size_Received,size_to_recv,return_Value,option_size;
char surname[31],name[21],account[21],password[33];

recv(client,&option_size,sizeof(int),0);
  size_Received=0;
  size_to_recv=option_size;
    while(size_Received<size_to_recv)
    {
      return_Value=recv(client,surname+size_Received,size_to_recv-size_Received, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la recv\n");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected\n" );
        break;
      }
      size_Received+=return_Value;
    }
surname[strlen(surname)]='\0';

recv(client,&option_size,sizeof(int),0);
  size_Received=0;
  size_to_recv=option_size;
    while(size_Received<size_to_recv)
    {
      return_Value=recv(client,name+size_Received,size_to_recv-size_Received, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la recv\n");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected\n" );
        break;
      }
      size_Received+=return_Value;
    }
name[strlen(name)]='\0';

recv(client,&option_size,sizeof(int),0);
  size_Received=0;
  size_to_recv=option_size;
    while(size_Received<size_to_recv)
    {
      return_Value=recv(client,account+size_Received,size_to_recv-size_Received, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la recv\n");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected\n" );
        break;
      }
      size_Received+=return_Value;
    }
account[strlen(account)]='\0';

recv(client,&option_size,sizeof(int),0);
  size_Received=0;
  size_to_recv=option_size;
    while(size_Received<size_to_recv)
    {
      return_Value=recv(client,password+size_Received,size_to_recv-size_Received, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la recv\n");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected\n" );
        break;
      }
      size_Received+=return_Value;
    }
password[strlen(password)]='\0';

  
    if(strcmp(surname,"")!=0&&strcmp(name,"")!=0&&strcmp(account,"")!=0&&strcmp(password,"d41d8cd98f00b204e9800998ecf8427e")!=0)
    {
          bool result=create_account(surname,name,account,password);
          send(client,&result,sizeof(bool),0);
    }
close(client);
}


void requestHandler(char *username,char*password)
{
  int option_size,argument1_size,argument2_size,size_Received,return_Value,size_to_recv;
  char option[10],argument1[20],argument2[20];
  do
  {
  recv(client,&option_size,sizeof(int),0);
  size_Received=0;
  size_to_recv=option_size;
    while(size_Received<size_to_recv)
    {
      return_Value=recv(client,option+size_Received,size_to_recv-size_Received, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la recv\n");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected\n" );
        break;
      }
      size_Received+=return_Value;
    }
          
    option[size_Received]='\0';
    if(strcmp(option,"logout")==0)
    {
      printf("Clientul %s s-a deconectat!\n\n",username);
      close(client);
    }

    if(strcmp(option,"sugestii")==0)
    {
      printf("Generare sugestii pentru clientul %s\n",username);
      send_sugestii();
      printf("\n");

    }
    if(strcmp(option,"search")==0)
    {
      send_search_results();
    }

    if(strcmp(option,"download")==0)
    {
      send_download();
    }
     
     if(strcmp(option,"update_log")==0)
    {
      update_log();
    }

  }while(strcmp(option,"logout")!=0);
    
}




bool initialize_database()
{
int rc = sqlite3_open("server.db", &db);
    if (rc != SQLITE_OK) 
    {
        
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }
    else printf("Database successful opened\n\n");
return 1;
}

bool verrify_account(char *username,char*password)
{
  int rc,step;
  char *sql="SELECT NUME_CONT,PAROLA,UTILIZATOR_ID FROM UTILIZATORI WHERE NUME_CONT = ? AND PAROLA = ?";
  rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
  if (rc == SQLITE_OK) 
  {
        sqlite3_bind_text(res, 1, username,strlen(username),0);
        sqlite3_bind_text(res, 2, password,strlen(password),0);
  }
  
  while((step = sqlite3_step(res))!=SQLITE_DONE)
    {
       if(step == SQLITE_ROW) 
        {    
          utilizator_id=(*sqlite3_column_text(res, 2))-'0';
           return 1;   
        }
    }
    sqlite3_finalize(res);
    //sqlite3_close(db);
return 0;
}






int main ()
{
  struct sockaddr_in server;	// structura folosita de server
  struct sockaddr_in from;	
  int sd;			//descriptorul de socket
  int actual_size,size_to_recv,return_value,length,size_Received,return_Value;	
  bool login_result;
  pid_t pID;
  while(initialize_database()==0);




  /* crearea unui socket */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[server]Eroare la socket().\n");
      return errno;
    }

  /* pregatirea structurilor de date */
  bzero (&server, sizeof (server));
  bzero (&from, sizeof (from));

  
  /* umplem structura folosita de server */
  /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;	
  /* acceptam orice adresa */
    server.sin_addr.s_addr = htonl (INADDR_ANY);
  /* utilizam un port utilizator */
    server.sin_port = htons (PORT);
  
  /* atasam socketul */
  if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("[server]Eroare la bind().\n");
      return errno;
    }
   int on=1;
    setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

  /* punem serverul sa asculte daca vin clienti sa se conecteze */
  if (listen (sd, 100) == -1)
    {
      perror ("[server]Eroare la listen().\n");
      return errno;
    }

  /* servim in mod iterativ clientii... */
  while (1)
    {
      length = sizeof (from);

      if(pID==0)printf ("[server]Asteptam la portul %d...\n",PORT);
      fflush (stdout);

      /* acceptam un client (stare blocanta pina la realizarea conexiunii) */
      client = accept (sd, (struct sockaddr *) &from, &length);

      /* eroare la acceptarea conexiunii de la un client */
      pID=fork();

      if (client < 0)
	{
	  perror ("[server]Eroare la accept().\n");
	  continue;
  }
  else if(pID==0) 
  {
    int login_option;
    recv(client,&login_option,sizeof(int),0);

    if(login_option==1)
    {
      /* s-a realizat conexiunea, se astepta mesajul */
      bzero (username, 21);
      bzero (password,33);
      printf ("[server]Asteptam numele de utilizator si parola...\n");
      fflush (stdout);
      
    
    recv(client,&size_to_recv,sizeof(int),0);
    size_Received=0;
    while(size_Received<size_to_recv)
    {
      return_Value=recv(client,username+size_Received,size_to_recv-size_Received, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la recv");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected" );
        break;
      }
      size_Received+=return_Value;
    }

    recv(client,&size_to_recv,sizeof(int),0);
    size_Received=0;
    while(size_Received<size_to_recv)
    {
      return_Value=recv(client,password+size_Received,size_to_recv-size_Received, 0);
      if(return_Value==-1)
      {
        perror("[Server]:Eroare la recv");
        break;
      }
      else if(return_Value== 0)
      {
        printf("[Server]:A client has been disconnected" );
        break;
      }
      size_Received+=return_Value;
    }

    printf("Username si parola in curs de verificare %s %s \n",username,password);
    login_result=verrify_account(username,password);
    printf("Rezultat login: %d\n",login_result);
    
    fflush(stdout);
    send(client,&login_result,sizeof(bool),0);
    if(login_result==1)
    {
    printf("\nInitializare requestHandler \n");
    requestHandler(username,password);
    }
    else close(client);
    }
  else
  {
    register_account();
    close(client);
  }
  }
    close(pID);
    }				/* while */
}				/* main */
