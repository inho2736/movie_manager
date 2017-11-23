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
struct movie{
  int serial_number;
  char * title;
  char * genre;
  char * director;
  int year;
  int run_time;
  struct m_actor * movie_actor;
  struct movie * next;
};

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

int main(void){
  char ** a;
  int i = 0;
  int movie_serial=1;
  int actor_serial;
  int director_serial;
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
  add(&movie_serial);
  /*for(i=0;i<5;++i)
  {
    printf("%s", *(a+i));
  }*/
  return 0;
}

void start(void){
  printf(">>Welcome to My Movie <<\n");
  printf("File Loading...\n");
}
void flush(void)
{
  while(getchar()!='\n');
}

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
