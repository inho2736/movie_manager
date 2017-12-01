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
void input_a_log(actor *);
void input_d_log(director *);
//void input_m_actor(FILE *, movie *);
void string_input(FILE *, char **);
void link_input(FILE *, m_director *);
void actor_link_input(FILE *, m_actor *);
void title_link_input(FILE *, m_title *);

int main(void){
  FILE *movie_file;
  movie_file = fopen("movie_log.txt", "r");
  movie *m_log = (movie *)malloc(sizeof(movie));
  actor *a_log = (actor *)malloc(sizeof(actor));
  director *d_log = (director *)malloc(sizeof(director));
  input_m_log(movie_file, m_log);
  input_a_log(a_log);
  input_d_log(d_log);
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
  if (feof(movie_file) == 0)
    input_m_log(movie_file, m_log);



  printf("%s\n", m_log -> run_time);
  printf("%s\n", m_log -> year);
  printf("%s\n", m_log -> movie_director -> director);
  printf("%s\n", m_log -> genre);
  printf("%s\n", m_log -> title);
  printf("%s\n", m_log -> serial_number);
  printf("%s\n", m_log -> tag);
  printf("\n");
}

void input_d_log(director *d_log){
  FILE *d_file = fopen("director_log.txt", "r");


  //tag입력
  string_input(d_file, &(d_log -> tag));
  string_input(d_file, &(d_log -> serial_number));
  string_input(d_file, &(d_log -> d_name));
  string_input(d_file, &(d_log -> s));
  string_input(d_file, &(d_log -> birth));
  (d_log -> director_title) = (m_title *)malloc(sizeof(m_title));
  title_link_input(d_file, (d_log -> director_title));

  fclose(d_file);

  printf("%s\n", d_log -> tag);
  printf("%s\n", d_log -> serial_number);
  printf("%s\n", d_log -> d_name);
  printf("%s\n", d_log -> s);
  printf("%s\n", d_log -> birth);
  printf("\n");
}
void input_a_log(actor *a_log){
  FILE *a_file = fopen("actor_log.txt", "r");



  string_input(a_file, &(a_log -> tag));
  string_input(a_file, &(a_log -> serial_number));
  string_input(a_file, &(a_log -> actor));
  string_input(a_file, &(a_log -> s));
  string_input(a_file, &(a_log -> birth));
  (a_log -> actor_title) = (m_title *)malloc(sizeof(m_title*));
  title_link_input(a_file, (a_log -> actor_title));

  fclose(a_file);

  printf("%s\n", a_log -> tag);
  printf("%s\n", a_log -> serial_number);
  printf("%s\n", a_log -> actor);
  printf("%s\n", a_log -> s);
  printf("%s\n", a_log -> birth);
  printf("%s\n", a_log -> actor_title -> next -> title);
  printf("\n");

}

void string_input(FILE *movie_file, char **subject){
  char tmp;
  char *s_tmp;
  int size;

  fscanf(movie_file, "%c", &tmp);   //동적 메모리 할당을 위해 입력받는 string의 크기 알아보기
  while (tmp != ':'){
    size++;
    fscanf(movie_file, "%c", &tmp);
  }

    (*subject) = (char *)malloc(sizeof(char) * size + 1); //NULL까지 고려하여 동적 메모리 할당
    fseek(movie_file, -(size + 1), SEEK_CUR); //파일 위치 지시자를 읽기 시작했던 곳으로 돌림

    fscanf(movie_file, "%c", &tmp);         // tmp에 먼저 저장하여 :가 나오기 전까지 subject 스트링에 입력
    for (int i = 0; tmp != ':'; i++){
      *(*subject + i) = tmp;    //**(subject + i)와 *(*subject + i)의 차이점??
      fscanf(movie_file, "%c", &tmp);
    }

    size = 0;
}

void link_input(FILE *file, m_director *movie_director){
  char tmp;
  int size = 0;

  fscanf(file, "%c", &tmp);   //동적 메모리 할당을 위해 입력받는 string의 크기 알아보기
  while ((tmp != '\n') && (feof(file) == 0) && (tmp != ':')) {
    while ((tmp != ':') && (tmp != ',')){
      size++;
      fscanf(file, "%c", &tmp);
    }

      movie_director -> director = (char *)malloc(sizeof(char) * size + 1); //NULL까지 고려하여 동적 메모리 할당
      fseek(file, -(size + 1), SEEK_CUR); //파일 위치 지시자를 읽기 시작했던 곳으로 돌림

      fscanf(file, "%c", &tmp);         // tmp에 먼저 저장하여 :가 나오기 전까지 subject 스트링에 입력
      for (int i = 0; (tmp != ':') && (tmp != ','); i++){
        *(movie_director -> director + i) = tmp;    //**(subject + i)와 *(*subject + i)의 차이점??
        fscanf(file, "%c", &tmp);
      }
      size = 0;
  }
}

