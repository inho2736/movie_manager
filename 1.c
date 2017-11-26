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

struct director{
  int serial_number;
  char * d_name;
  char s;
  int birth;
  struct d_title * director_title;
  struct director * next;
};
struct m_actor{
  char * actor;
  struct actor * link;
  struct m_actor * next;
};
typedef struct movie{
  char * serial_number;
  char * year;
  char * run_time;
  char *tag;
  char * title;
  char * genre;
  char * director;
  struct m_actor * movie_actor;
  struct movie * next;
} movie;

struct a_title{
  char * title;
  struct movie * link;
  struct a_title * next;
};
struct actor{
  int serial_number;
  char * actor;
  char s;
  int birth;
  struct a_title * actor_title;
  struct actor * next;
};

void input_log(movie *, FILE *);
void string_input(FILE *, char **);

int main(void){
  char ** a;
  int i = 0;
  movie *m_log = (movie *)malloc(sizeof(movie));
  FILE *movie_file;
  input_log(m_log, movie_file);


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

void input_log(movie *m_log, FILE *movie_file){
  movie_file = fopen("movie_log.txt", "r");
  char tmp;
  char *s_tmp;
  int size = 0;

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
    size = 0;

//run_time 입력

    string_input(movie_file, &(m_log -> run_time));

//actor은 어떻게 입력하징

  printf("%s\n", m_log -> run_time);
  printf("%s\n", m_log -> year);
  printf("%s\n", m_log -> director);
  printf("%s\n", m_log -> genre);
  printf("%s\n", m_log -> title);
  printf("%s\n", m_log -> serial_number);
  printf("%s", m_log -> tag);

}

void string_input(FILE *movie_file, char **subject){ //반복되는 문장 함수로 만들어보는중
  char tmp;
  char *s_tmp;
  int size;
  fscanf(movie_file, "%c", &tmp);
  while (tmp != ':'){
    size++;
    fscanf(movie_file, "%c", &tmp);
  }

    (*subject) = (char *)malloc(sizeof(char) * size + 1);
    fseek(movie_file, -(size + 1), SEEK_CUR);

    fscanf(movie_file, "%c", &tmp);
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
