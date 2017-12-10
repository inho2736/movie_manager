#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
int add_m_number = 0;
int add_d_number = 0;
int add_a_number = 0;
void quit(int);
void flush(void);
void start(void);
void changes(char *);
typedef struct d_title{
  char * title;
  struct movie * link;
  struct d_title * next;
}d_title;
typedef struct director{
  char * serial_number;
  char * d_name;
  char * s;
  char * birth;
  struct d_title * director_title;
  struct director * next;
}director;
typedef struct m_actor{
  char * actor;
  struct actor * link;
  struct m_actor * next;
}m_actor;
typedef struct m_director{
  char * director;
  director *link;
}m_director;
typedef struct movie{
  char * serial_number;
  char * title;
  char * genre;
  struct m_director * movie_director;
  char * year;
  char * run_time;
  struct m_actor * movie_actor;
  struct movie * next;
}movie;
typedef struct a_title{
  char * title;
  struct movie * link;
  struct a_title * next;
}a_title;
typedef struct actor{
  char * serial_number;
  char * a_name;
  char * s;
  char * birth;
  struct a_title * actor_title;
  struct actor * next;
} actor;

void deletem(movie *, char *);
void command(movie *, actor *, director *);
void addd(director *);
void adda(actor *);
void addm(movie *, director *, actor *);
void input_m_log(movie **, FILE *);
void input_log(movie **, actor **, director **);
void string_input(FILE *, char **);
void add_mlog(movie **, char*, char*, char*, char*, char*, char*, char*);
void m_log_print(movie *);
void delete_mlog(movie * , char *);
void update_mlog(movie ** , char *,char *,char *,char *,char *,char *,char *);
void input_d_log(director **, FILE *);
void add_dlog(director **, char *, char *, char *, char *, char *);
void delete_dlog(director *, char *);
void input_a_log(actor **, FILE *);
void add_alog(actor **, char *, char *, char *, char *, char *);
void delete_alog(actor *, char *);
void update_dlog(director **, char *,char *,char *,char *, char *);
void update_alog(actor ** , char *, char *, char *,char *, char * );
void link_struct(movie *, director *, actor *);
void link_md(m_director *, director *);
void link_ma(m_actor *, actor *);
void link_dm(d_title *, movie *);
void link_am(a_title *, movie *);
int same_m_check(movie *, char *);
void print_for_same(movie *, m_actor*, char *);
int same_d_check(director *a_log, char *title);
int same_a_check(actor *a_log, char *title);
void memory_to_listm(movie *);
void deletea(actor *, char * );
void deleted(director *, char *);
void print_m(movie *, char *);
void print_d(director *, char *);
void print_a(actor *, char*);
void inverse_ch(char *);
void updatem(movie *, char *);
void updated(director *, char *);
int cmp_word(const void *, const void *);
void updatea(actor *, char *);
void sort_m(movie *);
void sort_d(director *);
void sort_a(actor *);
void search(movie *, director *, actor *);
int _check(char *, char *);
int check_(char *, char *);
int check(char * , char * );
void con_printm(int , movie *, m_actor *);
void con_printd(int , director *, d_title *);
void con_printa(int print_it, actor *, a_title *);
int q_check(char * );
void savem(movie *);
void saved(director *);
char* timefilem(void);
char* timefiled(void);
void end(movie *, director *, actor *);
int main(void)
{
  movie *m_log = (movie *)malloc(sizeof(movie));
  m_log = NULL;
  actor *a_log = (actor *)malloc(sizeof(actor));
  a_log = NULL;
  director *d_log = (director *)malloc(sizeof(director));
  d_log = NULL;
  signal(SIGINT, (void*)quit);
  input_log(&m_log, &a_log, &d_log);
  link_struct(m_log, d_log, a_log);

  start();
  while(1){
  printf("(movie) ");
  command(m_log, a_log, d_log);
  link_struct(m_log, d_log, a_log);//안되면 앞에 모든 구조체 널로 하는 함수 넣기
  //memory_to_listm(m_log);
}
  return 0;
}


void input_log(movie **m_log, actor **a_log, director **d_log){
  FILE *m_file = fopen("movie_log.txt", "r");
  FILE *a_file = fopen("actor_log.txt", "r");
  FILE *d_file = fopen("director_log.txt", "r");
  input_m_log(m_log, m_file);
  input_d_log(d_log, d_file);
  input_a_log(a_log, a_file);
}