void actor_link_input(FILE *file, m_actor *movie_actor){
  char tmp;
  int size = 0;

  fscanf(file, "%c", &tmp);   //동적 메모리 할당을 위해 입력받는 string의 크기 알아보기
    while ((tmp != ':') && (tmp != ',') && (tmp != '\n') && (feof(file) == 0 )){
      size++;
      fscanf(file, "%c", &tmp);
    }

      movie_actor -> actor = (char *)malloc(sizeof(char) * size + 1); //NULL까지 고려하여 동적 메모리 할당

      if (feof(file) == 0)    // 파일의 끝일 경우 ',' 뒤의 스페이스가 문자열에 들어가므로 이를 방지
        fseek(file, -(size + 1), SEEK_CUR);
      else
        fseek(file, -size, SEEK_CUR);

      fscanf(file, "%c", &tmp);         // tmp에 먼저 저장하여 :가 나오기 전까지 subject 스트링에 입력
      for (int i = 0; (tmp != ':') && (tmp != ',') && (tmp != '\n') && (feof(file) == 0); i++){
        *(movie_actor -> actor + i) = tmp;
        fscanf(file, "%c", &tmp);
      }
      printf("%s\n", (movie_actor -> actor));
      size = 0;

  if (tmp == ','){
    fseek(file, 1, SEEK_CUR);
    (movie_actor -> next) = (m_actor *)malloc(sizeof(m_actor)); //
    movie_actor = movie_actor -> next;
    actor_link_input(file, movie_actor);
  }
}

void title_link_input(FILE *file, m_title *director_title){
  char tmp;
  int size = 0;

  fscanf(file, "%c", &tmp);   //동적 메모리 할당을 위해 입력받는 string의 크기 알아보기
    while ((tmp != ':') && (tmp != ',') && (tmp != '\n') && (feof(file) == 0 )){
      size++;
      fscanf(file, "%c", &tmp);
    }

      director_title -> title = (char *)malloc(sizeof(char) * size + 1); //NULL까지 고려하여 동적 메모리 할당

      if (feof(file) == 0)    // 파일의 끝일 경우 ',' 뒤의 스페이스가 문자열에 들어가므로 이를 방지
        fseek(file, -(size + 1), SEEK_CUR);
      else
        fseek(file, -size, SEEK_CUR);

      fscanf(file, "%c", &tmp);         // tmp에 먼저 저장하여 :가 나오기 전까지 subject 스트링에 입력
      for (int i = 0; (tmp != ':') && (tmp != ',') && (tmp != '\n') && (feof(file) == 0); i++){
        *(director_title -> title + i) = tmp;
        fscanf(file, "%c", &tmp);
      }
      printf("%s\n", (director_title -> title));
      size = 0;

  if (tmp == ','){
    fseek(file, 1, SEEK_CUR);
    (director_title -> next) = (m_title *)malloc(sizeof(m_title)); // 무조건 메모리를 주고 접근해야함
    director_title = director_title -> next;
    title_link_input(file, director_title);
  }
}


void start(void){
  printf(">>Welcome to My Movie <<\n");
  printf("File Loading...\n");
}
/*
void flush(void)
{
  while(getchar()!='\n');
}

void add(int * movie_serial)
{

  FILE * movie_log;
  if ((movie_log = fopen("movie_log.txt", "a")) == NULL)
  {
    printf("오류 : 파일을 열 수 없습니다. \n");
  }
  else
  {
    struct movie tmp;
    tmp.title = (char *)malloc(sizeof(char)*20);
    tmp.genre = (char *)malloc(sizeof(char)*10);
    tmp.director = (char *)malloc(sizeof(char)*20);
    //tmp.movie_actor = (struct m_actor *)malloc(sizeof(struct m_actor)*20);
    fprintf(movie_log, "add:");
    printf("title > ");
    scanf("%[^\n]", tmp.title);
	  flush();
	  printf("genre > ");
	  scanf("%[^\n]", tmp.genre);
	  flush();
	  printf("director > ");
	  scanf("%[^\n]", tmp.director);
	  flush();
	  printf("year > ");
	  scanf("%d", &(tmp.year));
    flush();
	  printf("run time > ");
	  scanf("%d", &(tmp.run_time));
    fprintf(movie_log, "%s:%s:%s:%d:%d", tmp.title, tmp.genre, tmp.director, tmp.year, tmp.run_time);
	fclose(movie_log);
  }



}
*/
