#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
void flush(void);
void start(void);
void add(int *);

struct d_title{
  char * title;
  struct movie * link;
  struct d_title * next;
};

typedef struct director{
  char *tag;
  char * serial_number;
  char * d_name;
  char *s;
  char * birth;
  struct d_title * director_title;
  struct director * next;
} director;
struct m_actor{
  char * actor;
  struct actor * link;
  struct m_actor * next;
};


struct a_title{
  char * title;
  struct movie * link;
  struct a_title * next;
};
typedef struct actor{
  char *tag;
  char *serial_number;
  char * actor;
  char *s;
  char * birth;
  struct a_title * actor_title;
  struct actor * next;
} actor;
typedef struct movie{
  char * serial_number;
  char * year;
  char * run_time;
  char *tag;
  char * title;
  char * genre;
  char * director;
  struct m_actor movie_actor;
  struct movie * next;
} movie;

void input_m_log(movie *);
void input_a_log(actor *);
void input_d_log(director *);
//void input_m_actor(FILE *, movie *);
void string_input(FILE *, char **);

int main(void){
  char ** a;
  int i = 0;
  movie *m_log = (movie *)malloc(sizeof(movie));
  actor *a_log = (actor *)malloc(sizeof(actor));
  director *d_log = (director *)malloc(sizeof(director));
  input_m_log(m_log);
  input_a_log(a_log);
  input_d_log(d_log);



/*  a = (char **)malloc(sizeof(char *) * 5);
  for(i=0;i<5;++i)
  {
    *(a + i) = (char *)malloc(10);
    while(scanf("%s", *(a+i)) != 1) ;
    {
      free(*(a+i));
    }
  }
  */
  //add(&movie_serial);
  /*for(i=0;i<5;++i)
  {
    printf("%s", *(a+i));
  }*/
  return 0;
}

void input_m_log(movie *m_log){

  FILE *movie_file;
  movie_file = fopen("movie_log.txt", "r");
//tag입력
  string_input(movie_file, &(m_log -> tag));

//serial number 입력
  string_input(movie_file, &(m_log -> serial_number));

//title 입력
  string_input(movie_file, &(m_log -> title));

//genre 입력
  string_input(movie_file, &(m_log -> genre));

//director 입력
  string_input(movie_file, &(m_log -> director));

//year 입력
  string_input(movie_file, &(m_log -> year));

//run_time 입력
    string_input(movie_file, &(m_log -> run_time));

//actor은 어떻게 입력하징

  fclose(movie_file);
  printf("%s\n", m_log -> run_time);
  printf("%s\n", m_log -> year);
  printf("%s\n", m_log -> director);
  printf("%s\n", m_log -> genre);
  printf("%s\n", m_log -> title);
  printf("%s\n", m_log -> serial_number);
  printf("%s\n", m_log -> tag);


}
/*
void input_m_actor(FILE *movie_file, movie *m_log){
  char tmp;
  int size;
  (m_log -> movie_actor) = (struct m_actor *)malloc(sizeof(struct m_actor));

  fscanf(movie_file, "%c", &tmp);   //동적 메모리 할당을 위해 입력받는 string의 크기 알아보기
  while (tmp != ','){
    size++;
    fscanf(movie_file, "%c", &tmp);
  }

  m_log -> movie_actor -> actor = (char *)malloc(sizeof(char) * size + 1);
  fseek(movie_file, -(size + 1), SEEK_CUR);

  fscanf(movie_file, "%c", &tmp);
  for (int i = 0; tmp != ','; i++){
    *(m_log -> movie_actor -> actor + i) = tmp;
    fscanf(movie_file, "%c", &tmp);
  }

  printf("%s\n", m_log -> movie_actor -> actor);

}
*/
void input_d_log(director *d_log){
  FILE *d_file = fopen("director_log.txt", "r");


  //tag입력
  string_input(d_file, &(d_log -> tag));
  string_input(d_file, &(d_log -> serial_number));
  string_input(d_file, &(d_log -> d_name));
  string_input(d_file, &(d_log -> s));
  string_input(d_file, &(d_log -> birth));

  printf("%s\n", d_log -> tag);
  printf("%s\n", d_log -> serial_number);
  printf("%s\n", d_log -> d_name);
  printf("%s\n", d_log -> s);
  printf("%s\n", d_log -> birth);
}
void input_a_log(actor *a_log){
  FILE *a_file = fopen("actor_log.txt", "r");


  //tag입력
  string_input(a_file, &(a_log -> tag));
  string_input(a_file, &(a_log -> serial_number));
  string_input(a_file, &(a_log -> actor));
  string_input(a_file, &(a_log -> s));
  string_input(a_file, &(a_log -> birth));

  printf("%s\n", a_log -> tag);
  printf("%s\n", a_log -> serial_number);
  printf("%s\n", a_log -> actor);
  printf("%s\n", a_log -> s);
  printf("%s\n", a_log -> birth);

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


void start(void){
  printf(">>Welcome to My Movie <<\n");
  printf("File Loading...\n");
}
/*
void flush(void)
{
  while(getchar()!='\n');
}*/
/*
void add(int * movie_serial)
{

  FILE * movie_log;
  if ((movie_log = fopen("movie_log.txt", "w")) == NULL)
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
