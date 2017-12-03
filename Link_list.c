#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
void flush(void);
void start(void);
void add(int *);

typedef struct m_title{
  char * title;
  struct movie * link;
  struct m_title * next;
} m_title;
/*
typedef struct m_title{     위 구조체와 중복되는 구조체. 합침.
  char * title;
  struct movie * link;
  struct m_title * next;
} m_title;
*/

typedef struct director{
  char *tag;
  char * serial_number;
  char * d_name;
  char *s;
  char * birth;
  struct m_title * director_title;
  struct director * next;
} director;
typedef struct m_actor{
  char * actor;
  struct actor * link;
  struct m_actor * next;
} m_actor;

typedef struct m_director{
  char * director;
  director *link;
  struct m_director *next;
} m_director;



typedef struct actor{
  char *tag;
  char *serial_number;
  char * actor;
  char *s;
  char * birth;
  struct m_title * actor_title;
  struct actor * next;
} actor;
typedef struct movie{
  char * serial_number;
  char * year;
  char * run_time;
  char *tag;
  char * title;
  char * genre;
  struct m_director * movie_director;
  struct m_actor *movie_actor;
  struct movie * next;
} movie;

void input_m_log(FILE *, movie *);
void input_a_log(FILE *, actor *);
void input_d_log(FILE *, director *);
//void input_m_actor(FILE *, movie *);
void string_input(FILE *, char **);
void link_input(FILE *, m_director *);
void actor_link_input(FILE *, m_actor *);
void title_link_input(FILE *, m_title *);

int main(void){
  FILE *movie_file;
  FILE *a_file;
  FILE *d_file;
  movie_file = fopen("movie_log.txt", "r");
  a_file = fopen("actor_log.txt", "r");
  d_file = fopen("director_log.txt", "r");

  movie *m_log = (movie *)malloc(sizeof(movie));
  actor *a_log = (actor *)malloc(sizeof(actor));
  director *d_log = (director *)malloc(sizeof(director));
  fseek(movie_file, 0, SEEK_SET);
  input_m_log(movie_file, m_log);
  fclose(movie_file);


  fseek(a_file, 0, SEEK_SET);
  input_a_log(a_file, a_log);
  fseek(d_file, 0, SEEK_SET);
  input_d_log(d_file, d_log);


  return 0;
}

void input_m_log(FILE *movie_file, movie *m_log){


//tag입력
  string_input(movie_file, &(m_log -> tag));

//serial number 입력
  string_input(movie_file, &(m_log -> serial_number));
//title 입력
  string_input(movie_file, &(m_log -> title));

//genre 입력
  string_input(movie_file, &(m_log -> genre));
//director 입력

  (m_log -> movie_director) = (m_director *)malloc(sizeof(m_director));
  link_input(movie_file, (m_log -> movie_director));
//year 입력

  string_input(movie_file, &(m_log -> year));
//run_time 입력
    string_input(movie_file, &(m_log -> run_time));
//actor 입력

(m_log -> movie_actor) = (m_actor *)malloc(sizeof(m_actor));
  actor_link_input(movie_file, (m_log -> movie_actor));

  if (feof(movie_file) == 0){
    (m_log -> next) = (movie *)malloc(sizeof(movie));
    input_m_log(movie_file, m_log -> next);
  }

printf("출력시작 : -------------------------------\n");


  printf("%s\n", m_log -> run_time);
  printf("%s\n", m_log -> year);
  printf("%s\n", m_log -> movie_director -> director);
  printf("%s\n", m_log -> genre);
  printf("%s\n", m_log -> title);
  printf("%s\n", m_log -> serial_number);
  printf("%s\n", m_log -> tag);


}

void input_d_log(FILE *d_file, director *d_log){

  string_input(d_file, &(d_log -> tag));
  string_input(d_file, &(d_log -> serial_number));
  string_input(d_file, &(d_log -> d_name));
  string_input(d_file, &(d_log -> s));
  string_input(d_file, &(d_log -> birth));
  (d_log ->director_title) = (m_title *)malloc(sizeof(m_title));
  title_link_input(d_file, (d_log -> director_title));

  if (feof(d_file) == 0){
    (d_log -> next) = (director *)malloc(sizeof(director));
    input_d_log(d_file, d_log -> next);
  }


  printf("출력시작 : -------------------------------\n");
  printf("%s\n", d_log -> tag);
  printf("%s\n", d_log -> serial_number);
  printf("%s\n", d_log -> d_name);
  printf("%s\n", d_log -> s);
  printf("%s\n", d_log -> birth);
  printf("================");
  printf("%s\n", d_log -> director_title -> next -> title);
  printf("================");

}
void input_a_log(FILE *a_file, actor *a_log){
  string_input(a_file, &(a_log -> tag));
  string_input(a_file, &(a_log -> serial_number));
  string_input(a_file, &(a_log -> actor));
  string_input(a_file, &(a_log -> s));
  string_input(a_file, &(a_log -> birth));
  (a_log -> actor_title) = (m_title *)malloc(sizeof(m_title));
  title_link_input(a_file, (a_log -> actor_title));

  if (feof(a_file) == 0){
    (a_log -> next) = (actor *)malloc(sizeof(actor));
    input_a_log(a_file, a_log -> next);
  }


printf("출력시작 : -------------------------------\n");
  printf("%s\n", a_log -> tag);
  printf("%s\n", a_log -> serial_number);
  printf("%s\n", a_log -> actor);
  printf("%s\n", a_log -> s);
  printf("%s\n", a_log -> birth);
  printf("================");
  printf("%s\n", a_log -> actor_title -> next -> title);
  printf("================");
}