void input_m_log(movie **m_log, FILE *m_file) {
  char *tag;
  char *serial_number;
  char *title;
  char *genre;
  char *movie_director;
  char *year;
  char *run_time;
  char *movie_actor;
  char tmp;
  static int count = 0;

  while (feof(m_file) == 0){

    if (count == 0)
      fseek(m_file, 0, SEEK_SET);
    string_input(m_file, &tag);

    //if (count == 0)
      //tag = tag+3;
    string_input(m_file, &serial_number);
    string_input(m_file, &title);
    string_input(m_file, &genre);
    string_input(m_file, &movie_director);
    string_input(m_file, &year);
    string_input(m_file, &run_time);
    string_input(m_file, &movie_actor);
    if (strcmp(tag, "add") == 0){
      add_mlog(m_log, serial_number, title, genre, movie_director, year, run_time, movie_actor);
      add_m_number ++;
    }
    else if (strcmp(tag, "delete") == 0){
      delete_mlog((*m_log), serial_number);
    }
    else if (strcmp(tag, "update") == 0){
      update_mlog(m_log, serial_number, title, genre, movie_director, year, run_time, movie_actor);
    }
    count++;

  }
}
void input_d_log(director **d_log, FILE *d_file) {
  char *tag;
  char *serial_number;
  char *d_name;
  char *s;
  char *birth;
  char *director_title;
  char tmp;
  static int count = 0;

  while (feof(d_file) == 0){

    if (count == 0)
      fseek(d_file, 0, SEEK_SET);

    string_input(d_file, &tag);

    string_input(d_file, &serial_number);
    string_input(d_file, &d_name);
    string_input(d_file, &s);
    string_input(d_file, &birth);
    string_input(d_file, &director_title);
    if (strcmp(tag, "add") == 0){
      printf("에드직전");
      add_dlog(d_log, serial_number, d_name, s, birth, director_title);
      add_d_number ++;
    }

    else if (strcmp(tag, "delete") == 0){
      printf("딜리트 직전");
      delete_dlog((*d_log), serial_number);
    }
    else if (strcmp(tag, "update") == 0){
      printf("업데이트 직전");
      update_dlog(d_log, serial_number, d_name, s, birth, director_title);
    }
    count++;

  }
}
void input_a_log(actor **a_log, FILE *a_file) {
  char *tag;
  char *serial_number;
  char *actor;
  char *s;
  char *birth;
  char *actor_title;
  static int count = 0;

  while (feof(a_file) == 0){

    if (count == 0)
      fseek(a_file, 0, SEEK_SET);
    string_input(a_file, &tag);

    string_input(a_file, &serial_number);
    string_input(a_file, &actor);
    string_input(a_file, &s);
    string_input(a_file, &birth);
    string_input(a_file, &actor_title);
    if (strcmp(tag, "add") == 0){
      add_alog(a_log, serial_number, actor, s, birth, actor_title);
      add_a_number ++;
    }
    else if (strcmp(tag, "delete") == 0){
      delete_alog((*a_log), serial_number);
    }

    else if (strcmp(tag, "update") == 0){
      update_alog(a_log, serial_number, actor, s, birth, actor_title);
    }
    count++;

  }
}
void add_dlog(director ** d_log, char *serial_number, char *d_name, char *s, char *birth, char *whole_string){
  director ** tmp_d_log;
  char * token = (char*)malloc(sizeof(char)*2);
  char * string_cut;
  struct d_title * move;
  struct d_title * d_t_tmp;
  struct d_title * space;
  *(token + 0) = ',';
  *(token + 1) = '\n';

  if (*d_log == NULL)// tmp_m_log이 마지막 구조체를 가리키게함.
  {
    (*d_log) = (director *)malloc(sizeof(director)*1);
    tmp_d_log = d_log;
  }
  else
    {
      tmp_d_log = &((*d_log) -> next);
      while(1)
      {
        if((*tmp_d_log)== NULL)
        break;
        (tmp_d_log) = &((*tmp_d_log) -> next);
      }
      (*tmp_d_log)  = (director*)malloc(sizeof(director));

    }

  (*tmp_d_log) -> director_title= (d_title *)malloc(sizeof(d_title)*1);
  (*tmp_d_log) -> serial_number = serial_number;
  (*tmp_d_log) -> d_name = d_name;
  (*tmp_d_log) -> s = s;
  (*tmp_d_log) -> birth = birth; // 링크연결
  (*tmp_d_log) -> next = NULL;

  (*tmp_d_log) -> director_title -> title = strtok(whole_string, token);// whole_string은 배우이름들 통째로
  (*tmp_d_log) -> director_title -> link = NULL; // 링크연결
  (*tmp_d_log) -> director_title -> next = (struct d_title *)malloc(sizeof(struct d_title));
  move = (*tmp_d_log) -> director_title -> next;
  space = (*tmp_d_log)-> director_title;
  while ((string_cut = strtok(NULL, token))!=NULL)
  {
    move -> title = string_cut;
    move -> link = NULL;// 링크연결
    move -> next =  (struct d_title *)malloc(sizeof(struct d_title));
    move = move -> next;
    move -> next = NULL;
  }
  while (space->next != NULL)
   {
      if (*(space->title) == ' ')
         space->title = (space->title) + 1;
      space = space->next;
   }

}
void add_alog(actor ** a_log, char *serial_number, char *a_name, char *s, char *birth, char *whole_string){
  actor ** tmp_a_log;
  char * token = (char*)malloc(sizeof(char)*2);
  char * string_cut;
  struct a_title * move;
  struct a_title * a_t_tmp;
  struct a_title * space;
  *(token + 0) = ',';
  *(token + 1) = '\n';

  if (*a_log == NULL)
  {
    (*a_log) = (actor *)malloc(sizeof(actor)*1);
    tmp_a_log = a_log;
  }
  else
    {
      tmp_a_log = &((*a_log) -> next);
      while(1)
      {
        if((*tmp_a_log)== NULL)
        break;
        (tmp_a_log) = &((*tmp_a_log) -> next);
      }
      (*tmp_a_log)  = (actor *)malloc(sizeof(actor));

    }

  (*tmp_a_log) -> actor_title= (a_title *)malloc(sizeof(a_title)*1);
  (*tmp_a_log) -> serial_number = serial_number;
  (*tmp_a_log) -> a_name = a_name;
  (*tmp_a_log) -> s = s;
  (*tmp_a_log) -> birth = birth;
  (*tmp_a_log) -> next = NULL;

  (*tmp_a_log) -> actor_title -> title = strtok(whole_string, token);// whole_string은 배우이름들 통째로
  (*tmp_a_log) -> actor_title -> link = NULL; // 링크연결
  (*tmp_a_log) -> actor_title -> next = (struct a_title *)malloc(sizeof(struct a_title));
  move = (*tmp_a_log) -> actor_title -> next;
  space = (*tmp_a_log)-> actor_title;
  while ((string_cut = strtok(NULL, token))!=NULL)
  {
    move -> title = string_cut;
    move -> link = NULL;// 링크연결
    move -> next =  (struct a_title *)malloc(sizeof(struct a_title));
    move = move -> next;
    move -> next = NULL;
  }
  while (space->next != NULL)
   {
      if (*(space->title) == ' ')
         space->title = (space->title) + 1;
      space = space->next;
   }

}
void m_log_print(movie *m_log){
  m_actor *a_list = m_log -> movie_actor;
  printf("%s\n", m_log -> serial_number);
  printf("%s\n", m_log -> title);
  printf("%s\n", m_log -> genre);
  printf("%s\n", m_log -> movie_director -> director);
  printf("%s\n", m_log -> year);
  printf("%s\n", m_log -> run_time);

  while(a_list != NULL){
    printf("%s\n", a_list -> actor);
    a_list = a_list -> next;
  }

}
void update_mlog(movie ** m_log, char *serial_number,char *title,char *genre,char *movie_director,char *year,char *run_time,char * whole_string)
{

  movie ** tmp;
  tmp = m_log;

  char * token = (char*)malloc(sizeof(char)*2);
  char * string_cut;
  struct m_actor * move;
  struct m_actor * m_a_tmp;
  struct m_actor * space;
  *(token + 0) = ',';
  *(token + 1) = '\n';

  if (strcmp(((*tmp) -> serial_number), serial_number) == 0) // 첫번째일때
  {
    if(strcmp(title,"=") != 0)
    {
      (*m_log) ->title = title;
    }
    if(strcmp(genre,"=") != 0)
    {
      (*m_log) ->genre = genre;
    }
    if(strcmp(movie_director,"=") != 0)
    {
      (*m_log) ->movie_director -> director  = movie_director;
    }
    if(strcmp(year,"=") != 0)
    {
      (*m_log) ->year  = year;
    }
    if(strcmp(run_time,"=") != 0)
    {
      (*m_log) ->run_time  = run_time;
    }
    if(strcmp(whole_string,"=") != 0)
    {
      (*m_log) ->movie_actor = NULL;
      (*m_log) ->movie_actor = (m_actor *)malloc(sizeof(m_actor));
      (*m_log) ->movie_actor -> actor  = strtok(whole_string, token);
      (*m_log) ->movie_actor -> link = NULL;//링크추가
      (*m_log) ->movie_actor -> next = (m_actor *)malloc(sizeof( m_actor));

      move = (*m_log) -> movie_actor -> next;
      space = (*m_log)-> movie_actor;
      while ((string_cut = strtok(NULL, token))!=NULL)
      {
        move -> actor = string_cut;
        move -> link = NULL;// 링크연결
        move -> next =  (struct m_actor *)malloc(sizeof(struct m_actor));
        move = move -> next;
        move -> next = NULL;
      }
      while (space->next != NULL)
       {
          if (*(space->actor) == ' ')
             space->actor = (space->actor) + 1;
          space = space->next;
       }
    }

    return;
  }
  while(1)
  {
    if (strcmp(((*tmp) -> next -> serial_number), serial_number) == 0)
    {
      if(strcmp(title,"=") != 0)
      {
        (*tmp) -> next ->title = title;
      }
      if(strcmp(genre,"=") != 0)
      {
        (*tmp) ->next ->genre = genre;
      }
      if(strcmp(movie_director,"=") != 0)
      {
        (*tmp) ->next ->movie_director -> director  = movie_director;
      }
      if(strcmp(year,"=") != 0)
      {
        (*tmp) ->next ->year  = year;
      }
      if(strcmp(run_time,"=") != 0)
      {
        (*tmp) ->next ->run_time  = run_time;
      }
      if(strcmp(whole_string,"=") != 0)
      {
        (*tmp) ->next ->movie_actor = NULL;
        (*tmp) ->next ->movie_actor = (m_actor *)malloc(sizeof(m_actor));
        (*tmp) ->next ->movie_actor -> actor  = strtok(whole_string, token);
        (*tmp) ->next ->movie_actor -> link = NULL;//링크추가
        (*tmp) ->next ->movie_actor -> next = (m_actor *)malloc(sizeof( m_actor));

        move = (*tmp) -> next ->movie_actor -> next;
        space = (*tmp)-> next ->movie_actor;
        while ((string_cut = strtok(NULL, token))!=NULL)
        {
          move -> actor = string_cut;
          move -> link = NULL;// 링크연결
          move -> next =  (struct m_actor *)malloc(sizeof(struct m_actor));
          move = move -> next;
          move -> next = NULL;
        }
        while (space->next != NULL)
         {
            if (*(space->actor) == ' ')
               space->actor = (space->actor) + 1;
            space = space->next;
         }
       }// actor

      return;
     }
    (*tmp) = (*tmp) -> next;
  }//while


}//함수
void update_dlog(director ** d_log, char *serial_number,char *d_name,char *s,char *birth, char * whole_string)
{

  director ** tmp;
  tmp = d_log;

  char * token = (char*)malloc(sizeof(char)*2);
  char * string_cut;
  struct d_title * move;
  struct d_title * d_t_tmp;
  struct d_title * space;
  *(token + 0) = ',';
  *(token + 1) = '\n';

  if (strcmp(((*tmp) -> serial_number), serial_number) == 0) // 첫번째일때
  {
    if(strcmp(d_name,"=") != 0)
    {
      (*d_log) -> d_name = d_name;
    }
    if(strcmp(s,"=") != 0)
    {
      (*d_log) -> s = s;
    }
    if(strcmp(birth,"=") != 0)
    {
      (*d_log) -> birth  = birth;
    }
    if(strcmp(whole_string,"=") != 0)
    {
      (*d_log) ->director_title = NULL;
      (*d_log) ->director_title = (d_title *)malloc(sizeof(d_title));
      (*d_log) ->director_title -> title  = strtok(whole_string, token);
      (*d_log) ->director_title -> link = NULL;//링크추가
      (*d_log) ->director_title -> next = (d_title *)malloc(sizeof( d_title));

      move = (*d_log) -> director_title -> next;
      space = (*d_log)-> director_title;
      while ((string_cut = strtok(NULL, token))!=NULL)
      {
        move -> title = string_cut;
        move -> link = NULL;// 링크연결
        move -> next =  (struct d_title *)malloc(sizeof(struct d_title));
        move = move -> next;
        move -> next = NULL;
      }
      while (space->next != NULL)
       {
          if (*(space->title) == ' ')
             space->title = (space->title) + 1;
          space = space->next;
       }
    }

    return;
  }
  while(1)
  {
    if (strcmp(((*tmp) -> next -> serial_number), serial_number) == 0)
    {
      if(strcmp(d_name,"=") != 0)
      {
        (*tmp) -> next ->d_name = d_name;
      }
      if(strcmp(s,"=") != 0)
      {
        (*tmp) ->next ->s = s;
      }
      if(strcmp(birth,"=") != 0)
      {
        (*tmp) ->next ->birth  = birth;
      }
      if(strcmp(whole_string,"=") != 0)
      {
        (*tmp) ->next ->director_title = NULL;
        (*tmp) ->next ->director_title = (d_title *)malloc(sizeof(d_title));
        (*tmp) ->next ->director_title -> title  = strtok(whole_string, token);
        (*tmp) ->next ->director_title -> link = NULL;//링크추가
        (*tmp) ->next ->director_title -> next = (d_title *)malloc(sizeof( d_title));

        move = (*tmp) -> next ->director_title -> next;
        space = (*tmp)-> next ->director_title;
        while ((string_cut = strtok(NULL, token))!=NULL)
        {
          move -> title = string_cut;
          move -> link = NULL;// 링크연결
          move -> next =  (struct d_title *)malloc(sizeof(struct d_title));
          move = move -> next;
          move -> next = NULL;
        }
        while (space->next != NULL)
         {
            if (*(space->title) == ' ')
               space->title = (space->title) + 1;
            space = space->next;
         }
       }// actor

      return;
     }
    (*tmp) = (*tmp) -> next;
  }//while


}//함수
void update_alog(actor ** a_log, char *serial_number,char *a_name,char *s,char *birth, char * whole_string)
{

  actor ** tmp;
  tmp = a_log;

  char * token = (char*)malloc(sizeof(char)*2);
  char * string_cut;
  struct a_title * move;
  struct a_title * a_t_tmp;
  struct a_title * space;
  *(token + 0) = ',';
  *(token + 1) = '\n';

  if (strcmp(((*tmp) -> serial_number), serial_number) == 0) // 첫번째일때
  {
    if(strcmp(a_name,"=") != 0)
    {
      (*a_log) -> a_name = a_name;
    }
    if(strcmp(s,"=") != 0)
    {
      (*a_log) -> s = s;
    }
    if(strcmp(birth,"=") != 0)
    {
      (*a_log) -> birth  = birth;
    }
    if(strcmp(whole_string,"=") != 0)
    {
      (*a_log) ->actor_title = NULL;
      (*a_log) ->actor_title= (a_title *)malloc(sizeof(a_title));
      (*a_log) ->actor_title -> title  = strtok(whole_string, token);
      (*a_log) ->actor_title -> link = NULL;//링크추가
      (*a_log) ->actor_title -> next = (a_title *)malloc(sizeof( a_title));

      move = (*a_log) -> actor_title -> next;
      space = (*a_log)-> actor_title;
      while ((string_cut = strtok(NULL, token))!=NULL)
      {
        move -> title = string_cut;
        move -> link = NULL;// 링크연결
        move -> next =  (struct a_title *)malloc(sizeof(struct a_title));
        move = move -> next;
        move -> next = NULL;
      }
      while (space->next != NULL)
       {
          if (*(space->title) == ' ')
             space->title = (space->title) + 1;
          space = space->next;
       }
    }

    return;
  }
  while(1)
  {
    if (strcmp(((*tmp) -> next -> serial_number), serial_number) == 0)
    {
      if(strcmp(a_name,"=") != 0)
      {
        (*tmp) -> next ->a_name = a_name;
      }
      if(strcmp(s,"=") != 0)
      {
        (*tmp) ->next ->s = s;
      }
      if(strcmp(birth,"=") != 0)
      {
        (*tmp) ->next ->birth  = birth;
      }
      if(strcmp(whole_string,"=") != 0)
      {
        (*tmp) ->next ->actor_title = NULL;
        (*tmp) ->next ->actor_title = (a_title *)malloc(sizeof(a_title));
        (*tmp) ->next ->actor_title -> title  = strtok(whole_string, token);
        (*tmp) ->next ->actor_title -> link = NULL;//링크추가
        (*tmp) ->next ->actor_title -> next = (a_title *)malloc(sizeof( a_title));

        move = (*tmp) -> next ->actor_title -> next;
        space = (*tmp)-> next ->actor_title;
        while ((string_cut = strtok(NULL, token))!=NULL)
        {
          move -> title = string_cut;
          move -> link = NULL;// 링크연결
          move -> next =  (struct a_title *)malloc(sizeof(struct a_title));
          move = move -> next;
          move -> next = NULL;
        }
        while (space->next != NULL)
         {
            if (*(space->title) == ' ')
               space->title = (space->title) + 1;
            space = space->next;
         }
       }// actor

      return;
     }
    (*tmp) = (*tmp) -> next;
  }//while


}//함수
void string_input(FILE *movie_file, char **subject){
  char tmp;
  int size = 0;

  fscanf(movie_file, "%c", &tmp); //동적 메모리 할당을 위해 입력받는 string의 크기 알아보기
  if (tmp == '\n')                        //첫번째 줄에서 두번째 줄 넘어갈 때 \n이 tag에 들어가는 것 방지
    fscanf(movie_file, "%c\n", &tmp);
  while ((tmp != '\r') && (tmp != ':') && (tmp != '\n') && feof(movie_file) == 0) {
    size++;
    fscanf(movie_file, "%c", &tmp);
  }


    (*subject) = (char *)malloc(sizeof(char) * size + 1); //NULL까지 고려하여 동적 메모리 할당
    fseek(movie_file, -(size + 1), SEEK_CUR); //파일 위치 지시자를 읽기 시작했던 곳으로 돌림

    fscanf(movie_file, "%c", &tmp);         // tmp에 먼저 저장하여 :가 나오기 전까지 subject 스트링에 입력
    if (tmp == '\n')                        //첫번째 줄에서 두번째 줄 넘어갈 때 \n이 tag에 들어가는 것 방지
      fscanf(movie_file, "%c", &tmp);
    if (tmp == ':')
      fscanf(movie_file, "%c", &tmp);

    for (int i = 0; (tmp != '\r') &&(tmp != ':') && (tmp != '\n') && feof(movie_file) == 0 ; i++){
      *(*subject + i) = tmp;
      fscanf(movie_file, "%c", &tmp);
    }
    size = 0;
}
void start(void)
{
  printf(">>Welcome to My Movie <<\n");
  printf("File Loading...\n");
}
void flush(void)
{
  while(getchar()!='\n');
}
void command(movie *m_log, actor *a_log, director *d_log)
{
  char *order=(char *)malloc(100);
	char *minopt=(char*)malloc(100);
  char *delete_num=(char*)malloc(50);
  char *update_s = (char*)malloc(50);
  char *print_num = (char*)calloc(10, sizeof(char));
	char space,optmda;
  char *filename = (char*)calloc(30, sizeof(char));
  char *s_option = (char*)calloc(5, sizeof(char));
  char *dump = (char*)calloc(5, sizeof(char));
	scanf("%s",order);
	space=getchar();
	if((strcmp(order,"search")!=0)&&(strcmp(order,"end")!=0)) {//search와 order를 제외한 모든 명령어는 m|d|a하나를 받는 부분
		scanf("%c",&optmda);
	}

	if(strcmp(order,"add")==0){//add명령어를 받으면 m|d|a중 골라서 함수 호출
		if(optmda=='m'){
				addm(m_log, d_log, a_log);
		}
		else if(optmda=='d'){
			addd(d_log);
		}
		else if(optmda=='a'){
			adda(a_log);
		}
	}
	else if(strcmp(order,"update")==0){//update명령어를 받으면 m|d|a중 골라서 함수호출
    getchar();
    scanf("%[^\n]",update_s);
    //if (('0'<(*(update_1+0))) && ((*(update_1+0)) < '9'))

    if(optmda=='m'){
				updatem(m_log, update_s);
		}
		else if(optmda=='d'){
			updated(d_log, update_s);
		}
		else if(optmda=='a'){
			updatea(a_log, update_s);
		}
	}
	else if(strcmp(order,"print")==0){//print명령어를 받으면 m|d|a를 골라서 함수호출
    getchar();
    scanf("%s", print_num);
    if(optmda=='m'){
				print_m(m_log, print_num);
		}
		else if(optmda=='d'){
      print_d(d_log, print_num);
		}
		else if(optmda=='a'){
			print_a(a_log, print_num);
		}
	}
	else if(strcmp(order,"delete")==0){//delete명령어를 받으면 m|d|a중 골라서 함수 호출
    getchar();
    scanf("%s",delete_num);

    if(optmda=='m'){
				deletem(m_log, delete_num);
		}
		else if(optmda=='d'){
      deleted(d_log, delete_num);
		}
		else if(optmda=='a'){
      deletea(a_log, delete_num);
		}
	}
	else if(strcmp(order,"sort")==0){//sort 명령어를 입력받으면 m|d|a를 골라서 함수호출
    if(optmda=='m'){
      sort_m(m_log);
		}
		else if(optmda=='d'){
      sort_d(d_log);
    }
    else if (optmda=='a'){
      sort_a(a_log);
        }
      }
	else if(strcmp(order,"save")==0){//save명령어를 입력받으면 m|d|a를 ㄹ골라서 함수 호출
		if(optmda=='m'){
				savem(m_log);
		}
		else if(optmda=='d'){
			saved(d_log);
		}
		else if(optmda=='a'){
			printf("14");
		}
	}
	else if(strcmp(order,"search")==0){
		search(m_log, d_log, a_log);
	}

}
void con_printm(int print_it, movie *m_tmp, m_actor *movie_actor){
  char *print_str = (char *)malloc(50);
  if (print_it != 0){
    strcpy(print_str, m_tmp -> serial_number);
    inverse_ch(print_str);
    printf("%s:",print_str);
    strcpy(print_str, m_tmp -> title);
    inverse_ch(print_str);
    printf("%s:",print_str);
    strcpy(print_str, m_tmp -> genre);
    inverse_ch(print_str);
    printf("%s:",print_str);
    strcpy(print_str, m_tmp -> movie_director -> director);
    inverse_ch(print_str);
    printf("%s:",print_str);
    strcpy(print_str, m_tmp -> year);
    inverse_ch(print_str);
    printf("%s:",print_str);
    strcpy(print_str, m_tmp -> run_time);
    inverse_ch(print_str);
    printf("%s:",print_str);
    while (1){
      strcpy(print_str, movie_actor -> actor);
      inverse_ch(print_str);
      printf("%s",print_str);
      if(movie_actor -> next -> actor == NULL)
        break;
      movie_actor = movie_actor -> next;
      printf(", ");
    }
    printf("\n");
  }
}
void con_printd(int print_it, director *d_tmp, d_title *director_title){
  char *print_str = (char *)malloc(50);
  if (print_it != 0){
    strcpy(print_str, d_tmp -> serial_number);
    inverse_ch(print_str);
    printf("%s:",print_str);
    strcpy(print_str, d_tmp -> d_name);
    inverse_ch(print_str);
    printf("%s:",print_str);
    strcpy(print_str, d_tmp -> s);
    inverse_ch(print_str);
    printf("%s:",print_str);
    strcpy(print_str, d_tmp -> birth);
    inverse_ch(print_str);
    printf("%s:",print_str);
    while (1){
      strcpy(print_str, director_title -> title);
      inverse_ch(print_str);
      printf("%s",print_str);
      if(director_title -> next -> next == NULL)
        break;
        director_title = director_title -> next;
      printf(", ");
    }
    printf("\n");
  }
}
void con_printa(int print_it, actor *a_tmp, a_title *actor_title){
  char *print_str = (char *)malloc(50);
  if (print_it != 0){
    strcpy(print_str, a_tmp -> serial_number);
    inverse_ch(print_str);
    printf("%s:",print_str);
    strcpy(print_str, a_tmp -> a_name);
    inverse_ch(print_str);
    printf("%s:",print_str);
    strcpy(print_str, a_tmp -> s);
    inverse_ch(print_str);
    printf("%s:",print_str);
    strcpy(print_str, a_tmp -> birth);
    inverse_ch(print_str);
    printf("%s:",print_str);
    while (1){
      strcpy(print_str, actor_title -> title);
      inverse_ch(print_str);
      printf("%s",print_str);
      if(actor_title -> next -> title == NULL)
        break;
      actor_title = actor_title -> next;
      printf(", ");
    }
    printf("\n");
  }
}
int check(char * string, char * data)
{
   int str_len = strlen(string);
   int data_len = strlen(data);
   int j = 0;
   int count = 0;
   for (int i = 0; i< str_len; i++)
   {
      if ((*(data + i)) == (*(string + i)))
      {
         count++;
      }
      else if ((*(string + i)) == '?')
      {
         count++;
      }

   }
   if ((count == str_len) && (count == data_len))
   {
      return 1;
   }
   else
   {
      return 0;
   }
}
int q_check(char * str){
  for (int i = 0; *(str + i) != '\0'; i++){
    if (*(str + i) == '?')
      return 1;
  }
  return 0;
}
void search(movie *m_log, director *d_log, actor *a_log)
{
  char *option = (char *)calloc(50, sizeof(char));
  char *str = (char *)calloc(50, sizeof(char));
  char *print_str = (char *)calloc(50, sizeof(char));
  char ** m_array;
  int print_it = 0;
  movie *m_tmp = m_log;
  director *d_tmp = d_log;
  actor *a_tmp = a_log;
  m_actor *movie_actor = m_log -> movie_actor;
  d_title *director_title = d_log -> director_title;
  a_title *actor_title = a_log -> actor_title;

  int m = 0, d = 0, a = 0, m_count = 0, d_count = 0, a_count = 0;
  //movie, director, actor의 구조체 개수 카운팅
  while (1){
    m_count++;
    if (m_tmp -> next == NULL)
      break;
    m_tmp = m_tmp -> next;
  }
  m_tmp = m_log;
  while(1){
    d_count++;
    if(d_tmp -> next == NULL)
      break;
      d_tmp = d_tmp -> next;
  }
  d_tmp = d_log;
  while(1){
    a_count++;
    if(a_tmp -> next == NULL)
      break;
    a_tmp = a_tmp -> next;
  }
  a_tmp = a_log;

  scanf("%s", option);
  if ((*option) != '-')
    strcpy(str, option);
  else {
    scanf("%s", str);
    for (int i = 1; *(option + i) != '\0'; i++){
      if (*(option + i) == 'd')
        d++;
      else if (*(option + i) == 'm')
        m++;
      else if (*(option + i) == 'a')
        a++;
    }
  }//?나 *가 없을 때!-------------------------
  if ((m == 0) && (a == 0) && (d == 0)){
    m = 1;
    a = 1;
    d = 1;
  }
  if (m == 1){  //-m옵션이 있는 경우
    if (*str == '*'){
      while (1) {
        strcpy(print_str, m_tmp -> serial_number);
        inverse_ch(print_str);
        if(_check(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> title);
        inverse_ch(print_str);
        if(_check(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> genre);
        inverse_ch(print_str);
        if(_check(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> movie_director -> director);
        inverse_ch(print_str);
        if(_check(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> year);
        inverse_ch(print_str);
        if(_check(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> run_time);
        inverse_ch(print_str);
        if(_check(str, print_str))
          print_it++;
        while (1) {
          strcpy(print_str, movie_actor -> actor);
          inverse_ch(print_str);
          if(_check(str, print_str))
            print_it++;
          if (movie_actor -> next -> next == NULL)
            break;
          movie_actor = movie_actor -> next;
        }
        movie_actor = m_tmp -> movie_actor;
        con_printm(print_it, m_tmp, movie_actor);
        if (m_tmp -> next == NULL)
          break;
        print_it = 0;
        m_tmp = m_tmp -> next;
        movie_actor = m_tmp -> movie_actor;
      }
      m_tmp = m_log;
      movie_actor = m_log -> movie_actor;
    }
    else if (*(str + (strlen(str) - 1)) == '*') {
      while (1) {
        strcpy(print_str, m_tmp -> serial_number);
        inverse_ch(print_str);
        if(check_(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> title);
        inverse_ch(print_str);
        if(check_(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> genre);
        inverse_ch(print_str);
        if(check_(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> movie_director -> director);
        inverse_ch(print_str);
        if(check_(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> year);
        inverse_ch(print_str);
        if(check_(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> run_time);
        inverse_ch(print_str);
        if(check_(str, print_str))
          print_it++;
        while (1) {
          strcpy(print_str, movie_actor -> actor);
          inverse_ch(print_str);
          if(check_(str, print_str))
            print_it++;
          if (movie_actor -> next -> next == NULL)
            break;
          movie_actor = movie_actor -> next;
        }
        movie_actor = m_tmp -> movie_actor;
        con_printm(print_it, m_tmp, movie_actor);
        if (m_tmp -> next == NULL)
          break;
        print_it = 0;
        m_tmp = m_tmp -> next;
        movie_actor = m_tmp -> movie_actor;
      }
      m_tmp = m_log;
      movie_actor = m_log -> movie_actor;
    }
    else if (q_check(str)){
      while (1) {
        strcpy(print_str, m_tmp -> serial_number);
        inverse_ch(print_str);
        if(check(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> title);
        inverse_ch(print_str);
        if(check(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> genre);
        inverse_ch(print_str);
        if(check(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> movie_director -> director);
        inverse_ch(print_str);
        if(check(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> year);
        inverse_ch(print_str);
        if(check(str, print_str))
          print_it++;
        strcpy(print_str, m_tmp -> run_time);
        inverse_ch(print_str);
        if(check(str, print_str))
          print_it++;
        while (1) {
          strcpy(print_str, movie_actor -> actor);
          inverse_ch(print_str);
          if(check(str, print_str))
            print_it++;
          if (movie_actor -> next -> next == NULL)
            break;
          movie_actor = movie_actor -> next;
        }
        movie_actor = m_tmp -> movie_actor;
        con_printm(print_it, m_tmp, movie_actor);
        if (m_tmp -> next == NULL)
          break;
        print_it = 0;
        m_tmp = m_tmp -> next;
        movie_actor = m_tmp -> movie_actor;
      }
      m_tmp = m_log;
      movie_actor = m_log -> movie_actor;
    }
    else {
    for (int i = 0; i < m_count; i++){
      if (strcmp(m_tmp -> title, str) == 0)
        print_it++;
      else if (strcmp(m_tmp -> serial_number, str) == 0)
        print_it++;
      else if (strcmp(m_tmp -> genre, str) == 0)
        print_it++;
      else if (strcmp(m_tmp -> movie_director -> director, str) == 0)
        print_it++;
      else if (strcmp(m_tmp -> year, str) == 0)
        print_it++;
      else if (strcmp(m_tmp -> run_time, str) == 0)
        print_it++;
      while (1){
        if (strcmp(movie_actor -> actor, str) == 0){
          print_it++;
          break;
        }
        if (movie_actor -> next -> actor == NULL)
          break;
        movie_actor = movie_actor -> next;
      }
      movie_actor = m_tmp -> movie_actor;
      con_printm(print_it, m_tmp, movie_actor);
      print_it = 0;
      if(i < m_count - 1){

        m_tmp = m_tmp -> next;
        movie_actor = m_tmp -> movie_actor;
      }

    }
    m_tmp = m_log;
    movie_actor = m_log -> movie_actor;

      }
    }

  if (d == 1) {  //-d옵션이 있는 경우
     if (*str == '*'){
       while (1) {
         strcpy(print_str, d_tmp -> serial_number);
         inverse_ch(print_str);
         if(_check(str, print_str))
           print_it++;
         strcpy(print_str, d_tmp -> d_name);
         inverse_ch(print_str);
         if(_check(str, print_str))
           print_it++;
         strcpy(print_str, d_tmp -> s);
         inverse_ch(print_str);
         if(_check(str, print_str))
           print_it++;
         strcpy(print_str, d_tmp -> birth);
         inverse_ch(print_str);
         if(_check(str, print_str))
           print_it++;
         while (1) {
           strcpy(print_str, director_title -> title);
           inverse_ch(print_str);
           if(_check(str, print_str))
             print_it++;
           if (director_title -> next -> next == NULL)
             break;
           director_title = director_title -> next;
         }
         director_title = d_tmp -> director_title;
         con_printd(print_it, d_tmp, director_title);
         if (d_tmp -> next == NULL)
           break;
         print_it = 0;
         d_tmp = d_tmp -> next;
         director_title = d_tmp -> director_title;
       }
       d_tmp = d_log;
       director_title = d_log -> director_title;
     }
     else if (*(str + (strlen(str) - 1)) == '*') {
       while (1) {
         strcpy(print_str, d_tmp -> serial_number);
         inverse_ch(print_str);
         if(check_(str, print_str))
           print_it++;
         strcpy(print_str, d_tmp -> d_name);
         inverse_ch(print_str);
         if(check_(str, print_str))
           print_it++;
         strcpy(print_str, d_tmp -> s);
         inverse_ch(print_str);
         if(check_(str, print_str))
           print_it++;
         strcpy(print_str, d_tmp -> birth);
         inverse_ch(print_str);
         if(check_(str, print_str))
           print_it++;
         while (1) {
           strcpy(print_str, director_title -> title);
           inverse_ch(print_str);
           if(check_(str, print_str))
             print_it++;
           if (director_title -> next -> next == NULL)
             break;
           director_title = director_title -> next;
         }
         director_title = d_tmp -> director_title;
         con_printd(print_it, d_tmp, director_title);
         if (d_tmp -> next == NULL)
           break;
         print_it = 0;
         d_tmp = d_tmp -> next;
         director_title = d_tmp -> director_title;
       }
       d_tmp = d_log;
       director_title = d_log -> director_title;
     }
     else if (q_check(str)){
       while (1) {
         strcpy(print_str, d_tmp -> serial_number);
         inverse_ch(print_str);
         if(check(str, print_str))
           print_it++;
         strcpy(print_str, d_tmp -> d_name);
         inverse_ch(print_str);
         if(check(str, print_str))
           print_it++;
         strcpy(print_str, d_tmp -> s);
         inverse_ch(print_str);
         if(check(str, print_str))
           print_it++;
         strcpy(print_str, d_tmp -> birth);
         inverse_ch(print_str);
         if(check(str, print_str))
           print_it++;
         while (1) {
           strcpy(print_str, director_title -> title);
           inverse_ch(print_str);
           if(check(str, print_str))
             print_it++;
           if (director_title -> next -> next == NULL)
             break;
           director_title = director_title -> next;
         }
         director_title = d_tmp -> director_title;
         con_printd(print_it, d_tmp, director_title);
         if (d_tmp -> next == NULL)
           break;
         print_it = 0;
         d_tmp = d_tmp -> next;
         director_title = d_tmp -> director_title;
       }
       d_tmp = d_log;
       director_title = d_log -> director_title;
     }
     else {
     for (int i = 0; i < d_count; i++){
       if (strcmp(d_tmp -> d_name, str) == 0)
         print_it++;
       else if (strcmp(d_tmp -> serial_number, str) == 0)
         print_it++;
       else if (strcmp(d_tmp -> s, str) == 0)
         print_it++;
       else if (strcmp(d_tmp -> birth, str) == 0)
         print_it++;
       while (1){
         if (strcmp(director_title -> title, str) == 0){
           print_it++;
           break;
         }
         if (director_title -> next -> next == NULL)
           break;
         director_title = director_title -> next;
       }
       director_title = d_tmp -> director_title;
       con_printd(print_it, d_tmp, director_title);
       print_it = 0;
       if(i < d_count - 1){
         d_tmp = d_tmp -> next;
         director_title = d_tmp -> director_title;
       }

     }
     d_tmp = d_log;
     director_title = d_log -> director_title;

       }
     }

  //--------------------------------------------

  if (a == 1) {  //-d옵션이 있는 경우
          if (*str == '*'){
            while (1) {
              strcpy(print_str, a_tmp -> serial_number);
              inverse_ch(print_str);
              if(_check(str, print_str))
                print_it++;
              strcpy(print_str, a_tmp -> a_name);
              inverse_ch(print_str);
              if(_check(str, print_str))
                print_it++;
              strcpy(print_str, a_tmp -> s);
              inverse_ch(print_str);
              if(_check(str, print_str))
                print_it++;
              strcpy(print_str, a_tmp -> birth);
              inverse_ch(print_str);
              if(_check(str, print_str))
                print_it++;
              while (1) {
                strcpy(print_str, actor_title -> title);
                inverse_ch(print_str);
                if(_check(str, print_str))
                  print_it++;
                if (actor_title -> next -> next == NULL)
                  break;
                actor_title = actor_title -> next;
              }
              actor_title = a_tmp -> actor_title;
              con_printa(print_it, a_tmp, actor_title);
              if (a_tmp -> next == NULL)
                break;
              print_it = 0;
              a_tmp = a_tmp -> next;
              actor_title = a_tmp -> actor_title;
            }
            a_tmp = a_log;
            actor_title = a_log -> actor_title;
          }
          else if (*(str + (strlen(str) - 1)) == '*') {
            while (1) {
              strcpy(print_str, a_tmp -> serial_number);
              inverse_ch(print_str);
              if(check_(str, print_str))
                print_it++;
              strcpy(print_str, a_tmp -> a_name);
              inverse_ch(print_str);
              if(check_(str, print_str))
                print_it++;
              strcpy(print_str, a_tmp -> s);
              inverse_ch(print_str);
              if(check_(str, print_str))
                print_it++;
              strcpy(print_str, a_tmp -> birth);
              inverse_ch(print_str);
              if(check_(str, print_str))
                print_it++;
              while (1) {
                strcpy(print_str, actor_title -> title);
                inverse_ch(print_str);
                if(check_(str, print_str))
                  print_it++;
                if (actor_title -> next -> next == NULL)
                  break;
                actor_title = actor_title -> next;
              }
              actor_title = a_tmp -> actor_title;
              con_printa(print_it, a_tmp, actor_title);
              if (a_tmp -> next == NULL)
                break;
              print_it = 0;
              a_tmp = a_tmp -> next;
              actor_title = a_tmp -> actor_title;
            }
            a_tmp = a_log;
            actor_title = a_log -> actor_title;
          }
          else if (q_check(str)){
            while (1) {
              strcpy(print_str, a_tmp -> serial_number);
              inverse_ch(print_str);
              if(check(str, print_str))
                print_it++;
              strcpy(print_str, a_tmp -> a_name);
              inverse_ch(print_str);
              if(check(str, print_str))
                print_it++;
              strcpy(print_str, a_tmp -> s);
              inverse_ch(print_str);
              if(check(str, print_str))
                print_it++;
              strcpy(print_str, a_tmp -> birth);
              inverse_ch(print_str);
              if(check(str, print_str))
                print_it++;
              while (1) {
                strcpy(print_str, actor_title -> title);
                inverse_ch(print_str);
                if(check(str, print_str))
                  print_it++;
                if (actor_title -> next -> next == NULL)
                  break;
                actor_title = actor_title -> next;
              }
              actor_title = a_tmp -> actor_title;
              con_printa(print_it, a_tmp, actor_title);
              if (a_tmp -> next == NULL)
                break;
              print_it = 0;
              a_tmp = a_tmp -> next;
              actor_title = a_tmp -> actor_title;
            }
            a_tmp = a_log;
            actor_title = a_log -> actor_title;
          }
          else {
          for (int i = 0; i < a_count; i++){
            if (strcmp(a_tmp -> a_name, str) == 0)
              print_it++;
            else if (strcmp(a_tmp -> serial_number, str) == 0)
              print_it++;
            else if (strcmp(a_tmp -> s, str) == 0)
              print_it++;
            else if (strcmp(a_tmp -> birth, str) == 0)
              print_it++;
            while (1){
              if (strcmp(actor_title -> title, str) == 0){
                print_it++;
                break;
              }
              if (actor_title -> next -> next == NULL)
                break;
              actor_title = actor_title -> next;
            }
            actor_title = a_tmp -> actor_title;
            con_printa(print_it, a_tmp, actor_title);
            print_it = 0;
            if(i < a_count - 1){
              a_tmp = a_tmp -> next;
              actor_title = a_tmp -> actor_title;
            }

          }
          a_tmp = a_log;
          actor_title = a_log -> actor_title;

            }
          }
}
int check_(char * string, char * data)
{
   int str_len = strlen(string);
   int data_len = strlen(data);
   int j = 0;
   int count = 0;
   for (int i = 0; i< str_len; i++)
   {
      if ((*(data + i)) == (*(string + j)))
      {
         count++;
      }
      j++;
   }
   if (count == str_len-1)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}
int _check(char * string, char * data)
{
   int str_len = strlen(string);
   int data_len = strlen(data);
   printf("str_len %d\n", str_len);
   printf("data_len %d\n", data_len);
   int j = 1;
   int count = 0;
   for (int i = data_len - str_len + 1; i< data_len; i++)
   {
      if ((*(data + i)) == (*(string + j)))
      {
         count++;
      }
      j++;
   }
   if (count == str_len - 1)
   {
      return 1;
   }
   else
   {
      return 0;
   }

}
int cmp_word(const void *p, const void *q){
  return strcmp(*(char **)p, *(char **)q);
}
void sort_m(movie *m_log)
{
  char space;
  char *s_option = (char *)calloc(5, sizeof(char));
  char *filename = (char *)calloc(30, sizeof(char));
  char *dump = (char *)calloc(5, sizeof(char));
  char ** t_array, **a_array;
  char *title = (char *)malloc(50);
  char *genre = (char *)malloc(20);
  char *movie_director = (char *)malloc(20);
  char *run_time = (char *)malloc(10);
  char *a_name = (char *)malloc(30);
  FILE *file;
  movie *m_tmp = m_log;
  m_actor *movie_actor = m_log -> movie_actor;
  int count = 0, a_count = 0, for_count = 0;
  //movie의 구조체, m_actor의 구조체 개수 카운팅
  while (1){
    count++;
    while (1) {
      a_count++;
      if (movie_actor -> next -> next == NULL)
        break;
      movie_actor = movie_actor -> next;
    }
    if (m_tmp -> next == NULL)
      break;
    m_tmp = m_tmp -> next;
    movie_actor = m_tmp -> movie_actor;
  }
  m_tmp = m_log;
  movie_actor = m_log -> movie_actor;
   //t,g,d,y,r,g 메모리 할당
  t_array = (char **)malloc(sizeof(char *) * count);
  for (int i = 0; i < count; i++){
    *(t_array + i) = (char *)malloc(50);
  }
  a_array = (char **)malloc(sizeof(char *) * a_count);
  for (int i = 0; i < a_count; i++){
    *(a_array + i) = (char *)malloc(50);
  }

  //각 배열에 정


      space = getchar();
      if (space == ' '){
        scanf("%s", s_option);
        if (strcmp(s_option, "-f") == 0) {//-----------------------------시작
          space = getchar();
          scanf("%s", filename);
          for (int i = 0; m_tmp != NULL; i++){
            title = m_tmp -> title;
            inverse_ch(title);
            strcpy((*(t_array + i)), title);
          if (m_tmp -> next == NULL)
            break;
          m_tmp = m_tmp -> next;
          }
          qsort((void *)t_array, count, sizeof(char *), cmp_word);
          file = fopen(filename, "w");
          for (int i = 0; i < count; i++){
            fprintf(file, "%s\n", *(t_array + i));
          }
          fclose(file);
          //~only filename까지의 코드 넣기-----------------------------------
        }
        else {
          space = getchar();
          if (space == '\n'){
            //---------------------------------------
            if (strcmp(s_option, "t") == 0){
              for (int i = 0; m_tmp != NULL; i++){
                title = m_tmp -> title;
                inverse_ch(title);
                strcpy((*(t_array + i)), title);
              if (m_tmp -> next == NULL)
                break;
              m_tmp = m_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < count; i++){
                printf("%s\n", *(t_array + i));
              }
            }//-------------------------------------------------
            else if (strcmp(s_option, "g") == 0) {
              for (int i = 0; m_tmp != NULL; i++){
                genre = m_tmp -> genre;
                inverse_ch(genre);
                strcpy((*(t_array + i)), genre);
                if (m_tmp -> next ==NULL)
                  break;
                  m_tmp = m_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < count; i++){
                printf("%s\n", *(t_array + i));
              }
            }//-------------------------------------------------
            else if (strcmp(s_option, "d") == 0) {
              for (int i = 0; m_tmp != NULL; i++){
                movie_director = m_tmp -> movie_director -> director;
                inverse_ch(movie_director);
                strcpy((*(t_array + i)), movie_director);
                if (m_tmp -> next ==NULL)
                  break;
                  m_tmp = m_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < count; i++){
                printf("%s\n", *(t_array + i));
              }
            }//------------------------------
            else if (strcmp(s_option, "y") == 0) {
              for (int i = 0; m_tmp != NULL; i++){
                strcpy((*(t_array + i)), m_tmp -> year);
                if (m_tmp -> next ==NULL)
                  break;
                  m_tmp = m_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < count; i++){
                printf("%s\n", *(t_array + i));
              }
            }//-----------------------------------
            else if (strcmp(s_option, "r") == 0) {
              for (int i = 0; m_tmp != NULL; i++){
                run_time = m_tmp -> run_time;
                inverse_ch(run_time);
                strcpy((*(t_array + i)), run_time);
                if (m_tmp -> next ==NULL)
                  break;
                  m_tmp = m_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < count; i++){
                printf("%s\n", *(t_array + i));
              }
            }//-------------------------------------------
            else if (strcmp(s_option, "a") == 0) {
              for (int i = 0; m_tmp != NULL; i++){
                for (int j = 0; movie_actor -> actor != NULL; j++){
                  a_name = movie_actor -> actor;
                  inverse_ch(a_name);
                  strcpy((*(a_array + for_count)), a_name);
                  for_count++;
                  if (movie_actor -> next -> actor == NULL)
                    break;
                  movie_actor = movie_actor -> next;
                }
                if (m_tmp -> next == NULL)
                  break;
                m_tmp = m_tmp -> next;
                movie_actor = m_tmp -> movie_actor;
              }
              qsort((void *)a_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < a_count; i++){
                printf("%s\n", *(a_array + i));
              }
            }
            //~option까지의 코드 넣기---------------------------------------------
          }
          else{
            scanf("%s %s", dump, filename);

            if (strcmp(s_option, "t") == 0){
              for (int i = 0; m_tmp != NULL; i++){
                title = m_tmp -> title;
                inverse_ch(title);
                strcpy((*(t_array + i)), title);
              if (m_tmp -> next == NULL)
                break;
              m_tmp = m_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < count; i++){
                fprintf(file, "%s\n", *(t_array + i));
              }
              fclose(file);
            }//-------------------------------------------------
            else if (strcmp(s_option, "g") == 0) {
              for (int i = 0; m_tmp != NULL; i++){
                genre = m_tmp -> genre;
                inverse_ch(genre);
                strcpy((*(t_array + i)), genre);
                if (m_tmp -> next ==NULL)
                  break;
                  m_tmp = m_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < count; i++){
                fprintf(file, "%s\n", *(t_array + i));
              }
              fclose(file);
            }//-------------------------------------------------
            else if (strcmp(s_option, "d") == 0) {
              for (int i = 0; m_tmp != NULL; i++){
                movie_director = m_tmp -> movie_director -> director;
                inverse_ch(movie_director);
                strcpy((*(t_array + i)), movie_director);
                if (m_tmp -> next ==NULL)
                  break;
                  m_tmp = m_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < count; i++){
                fprintf(file, "%s\n", *(t_array + i));
              }
              fclose(file);
            }//------------------------------
            else if (strcmp(s_option, "y") == 0) {
              for (int i = 0; m_tmp != NULL; i++){
                strcpy((*(t_array + i)), m_tmp -> year);
                if (m_tmp -> next ==NULL)
                  break;
                  m_tmp = m_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < count; i++){
                fprintf(file, "%s\n", *(t_array + i));
              }
              fclose(file);
            }//-----------------------------------
            else if (strcmp(s_option, "r") == 0) {
              for (int i = 0; m_tmp != NULL; i++){
                run_time = m_tmp -> run_time;
                inverse_ch(run_time);
                strcpy((*(t_array + i)), run_time);
                if (m_tmp -> next ==NULL)
                  break;
                  m_tmp = m_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < count; i++){
                fprintf(file, "%s\n", *(t_array + i));
              }
              fclose(file);
            }//-------------------------------------------
            else if (strcmp(s_option, "a") == 0) {
              for (int i = 0; m_tmp != NULL; i++){
                for (int j = 0; movie_actor -> actor != NULL; j++){
                  a_name = movie_actor -> actor;
                  inverse_ch(a_name);
                  strcpy((*(a_array + for_count)), a_name);
                  for_count++;
                  if (movie_actor -> next -> actor == NULL)
                    break;
                  movie_actor = movie_actor -> next;
                }
                if (m_tmp -> next == NULL)
                  break;
                m_tmp = m_tmp -> next;
                movie_actor = m_tmp -> movie_actor;
              }
              qsort((void *)a_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < a_count; i++){
                fprintf(file, "%s\n", *(a_array + i));
              }
              fclose(file);
            }
            //~전부다--------------------------------------------------------------
          }
        }
      }
      else{
        for (int i = 0; m_tmp != NULL; i++){
          title = m_tmp -> title;
          inverse_ch(title);
          strcpy((*(t_array + i)), title);
        if (m_tmp -> next == NULL)
          break;
        m_tmp = m_tmp -> next;
        }
        qsort((void *)t_array, count, sizeof(char *), cmp_word);
        for(int i = 0; i < count; i++ ){
          printf("%s\n", *(t_array + i));
        }
      }
}
void sort_d(director *d_log)
{
  char space;
  char *s_option = (char *)calloc(5, sizeof(char));
  char *filename = (char *)calloc(30, sizeof(char));
  char *dump = (char *)calloc(5, sizeof(char));
  char ** t_array, **a_array;
  char *title = (char *)malloc(50);
  char *sex = (char *)malloc(5);
  char *birth = (char *)malloc(10);
  char *d_name = (char *)malloc(30);
  FILE *file;
  director *d_tmp = d_log;
  d_title *director_title = d_log -> director_title;
  int count = 0, a_count = 0, for_count = 0;
  //director의 구조체, d_title의 구조체 개수 카운팅
  while (1){
    count++;
    while (1) {
      a_count++;
      if (director_title -> next -> title == NULL)
        break;
      director_title = director_title -> next;
    }
    if (d_tmp -> next == NULL)
      break;
    d_tmp = d_tmp -> next;
    director_title = d_tmp -> director_title;
  }
  d_tmp = d_log;
  director_title = d_log -> director_title;
  //t,g,d,y,r,g 메모리 할당
  t_array = (char **)malloc(sizeof(char *) * count);
  for (int i = 0; i < count; i++){
    *(t_array + i) = (char *)malloc(50);
  }
  a_array = (char **)malloc(sizeof(char *) * a_count);
  for (int i = 0; i < a_count; i++){
    *(a_array + i) = (char *)malloc(50);
  }

  //각 배열에 정


      space = getchar();
      if (space == ' '){
        scanf("%s", s_option);
        if (strcmp(s_option, "-f") == 0) {//-----------------------------시작
          space = getchar();
          scanf("%s", filename);
          for (int i = 0; d_tmp != NULL; i++){
            d_name = d_tmp -> d_name;
            inverse_ch(d_name);
            strcpy((*(t_array + i)), d_name);
          if (d_tmp -> next == NULL)
            break;
          d_tmp = d_tmp -> next;
          }
          qsort((void *)t_array, count, sizeof(char *), cmp_word);
          file = fopen(filename, "w");
          for (int i = 0; i < count; i++){
            fprintf(file, "%s\n", *(t_array + i));
          }
          fclose(file);
          //~only filename까지의 코드 넣기-----------------------------------
        }
        else {
          space = getchar();
          if (space == '\n'){
            //---------------------------------------
            if (strcmp(s_option, "n") == 0){
              for (int i = 0; d_tmp != NULL; i++){
                d_name = d_tmp -> d_name;
                inverse_ch(d_name);
                strcpy((*(t_array + i)), d_name);
              if (d_tmp -> next == NULL)
                break;
              d_tmp = d_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < count; i++){
                printf("%s\n", *(t_array + i));
              }
            }//-------------------------------------------------
            else if (strcmp(s_option, "s") == 0) {
              for (int i = 0; d_tmp != NULL; i++){
                sex = d_tmp -> s;
                inverse_ch(sex);
                strcpy((*(t_array + i)), sex);
                if (d_tmp -> next ==NULL)
                  break;
                  d_tmp = d_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < count; i++){
                printf("%s\n", *(t_array + i));
              }
            }//-------------------------------------------------
            else if (strcmp(s_option, "b") == 0) {
              for (int i = 0; d_tmp != NULL; i++){
                birth = d_tmp -> birth;
                inverse_ch(birth);
                strcpy((*(t_array + i)), birth);
                if (d_tmp -> next ==NULL)
                  break;
                  d_tmp = d_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < count; i++){
                printf("%s\n", *(t_array + i));
              }
            }//------------------------------
            else if (strcmp(s_option, "m") == 0) {
              for (int i = 0; d_tmp != NULL; i++){
                for (int j = 0; director_title -> title != NULL; j++){
                  title = director_title -> title;
                  inverse_ch(title);
                  strcpy((*(a_array + for_count)), title);
                  for_count++;
                  if (director_title -> next -> title == NULL)
                    break;
                  director_title = director_title -> next;
                }
                if (d_tmp -> next == NULL)
                  break;
                d_tmp = d_tmp -> next;
                director_title = d_tmp -> director_title;
              }
              qsort((void *)a_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < a_count; i++){
                printf("%s\n", *(a_array + i));
              }
            }
            //~option까지의 코드 넣기---------------------------------------------
          }
          else{
            scanf("%s %s", dump, filename);

            if (strcmp(s_option, "n") == 0){
              for (int i = 0; d_tmp != NULL; i++){
                d_name = d_tmp -> d_name;
                inverse_ch(d_name);
                strcpy((*(t_array + i)), d_name);
              if (d_tmp -> next == NULL)
                break;
              d_tmp = d_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < count; i++){
                fprintf(file, "%s\n", *(t_array + i));
              }
              fclose(file);
            }//-------------------------------------------------
            else if (strcmp(s_option, "s") == 0) {
              for (int i = 0; d_tmp != NULL; i++){
                sex = d_tmp -> s;
                inverse_ch(sex);
                strcpy((*(t_array + i)), sex);
                if (d_tmp -> next ==NULL)
                  break;
                  d_tmp = d_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < count; i++){
                fprintf(file, "%s\n", *(t_array + i));
              }
              fclose(file);
            }//-------------------------------------------------
            else if (strcmp(s_option, "b") == 0) {
              for (int i = 0; d_tmp != NULL; i++){
                birth = d_tmp -> birth;
                inverse_ch(birth);
                strcpy((*(t_array + i)), birth);
                if (d_tmp -> next ==NULL)
                  break;
                  d_tmp = d_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < count; i++){
                fprintf(file, "%s\n", *(t_array + i));
              }
              fclose(file);
            }//------------------------------
            else if (strcmp(s_option, "m") == 0) {
              for (int i = 0; d_tmp != NULL; i++){
                for (int j = 0; director_title -> title != NULL; j++){
                  title = director_title -> title;
                  inverse_ch(title);
                  strcpy((*(a_array + for_count)), title);
                  for_count++;
                  if (director_title -> next -> title == NULL)
                    break;
                  director_title = director_title -> next;
                }
                if (d_tmp -> next == NULL)
                  break;
                d_tmp = d_tmp -> next;
                director_title = d_tmp -> director_title;
              }
              qsort((void *)a_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < a_count; i++){
                fprintf(file, "%s\n", *(a_array + i));
              }
              fclose(file);
            }
            //~전부다--------------------------------------------------------------
          }
        }
      }
      else{
        for (int i = 0; d_tmp != NULL; i++){
          d_name = d_tmp -> d_name;
          inverse_ch(d_name);
          strcpy((*(t_array + i)), d_name);
        if (d_tmp -> next == NULL)
          break;
        d_tmp = d_tmp -> next;
        }
        qsort((void *)t_array, count, sizeof(char *), cmp_word);
        for(int i = 0; i < count; i++ ){
          printf("%s\n", *(t_array + i));
        }
      }
}
void sort_a(actor *a_log){
  char space;
  char *s_option = (char *)calloc(5, sizeof(char));
  char *filename = (char *)calloc(30, sizeof(char));
  char *dump = (char *)calloc(5, sizeof(char));
  char ** t_array, **a_array;
  char *title = (char *)malloc(50);
  char *sex = (char *)malloc(5);
  char *birth = (char *)malloc(10);
  char *a_name = (char *)malloc(30);
  FILE *file;
  actor *a_tmp = a_log;
  a_title *actor_title = a_log -> actor_title;
  int count = 0, a_count = 0, for_count = 0;
  //director의 구조체, d_title의 구조체 개수 카운팅
  while (1){
    count++;
    while (1) {
      a_count++;
      if (actor_title -> next -> title == NULL)
        break;
      actor_title = actor_title -> next;
    }
    if (a_tmp -> next == NULL)
      break;
    a_tmp = a_tmp -> next;
    actor_title = a_tmp -> actor_title;
  }
  a_tmp = a_log;
  actor_title = a_log -> actor_title;
  //t,g,d,y,r,g 메모리 할당
  t_array = (char **)malloc(sizeof(char *) * count);
  for (int i = 0; i < count; i++){
    *(t_array + i) = (char *)malloc(50);
  }
  a_array = (char **)malloc(sizeof(char *) * a_count);
  for (int i = 0; i < a_count; i++){
    *(a_array + i) = (char *)malloc(50);
  }

  //각 배열에 정


      space = getchar();
      if (space == ' '){
        scanf("%s", s_option);
        if (strcmp(s_option, "-f") == 0) {//-----------------------------시작
          space = getchar();
          scanf("%s", filename);
          for (int i = 0; a_tmp != NULL; i++){
            a_name = a_tmp -> a_name;
            inverse_ch(a_name);
            strcpy((*(t_array + i)), a_name);
          if (a_tmp -> next == NULL)
            break;
          a_tmp = a_tmp -> next;
          }
          qsort((void *)t_array, count, sizeof(char *), cmp_word);
          file = fopen(filename, "w");
          for (int i = 0; i < count; i++){
            fprintf(file, "%s\n", *(t_array + i));
          }
          fclose(file);
          //~only filename까지의 코드 넣기-----------------------------------
        }
        else {
          space = getchar();
          if (space == '\n'){
            //---------------------------------------
            if (strcmp(s_option, "n") == 0){
              for (int i = 0; a_tmp != NULL; i++){
                a_name = a_tmp -> a_name;
                inverse_ch(a_name);
                strcpy((*(t_array + i)), a_name);
              if (a_tmp -> next == NULL)
                break;
              a_tmp = a_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < count; i++){
                printf("%s\n", *(t_array + i));
              }
            }//-------------------------------------------------
            else if (strcmp(s_option, "s") == 0) {
              for (int i = 0; a_tmp != NULL; i++){
                sex = a_tmp -> s;
                inverse_ch(sex);
                strcpy((*(t_array + i)), sex);
                if (a_tmp -> next ==NULL)
                  break;
                  a_tmp = a_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < count; i++){
                printf("%s\n", *(t_array + i));
              }
            }//-------------------------------------------------
            else if (strcmp(s_option, "b") == 0) {
              for (int i = 0; a_tmp != NULL; i++){
                birth = a_tmp -> birth;
                inverse_ch(birth);
                strcpy((*(t_array + i)), birth);
                if (a_tmp -> next ==NULL)
                  break;
                  a_tmp = a_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < count; i++){
                printf("%s\n", *(t_array + i));
              }
            }//------------------------------
            else if (strcmp(s_option, "m") == 0) {
              for (int i = 0; a_tmp != NULL; i++){
                for (int j = 0; actor_title -> title != NULL; j++){
                  title = actor_title -> title;
                  inverse_ch(title);
                  strcpy((*(a_array + for_count)), title);
                  for_count++;
                  if (actor_title -> next -> title == NULL)
                    break;
                  actor_title =actor_title -> next;
                }
                if (a_tmp -> next == NULL)
                  break;
                a_tmp = a_tmp -> next;
                actor_title = a_tmp -> actor_title;
              }
              qsort((void *)a_array, count, sizeof(char *), cmp_word);
              for (int i = 0; i < a_count; i++){
                printf("%s\n", *(a_array + i));
              }
            }
            //~option까지의 코드 넣기---------------------------------------------
          }
          else{
            scanf("%s %s", dump, filename);

            if (strcmp(s_option, "n") == 0){
              for (int i = 0; a_tmp != NULL; i++){
                a_name = a_tmp -> a_name;
                inverse_ch(a_name);
                strcpy((*(t_array + i)), a_name);
              if (a_tmp -> next == NULL)
                break;
              a_tmp = a_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < count; i++){
                fprintf(file, "%s\n", *(t_array + i));
              }
              fclose(file);
            }//-------------------------------------------------
            else if (strcmp(s_option, "s") == 0) {
              for (int i = 0; a_tmp != NULL; i++){
                sex = a_tmp -> s;
                inverse_ch(sex);
                strcpy((*(t_array + i)), sex);
                if (a_tmp -> next ==NULL)
                  break;
                  a_tmp = a_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < count; i++){
                fprintf(file, "%s\n", *(t_array + i));
              }
              fclose(file);
            }//-------------------------------------------------
            else if (strcmp(s_option, "b") == 0) {
              for (int i = 0; a_tmp != NULL; i++){
                birth = a_tmp -> birth;
                inverse_ch(birth);
                strcpy((*(t_array + i)), birth);
                if (a_tmp -> next ==NULL)
                  break;
                  a_tmp = a_tmp -> next;
              }
              qsort((void *)t_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < count; i++){
                fprintf(file, "%s\n", *(t_array + i));
              }
              fclose(file);
            }//------------------------------
            else if (strcmp(s_option, "m") == 0) {
              for (int i = 0; a_tmp != NULL; i++){
                for (int j = 0; actor_title -> title != NULL; j++){
                  title = actor_title -> title;
                  inverse_ch(title);
                  strcpy((*(a_array + for_count)), title);
                  for_count++;
                  if (actor_title -> next -> title == NULL)
                    break;
                  actor_title = actor_title -> next;
                }
                if (a_tmp -> next == NULL)
                  break;
                a_tmp = a_tmp -> next;
                actor_title = a_tmp -> actor_title;
              }
              qsort((void *)a_array, count, sizeof(char *), cmp_word);
              file = fopen(filename, "w");
              for (int i = 0; i < a_count; i++){
                fprintf(file, "%s\n", *(a_array + i));
              }
              fclose(file);
            }
            //~전부다--------------------------------------------------------------
          }
        }
      }
      else{
        for (int i = 0; a_tmp != NULL; i++){
          a_name = a_tmp -> a_name;
          inverse_ch(a_name);
          strcpy((*(t_array + i)), a_name);
        if (a_tmp -> next == NULL)
          break;
        a_tmp = a_tmp -> next;
        }
        qsort((void *)t_array, count, sizeof(char *), cmp_word);
        for(int i = 0; i < count; i++ ){
          printf("%s\n", *(t_array + i));
        }
      }
}

void print_m(movie *m_log, char *num){
  movie *m_tmp = m_log;
  m_actor *movie_actor = m_log -> movie_actor;
  int a_number = 1;
  char *title = (char *)calloc(50, sizeof(char));
  char *genre = (char *)calloc(20, sizeof(char));
  char *a_name = (char *)calloc(30, sizeof(char));
  char *d_name = (char *)calloc(30, sizeof(char));
  while(strcmp(m_tmp -> serial_number, num) != 0){
    if (m_tmp -> next == NULL){
      printf("No such data\n");
      return;
    }
    m_tmp = m_tmp -> next;
    movie_actor = m_tmp -> movie_actor;
  }
  title = m_tmp -> title;
  inverse_ch(title);
  genre = m_tmp -> genre;
  inverse_ch(genre);
  d_name = m_tmp -> movie_director -> director;
  inverse_ch(d_name);
  printf("%s, %s, %s\n", m_tmp -> serial_number, title, genre);
  if (m_tmp -> movie_director -> link == NULL){
    printf("\tD : %s(-)\n", d_name);
  }
  else
    printf("\tD : %s(%s)\n", d_name, m_tmp -> movie_director -> link -> birth);
  while(1){
    a_name = movie_actor -> actor;
    inverse_ch(a_name);
    if (movie_actor -> link == NULL)
      printf("\tA%d : %s(-)\n", a_number, a_name);
    else
      printf("\tA%d : %s(%s)\n", a_number, a_name, movie_actor -> link -> birth);
      a_number++;
    if (movie_actor -> next -> actor == NULL)
      break;
    movie_actor = movie_actor -> next;
  }
}
void print_d(director *d_log, char *num){
  director *d_tmp = d_log;
  d_title *director_title = d_log -> director_title;
  char *d_name = (char *)calloc(30, sizeof(char));
  char *title = (char *)calloc(50, sizeof(char));
  int t_number = 1;
  while(strcmp(d_tmp -> serial_number, num) != 0){
    if (d_tmp -> next == NULL){
      printf("No such data\n");
      return;
    }
    d_tmp = d_tmp -> next;
    director_title = d_tmp -> director_title;
  }
  d_name = d_tmp -> d_name;
  inverse_ch(d_name);
  printf("%s, %s, %s, %s\n", d_tmp -> serial_number, d_name, d_tmp -> s, d_tmp -> birth);
  while(1){
    title = director_title -> title;
    inverse_ch(title);
    printf("\t%s, ", title);
    if (director_title -> link == NULL){
      printf("-, -\n");
    }
    else
      printf("%s, %s\n",director_title -> link -> year, director_title -> link -> run_time);
    if (director_title -> next -> next == NULL)
      break;
    director_title = director_title -> next;
  }

}
void print_a(actor *a_log, char *num){
  actor *a_tmp = a_log;
  a_title *actor_title = a_log -> actor_title;
  int a_number = 1;
  char *title = (char *)calloc(50, sizeof(char));
  char *a_name = (char *)calloc(30, sizeof(char));
  while(strcmp(a_tmp -> serial_number, num) != 0){
    if (a_tmp -> next == NULL){
      printf("No such data\n");
      return;
    }
    a_tmp = a_tmp -> next;
    actor_title = a_tmp -> actor_title;
  }
  a_name = a_tmp -> a_name;
  inverse_ch(a_name);
  printf("%s, %s, %s, %s\n", a_tmp -> serial_number, a_name, a_tmp -> s, a_tmp -> birth);
  while(1){
    title = actor_title -> title;
    inverse_ch(title);
    printf("\t%s, ", title);
    if (actor_title -> link == NULL){
      printf("-, -\n");
    }
    else
      printf("%s, %s\n",actor_title -> link -> year, actor_title -> link -> run_time);
    if (actor_title -> next -> next == NULL)
      break;
    actor_title = actor_title -> next;
  }

}
int same_m_check(movie *m_log, char *title){
  while(1){
    if (strcmp(m_log -> title, title) == 0){
      return 1;
    }
    if (m_log -> next == NULL)
      break;
    m_log = m_log -> next;
  }
  return 0;
}
int same_d_check(director *d_log, char *d_name){
  while(1){
    if (strcmp(d_log -> d_name, d_name) == 0){
      return 1;
    }
    if (d_log -> next == NULL)
      break;
    d_log = d_log -> next;
  }
  return 0;
}
int same_a_check(actor *a_log, char *a_name){
  while(1){
    if (strcmp(a_log -> a_name, a_name) == 0){
      return 1;
    }
    if (a_log -> next == NULL)
      break;
    a_log = a_log -> next;
  }
  return 0;
}
void print_for_same(movie *m_log, m_actor *movie_actor, char *title){
  while (1){
    if (strcmp(title, m_log -> title) == 0){
          break;
   }
    m_log = m_log -> next;
    movie_actor = m_log -> movie_actor;
  }
  printf("%s:%s:", m_log -> serial_number, m_log -> title);
  printf("%s:%s:", m_log -> genre, m_log -> movie_director -> director);
  printf("%s:%s:", m_log -> year, m_log -> run_time);
  while (1){
    printf("%s, ", movie_actor -> actor);
    if (movie_actor -> next -> next == NULL)
      break;
    movie_actor = movie_actor -> next;
  }
}
void addm(movie *m_log, director *d_log, actor *a_log)
{
    char * whole_string = (char*)malloc(sizeof(char) * 100);
    char * token = (char*)malloc(sizeof(char)*2);// actor 입력시 ,와 개행으로 문자열 나누기
    char * string_cut;
    char * serial_number = (char*)malloc(sizeof(char) * 10);//추가
    char * title = (char*)malloc(sizeof(char)*100);
    movie tmp;
    struct m_actor * move;
    struct m_actor * m_a_tmp;
    char * genre = (char*)malloc(sizeof(char)*100);
    char * director = (char*)malloc(sizeof(char)*100);
    char * year = (char*)malloc(sizeof(char)*10);
    char * run_time = (char*)malloc(sizeof(char)*10);
    int comma =0;
    char *answer = (char *)calloc(5, sizeof(char));
    char *check;
    char c_check;
    movie *m_tmp = m_log;
    int count = 0;
    int f_location;
    tmp.movie_actor = (struct m_actor *)malloc(sizeof(struct m_actor) * 1);

    *(token + 0) = ',';
    *(token + 1) = '\n';

    FILE * movie_log;
    if ((movie_log = fopen("movie_log.txt", "a+")) == NULL)
    {
      printf("오류 : 파일을 열 수 없습니다. \n");
      }
      else
      {
        f_location = ftell(movie_log);
        flush();
        printf("title > ");
        scanf("%[^\n]", title);
        changes(title);
        flush();
    	  printf("genre > ");
    	  scanf("%[^\n]", genre);
        changes(genre);
    	  flush();
    	  printf("director > ");
    	  scanf("%[^\n]", director);
        changes(director);
    	  flush();
    	  printf("year > ");
    	  scanf("%[^\n]", year);
        flush();
    	  printf("run time > ");
    	  scanf("%[^\n]", run_time);
        flush();
        printf("actors > ");
        scanf("%[^\n]", whole_string);
        changes(whole_string);
        flush();

        if (same_m_check(m_log, title)){  //시리얼넘버 찾아서 올바른 시리어넘버의 자료 출력해야함
          printf("@@ You have the same record\n");
          print_for_same(m_log, m_log -> movie_actor, title);
          printf("\n@@ Do you want to add anyway? (Yes / No) > "); //여기서 대답나오기 전에 밑의 '돌아보림'이 나와버림
          scanf("%s", answer);
          flush();
        }

        if (strcmp(answer, "No") == 0){
          return;
        }

        else if (strcmp(answer, "Yes") == 0){
          while(1){
            if (strcmp(m_tmp -> title, title) == 0){
              strcpy(serial_number, m_tmp -> serial_number);
              break;
            }
            m_tmp = m_tmp -> next;
          }
          fprintf(movie_log, "\n");
          fprintf(movie_log, "update:");
          fprintf(movie_log, "%s:", serial_number);
        }
        else{
          fprintf(movie_log, "\n");
          fprintf(movie_log, "add:");
          add_m_number++;
          fprintf(movie_log, "%d:", add_m_number);
        }


        tmp.movie_actor -> actor = strtok(whole_string, token);
        tmp.movie_actor -> link = NULL;
        tmp.movie_actor -> next = (struct m_actor *)malloc(sizeof(struct m_actor));
        move = tmp.movie_actor -> next;
        m_a_tmp = tmp.movie_actor;
        while ((string_cut = strtok(NULL, token))!=NULL)
    	{
        move -> actor = string_cut;
        move -> link = NULL;
        move -> next =  (struct m_actor *)malloc(sizeof(struct m_actor));
        move = move -> next;
        move -> next = NULL;
    	}

      fprintf(movie_log, "%s:%s:%s:%s:%s:", title, genre,director, year,run_time);

      while (m_a_tmp->next != NULL)
        {
          if (comma != 0)
            fprintf(movie_log,", ");
          if (*(m_a_tmp->actor) == ' ')
            m_a_tmp->actor = (m_a_tmp->actor) + 1;
          fprintf(movie_log, "%s", m_a_tmp->actor);
          m_a_tmp = m_a_tmp->next;
          comma++;

        }
        if (strcmp(answer, "Yes") == 0) {
        fseek(movie_log, f_location, SEEK_SET);
        update_mlog(&m_log, serial_number,title,genre,director,year,run_time,whole_string);
        fclose(movie_log);
        return;
        }

        fseek(movie_log, 0, SEEK_SET);
         string_input(movie_log, &check);
          for (int i = 0; i < add_m_number; string_input(movie_log, &check)){
            if (strcmp(check, "add") == 0){
              i++;
            }
            if (i == add_m_number)
              break;
          }
          fseek(movie_log, -4, SEEK_CUR);
          input_m_log(&m_log, movie_log);
    	fclose(movie_log);
      }
  }
void addd(director *d_log)
{
    char * whole_string = (char*)malloc(sizeof(char) * 100);// movie입력 전체를 한 문자열로 임시로 받음
    char * token = (char*)malloc(sizeof(char)*2);// movie 입력시 ,와 개행으로 문자열 나누기
    char * string_cut;
    char * serial_number = (char *)malloc(10);
    char * d_name = (char*)malloc(sizeof(char)*100);
    director tmp;
    struct d_title * move;
    struct d_title * d_t_tmp;
    char * s = (char*)malloc(sizeof(char)*100);
    char * birth = (char*)malloc(sizeof(char)*100);
    char *answer = (char *)malloc(sizeof(5));
    int comma =0;
    char *check;
    director *d_tmp = d_log;
    int count = 0;
    int f_location;
    d_title *director_title = d_log -> director_title;

    tmp.director_title = (struct d_title *)malloc(sizeof(struct d_title) * 1);

    *(token + 0) = ',';
    *(token + 1) = '\n';

    FILE * director_log;
    if ((director_log = fopen("director_log.txt", "a+")) == NULL)
    {
      printf("오류 : 파일을 열 수 없습니다. \n");
      }
      else
      {
        f_location = ftell(director_log);
        flush();
        printf("name > ");
        scanf("%[^\n]", d_name);
        changes(d_name);
    	  flush();
    	  printf("sex > ");
    	  scanf("%[^\n]", s);
        changes(s);
    	  flush();
    	  printf("birth > ");
    	  scanf("%[^\n]", birth);
        changes(birth);
    	  flush();

        printf("best_movies > ");
        scanf("%[^\n]", whole_string);
        changes(whole_string);
        flush();

        if(same_d_check(d_log, d_name)){
          printf("@@ You have the same record\n");
          while (1){
            if (strcmp(d_name, d_tmp -> d_name) == 0){
                  break;
           }
            d_tmp = d_tmp -> next;
            director_title = d_tmp -> director_title;
          }
          printf("%s:%s:", d_tmp -> serial_number, d_tmp -> d_name);
          printf("%s:%s:", d_tmp -> s, d_tmp -> birth);
          while (1){
            printf("%s, ", director_title -> title);
            if (director_title -> next -> title == NULL)
              break;
            director_title = director_title -> next;
          }

          printf("\n@@ Do you want to add anyway? (Yes / No) > ");
          scanf("%s", answer);
          flush();
        }

        if (strcmp(answer, "No") == 0){
          return;
        }

        else if (strcmp(answer, "Yes") == 0){
          while(1){
            if (strcmp(d_tmp -> d_name, d_name) == 0){
              strcpy(serial_number, d_tmp -> serial_number);
              break;
            }
            d_tmp = d_tmp -> next;
          }
          fprintf(director_log, "\n");
          fprintf(director_log, "update:");
          fprintf(director_log, "%s:", serial_number);
        }
        else{
          fprintf(director_log, "\n");
          fprintf(director_log, "add:");
          add_d_number++;
          fprintf(director_log, "%d:", add_d_number);
        }

        tmp.director_title -> title = strtok(whole_string, token);
        tmp.director_title -> link = NULL;
        tmp.director_title -> next = (struct d_title *)malloc(sizeof(struct d_title));
        move = tmp.director_title -> next;
        d_t_tmp = tmp.director_title;
        while ((string_cut = strtok(NULL, token))!=NULL)
    	{
        move -> title = string_cut;
        move -> link = NULL;
        move -> next =  (struct d_title *)malloc(sizeof(struct d_title));
        move = move -> next;
        move -> next = NULL;
    	}

      fprintf(director_log, "%s:%s:%s:", d_name, s, birth);

      while (d_t_tmp->next != NULL)
        {
          if (comma != 0)
            fprintf(director_log,", ");
          if (*(d_t_tmp->title) == ' ')
            d_t_tmp->title = (d_t_tmp->title) + 1;
          fprintf(director_log, "%s", d_t_tmp->title);
          d_t_tmp = d_t_tmp->next;
          comma++;
        }

        if (strcmp(answer, "Yes") == 0) {
        fseek(director_log, f_location, SEEK_SET);
        update_dlog(&d_log, serial_number, d_name,s,birth, whole_string);
        fclose(director_log);
        return;
        }

        fseek(director_log, 0, SEEK_SET);
         string_input(director_log, &check);
        for (int i = 0; i < add_d_number; string_input(director_log, &check)){
          if (strcmp(check, "add") == 0){
            i++;
          }
          if (i == add_d_number)
            break;
        }
        fseek(director_log, -4, SEEK_CUR);
        input_d_log(&d_log, director_log);
    	fclose(director_log);

      }
  }
void adda(actor *a_log)
{
  char * whole_string = (char*)malloc(sizeof(char) * 100);// movie입력 전체를 한 문자열로 임시로 받음
  char * token = (char*)malloc(sizeof(char)*2);// movie 입력시 ,와 개행으로 문자열 나누기
  char * string_cut;
  char * serial_number = (char *)malloc(10);
  char * a_name = (char*)malloc(sizeof(char)*100);
  actor tmp;
  struct a_title * move;
  struct a_title * a_t_tmp;
  char * s = (char*)malloc(sizeof(char)*100);
  char * birth = (char*)malloc(sizeof(char)*100);
  char *answer = (char *)malloc(sizeof(5));
  int comma =0;
  actor *a_tmp = a_log;
  char *check;
  int count = 0;
  int f_location;
  a_title *actor_title = a_log -> actor_title;
  tmp.actor_title = (struct a_title *)malloc(sizeof(struct a_title) * 1);

  *(token + 0) = ',';
  *(token + 1) = '\n';

  FILE * actor_log;
  if ((actor_log = fopen("actor_log.txt", "a+")) == NULL)
  {
    printf("오류 : 파일을 열 수 없습니다. \n");
    }
    else
    {
      f_location = ftell(actor_log);
      flush();
      printf("name > ");
      scanf("%[^\n]", a_name);
      changes(a_name);
      flush();
      printf("sex > ");
      scanf("%[^\n]", s);
      changes(s);
      flush();
      printf("birth > ");
      scanf("%[^\n]", birth);
      changes(birth);
      flush();
      printf("best_movies > ");
      scanf("%[^\n]", whole_string);
      changes(whole_string);
      flush();

      if(same_a_check(a_log, a_name)){
        printf("@@ You have the same record\n");
        while (1){
          if (strcmp(a_name, a_tmp -> a_name) == 0){
                break;
         }
          a_tmp = a_tmp -> next;
          actor_title = a_tmp -> actor_title;
        }
        printf("%s:%s:", a_tmp -> serial_number, a_tmp -> a_name);
        printf("%s:%s:", a_tmp -> s, a_tmp -> birth);
        while (1){
          printf("%s, ", actor_title -> title);
          if (actor_title -> next -> title == NULL)
            break;
          actor_title = actor_title -> next;
        }

        printf("\n@@ Do you want to add anyway? (Yes / No) > ");
        scanf("%s", answer);
        flush();
      }

      if (strcmp(answer, "No") == 0){
        return;
      }

      else if (strcmp(answer, "Yes") == 0){
        while(1){
          if (strcmp(a_tmp -> a_name, a_name) == 0){
            strcpy(serial_number, a_tmp -> serial_number);
            break;
          }
          a_tmp = a_tmp -> next;
        }
        fprintf(actor_log, "\n");
        fprintf(actor_log, "update:");
        fprintf(actor_log, "%s:", serial_number);
      }
      else{
        fprintf(actor_log, "\n");
        fprintf(actor_log, "add:");
        add_a_number++;
        fprintf(actor_log, "%d:", add_d_number);
      }

      tmp.actor_title -> title = strtok(whole_string, token);
      tmp.actor_title -> link = NULL;
      tmp.actor_title -> next = (struct a_title *)malloc(sizeof(struct a_title));
      move = tmp.actor_title -> next;
      a_t_tmp = tmp.actor_title;
      while ((string_cut = strtok(NULL, token))!=NULL)
    {
      move -> title = string_cut;
      move -> link = NULL;
      move -> next =  (struct a_title *)malloc(sizeof(struct a_title));
      move = move -> next;
      move -> next = NULL;
    }

    fprintf(actor_log, "%s:%s:%s:", a_name, s, birth);

    while (a_t_tmp->next != NULL)
      {
        if (comma != 0)
          fprintf(actor_log,", ");
        if (*(a_t_tmp->title) == ' ')
          a_t_tmp->title = (a_t_tmp->title) + 1;
        fprintf(actor_log, "%s", a_t_tmp->title);
        a_t_tmp = a_t_tmp->next;
        comma++;
      }

      if (strcmp(answer, "Yes") == 0) {
      fseek(actor_log, f_location, SEEK_SET);
      update_alog(&a_log, serial_number, a_name,s,birth, whole_string);
      fclose(actor_log);
      return;
      }

      fseek(actor_log, 0, SEEK_SET);
       string_input(actor_log, &check);
      for (int i = 0; i < add_a_number; string_input(actor_log, &check)){
        if (strcmp(check, "add") == 0){
          i++;
        }
        if (i == add_a_number)
          break;
      }
      fseek(actor_log, -4, SEEK_CUR);
      input_a_log(&a_log, actor_log);
    fclose(actor_log);

    }
}
void changes(char *old)
{
    int i=0;
    int j=0;
    char * token_bf;
    char * new;
    token_bf = (char*)malloc(sizeof(char)*1);
    *(token_bf) = ':';
    new = (char*)malloc(sizeof(char)*100);
    while (*(old+i) != '\0')
    {
      if (*(old+i) == ':')
      {
        *(new+j) = '?';
        *(new+(j+1)) = '?';
        *(new+(j+2)) = ';';
        j = j+3;
        i++;
      }
      else
      {
        *(new+j) = *(old+i);
        i++;
        j++;
      }
    }
    *(new+j) = '\0';
    strcpy(old, new);
    free(new);
  }
void inverse_ch(char *old)
{
    int i=0;
    int j=0;
    char * token_bf;
    char * new;
    token_bf = (char*)malloc(sizeof(char)*1);
    *(token_bf) = ':';
    new = (char*)malloc(sizeof(char)*100);
    while (*(old+i) != '\0')
    {
      if (*(old+i) == '?')
      {
        if(*(old + i + 1) == '?')
          if(*(old + i + 2) == ';'){
            *(new + j) = ':';
            j++;
            i = i + 3;
          }
      }
      else
      {
        *(new+j) = *(old+i);
        i++;
        j++;
      }
    }
    *(new+j) = '\0';
    strcpy(old, new);
    free(new);
  }
void quit(int signo)
{
  char a;
  printf("Get Interrupt Signal.\n");
  printf("Do you want to exit myMOVIE program? (Y/N)");
  scanf("%c", &a);
  flush();
  if (a=='Y')
    exit(0);
  else
  {

    return;
  }

}
void deletem(movie *m_log, char * num)
{
  int o_x=0;
  int count = 0;
  movie * testm = m_log;
  FILE * movie_log;
  if ((movie_log = fopen("movie_log.txt", "a")) == NULL)
  {
    printf("오류 : 파일을 열 수 없습니다. \n");
  }
  else
  {
    while (1)
    {
      if (strcmp(num, testm->serial_number )==0)
      {
        o_x=1;
        break;
      }
      if ((testm -> next) == NULL)
        break;
      testm = testm -> next;

    }
    if (o_x==0)
    {
      printf("No such record");
      return;
    }
    fprintf(movie_log,"\ndelete:%s::::",num);
    fseek(movie_log, 0, SEEK_SET);
    delete_mlog(m_log, num);
    printf("두번쩨ㅐ 무비 : %s\n", m_log -> next -> title);
  }
}
void deleted(director *d_log, char * num){
  int o_x=0;
  int count = 0;
  director * testd = d_log;
  FILE * director_log;
  if ((director_log = fopen("director_log.txt", "a")) == NULL)
  {
    printf("오류 : 파일을 열 수 없습니다. \n");
  }
  else
  {
    while (1)
    {
      if (strcmp(num, testd->serial_number )==0)
      {
        o_x=1;
        break;
      }
      if ((testd -> next) == NULL)
        break;
      testd = testd -> next;

    }
    if (o_x==0)
    {
      printf("No such record");
      return;
    }
    fprintf(director_log,"\ndelete:%s::::",num);
    fseek(director_log, 0, SEEK_SET);
    delete_dlog(d_log, num);
    printf("두번쩨ㅐ 디렉터 : %s\n", d_log -> d_name);
  }
}
void deletea(actor *a_log, char * num)
{
  int o_x=0;
  int count = 0;
  actor * testa = a_log;
  FILE * actor_log;
  if ((actor_log = fopen("actor_log.txt", "a")) == NULL)
  {
    printf("오류 : 파일을 열 수 없습니다. \n");
  }
  else
  {
    while (1)
    {
      if (strcmp(num, testa ->serial_number )==0)
      {
        o_x=1;
        break;
      }
      if ((testa -> next) == NULL)
        break;
      testa = testa -> next;

    }
    if (o_x==0)
    {
      printf("No such record");
      return;
    }
    fprintf(actor_log,"\ndelete:%s::::",num);
    fseek(actor_log, 0, SEEK_SET);
    delete_alog(a_log, num);
    printf("첫번쩨ㅐ 액터 : %s\n", a_log -> a_name);
  }
}
void add_mlog(movie ** m_log, char *serial_number,char *title,char *genre,char *movie_director,char *year,char *run_time,char * whole_string) // 인자로 시리얼넘버부터 액터까지 다 받음 char *형으로
{// 앞 m-log는 처음시작 주소, tmp_m_log는 연결해서 구조체 만들때 사용 -> next주소값을 만들때마다 넣어줘야함.

  movie ** tmp_m_log;
  char * token = (char*)malloc(sizeof(char)*2);
  char * string_cut;
  struct m_actor * move;
  struct m_actor * m_a_tmp;
  struct m_actor * space;
  *(token + 0) = ',';
  *(token + 1) = '\n';

  if (*m_log == NULL)// tmp_m_log이 마지막 구조체를 가리키게함.
  {
    (*m_log) = (movie *)malloc(sizeof(movie)*1);
    tmp_m_log = m_log;
  }
  else
    {
      tmp_m_log = &((*m_log) -> next);
      while(1)
      {
        if((*tmp_m_log)== NULL)
        break;
        (tmp_m_log) = &((*tmp_m_log) -> next);
        printf("(*tmp_m_log) =(*tmp_m_log) -> next걸림\n");
      }
      (*tmp_m_log)  = (movie*)malloc(sizeof(movie));

    }

  (*tmp_m_log) -> movie_actor = (m_actor *)malloc(sizeof(m_actor)*1);
  (*tmp_m_log) -> movie_director = (m_director *)malloc(sizeof(m_director)*1);
  (*tmp_m_log) -> serial_number = serial_number;
  (*tmp_m_log) -> title = title;
  (*tmp_m_log) -> genre = genre;
  (*tmp_m_log) -> movie_director -> director = movie_director; // 링크연결
  (*tmp_m_log) -> year = year;
  (*tmp_m_log) -> run_time = run_time;
  (*tmp_m_log) -> next = NULL;

  (*tmp_m_log) -> movie_actor -> actor = strtok(whole_string, token);// whole_string은 배우이름들 통째로
  (*tmp_m_log) -> movie_actor -> link = NULL; // 링크연결
  (*tmp_m_log) -> movie_actor -> next = (struct m_actor *)calloc(1, sizeof(struct m_actor));
  move = (*tmp_m_log) -> movie_actor -> next;
  space = (*tmp_m_log)-> movie_actor;
  while ((string_cut = strtok(NULL, token))!=NULL)
  {
    move -> actor = string_cut;
    move -> link = NULL;// 링크연결
    move -> next =  (struct m_actor *)calloc(1, sizeof(struct m_actor));
    move = move -> next;
    move -> next = NULL;
  }
  while (space->next != NULL)
   {
      if (*(space->actor) == ' ')
         space->actor = (space->actor) + 1;
      space = space->next;
   }
   printf("%s\n", (*tmp_m_log) -> title);

}
void delete_dlog(director * d_log, char *serial_number)
{

  director * tmp;
  tmp = d_log;

  if (strcmp(((tmp) -> serial_number), serial_number) == 0)
  {
    d_log = (d_log) -> next;
    return;
  }
  while (1)
  {
    if (strcmp(((tmp) -> next -> serial_number), serial_number) == 0)
    {
      if((tmp) -> next -> next == NULL)
      {
        (tmp) -> next = NULL;
        break;
      }
      (tmp) -> next = (tmp) -> next -> next;
      break;
    }
    (tmp) = (tmp) -> next;
  }
}
void delete_mlog(movie * m_log, char *serial_number)
{

  movie * tmp;
  tmp = m_log;

  if (strcmp(((tmp) -> serial_number), serial_number) == 0)
  {
    m_log = (m_log) -> next;
    return;
  }
  while (1)
  {

    if (strcmp(((tmp) -> next -> serial_number), serial_number) == 0)
    {
      if((tmp) -> next -> next == NULL)
      {
        (tmp) -> next = NULL;
        break;
      }
      (tmp) -> next = (tmp) -> next -> next;
      break;
    }
    (tmp) = (tmp) -> next;
  }
}
void delete_alog(actor * a_log, char *serial_number)
{

  actor * tmp;
  tmp = a_log;

  if (strcmp(((tmp) -> serial_number), serial_number) == 0)
  {
    a_log = (a_log) -> next;
    return;
  }
  while (1)
  {
    if (strcmp(((tmp) -> next -> serial_number), serial_number) == 0)
    {
      if((tmp) -> next -> next == NULL)
      {
        (tmp) -> next = NULL;
        break;
      }
      (tmp) -> next = (tmp) -> next -> next;
      break;
    }
    (tmp) = (tmp) -> next;
  }
}
void link_struct(movie *m_log, director *d_log, actor *a_log){
  movie *m_tmp = m_log;
  director *d_tmp = d_log;
  actor *a_tmp = a_log;

    while (1){
    link_md(m_tmp -> movie_director, d_log);
    if (m_tmp -> next == NULL)
      break;
    m_tmp = m_tmp -> next;
  }
  m_tmp = m_log;
    while (1){
    link_ma(m_tmp -> movie_actor, a_log);
    if (m_tmp -> next == NULL)
      break;
    m_tmp = m_tmp -> next;
  }
  m_tmp = m_log;
  while(1){
    link_dm(d_tmp -> director_title, m_log);
    if (d_tmp -> next == NULL)
      break;
    d_tmp = d_tmp -> next;
    }
    d_tmp = d_log;
    while(1){
      link_am(a_tmp -> actor_title, m_log);
      if (a_tmp -> next == NULL)
        break;
      a_tmp = a_tmp -> next;
      }
      a_tmp = a_log;
  }
void link_md(m_director *movie_director, director *d_log){
  director *d_tmp = d_log;
    while (1){
      if (strcmp(movie_director -> director, d_tmp -> d_name) == 0){
        movie_director -> link = d_tmp;
        break;
      }
      else if (d_tmp -> next == NULL)
        break;
      d_tmp = d_tmp -> next;
    }
}
void link_ma(m_actor *movie_actor, actor *a_log){
  actor *a_tmp = a_log;
    while (1){
      while (1){


        if (strcmp(movie_actor -> actor, a_tmp -> a_name) == 0){
        movie_actor -> link = a_tmp;
          break;
        }
        else if (a_tmp -> next == NULL)
          break;
        a_tmp = a_tmp -> next;
      }
      if ((movie_actor -> next -> actor) == NULL)
        break;
      movie_actor = movie_actor -> next;
      a_tmp = a_log;
    }
}
void link_dm(d_title *director_title, movie *m_log){
  movie *m_tmp = m_log;
    while (1){
      while (1){
        if (strcmp(director_title -> title, m_tmp -> title) == 0){
        director_title -> link = m_tmp;
          break;
        }
        else if (m_tmp -> next == NULL)
          break;
        m_tmp = m_tmp -> next;
      }
      if (director_title -> next -> title == NULL)
        break;
      director_title = director_title -> next;
      m_tmp = m_log;
    }
}
void link_am(a_title *actor_title, movie *m_log){
  movie *m_tmp = m_log;
    while (1){
      while (1){

        if (strcmp(actor_title -> title, m_tmp -> title) == 0){

        actor_title -> link = m_tmp;
          break;
        }
        else if (m_tmp -> next == NULL){

          break;
        }
        m_tmp = m_tmp -> next;
      }
      if (actor_title -> next -> title == NULL)
        break;
      actor_title = actor_title -> next;
      m_tmp = m_log;
    }
}
void memory_to_listm(movie * m_log)
{
  FILE *movie_p;
  movie_p = fopen("movie_list.txt", "w");

  movie * m_tmp = m_log;
  m_actor * m_a_tmp = m_log->movie_actor;



  while (1)
  {
    //printf("%s:", m_tmp->serial_number);
    fprintf(movie_p,"%s:", m_tmp->serial_number);
    fprintf(movie_p,"%s:", m_tmp->title);
    fprintf(movie_p,"%s:", m_tmp->genre);
    fprintf(movie_p,"%s:", m_tmp->movie_director->director);
    fprintf(movie_p,"%s:", m_tmp->year);
    fprintf(movie_p,"%s:", m_tmp->run_time);
    m_a_tmp = m_tmp->movie_actor;
    while(1)
    {
      fprintf(movie_p,"%s", m_a_tmp->actor);

      if ((m_a_tmp-> next -> next) == NULL)
        break;
      else
        fprintf(movie_p,",");

      m_a_tmp = m_a_tmp->next;
    }
    //printf("문제루프 넘어옴\n");

    if ((m_tmp->next)== NULL)
      break;
    else
      fprintf(movie_p,"\n");
    m_tmp = m_tmp->next;
  }
    fclose(movie_p);
}
void updatem(movie * m_log, char * string)
{
  FILE * movie_p;
  movie_p = fopen("movie_log.txt", "a");
  char * option = (char*)malloc(sizeof(char)*50);
  char * num = (char*)malloc(sizeof(char)*50);
  char * token2 = (char*)malloc(sizeof(char)*2);
  movie * m_tmp = m_log;
  int i=0;
  char * whole_string = (char*)malloc(sizeof(char) * 100);
  char * token = (char*)malloc(sizeof(char)*2);// actor 입력시 ,와 개행으로 문자열 나누기
  char * string_cut;
  char * all_string = (char*)malloc(sizeof(char) * 100);
  movie tmp;

  movie * ol_tmp = m_log;
  m_actor * ol_a_tmp;
  char * answer = (char*)malloc(sizeof(char)*10);

  struct m_actor * move;
  struct m_actor * m_a_tmp;
  char * title = (char*)malloc(sizeof(char)*100);
  char * genre = (char*)malloc(sizeof(char)*100);
  char * director = (char*)malloc(sizeof(char)*100);
  char * year = (char*)malloc(sizeof(char)*10);
  char * run_time = (char*)malloc(sizeof(char)*10);
  int comma =0;
  int pass =0;

  int t=0, g=0, d=0, y=0, r=0, a=0;
  int t_print =0, g_print =0, d_print =0, y_print =0, r_print =0, a_print =0;

  tmp.movie_actor = (struct m_actor *)malloc(sizeof(struct m_actor) * 1);

  *(token + 0) = ',';
  *(token + 1) = '\n';

  *(token2+0) = ' ';
  if (('0'<(*(string+0))) && ((*(string+0)) < '9'))
  {
      num = string;
      while(1)
      {
        if (strcmp(num, m_tmp->serial_number )==0)
          break;
        if ((m_tmp->next) == NULL)
        {
          printf("No such record");
          fclose(movie_p);
          return;
        }
        m_tmp = m_tmp -> next;
      }
      flush();
      printf("title > ");
      scanf("%[^\n]", title);
      changes(title);
      flush();
      printf("genre > ");
      scanf("%[^\n]", genre);
      changes(genre);
      flush();
      printf("director > ");
      scanf("%[^\n]", director);
      changes(director);
      flush();
      printf("year > ");
      scanf("%[^\n]", year);
      flush();
      printf("run time > ");
      scanf("%[^\n]", run_time);
      flush();
      printf("actors > ");
      scanf("%[^\n]", whole_string);
      changes(whole_string);
      strcpy(all_string, whole_string);
      flush();
      //중복처리
      while (1)
      {
        if(strcmp(ol_tmp ->title, title)== 0)
        {
          printf("You have the same record");
          printf("\n%s:", ol_tmp -> serial_number);
          printf("%s:", ol_tmp -> title);
          printf("%s:", ol_tmp -> genre);
          printf("%s:", ol_tmp -> movie_director -> director);
          printf("%s:", ol_tmp -> year);
          printf("%s", ol_tmp -> run_time);
          ol_a_tmp = ol_tmp -> movie_actor;
          while(1)
          {
            printf("%s", ol_a_tmp -> actor);
            if ((ol_a_tmp -> next -> next) == NULL)
              break;
            printf(", ");
            ol_a_tmp = ol_a_tmp -> next;
          }
          printf("\n@@Do you want to update anyway?(Yes/No)");
          scanf("%s", answer);
          if (strcmp(answer, "Yes")== 0)
          {
            pass = 1;

          }
          else if (strcmp(answer, "No")== 0)
          {
            fclose(movie_p);
            return;
          }
        }
        if (ol_tmp -> next == NULL)
          break;
        if (pass ==1)
          break;
        ol_tmp = ol_tmp -> next;
      }
      fprintf(movie_p,"\nupdate:");
      fprintf(movie_p,"%s:", m_tmp -> serial_number);
      fprintf(movie_p,"%s:", title);
      fprintf(movie_p,"%s:", genre);
      fprintf(movie_p,"%s:", director);
      fprintf(movie_p,"%s:", year);
      fprintf(movie_p,"%s:", run_time);

      tmp.movie_actor -> actor = strtok(whole_string, token);
      tmp.movie_actor -> link = NULL;
      tmp.movie_actor -> next = (struct m_actor *)malloc(sizeof(struct m_actor));
      move = tmp.movie_actor -> next;
      m_a_tmp = tmp.movie_actor;
      while ((string_cut = strtok(NULL, token))!=NULL)
    {
      move -> actor = string_cut;
      move -> link = NULL;
      move -> next =  (struct m_actor *)malloc(sizeof(struct m_actor));
      move = move -> next;
      move -> next = NULL;
    }

    while (m_a_tmp->next != NULL)
      {
        if (comma != 0)
          fprintf(movie_p,", ");
        if (*(m_a_tmp->actor) == ' ')
          m_a_tmp->actor = (m_a_tmp->actor) + 1;
        fprintf(movie_p, "%s", m_a_tmp->actor);
        m_a_tmp = m_a_tmp->next;
        comma++;

      }
      fseek(movie_p, 0 ,SEEK_SET);
      update_mlog(&m_log, m_tmp -> serial_number,title,genre,director,year,run_time,all_string);
      fclose(movie_p);
      return;


  }
  else
  {
    option = strtok(string, token2);
    num = strtok(NULL, token2);
    while(1)// ((m_tmp->next) != NULL)
    {
      if (strcmp(num, m_tmp->serial_number )==0)
        break;
      if ((m_tmp->next) == NULL)
      {
        printf("No such record");
        fclose(movie_p);
        return;
      }
      m_tmp = m_tmp -> next;
    }
    while (*(option+i) != '\0')
    {
      switch(*(option+i)){
          case 't':
            t=1;
            i++;
            break;
          case 'g':
            g=1;
            i++;
            break;
          case 'd':
            d=1;
            i++;
            break;
          case 'y':
            y=1;
            i++;
            break;
          case 'r':
            r=1;
            i++;
            break;
          case 'a':
            a=1;
            i++;
            break;
      }
    }
    while (t+g+d+y+r+a != 0)
    {
      if (t == 1)
      {
        flush();
        printf("title > ");
        scanf("%[^\n]", title);
        changes(title);
        t = 0;
        t_print =1;
        printf("yy");
      }
      else
      {
        strcpy(title, "=");
      }
      if (g == 1)
      {
        flush();
        printf("genre > ");
        scanf("%[^\n]", genre);
        changes(genre);
        g = 0;
        g_print =1;
      }
      else
      {
        strcpy(genre, "=");
      }
      if (d == 1)
      {
        flush();
        printf("director > ");
        scanf("%[^\n]", director);
        changes(director);
        d = 0;
        d_print =1;
      }
      else
      {
        strcpy(director, "=");
      }
      if (y == 1)
      {
        flush();
        printf("year > ");
        scanf("%[^\n]", year);
        y = 0 ;
        y_print =1;
      }
      else
      {
        strcpy(year, "=");
      }
      if (r == 1)
      {
        flush();
        printf("run time > ");
        scanf("%[^\n]", run_time);
        r =0;
        r_print =1;
      }
      else
      {
        strcpy(run_time, "=");
      }
      if (a == 1)
      {
        flush();
        printf("actors > ");
        scanf("%[^\n]", whole_string);
        changes(whole_string);
        strcpy(all_string, whole_string);
        flush();
        a =0;
        a_print =1;
      }
      else
      {
        strcpy(whole_string, "=");
      }
    }
  while (t_print ==1)
  {
      if(strcmp(ol_tmp ->title, title)== 0)
      {
        printf("You have the same record");
        printf("\n%s:", ol_tmp -> serial_number);
        printf("%s:", ol_tmp -> title);
        printf("%s:", ol_tmp -> genre);
        printf("%s:", ol_tmp -> movie_director -> director);
        printf("%s:", ol_tmp -> year);
        printf("%s:", ol_tmp -> run_time);
        ol_a_tmp = ol_tmp -> movie_actor;
        while(1)
        {
          printf("%s", ol_a_tmp -> actor);
          if ((ol_a_tmp -> next -> next) == NULL)
            break;
          printf(", ");
          ol_a_tmp = ol_a_tmp -> next;
        }
        printf("\n@@Do you want to update anyway?(Yes/No)");
        scanf("%s", answer);
        if (strcmp(answer, "Yes")==0)
        {
          pass =1;
        }
        else if (strcmp(answer, "No")==0){
          fclose(movie_p);
          return;
        }
      }
      if (ol_tmp -> next == NULL)
        break;
      if (pass ==1)
       break;
      ol_tmp = ol_tmp -> next;
    }


    while (t_print+g_print+d_print+y_print+r_print+a_print != 0)
    {
      fprintf(movie_p, "\nupdate:%s:", m_tmp -> serial_number);
      if (t_print == 1)
      {
        fprintf(movie_p, "%s:", title);
        t_print = 0;
      }
      else
      {
        fprintf(movie_p, "=:");
        t_print = 0;
      }
      if (g_print == 1)
      {
        fprintf(movie_p, "%s:", genre);
        g_print = 0;
      }
      else
      {
        fprintf(movie_p, "=:");
        g_print = 0;
      }
      if (d_print == 1)
      {
        fprintf(movie_p, "%s:", director);
        d_print = 0;
      }
      else
      {
        fprintf(movie_p, "=:");
        d_print = 0;
      }
      if (y_print == 1)
      {
        fprintf(movie_p, "%s:", year);
        y_print = 0;
      }
      else
      {
        fprintf(movie_p, "=:");
        y_print = 0;
      }
      if (r_print == 1)
      {
        fprintf(movie_p, "%s:", run_time);
        r_print = 0;
      }
      else
      {
        fprintf(movie_p, "=:");
        r_print = 0;
      }
      if (a_print == 1)
      {
        tmp.movie_actor -> actor = strtok(whole_string, token);
        tmp.movie_actor -> link = NULL;
        tmp.movie_actor -> next = (struct m_actor *)malloc(sizeof(struct m_actor));
        move = tmp.movie_actor -> next;
        m_a_tmp = tmp.movie_actor;
        while ((string_cut = strtok(NULL, token))!=NULL)
      {
        move -> actor = string_cut;
        move -> link = NULL;
        move -> next =  (struct m_actor *)malloc(sizeof(struct m_actor));
        move = move -> next;
        move -> next = NULL;
      }
      while (m_a_tmp->next != NULL)
        {
          if (comma != 0)
            fprintf(movie_p,", ");
          if (*(m_a_tmp->actor) == ' ')
            m_a_tmp->actor = (m_a_tmp->actor) + 1;
          fprintf(movie_p, "%s", m_a_tmp->actor);
          m_a_tmp = m_a_tmp->next;
          comma++;
        }
        a_print =0;
      }
      else
      {
        fprintf(movie_p, "=");
        a_print = 0;
      }
    }
    fseek(movie_p, 0 ,SEEK_SET);
    update_mlog(&m_log, m_tmp -> serial_number,title,genre,director,year,run_time,all_string);
    fclose(movie_p);

  }


}
void updated(director * d_log, char * string)
{
  FILE * movie_p;
  movie_p = fopen("director_log.txt", "a");
  char * option = (char*)malloc(sizeof(char)*50);
  char * num = (char*)malloc(sizeof(char)*50);
  char * token2 = (char*)malloc(sizeof(char)*2);
  director * d_tmp = d_log;
  int i=0;
  char * whole_string = (char*)malloc(sizeof(char) * 100);
  char * token = (char*)malloc(sizeof(char)*2);// actor 입력시 ,와 개행으로 문자열 나누기
  char * string_cut;
  char * all_string = (char*)malloc(sizeof(char) * 100);

  director tmp;

  director * ol_tmp = d_log;
  d_title * ol_m_tmp;
  char * answer = (char*)malloc(sizeof(char)*10);

  struct d_title * move;
  struct d_title * d_t_tmp;
  char * d_name = (char*)malloc(sizeof(char)*100);
  char * director = (char*)malloc(sizeof(char)*100);
  char * sex = (char*)malloc(sizeof(char)*100);
  char * birth = (char*)malloc(sizeof(char)*100);

  int comma =0;
  int pass =0;

  int n=0, s=0, b=0, m=0;
  int n_print =0, s_print =0, b_print =0, m_print =0;

  tmp.director_title = (struct d_title *)malloc(sizeof(struct d_title) * 1);

  *(token + 0) = ',';
  *(token + 1) = '\n';

  *(token2+0) = ' ';

  if (('0'<(*(string+0))) && ((*(string+0)) < '9'))
  {
      num = string;
      while(1)
      {
        if (strcmp(num, d_tmp->serial_number )==0)
          break;
        if ((d_tmp->next) == NULL)
        {
          printf("No such record");
          return;
        }
        d_tmp = d_tmp -> next;
      }
      flush();
      printf("name > ");
      scanf("%[^\n]", d_name);
      changes(d_name);
      flush();
      printf("sex > ");
      scanf("%[^\n]", sex);
      changes(sex);
      flush();
      printf("birth > ");
      scanf("%[^\n]", birth);
      changes(birth);
      flush();

      printf("movies > ");
      scanf("%[^\n]", whole_string);
      changes(whole_string);
      strcpy(all_string, whole_string);
      flush();
      //중복처리
      while (1)
      {
        if(strcmp(ol_tmp ->d_name, d_name)== 0)
        {
          printf("You have the same record");
          printf("\n%s:", ol_tmp -> serial_number);
          printf("%s:", ol_tmp -> d_name);
          printf("%s:", ol_tmp -> s);
          printf("%s:", ol_tmp -> birth);

          ol_m_tmp = ol_tmp -> director_title;
          while(1)
          {
            printf("%s", ol_m_tmp -> title);
            if ((ol_m_tmp -> next -> next) == NULL)
              break;
            printf(", ");
            ol_m_tmp = ol_m_tmp -> next;
          }
          printf("\n@@Do you want to update anyway?(Yes/No)");
          scanf("%s", answer);
          if (strcmp(answer, "Yes")== 0)
          {
            pass = 1;

          }
          else if (strcmp(answer, "No")== 0)
          {
            return;
          }
        }
        if (ol_tmp -> next == NULL)
          break;
        if (pass ==1)
          break;
        ol_tmp = ol_tmp -> next;
      }
      fprintf(movie_p,"\nupdate:");
      fprintf(movie_p,"%s:", ol_tmp -> serial_number);
      fprintf(movie_p,"%s:", d_name);
      fprintf(movie_p,"%s:", sex);
      fprintf(movie_p,"%s:", birth);


      tmp.director_title -> title = strtok(whole_string, token);
      tmp.director_title -> link = NULL;
      tmp.director_title -> next = (struct d_title *)malloc(sizeof(struct d_title));
      move = tmp.director_title -> next;
      d_t_tmp = tmp.director_title;
      while ((string_cut = strtok(NULL, token))!=NULL)
    {
      move -> title = string_cut;
      move -> link = NULL;
      move -> next =  (struct d_title *)malloc(sizeof(struct d_title));
      move = move -> next;
      move -> next = NULL;
    }

    while (d_t_tmp->next != NULL)
      {
        if (comma != 0)
          fprintf(movie_p,", ");
        if (*(d_t_tmp->title) == ' ')
          d_t_tmp->title = (d_t_tmp->title) + 1;
        fprintf(movie_p, "%s", d_t_tmp->title);
        d_t_tmp = d_t_tmp->next;
        comma++;

      }
      fseek(movie_p, 0 ,SEEK_SET);
      update_dlog(&d_log, d_tmp -> serial_number,d_name,sex,birth,all_string);
      fclose(movie_p);
      return;


  }

  else
  {
    option = strtok(string, token2);
    num = strtok(NULL, token2);
    while(1)// ((m_tmp->next) != NULL)
    {
      if (strcmp(num, d_tmp->serial_number )==0)
        break;
      if ((d_tmp->next) == NULL)
      {
        printf("No such record");
        return;
      }
      d_tmp = d_tmp -> next;
    }
    while (*(option+i) != '\0')
    {
      switch(*(option+i)){
          case 'n':
            n=1;
            i++;
            break;
          case 's':
            s=1;
            i++;
            break;
          case 'b':
            b=1;
            i++;
            break;
          case 'm':
            m=1;
            i++;
            break;

      }
    }
    while (n+s+b+m != 0)
    {
      if (n == 1)
      {
        flush();
        printf("name > ");
        scanf("%[^\n]", d_name);
        changes(d_name);
        n = 0;
        n_print =1;

      }
      else
      {
        strcpy(d_name, "=");
      }
      if (s == 1)
      {
        flush();
        printf("sex > ");
        scanf("%[^\n]", sex);
        changes(sex);
        s = 0;
        s_print =1;
      }
      else
      {
        strcpy(sex, "=");
      }
      if (b == 1)
      {
        flush();
        printf("birth > ");
        scanf("%[^\n]", birth);
        changes(birth);
        b = 0;
        b_print =1;
      }
      else
      {
        strcpy(birth, "=");
      }
      if (m == 1)
      {
        flush();
        printf("movies > ");
        scanf("%[^\n]", whole_string);
        strcpy(all_string, whole_string);
        m = 0 ;
        m_print =1;
      }
      else
      {
        strcpy(whole_string, "=");
      }

    }
      while (n_print ==1)
      {
          if(strcmp(ol_tmp ->d_name,d_name)== 0)
          {
            printf("You have the same record");
            printf("\n%s:", ol_tmp -> serial_number);
            printf("%s:", ol_tmp -> d_name);
            printf("%s:", ol_tmp -> s);
            printf("%s:", ol_tmp -> birth);

            ol_m_tmp = ol_tmp -> director_title;
            while(1)
            {
              printf("%s", ol_m_tmp -> title);
              if ((ol_m_tmp -> next -> next) == NULL)
                break;
              printf(", ");
              ol_m_tmp = ol_m_tmp -> next;
            }
            printf("\n@@Do you want to update anyway?(Yes/No)");
            scanf("%s", answer);
            if (strcmp(answer, "Yes")==0)
            {
              pass =1;
            }
            else if (strcmp(answer, "No")==0)
              return;
          }
          if (ol_tmp -> next == NULL)
            break;
          if (pass ==1)
           break;
          ol_tmp = ol_tmp -> next;
        }


    while (n_print+s_print+b_print+m_print != 0)
    {
      fprintf(movie_p, "\nupdate:%s:", d_tmp -> serial_number);
      if (n_print == 1)
      {
        fprintf(movie_p, "%s:", d_name);
        n_print = 0;
      }
      else
      {
        fprintf(movie_p, "=:");
        n_print = 0;
      }
      if (s_print == 1)
      {
        fprintf(movie_p, "%s:", sex);
        s_print = 0;
      }
      else
      {
        fprintf(movie_p, "=:");
        s_print = 0;
      }
      if (b_print == 1)
      {
        fprintf(movie_p, "%s:", birth);
        b_print = 0;
      }
      else
      {
        fprintf(movie_p, "=:");
        b_print = 0;
      }

      if (m_print == 1)
      {
        tmp.director_title -> title = strtok(whole_string, token);
        tmp.director_title -> link = NULL;
        tmp.director_title -> next = (struct d_title *)malloc(sizeof(struct d_title));
        move = tmp.director_title -> next;
        d_t_tmp = tmp.director_title;
        while ((string_cut = strtok(NULL, token))!=NULL)
      {
        move -> title = string_cut;
        move -> link = NULL;
        move -> next =  (struct d_title *)malloc(sizeof(struct d_title));
        move = move -> next;
        move -> next = NULL;
      }
      while (d_t_tmp->next != NULL)
        {
          if (comma != 0)
            fprintf(movie_p,", ");
          if (*(d_t_tmp->title) == ' ')
            d_t_tmp->title = (d_t_tmp->title) + 1;
          fprintf(movie_p, "%s", d_t_tmp->title);
          d_t_tmp = d_t_tmp->next;
          comma++;
        }
        m_print =0;
      }
      else
      {
        fprintf(movie_p, "=");
        m_print = 0;
      }
    }
    fseek(movie_p, 0 ,SEEK_SET);
    update_dlog(&d_log, d_tmp -> serial_number,d_name,sex,birth,all_string);
    fclose(movie_p);
  }
}
void updatea(actor * a_log, char * string)
{
  FILE * movie_p;
  movie_p = fopen("actor_log.txt", "a+");
  char * option = (char*)malloc(sizeof(char)*50);
  char * num = (char*)malloc(sizeof(char)*50);
  char * token2 = (char*)malloc(sizeof(char)*2);
  actor * a_tmp = a_log;
  int i=0;
  char * whole_string = (char*)malloc(sizeof(char) * 100);
  char * token = (char*)malloc(sizeof(char)*2);// actor 입력시 ,와 개행으로 문자열 나누기
  char * string_cut;
  char * all_string = (char*)malloc(sizeof(char) * 100);


  actor tmp;

  actor * ol_tmp = a_log;
  a_title * ol_m_tmp;
  char * answer = (char*)malloc(sizeof(char)*10);

  struct a_title * move;
  struct a_title * a_t_tmp;
  char * a_name = (char*)malloc(sizeof(char)*100);

  char * sex = (char*)malloc(sizeof(char)*100);
  char * birth = (char*)malloc(sizeof(char)*100);

  int comma =0;
  int pass =0;

  int n=0, s=0, b=0, m=0;
  int n_print =0, s_print =0, b_print =0, m_print =0;

  tmp.actor_title = (struct a_title *)malloc(sizeof(struct a_title) * 1);

  *(token + 0) = ',';
  *(token + 1) = '\n';

  *(token2+0) = ' ';

  if (('0'<(*(string+0))) && ((*(string+0)) < '9'))
  {
      num = string;
      while(1)
      {
        if (strcmp(num, a_tmp->serial_number )==0)
          break;
        if ((a_tmp->next) == NULL)
        {
          printf("No such record");
          return;
        }
        a_tmp = a_tmp -> next;
      }
      flush();
      printf("name > ");
      scanf("%[^\n]", a_name);
      changes(a_name);
      flush();
      printf("sex > ");
      scanf("%[^\n]", sex);
      changes(sex);
      flush();
      printf("birth > ");
      scanf("%[^\n]", birth);
      changes(birth);
      flush();

      printf("movies > ");
      scanf("%[^\n]", whole_string);
      changes(whole_string);
      strcpy(all_string, whole_string);
      flush();
      //중복처리
      while (1)
      {
        if(strcmp(ol_tmp ->a_name, a_name)== 0)
        {
          printf("You have the same record");
          printf("\n%s:", ol_tmp -> serial_number);
          printf("%s:", ol_tmp -> a_name);
          printf("%s:", ol_tmp -> s);
          printf("%s:", ol_tmp -> birth);

          ol_m_tmp = ol_tmp -> actor_title;
          while(1)
          {
            printf("%s", ol_m_tmp -> title);
            if ((ol_m_tmp -> next -> next) == NULL)
              break;
            printf(", ");
            ol_m_tmp = ol_m_tmp -> next;
          }
          printf("\n@@Do you want to update anyway?(Yes/No)");
          scanf("%s", answer);
          if (strcmp(answer, "Yes")== 0)
          {
            pass = 1;

          }
          else if (strcmp(answer, "No")== 0)
          {
            return;
          }
        }
        if (ol_tmp -> next == NULL)
          break;
        if (pass ==1)
          break;
        ol_tmp = ol_tmp -> next;
      }
      fprintf(movie_p,"\nupdate:");
      fprintf(movie_p,"%s:", ol_tmp -> serial_number);
      fprintf(movie_p,"%s:", a_name);
      fprintf(movie_p,"%s:", sex);
      fprintf(movie_p,"%s:", birth);


      tmp.actor_title -> title = strtok(whole_string, token);
      tmp.actor_title -> link = NULL;
      tmp.actor_title -> next = (struct a_title *)malloc(sizeof(struct a_title));
      move = tmp.actor_title -> next;
      a_t_tmp = tmp.actor_title;
      while ((string_cut = strtok(NULL, token))!=NULL)
    {
      move -> title = string_cut;
      move -> link = NULL;
      move -> next =  (struct a_title *)malloc(sizeof(struct a_title));
      move = move -> next;
      move -> next = NULL;
    }

    while (a_t_tmp->next != NULL)
      {
        if (comma != 0)
          fprintf(movie_p,", ");
        if (*(a_t_tmp->title) == ' ')
          a_t_tmp->title = (a_t_tmp->title) + 1;
        fprintf(movie_p, "%s", a_t_tmp->title);
        a_t_tmp = a_t_tmp->next;
        comma++;

      }
      fseek(movie_p, 0 ,SEEK_SET);
      update_alog(&a_log, a_tmp -> serial_number,a_name,sex,birth,all_string);
      fclose(movie_p);
      return;


  }

  else
  {
    option = strtok(string, token2);
    num = strtok(NULL, token2);
    while(1)// ((m_tmp->next) != NULL)
    {
      if (strcmp(num, a_tmp->serial_number )==0)
        break;
      if ((a_tmp->next) == NULL)
      {
        printf("No such record");
        return;
      }
      a_tmp = a_tmp -> next;
    }
    while (*(option+i) != '\0')
    {
      switch(*(option+i)){
          case 'n':
            n=1;
            i++;
            break;
          case 's':
            s=1;
            i++;
            break;
          case 'b':
            b=1;
            i++;
            break;
          case 'm':
            m=1;
            i++;
            break;

      }
    }
    while (n+s+b+m != 0)
    {
      if (n == 1)
      {
        flush();
        printf("name > ");
        scanf("%[^\n]", a_name);
        changes(a_name);
        n = 0;
        n_print =1;

      }
      else
      {
        strcpy(a_name, "=");
      }
      if (s == 1)
      {
        flush();
        printf("sex > ");
        scanf("%[^\n]", sex);
        changes(sex);
        s = 0;
        s_print =1;
      }
      else
      {
        strcpy(sex, "=");
      }
      if (b == 1)
      {
        flush();
        printf("birth > ");
        scanf("%[^\n]", birth);
        changes(birth);
        b = 0;
        b_print =1;
      }
      else
      {
        strcpy(birth, "=");
      }
      if (m == 1)
      {
        flush();
        printf("movies > ");
        scanf("%[^\n]", whole_string);
        strcpy(all_string, whole_string);
        m = 0 ;
        m_print =1;
      }
      else
      {
        strcpy(whole_string, "=");
      }

    }
      while (n_print ==1)
      {
          if(strcmp(ol_tmp ->a_name,a_name)== 0)
          {
            printf("You have the same record");
            printf("\n%s:", ol_tmp -> serial_number);
            printf("%s:", ol_tmp -> a_name);
            printf("%s:", ol_tmp -> s);
            printf("%s:", ol_tmp -> birth);

            ol_m_tmp = ol_tmp -> actor_title;
            while(1)
            {
              printf("%s", ol_m_tmp -> title);
              if ((ol_m_tmp -> next -> next) == NULL)
                break;
              printf(", ");
              ol_m_tmp = ol_m_tmp -> next;
            }
            printf("\n@@Do you want to update anyway?(Yes/No)");
            scanf("%s", answer);
            if (strcmp(answer, "Yes")==0)
            {
              pass =1;
            }
            else if (strcmp(answer, "No")==0)
              return;
          }
          if (ol_tmp -> next == NULL)
            break;
          if (pass ==1)
           break;
          ol_tmp = ol_tmp -> next;
        }


    while (n_print+s_print+b_print+m_print != 0)
    {
      fprintf(movie_p, "\nupdate:%s:", a_tmp -> serial_number);
      if (n_print == 1)
      {
        fprintf(movie_p, "%s:", a_name);
        n_print = 0;
      }
      else
      {
        fprintf(movie_p, "=:");
        n_print = 0;
      }
      if (s_print == 1)
      {
        fprintf(movie_p, "%s:", sex);
        s_print = 0;
      }
      else
      {
        fprintf(movie_p, "=:");
        s_print = 0;
      }
      if (b_print == 1)
      {
        fprintf(movie_p, "%s:", birth);
        b_print = 0;
      }
      else
      {
        fprintf(movie_p, "=:");
        b_print = 0;
      }

      if (m_print == 1)
      {
        tmp.actor_title -> title = strtok(whole_string, token);
        tmp.actor_title -> link = NULL;
        tmp.actor_title -> next = (struct a_title *)malloc(sizeof(struct a_title));
        move = tmp.actor_title -> next;
        a_t_tmp = tmp.actor_title;
        while ((string_cut = strtok(NULL, token))!=NULL)
      {
        move -> title = string_cut;
        move -> link = NULL;
        move -> next =  (struct a_title *)malloc(sizeof(struct a_title));
        move = move -> next;
        move -> next = NULL;
      }
      while (a_t_tmp->next != NULL)
        {
          if (comma != 0)
            fprintf(movie_p,", ");
          if (*(a_t_tmp->title) == ' ')
            a_t_tmp->title = (a_t_tmp->title) + 1;
          fprintf(movie_p, "%s", a_t_tmp->title);
          a_t_tmp = a_t_tmp->next;
          comma++;
        }
        m_print =0;
      }
      else
      {
        fprintf(movie_p, "=");
        m_print = 0;
      }
    }
    fseek(movie_p, 0 ,SEEK_SET);
    update_alog(&a_log, a_tmp -> serial_number,a_name,sex,birth,all_string);
    fclose(movie_p);
  }
}
void savem(movie * m_log)
{
  char space;
  char *s_option = (char *)calloc(5, sizeof(char));
  char *filename = (char *)calloc(30, sizeof(char));
  char *dump = (char *)calloc(5, sizeof(char));
  int t=0, g=0, d=0, y=0, r=0, a=0;
  int i =1;
  int comma = 0;
  movie * m_tmp = m_log;
  m_actor * m_a_tmp = m_log -> movie_actor;

  space = getchar();
  if (space == ' ')
  {
    scanf("%s", s_option);
    if (strcmp(s_option, "-f") == 0)
    {
      space = getchar();
      scanf("%s", filename);
      printf("파일이름만");

      FILE * movie_p;
      movie_p = fopen("a.txt", "w");

      while (1)
      {
        fprintf(movie_p,"%s:", m_tmp->serial_number);
        fprintf(movie_p,"%s:", m_tmp->title);
        fprintf(movie_p,"%s:", m_tmp->genre);
        fprintf(movie_p,"%s:", m_tmp->movie_director->director);
        fprintf(movie_p,"%s:", m_tmp->year);
        fprintf(movie_p,"%s:", m_tmp->run_time);
        m_a_tmp = m_tmp->movie_actor;
        while(1)
        {
          fprintf(movie_p,"%s", m_a_tmp->actor);

          if ((m_a_tmp-> next -> next) == NULL)
            break;
          else
            fprintf(movie_p,",");

          m_a_tmp = m_a_tmp->next;
        }

        if ((m_tmp->next)== NULL)
          break;
        else
          fprintf(movie_p,"\n");
        m_tmp = m_tmp->next;
      }
      fclose(movie_p);
      rename("a.txt", filename);

    }
    else
    {
      space = getchar();
      FILE * movie_p;

      if (space == '\n')
      {
        char * textfile = "./movie_list.txt";
        int f_ok = F_OK;
        char * aft_change;
        aft_change = timefilem();
        if (access(textfile, f_ok) == 0)
        {
          rename("movie_list.txt", aft_change);

        }
        movie_p = fopen("movie_list.txt", "w");


          while (*(s_option+i) != '\0')
          {
            switch(*(s_option+i)){
                case 't':
                  t=1;
                  i++;
                  break;
                case 'g':
                  g=1;
                  i++;
                  break;
                case 'd':
                  d=1;
                  i++;
                  break;
                case 'y':
                  y=1;
                  i++;
                  break;
                case 'r':
                  r=1;
                  i++;
                  break;
                case 'a':
                  a=1;
                  i++;
                  break;
            }
          }
          while (1)
          {
            if (t ==1)
            {
              fprintf(movie_p,"title : %s\n", m_tmp -> title);
            }
            if (g ==1)
            {
              fprintf(movie_p,"genre : %s\n", m_tmp -> genre);
            }
            if (d ==1)
            {
              fprintf(movie_p,"director : %s\n", m_tmp -> movie_director -> director);
            }
            if (y ==1)
            {
              fprintf(movie_p,"year : %s\n", m_tmp -> year);
            }
            if (r ==1)
            {
              fprintf(movie_p,"run_time : %s\n", m_tmp -> run_time);
            }
            if (a ==1)
            {
              fprintf(movie_p, "actor : ");
              m_a_tmp = m_tmp -> movie_actor;
              while(1)
              {

                if (comma != 0)
                  fprintf(movie_p, ", ");
                fprintf(movie_p, "%s", m_a_tmp -> actor);
                comma++;
                if ((m_a_tmp -> next -> next) == NULL)
                  break;
                m_a_tmp = m_a_tmp -> next;
              }
              comma = 0;
              fprintf(movie_p,"\n");
            }
            if (m_tmp -> next == NULL)
              break;
            m_tmp = m_tmp -> next;

          }
          fclose(movie_p);
      }

      else
      {
        movie_p = fopen("a.txt", "w");
        scanf("%s %s", dump, filename);
        printf("둘다");

        while (*(s_option+i) != '\0')
        {
          switch(*(s_option+i)){
              case 't':
                t=1;
                i++;
                break;
              case 'g':
                g=1;
                i++;
                break;
              case 'd':
                d=1;
                i++;
                break;
              case 'y':
                y=1;
                i++;
                break;
              case 'r':
                r=1;
                i++;
                break;
              case 'a':
                a=1;
                i++;
                break;
          }
        }
        while (1)
        {
          if (t ==1)
          {
            fprintf(movie_p,"title : %s\n", m_tmp -> title);
          }
          if (g ==1)
          {
            fprintf(movie_p,"genre : %s\n", m_tmp -> genre);
          }
          if (d ==1)
          {
            fprintf(movie_p,"director : %s\n", m_tmp -> movie_director -> director);
          }
          if (y ==1)
          {
            fprintf(movie_p,"year : %s\n", m_tmp -> year);
          }
          if (r ==1)
          {
            fprintf(movie_p,"run_time : %s\n", m_tmp -> run_time);
          }
          if (a ==1)
          {
            fprintf(movie_p, "actor : ");
            while(1)
            {

              if (comma != 0)
                fprintf(movie_p, ", ");
              fprintf(movie_p, "%s", m_a_tmp -> actor);
              comma++;
              if ((m_a_tmp -> next -> next) == NULL)
                break;
              m_a_tmp = m_a_tmp -> next;
            }
            fprintf(movie_p,"\n");
            comma = 0;
          }
          if (m_tmp -> next == NULL)
            break;
          m_tmp = m_tmp -> next;
          m_a_tmp = m_tmp -> movie_actor;

        }
        fclose(movie_p);
        rename("a.txt", filename);



      }

    }
  }
  else
  {
    printf("짧");
    FILE * movie_p;
    char * textfile = "./movie_list.txt";
    int f_ok = F_OK;
    char * aft_change;
    aft_change = timefilem();
    if (access(textfile, f_ok) == 0)
    {
      rename("movie_list.txt", aft_change);

    }
    movie_p = fopen("movie_list.txt", "w");
    while (1)
    {
      fprintf(movie_p,"%s:", m_tmp->serial_number);
      fprintf(movie_p,"%s:", m_tmp->title);
      fprintf(movie_p,"%s:", m_tmp->genre);
      fprintf(movie_p,"%s:", m_tmp->movie_director->director);
      fprintf(movie_p,"%s:", m_tmp->year);
      fprintf(movie_p,"%s:", m_tmp->run_time);
      m_a_tmp = m_tmp->movie_actor;
      while(1)
      {
        fprintf(movie_p,"%s", m_a_tmp->actor);

        if ((m_a_tmp-> next -> next) == NULL)
          break;
        else
          fprintf(movie_p,",");

        m_a_tmp = m_a_tmp->next;
      }

      if ((m_tmp->next)== NULL)
        break;
      else
        fprintf(movie_p,"\n");
      m_tmp = m_tmp->next;
    }

    printf("끝");
    fclose(movie_p);
    rename("movie_list.txt", "movie_list.txt");
  }// 짧

}
char * timefilem(void)
{
  char * aft_string;
  aft_string = (char *)malloc(sizeof(char)*50);
  struct tm * t;
  time_t tp;
  tp = time(NULL);
  t = localtime(&tp);
  sprintf(aft_string,"movie_list.%d%02d%02d%02d%02d", t -> tm_year + 1900, t -> tm_mon +1, t -> tm_mday, t -> tm_hour, t -> tm_min);
  return aft_string;
}
void saved(director * d_log)
{
  char space;
  char *s_option = (char *)calloc(5, sizeof(char));
  char *filename = (char *)calloc(30, sizeof(char));
  char *dump = (char *)calloc(5, sizeof(char));
  int n=0, s=0, b=0, m=0;
  int i =1;
  int comma = 0;
  director * d_tmp = d_log;
  d_title * d_t_tmp = d_log -> director_title;

  space = getchar();
  if (space == ' ')
  {
    scanf("%s", s_option);
    if (strcmp(s_option, "-f") == 0)
    {
      space = getchar();
      scanf("%s", filename);
      printf("파일이름만");

      FILE * movie_p;
      movie_p = fopen("a.txt", "w");

      while (1)
      {
        fprintf(movie_p,"%s:", d_tmp->serial_number);
        fprintf(movie_p,"%s:", d_tmp->d_name);
        fprintf(movie_p,"%s:", d_tmp->s);
        fprintf(movie_p,"%s:", d_tmp->birth);

        d_t_tmp = d_tmp->director_title;
        while(1)
        {
          fprintf(movie_p,"%s", d_t_tmp->title);

          if ((d_t_tmp-> next -> next) == NULL)
            break;
          else
            fprintf(movie_p,",");

          d_t_tmp = d_t_tmp->next;
        }

        if ((d_tmp->next)== NULL)
          break;
        else
          fprintf(movie_p,"\n");
        d_tmp = d_tmp->next;
      }
      fclose(movie_p);
      rename("a.txt", filename);

    }
    else
    {
      space = getchar();
      FILE * movie_p;

      if (space == '\n')
      {
        char * textfile = "./director_list.txt";
        int f_ok = F_OK;
        char * aft_change;
        aft_change = timefiled();
        if (access(textfile, f_ok) == 0)
        {
          rename("director_list.txt", aft_change);

        }
        movie_p = fopen("director_list.txt", "w");


          while (*(s_option+i) != '\0')
          {
            switch(*(s_option+i)){
                case 'n':
                  n=1;
                  i++;
                  break;
                case 's':
                  s=1;
                  i++;
                  break;
                case 'b':
                  b=1;
                  i++;
                  break;
                case 'm':
                  m=1;
                  i++;
                  break;

            }
          }
          while (1)
          {
            if (n ==1)
            {
              fprintf(movie_p,"name : %s\n", d_tmp -> d_name);
            }
            if (s ==1)
            {
              fprintf(movie_p,"sex : %s\n", d_tmp -> s);
            }
            if (b ==1)
            {
              fprintf(movie_p,"birth : %s\n", d_tmp -> birth);
            }

            if (m ==1)
            {
              fprintf(movie_p, "movie : ");
              d_t_tmp = d_tmp -> director_title;
              while(1)
              {

                if (comma != 0)
                  fprintf(movie_p, ", ");
                fprintf(movie_p, "%s", d_t_tmp -> title);
                comma++;
                if ((d_t_tmp -> next -> next) == NULL)
                  break;
                d_t_tmp = d_t_tmp -> next;
              }
              comma = 0;
              fprintf(movie_p,"\n");
            }
            if (d_tmp -> next == NULL)
              break;
            d_tmp = d_tmp -> next;

          }
          fclose(movie_p);
      }
      else
      {
        movie_p = fopen("a.txt", "w");
        scanf("%s %s", dump, filename);
        printf("둘다");

        while (*(s_option+i) != '\0')
        {
          switch(*(s_option+i)){
              case 'n':
                n=1;
                i++;
                break;
              case 's':
                s=1;
                i++;
                break;
              case 'b':
                b=1;
                i++;
                break;
              case 'm':
                m=1;
                i++;
                break;

          }
        }
        while (1)
        {
          if (n ==1)
          {
            fprintf(movie_p,"name : %s\n", d_tmp -> d_name);
          }
          if (s ==1)
          {
            fprintf(movie_p,"sex : %s\n", d_tmp -> s);
          }
          if (b ==1)
          {
            fprintf(movie_p,"birth : %s\n", d_tmp -> birth);
          }

          if (m ==1)
          {
            fprintf(movie_p, "movie : ");
            while(1)
            {

              if (comma != 0)
                fprintf(movie_p, ", ");
              fprintf(movie_p, "%s", d_t_tmp -> title);
              comma++;
              if ((d_t_tmp -> next -> next) == NULL)
                break;
              d_t_tmp = d_t_tmp -> next;
            }
            fprintf(movie_p,"\n");
            comma = 0;
          }
          if (d_tmp -> next == NULL)
            break;
          d_tmp = d_tmp -> next;
          d_t_tmp = d_tmp -> director_title;

        }
        fclose(movie_p);
        rename("a.txt", filename);



      }
    }
  }
  else
  {
    printf("짧");
    FILE * movie_p;
    char * textfile = "./director_list.txt";
    int f_ok = F_OK;
    char * aft_change;
    aft_change = timefiled();
    if (access(textfile, f_ok) == 0)
    {
      rename("director_list.txt", aft_change);

    }
    movie_p = fopen("director_list.txt", "w");
    while (1)
    {
      fprintf(movie_p,"%s:", d_tmp->serial_number);
      fprintf(movie_p,"%s:", d_tmp->d_name);
      fprintf(movie_p,"%s:", d_tmp->s);
      fprintf(movie_p,"%s:", d_tmp->birth);

      d_t_tmp = d_tmp->director_title;
      while(1)
      {
        fprintf(movie_p,"%s", d_t_tmp->title);

        if ((d_t_tmp-> next -> next) == NULL)
          break;
        else
          fprintf(movie_p,",");

        d_t_tmp = d_t_tmp->next;
      }

      if ((d_tmp->next)== NULL)
        break;
      else
        fprintf(movie_p,"\n");
      d_tmp = d_tmp->next;
    }
    fclose(movie_p);
  }// 짧
}
char * timefiled(void)
{
  char * aft_string;
  aft_string = (char *)malloc(sizeof(char)*50);
  struct tm * t;
  time_t tp;
  tp = time(NULL);
  t = localtime(&tp);
  sprintf(aft_string,"director_list.%d%02d%02d%02d%02d", t -> tm_year + 1900, t -> tm_mon +1, t -> tm_mday, t -> tm_hour, t -> tm_min);
  return aft_string;
}
