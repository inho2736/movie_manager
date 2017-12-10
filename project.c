#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
int add_m_number = 0; //add되는 태그번호 기록
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
}d_title;       //감도 구조체 속 영화 리스트
typedef struct director{
  char * serial_number;
  char * d_name;
  char * s;
  char * birth;
  struct d_title * director_title;
  struct director * next;
}director;    //감독 구조체
typedef struct m_actor{
  char * actor;
  struct actor * link;
  struct m_actor * next;
}m_actor;   //영화 구조체 속 배우 리스트
typedef struct m_director{
  char * director;
  director *link;
}m_director;    //영화 구조체 속 감독
typedef struct movie{
  char * serial_number;
  char * title;
  char * genre;
  struct m_director * movie_director;
  char * year;
  char * run_time;
  struct m_actor * movie_actor;
  struct movie * next;
}movie;   //영화 구조체
typedef struct a_title{
  char * title;
  struct movie * link;
  struct a_title * next;
}a_title;   //배우 구조체 속 영화 리스트
typedef struct actor{
  char * serial_number;
  char * a_name;
  char * s;
  char * birth;
  struct a_title * actor_title;
  struct actor * next;
} actor;    //배우 구조체

void deletem(movie *, char *, movie **);          //함수선언
void command(movie *, actor *, director *, movie **, actor **, director **);
void addd(director *);
void adda(actor *);
void addm(movie *, director *, actor *);
void input_m_log(movie **, FILE *);
void input_log(movie **, actor **, director **);
void string_input(FILE *, char **);
void add_mlog(movie **, char*, char*, char*, char*, char*, char*, char*);
void delete_mlog(movie * , char *, movie **);
void update_mlog(movie * , char *,char *,char *,char *,char *,char *,char *);
void input_d_log(director **, FILE *);
void add_dlog(director **, char *, char *, char *, char *, char *);
void delete_dlog(director *, char *, director **);
void input_a_log(actor **, FILE *);
void add_alog(actor **, char *, char *, char *, char *, char *);
void delete_alog(actor *, char *, actor **);
void update_dlog(director *, char *,char *,char *,char *, char *);
void update_alog(actor * , char *, char *, char *,char *, char * );
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
void deletea(actor *, char *, actor **);
void deleted(director *, char *, director **);
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
void savea(actor *);
char* timefilem(void);
char* timefiled(void);
char * timefilea(void);
void memory_to_listd(director *);
void memory_to_lista(actor *);
void end(movie *, actor *, director *);
int main(void)
{
  movie *m_log = (movie *)malloc(sizeof(movie));  //movie, actor, director에 해당하는 구조체 포인터 생성
  m_log = NULL;
  actor *a_log = (actor *)malloc(sizeof(actor));
  a_log = NULL;
  director *d_log = (director *)malloc(sizeof(director));
  d_log = NULL;
  signal(SIGINT, (void*)quit);    //ctrl + c 를 누르면 물어보도록

  input_log(&m_log, &a_log, &d_log);    //로그 파일 입력받기
  link_struct(m_log, d_log, a_log);     //구조체 간의 연결(감독의 - 영화구조체, 배우의 영화 - 영화구조체 등)
  memory_to_listm(m_log);     //로그파일 받자마자 리스트파일 만들기
  memory_to_listd(d_log);
  memory_to_lista(a_log);


  start();        //시작문 출력
  while(1){
  printf("(movie) ");
  command(m_log, a_log, d_log, &m_log, &a_log, &d_log);
  link_struct(m_log, d_log, a_log);   //명령어 입력 받을 때마다 링크
}
  return 0;
}


void input_log(movie **m_log, actor **a_log, director **d_log){
  FILE *m_file = fopen("movie_log.txt", "r");   //로그파일 열기
  FILE *a_file = fopen("actor_log.txt", "r");
  FILE *d_file = fopen("director_log.txt", "r");
  input_m_log(m_log, m_file);
  input_d_log(d_log, d_file);
  input_a_log(a_log, a_file);
  fclose(m_file);
  fclose(a_file);
  fclose(d_file);
}

void input_m_log(movie **m_log, FILE *m_file) { //영화 로그 입력
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

  while (feof(m_file) == 0){  //파일의 끝까지 반복

    if (count == 0)   //맨 첫줄일 경우 파일 위치 지시자를 맨 처음으로 확실하게 설정
      fseek(m_file, 0, SEEK_SET);
    string_input(m_file, &tag); //한 줄의 정보 입력

    string_input(m_file, &serial_number);
    if (strcmp(tag, "delete") != 0){
      string_input(m_file, &title);
      string_input(m_file, &genre);
      string_input(m_file, &movie_director);
      string_input(m_file, &year);
      string_input(m_file, &run_time);
      string_input(m_file, &movie_actor);
    }
    else
      fseek(m_file, 6, SEEK_CUR);
    if (strcmp(tag, "add") == 0){ //tag에 따라 add, delete, update
      add_mlog(m_log, serial_number, title, genre, movie_director, year, run_time, movie_actor);
      add_m_number ++;    //add할 경우 그 태그 번호 기록
    }
    else if (strcmp(tag, "delete") == 0){
      delete_mlog((*m_log), serial_number, m_log);
    }
    else if (strcmp(tag, "update") == 0){
      update_mlog((*m_log), serial_number, title, genre, movie_director, year, run_time, movie_actor);
    }
    count++;

  }
}
void input_d_log(director **d_log, FILE *d_file) {  //감독 로그 입력
  char *tag;
  char *serial_number;
  char *d_name;
  char *s;
  char *birth;
  char *director_title;
  char tmp;
  static int count = 0;

  while (feof(d_file) == 0){    //파일 끝까지 반복

    if (count == 0)   //맨 첫줄의 경우 파일 위치 지시자를 맨 처음으로 확실하게 고정
      fseek(d_file, 0, SEEK_SET);

    string_input(d_file, &tag);
    string_input(d_file, &serial_number);
    if (strcmp(tag, "delete") != 0){
      string_input(d_file, &d_name);
      string_input(d_file, &s);
      string_input(d_file, &birth);
      string_input(d_file, &director_title);
    }
    else
      fseek(d_file, 4, SEEK_CUR);
    if (strcmp(tag, "add") == 0){
      add_dlog(d_log, serial_number, d_name, s, birth, director_title);
      add_d_number ++;
    }

    else if (strcmp(tag, "delete") == 0){
      delete_dlog((*d_log), serial_number, d_log);
    }
    else if (strcmp(tag, "update") == 0){
      update_dlog((*d_log), serial_number, d_name, s, birth, director_title);
    }
    count++;

  }
}
void input_a_log(actor **a_log, FILE *a_file) {//배우 로그 입력
  char *tag;
  char *serial_number;
  char *actor;
  char *s;
  char *birth;
  char *actor_title;
  static int count = 0;

  while (feof(a_file) == 0){    //파일 끝까지 입력

    if (count == 0)   //맨 첫줄일 경우 파일 위치 지시자를 맨 처음에 고정
      fseek(a_file, 0, SEEK_SET);
    string_input(a_file, &tag);

    string_input(a_file, &serial_number);
    if (strcmp(tag, "delete") != 0){
      string_input(a_file, &actor);
      string_input(a_file, &s);
      string_input(a_file, &birth);
      string_input(a_file, &actor_title);
    }
    else
      fseek(a_file, 4, SEEK_CUR);
    if (strcmp(tag, "add") == 0){
      add_alog(a_log, serial_number, actor, s, birth, actor_title);
      add_a_number ++;
    }
    else if (strcmp(tag, "delete") == 0){
      delete_alog((*a_log), serial_number, a_log);
    }

    else if (strcmp(tag, "update") == 0){
      update_alog((*a_log), serial_number, actor, s, birth, actor_title);
    }
    count++;

  }
}
void add_dlog(director ** d_log, char *serial_number, char *d_name, char *s, char *birth, char *whole_string){  //감독 로그 add처리
  director ** tmp_d_log;
  char * token = (char*)malloc(sizeof(char)*2); // 영화 목록을 통채로 입력받아 strtok으로 자를 문자열
  char * string_cut;
  struct d_title * move;
  struct d_title * d_t_tmp;
  struct d_title * space;
  *(token + 0) = ',';// , 일때 자르기
  *(token + 1) = '\n'; // 엔터일 때 자르기

  if (*d_log == NULL)// 아무것도 없을때 첫 노드 만들고 그걸 가리키게 하기.
  {
    (*d_log) = (director *)malloc(sizeof(director)*1);
    tmp_d_log = d_log;
  }
  else // 노드가 하나라도 있을 때 마지막 노드를 가리키게 하기
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

  (*tmp_d_log) -> director_title= (d_title *)malloc(sizeof(d_title)*1);// 대표 영화들 입력할 구조체 만듬
  (*tmp_d_log) -> serial_number = serial_number;//넘겨받은 정보들 입력
  (*tmp_d_log) -> d_name = d_name;
  (*tmp_d_log) -> s = s;
  (*tmp_d_log) -> birth = birth;
  (*tmp_d_log) -> next = NULL;// 마지막 노드에 null넣기

  (*tmp_d_log) -> director_title -> title = strtok(whole_string, token);// whole_string은 영화이름들 통째로
  (*tmp_d_log) -> director_title -> link = NULL;
  (*tmp_d_log) -> director_title -> next = (struct d_title *)malloc(sizeof(struct d_title)); // 다음 노드 생성(이후에 영화가 추가되지 않더라도 만듬)
  move = (*tmp_d_log) -> director_title -> next;
  space = (*tmp_d_log)-> director_title;
  while ((string_cut = strtok(NULL, token))!=NULL) // 처음 ,전까지의 영화는 입력되었고 이후의 null까지 반복
  {
    move -> title = string_cut;//, 전까지 입력
    move -> link = NULL;
    move -> next =  (struct d_title *)malloc(sizeof(struct d_title));
    move = move -> next;
    move -> next = NULL;
  }
  while (space->next != NULL) //다 잘라서 들어간 영화 이름들의 맨 처음 주소가 스페이스를 가지고 있을 때 그 스페이스를 없애기
   {
      if (*(space->title) == ' ')
         space->title = (space->title) + 1;
      space = space->next;
   }

}
void add_alog(actor ** a_log, char *serial_number, char *a_name, char *s, char *birth, char *whole_string){ //배우의 로그 add 입력
  actor ** tmp_a_log;
  char * token = (char*)malloc(sizeof(char)*2); // 대표 영화들 통째로 받고 토큰으로 자를 것(그 토큰들 저장할 포인터)
  char * string_cut;
  struct a_title * move; // 컴마 기준으로 whole_string 을 자를 때 사용하는 구조체
  struct a_title * a_t_tmp;
  struct a_title * space; // 컴마로 자른 후 첫 칸에 스페이스가 들어갈 시 이를 없앨 때 사용하는 구조체
  *(token + 0) = ',';
  *(token + 1) = '\n'; // 토큰들 저장 컴마랑 맨마지막에 들어갈 엔터

  if (*a_log == NULL) // 노드가 없을떼 첫 노드 생성
  {
    (*a_log) = (actor *)malloc(sizeof(actor)*1);
    tmp_a_log = a_log;
  }
  else
    { // 마지막 노드를 가리키게함.
      tmp_a_log = &((*a_log) -> next);
      while(1)
      {
        if((*tmp_a_log)== NULL)
        break;
        (tmp_a_log) = &((*tmp_a_log) -> next);
      }
      (*tmp_a_log)  = (actor *)malloc(sizeof(actor));

    }

  (*tmp_a_log) -> actor_title= (a_title *)malloc(sizeof(a_title)*1); // 대표영화들 입력할 구조체 만들기
  (*tmp_a_log) -> serial_number = serial_number; // 이후로 쭉 정보입력
  (*tmp_a_log) -> a_name = a_name;
  (*tmp_a_log) -> s = s;
  (*tmp_a_log) -> birth = birth;
  (*tmp_a_log) -> next = NULL;

  (*tmp_a_log) -> actor_title -> title = strtok(whole_string, token);// whole_string은 배우이름들 통째로, 첫번째 컴마 전까지를 구조체에 넣음
  (*tmp_a_log) -> actor_title -> link = NULL;
  (*tmp_a_log) -> actor_title -> next = (struct a_title *)malloc(sizeof(struct a_title));// 다음 영화를 담을 구조체 선언
  move = (*tmp_a_log) -> actor_title -> next; // 움직이면서 계속해서 영화들 저장
  space = (*tmp_a_log)-> actor_title; // 영화 맨 앞에 스페이스가 있을 시 이를 삭제할 임시 구조체
  while ((string_cut = strtok(NULL, token))!=NULL)// 컴마 전 문자열 저장한 후 이후 실행됨. 이후로도 컴마로 문자열을 끊어서 저장함
  {
    move -> title = string_cut;
    move -> link = NULL;// 링크연결
    move -> next =  (struct a_title *)malloc(sizeof(struct a_title)); //다음 영화를 담을 구조체 선언
    move = move -> next;
    move -> next = NULL;
  }
  while (space->next != NULL)// 컴마 다음에 스페이스를 입력할 시 영화이름 맨 처음에 있는 스페이스를 없애줌.
   {
      if (*(space->title) == ' ')
         space->title = (space->title) + 1;
      space = space->next;
   }

}

void update_mlog(movie * m_log, char *serial_number,char *title,char *genre,char *movie_director,char *year,char *run_time,char * whole_string) // 영화의 로그 업데이트
{

  movie * tmp;
  tmp = m_log;

  char * token = (char*)malloc(sizeof(char)*2); // 컴마와 개행을 토큰으로 삼아 배우 이름 한번에 입력받은 문자열을 자를것임. 토큰을 저장할 문자열포인터
  char * string_cut;
  struct m_actor * move;
  struct m_actor * m_a_tmp;
  struct m_actor * space;//스페이스 없애는 구조체
  *(token + 0) = ',';//토큰들 저장
  *(token + 1) = '\n';

  if (strcmp(((tmp) -> serial_number), serial_number) == 0) // 첫번째일때
  {
    if(strcmp(title,"=") != 0)
    {
      (m_log) ->title = title; // 받은 문자열이 =가 아니면 받은 문자열을 구조체에 저장. 아래도 쭉 같은방식
    }
    if(strcmp(genre,"=") != 0)
    {
      (m_log) ->genre = genre;
    }
    if(strcmp(movie_director,"=") != 0)
    {
      (m_log) ->movie_director -> director  = movie_director;
    }
    if(strcmp(year,"=") != 0)
    {
      (m_log) ->year  = year;
    }
    if(strcmp(run_time,"=") != 0)
    {
      (m_log) ->run_time  = run_time;
    }
    if(strcmp(whole_string,"=") != 0)
    {
      (m_log) ->movie_actor = NULL;
      (m_log) ->movie_actor = (m_actor *)malloc(sizeof(m_actor));
      (m_log) ->movie_actor -> actor  = strtok(whole_string, token);// 첫 컴마 나오기 전 배우를 저장
      (m_log) ->movie_actor -> link = NULL;
      (m_log) ->movie_actor -> next = (m_actor *)malloc(sizeof( m_actor));

      move = (m_log) -> movie_actor -> next;
      space = (m_log)-> movie_actor; // 스페이스 없애는 임시 구조체
      while ((string_cut = strtok(NULL, token))!=NULL) // 첫 컴마 이후 나머지 문자열들 모두 컴마로 잘라 저장
      {
        move -> actor = string_cut;
        move -> link = NULL;
        move -> next =  (struct m_actor *)malloc(sizeof(struct m_actor));
        move = move -> next;
        move -> next = NULL;
      }
      while (space->next != NULL) // 배우 이름 맨 앞에 스페이스 저장시 이를 없앰
       {
          if (*(space->actor) == ' ')
             space->actor = (space->actor) + 1;
          space = space->next;
       }
    }

    return;
  }
  while(1) // 첫 노드가 아닐 경우 그 tmp의 next에 정보를 저장. 이후부터는 tmp에 tmp의 넥스트를 저장해 와일문이 계속 돌아감.
  {
    if (strcmp(((tmp) -> next -> serial_number), serial_number) == 0)
    {
      if(strcmp(title,"=") != 0)
      {
        (tmp) -> next ->title = title; // 받은 문자열이 = 이 아닐경우 정보들 저장.
      }
      if(strcmp(genre,"=") != 0)
      {
        (tmp) ->next ->genre = genre;
      }
      if(strcmp(movie_director,"=") != 0)
      {
        (tmp) ->next ->movie_director -> director  = movie_director;
      }
      if(strcmp(year,"=") != 0)
      {
        (tmp) ->next ->year  = year;
      }
      if(strcmp(run_time,"=") != 0)
      {
        (tmp) ->next ->run_time  = run_time;
      }
      if(strcmp(whole_string,"=") != 0)
      {
        (tmp) ->next ->movie_actor = NULL;
        (tmp) ->next ->movie_actor = (m_actor *)malloc(sizeof(m_actor));
        (tmp) ->next ->movie_actor -> actor  = strtok(whole_string, token); // 첫 컴마 전 문자열 저장
        (tmp) ->next ->movie_actor -> link = NULL;
        (tmp) ->next ->movie_actor -> next = (m_actor *)malloc(sizeof( m_actor));

        move = (tmp) -> next ->movie_actor -> next;
        space = (tmp)-> next ->movie_actor;
        while ((string_cut = strtok(NULL, token))!=NULL)// 첫 컴마 이후 문자열들 컴마로 끊어서 저장
        {
          move -> actor = string_cut;
          move -> link = NULL;
          move -> next =  (struct m_actor *)malloc(sizeof(struct m_actor));
          move = move -> next;
          move -> next = NULL;
        }
        while (space->next != NULL)// 배우 이름 처음에 스페이스 있을 시 이를 없앰
         {
            if (*(space->actor) == ' ')
               space->actor = (space->actor) + 1;
            space = space->next;
         }
       }// actor

      return;
     }
    (tmp) = (tmp) -> next;
  }//while


}//함수
void update_dlog(director * d_log, char *serial_number,char *d_name,char *s,char *birth, char * whole_string)
{// update_mlog 방식과 동일함

  director * tmp;
  tmp = d_log;

  char * token = (char*)malloc(sizeof(char)*2);
  char * string_cut;
  struct d_title * move;
  struct d_title * d_t_tmp;
  struct d_title * space;
  *(token + 0) = ',';
  *(token + 1) = '\n';

  if (strcmp(((tmp) -> serial_number), serial_number) == 0) // 첫번째일때
  {
    if(strcmp(d_name,"=") != 0)
    {
      (d_log) -> d_name = d_name;
    }
    if(strcmp(s,"=") != 0)
    {
      (d_log) -> s = s;
    }
    if(strcmp(birth,"=") != 0)
    {
      (d_log) -> birth  = birth;
    }
    if(strcmp(whole_string,"=") != 0)
    {
      (d_log) ->director_title = NULL;
      (d_log) ->director_title = (d_title *)malloc(sizeof(d_title));
      (d_log) ->director_title -> title  = strtok(whole_string, token);
      (d_log) ->director_title -> link = NULL;//링크추가
      (d_log) ->director_title -> next = (d_title *)malloc(sizeof( d_title));

      move = (d_log) -> director_title -> next;
      space = (d_log)-> director_title;
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
    if (strcmp(((tmp) -> next -> serial_number), serial_number) == 0)
    {
      if(strcmp(d_name,"=") != 0)
      {
        (tmp) -> next ->d_name = d_name;
      }
      if(strcmp(s,"=") != 0)
      {
        (tmp) ->next ->s = s;
      }
      if(strcmp(birth,"=") != 0)
      {
        (tmp) ->next ->birth  = birth;
      }
      if(strcmp(whole_string,"=") != 0)
      {
        (tmp) ->next ->director_title = NULL;
        (tmp) ->next ->director_title = (d_title *)malloc(sizeof(d_title));
        (tmp) ->next ->director_title -> title  = strtok(whole_string, token);
        (tmp) ->next ->director_title -> link = NULL;//링크추가
        (tmp) ->next ->director_title -> next = (d_title *)malloc(sizeof( d_title));

        move = (tmp) -> next ->director_title -> next;
        space = (tmp)-> next ->director_title;
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
    (tmp) = (tmp) -> next;
  }//while


}//함수
void update_alog(actor * a_log, char *serial_number,char *a_name,char *s,char *birth, char * whole_string)
{// update_mlog 방식과 동일함

  actor * tmp;
  tmp = a_log;

  char * token = (char*)malloc(sizeof(char)*2);
  char * string_cut;
  struct a_title * move;
  struct a_title * a_t_tmp;
  struct a_title * space;
  *(token + 0) = ',';
  *(token + 1) = '\n';

  if (strcmp(((tmp) -> serial_number), serial_number) == 0) // 첫번째일때
  {
    if(strcmp(a_name,"=") != 0)
    {
      (a_log) -> a_name = a_name;
    }
    if(strcmp(s,"=") != 0)
    {
      (a_log) -> s = s;
    }
    if(strcmp(birth,"=") != 0)
    {
      (a_log) -> birth  = birth;
    }
    if(strcmp(whole_string,"=") != 0)
    {
      (a_log) ->actor_title = NULL;
      (a_log) ->actor_title= (a_title *)malloc(sizeof(a_title));
      (a_log) ->actor_title -> title  = strtok(whole_string, token);
      (a_log) ->actor_title -> link = NULL;//링크추가
      (a_log) ->actor_title -> next = (a_title *)malloc(sizeof( a_title));

      move = (a_log) -> actor_title -> next;
      space = (a_log)-> actor_title;
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
    if (strcmp(((tmp) -> next -> serial_number), serial_number) == 0)
    {
      if(strcmp(a_name,"=") != 0)
      {
        (tmp) -> next ->a_name = a_name;
      }
      if(strcmp(s,"=") != 0)
      {
        (tmp) ->next ->s = s;
      }
      if(strcmp(birth,"=") != 0)
      {
        (tmp) ->next ->birth  = birth;
      }
      if(strcmp(whole_string,"=") != 0)
      {
        (tmp) ->next ->actor_title = NULL;
        (tmp) ->next ->actor_title = (a_title *)malloc(sizeof(a_title));
        (tmp) ->next ->actor_title -> title  = strtok(whole_string, token);
        (tmp) ->next ->actor_title -> link = NULL;//링크추가
        (tmp) ->next ->actor_title -> next = (a_title *)malloc(sizeof( a_title));

        move = (tmp) -> next ->actor_title -> next;
        space = (tmp)-> next ->actor_title;
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
    (tmp) = (tmp) -> next;
  }//while


}//함수
void string_input(FILE *movie_file, char **subject){  //파일을 읽어서 문자열에 배정함
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
    if (tmp == ':')                         //:일 경우 방지
      fscanf(movie_file, "%c", &tmp);

    for (int i = 0; (tmp != '\r') &&(tmp != ':') && (tmp != '\n') && feof(movie_file) == 0 ; i++){
      *(*subject + i) = tmp;      //한글자씩 문자열에 배정
      fscanf(movie_file, "%c", &tmp);
    }
    size = 0;
}
void start(void)
{
  printf(">>Welcome to My Movie <<\n");
  printf("File Loading...\n");// 첫 시작 문구 함수
}
void flush(void)
{
  while(getchar()!='\n');
}// 개행이 나올때까지 움직이며 버퍼를 비워줌
void end(movie *m_log, actor *a_log, director *d_log){
  memory_to_listm(m_log);
  memory_to_lista(a_log);
  memory_to_listd(d_log);
  exit(0);// 모든 메모리를 리스트파일로 저장 후 종료
}
void command(movie *m_log, actor *a_log, director *d_log, movie **m_add, actor **a_add, director **d_add)
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
  else if ((strcmp(order,"search")!=0) && (space = '\n')) {// end부분
    end(m_log, a_log, d_log);
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
    getchar();//스페이스 받기
    scanf("%[^\n]",update_s); // 옵션과 숫자를 한 문자열로 저장해서 함수에 보냄


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
    getchar();// 스페이스 받기
    scanf("%s", print_num); //넘버 저장해 함수에 보냄
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
    getchar();//스페이스 받기
    scanf("%s",delete_num);//넘버 함수에 보냄

    if(optmda=='m'){
				deletem(m_log, delete_num, m_add);
		}
		else if(optmda=='d'){
      deleted(d_log, delete_num, d_add);
		}
		else if(optmda=='a'){
      deletea(a_log, delete_num, a_add);
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
	else if(strcmp(order,"save")==0){//save명령어를 입력받으면 m|d|a를 골라서 함수 호출
		if(optmda=='m'){
				savem(m_log);
		}
		else if(optmda=='d'){
			saved(d_log);
		}
		else if(optmda=='a'){
			savea(a_log);
		}
	}
	else if(strcmp(order,"search")==0){  //search 명령어일 때
		search(m_log, d_log, a_log);
	}


}
void con_printm(int print_it, movie *m_tmp, m_actor *movie_actor){  //print_it이 0이 아닐 때 해당 구조체의 자료 전체 출력
  char *print_str = (char *)malloc(50);
  if (print_it != 0){
    strcpy(print_str, m_tmp -> serial_number);
    inverse_ch(print_str);                  // 문자열 중 : 변환
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
void con_printd(int print_it, director *d_tmp, d_title *director_title){//print_it이 0이 아닐 때 해당 구조체의 자료 전체 출력
  char *print_str = (char *)malloc(50);
  if (print_it != 0){
    strcpy(print_str, d_tmp -> serial_number);
    inverse_ch(print_str);      //문자열 중 : 변환
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
void con_printa(int print_it, actor *a_tmp, a_title *actor_title){  //print_it이 0이 아닐 때 해당 구조체의 자료 전체 출력
  char *print_str = (char *)malloc(50);
  if (print_it != 0){
    strcpy(print_str, a_tmp -> serial_number);
    inverse_ch(print_str);    //문자열 중 : 변환
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
{ // 메타문자 중 ?를 확인. 입력받은 물음표가 포함된 스트링과 기존의 데이터가 일치할 시 1 리턴
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
int q_check(char * str){    // 받은 문자열 중 ?가 있는지 검사
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

  scanf("%s", option);    //옵션 받기
  if ((*option) != '-')   //옵션이 오지 않고 string이 올 경우
    strcpy(str, option);
  else {
    scanf("%s", str);
    for (int i = 1; *(option + i) != '\0'; i++){
      if (*(option + i) == 'd')       //옵션이 각각 d, m, a, 일 경우 해당 정수 1올리기
        d++;
      else if (*(option + i) == 'm')
        m++;
      else if (*(option + i) == 'a')
        a++;
    }
  }
  if ((m == 0) && (a == 0) && (d == 0)){  // 옵션이 없는 경우 전부 다 출력하게 하기 위함
    m = 1;
    a = 1;
    d = 1;
  }
  if (m == 1){  //-m옵션이 있는 경우
    if (*str == '*'){ //*이 맨 앞에 있는경우
      while (1) {
        strcpy(print_str, m_tmp -> serial_number); //입력한 string을 각 자료에 비교하여 일치할 경우 print_it 값 상승
        inverse_ch(print_str);  // : 처리
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
        print_it = 0;   //pirnt_it을 0으로 재설정해줌
        m_tmp = m_tmp -> next;
        movie_actor = m_tmp -> movie_actor;
      }
      m_tmp = m_log;    //m_tmp, movie_actor 초기화
      movie_actor = m_log -> movie_actor;
    }
    else if (*(str + (strlen(str) - 1)) == '*') { //*이 맨 뒤에 있을 경우
      while (1) {
        strcpy(print_str, m_tmp -> serial_number);  //방식은 위와 동일
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
    else if (q_check(str)){   //문자열에 ?가 있을 경우
      while (1) {
        strcpy(print_str, m_tmp -> serial_number);    //방식은 위와 동일
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
    else {  //문자열에 아무런 메타문자가 없을 경우
    for (int i = 0; i < m_count; i++){  //구조체 개수만큼 반복함
      if (strcmp(m_tmp -> title, str) == 0)     //방식은 위와 같음. 일치할 경우 print_it 상승
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

  if (d == 1) {  //-d옵션이 있는 경우. 방식이나 구조는 -m옵션이 있는 경우와 같음
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

  if (a == 1) {  //-d옵션이 있는 경우. 방식이나 구조는 -m옵션이 있는 경우와 같음
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
{//메타문자 *이 문자열의 맨 뒤에 입력될 시 기존의 데이터가 문자열과 일치하면 1리턴
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
{//메타문자 *이 문자열의 맨 앞에 입력될 시 기존의 데이터가 문자열과 일치하면 1리턴
   int str_len = strlen(string);
   int data_len = strlen(data);
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
int cmp_word(const void *p, const void *q){ //qsort에 쓰이는 비교함수
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
   //2차원 배열 메모리 할당
  t_array = (char **)malloc(sizeof(char *) * count);
  for (int i = 0; i < count; i++){
    *(t_array + i) = (char *)malloc(50);
  }
  a_array = (char **)malloc(sizeof(char *) * a_count);
  for (int i = 0; i < a_count; i++){
    *(a_array + i) = (char *)malloc(50);
  }




      space = getchar();
      if (space == ' '){
        scanf("%s", s_option);
        if (strcmp(s_option, "-f") == 0) {//option 없이 -f옵션만 있는 경우
          space = getchar();
          scanf("%s", filename);
          for (int i = 0; m_tmp != NULL; i++){
            title = m_tmp -> title;
            inverse_ch(title);
            strcpy((*(t_array + i)), title);  //각 배열에 title 저장
          if (m_tmp -> next == NULL)
            break;
          m_tmp = m_tmp -> next;
          }
          qsort((void *)t_array, count, sizeof(char *), cmp_word);  //정렬
          file = fopen(filename, "w");
          for (int i = 0; i < count; i++){  //filename파일을 생성하여 거기에 써주기
            fprintf(file, "%s\n", *(t_array + i));
          }
          fclose(file);
        }
        else {
          space = getchar();
          if (space == '\n'){ //옵션이 있고 -f가 없는 경우
            //---------------------------------------
            if (strcmp(s_option, "t") == 0){  //t옵션. 방식은 위와 같으나 파일 저장 대신 출력함
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
            }
            else if (strcmp(s_option, "g") == 0) {  //g옵션. 방식은 위와 같음
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
            }
            else if (strcmp(s_option, "d") == 0) {  //d옵션. 방식은 위와 같음
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
            }
            else if (strcmp(s_option, "y") == 0) {  //y옵션. 방식은 위와 같음
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
            }
            else if (strcmp(s_option, "r") == 0) {  //r옵션. 방식은 위와 같음
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
            }
            else if (strcmp(s_option, "a") == 0) {  //a옵션. 방식은 위와 같음
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
          }
          else{ //옵션에 -f까지 있는 경우
            scanf("%s %s", dump, filename);

            if (strcmp(s_option, "t") == 0){  //t옵션. 방식은 위와 같으나 출력 대신 파일에 저장
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
            }
            else if (strcmp(s_option, "g") == 0) {  //g옵션. 방식은 위와 같음
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
            }
            else if (strcmp(s_option, "d") == 0) {  //d옵션. 방식은 위와 같음
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
            }
            else if (strcmp(s_option, "y") == 0) {  //y옵션. 방식은 위와 같음
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
            }
            else if (strcmp(s_option, "r") == 0) {  //r옵션. 방식은 위와 같음
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
            }
            else if (strcmp(s_option, "a") == 0) {  //a옵션. 방식은 위와 같음
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
          }
        }
      }
      else{ //옵션이 없는 경우. 방식은 위와 같으나 저장 대신 출력함
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
{   //방식과 구조는 sort_m과 같음
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
void sort_a(actor *a_log){  ////방식과 구조는 sort_m과 같음
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

void print_m(movie *m_log, char *num){  //print 명령어의 m옵션
  movie *m_tmp = m_log;
  m_actor *movie_actor = m_log -> movie_actor;
  int a_number = 1;
  char *title = (char *)calloc(50, sizeof(char));
  char *genre = (char *)calloc(20, sizeof(char));
  char *a_name = (char *)calloc(30, sizeof(char));
  char *d_name = (char *)calloc(30, sizeof(char));
  while(strcmp(m_tmp -> serial_number, num) != 0){
    if (m_tmp -> next == NULL){ //해당 구조체가 없을 경우 걸러내기
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
  printf("%s, %s, %s\n", m_tmp -> serial_number, title, genre);   // :를 적절히 처리하여 출력
  if (m_tmp -> movie_director -> link == NULL){
    printf("\tD : %s(-)\n", d_name);
  }
  else
    printf("\tD : %s(%s)\n", d_name, m_tmp -> movie_director -> link -> birth);
  while(1){ //배우출력
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
void print_d(director *d_log, char *num){ //방식과 구조는 위 print_m과 같음
  director *d_tmp = d_log;
  d_title *director_title = d_log -> director_title;
  char *d_name = (char *)calloc(30, sizeof(char));
  char *title = (char *)calloc(50, sizeof(char));
  int t_number = 1;
  while(strcmp(d_tmp -> serial_number, num) != 0){
    if (d_tmp -> next == NULL){ //구조체가 없는 경우
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
void print_a(actor *a_log, char *num){  //방식과 구조는 위 print_m과 같음
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
  while(1){   //입력 문자열과 구조체의 영화이름에서 하나라도 일치하는게 있는지 검사
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
  while(1){ //입력 문자열과 구조체의 감독이름에서 하나라도 일치하는게 있는지 검사
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
  while(1){ //입력 문자열과 구조체의 배우이름에서 하나라도 일치하는게 있는지 검사
    if (strcmp(a_log -> a_name, a_name) == 0){
      return 1;
    }
    if (a_log -> next == NULL)
      break;
    a_log = a_log -> next;
  }
  return 0;
}
void print_for_same(movie *m_log, m_actor *movie_actor, char *title){ //중복시 중복되는 내용 출력
  while (1){  //중복되는 구조체까지 돌리기
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
      printf("오류 : 파일을 열 수 없습니다. \n"); // 오류처리
      }
      else
      {
        f_location = ftell(movie_log);
        flush(); // 버퍼 비워가며 사용자로부터 정보들을 입력받아 문자열로 저장함
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
          print_for_same(m_log, m_log -> movie_actor, title); //중복되는 내용 출력
          printf("\n@@ Do you want to add anyway? (Yes / No) > "); //여기서 대답나오기 전에 밑의 '돌아보림'이 나와버림
          scanf("%s", answer);
          flush();
        }

        if (strcmp(answer, "No") == 0){
          return;
        }

        else if (strcmp(answer, "Yes") == 0){
          while(1){// 이름이 같은 그 노드를 가리키게 함
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


        tmp.movie_actor -> actor = strtok(whole_string, token);//첫 컴마 나오기 전까지의 문자열 저장
        tmp.movie_actor -> link = NULL;
        tmp.movie_actor -> next = (struct m_actor *)malloc(sizeof(struct m_actor));//다음 노드 생성
        move = tmp.movie_actor -> next;
        m_a_tmp = tmp.movie_actor;
        while ((string_cut = strtok(NULL, token))!=NULL)//첫 컴마 이후 나머지 문자열 컴마로 나누어 저장
    	{
        move -> actor = string_cut;
        move -> link = NULL;
        move -> next =  (struct m_actor *)malloc(sizeof(struct m_actor));
        move = move -> next;
        move -> next = NULL;
    	}

      fprintf(movie_log, "%s:%s:%s:%s:%s:", title, genre,director, year,run_time);// 로그파일에 입력

      while (m_a_tmp->next != NULL) // 컴마 찍어가며 배우들 이름 입력
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
        update_mlog(m_log, serial_number,title,genre,director,year,run_time,whole_string);
        fclose(movie_log);
        return;
        }

        fseek(movie_log, 0, SEEK_SET);  //로그파일을 입력을 시작한 곳으로 돌려서 현재까지 입력한 내용을 쓰기
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
{// addm과 방식 같음
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
        update_dlog(d_log, serial_number, d_name,s,birth, whole_string);
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
{// addm과 방식 같음
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
      update_alog(a_log, serial_number, a_name,s,birth, whole_string);
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
{// 콜론을 ??; 으로 바꾸어 저장하는 함수
    int i=0;
    int j=0;
    char * token_bf;
    char * new;
    token_bf = (char*)malloc(sizeof(char)*1);
    *(token_bf) = ':';
    new = (char*)malloc(sizeof(char)*100);
    while (*(old+i) != '\0')// 끝까지 반복
    {
      if (*(old+i) == ':')// 콜론 발견시 ??; 입력, 커서옮김
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
void inverse_ch(char *old)  //:처리. 즉 ??;을 :로 바꿔줌
{
    int i=0;
    int j=0;
    char * token_bf;
    char * new;
    token_bf = (char*)malloc(sizeof(char)*1);
    *(token_bf) = ':';
    new = (char*)malloc(sizeof(char)*100);
    while (*(old+i) != '\0')    //한문자 한문자 입력받아서 만약 ??;가 있는 경우 그걸 :로 치환하여 new에 저장.
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
    strcpy(old, new); //new에 입력된 문자를 old에 넣음
    free(new);
  }
void quit(int signo)
{// 컨트롤 씨 입력시 계속할거냐고 물어본 후 종료
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
void deletem(movie *m_log, char * num, movie **m_add)
{
  int o_x=0;
  int count = 0;
  movie * testm = m_log;
  FILE * movie_log;
  if ((movie_log = fopen("movie_log.txt", "a")) == NULL)
  {
    printf("오류 : 파일을 열 수 없습니다. \n"); //오류처리
  }
  else
  {
    while (1)
    {
      if (strcmp(num, testm->serial_number )==0) // 해당 넘버가 메모리에 존재할 시 변수에 저장
      {
        o_x=1;
        break;
      }
      if ((testm -> next) == NULL)
        break;
      testm = testm -> next;

    }
    if (o_x==0)// 메모리에 없을 시 문구 띄움
    {
      printf("No such record");
      return;
    }
    fprintf(movie_log,"\ndelete:%s::::",num);
    fseek(movie_log, 0, SEEK_SET);
    delete_mlog(m_log, num, m_add);
  }
}
void deleted(director *d_log, char * num, director **d_add){// deletem과 방식 동일
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
    delete_dlog(d_log, num, d_add);
  }
}
void deletea(actor *a_log, char * num, actor **a_add)// deletem과 방식 동일
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
    delete_alog(a_log, num, a_add);
  }
}
void add_mlog(movie ** m_log, char *serial_number,char *title,char *genre,char *movie_director,char *year,char *run_time,char * whole_string) // 인자로 시리얼넘버부터 액터까지 다 받음 char *형으로
{// 앞 m-log는 처음시작 주소, tmp_m_log는 연결해서 구조체 만들때 사용 -> next주소값을 만들때마다 넣어줘야함.

  movie ** tmp_m_log;
  char * token = (char*)malloc(sizeof(char)*2); //배우들을 whole_string으로 통채로 입력받고 토큰으로 잘라서 저장할 것. 그때 사용할 토큰들을 저장할 문자열 포인터
  char * string_cut;
  struct m_actor * move; //움직이면서 컴마로 배우들 이름을 잘라서 저장할 임시 구조체
  struct m_actor * m_a_tmp;
  struct m_actor * space; // 배우이름들에 스페이스가 같이 저장되면 없앨때 쓰는 임시 구조체
  *(token + 0) = ',';
  *(token + 1) = '\n';// 마지막 개행이 입력되도 끊어야함

  if (*m_log == NULL)//아무 노드도 없을 때 첫 노드 생성
  {
    (*m_log) = (movie *)malloc(sizeof(movie)*1);
    tmp_m_log = m_log;
  }
  else // 노드가 존재할 때 tmp_m_log가 마지막 노드를 가리키게 함
    {
      tmp_m_log = &((*m_log) -> next);
      while(1)
      {
        if((*tmp_m_log)== NULL)
        break;
        (tmp_m_log) = &((*tmp_m_log) -> next);
      }
      (*tmp_m_log)  = (movie*)malloc(sizeof(movie));

    }

  (*tmp_m_log) -> movie_actor = (m_actor *)malloc(sizeof(m_actor)*1);// 첫 배우를 넣을 구조체 선언
  (*tmp_m_log) -> movie_director = (m_director *)malloc(sizeof(m_director)*1);//감독 넣을 구조체선언
  (*tmp_m_log) -> serial_number = serial_number;// 아래로 쭉 정보저장
  (*tmp_m_log) -> title = title;
  (*tmp_m_log) -> genre = genre;
  (*tmp_m_log) -> movie_director -> director = movie_director;  // 디렉터는 링크도 되야 하므로 구조체에 저장함.
  (*tmp_m_log) -> year = year;
  (*tmp_m_log) -> run_time = run_time;
  (*tmp_m_log) -> next = NULL;

  (*tmp_m_log) -> movie_actor -> actor = strtok(whole_string, token);// 첫 , 나오기 전 배우 이름 저장
  (*tmp_m_log) -> movie_actor -> link = NULL;
  (*tmp_m_log) -> movie_actor -> next = (struct m_actor *)calloc(1, sizeof(struct m_actor));// 다음 노드 생성
  move = (*tmp_m_log) -> movie_actor -> next;// 노드의 다음을 포인트
  space = (*tmp_m_log)-> movie_actor;// , 뒤에 스페이스가 같이 입력될 시 배우 이름 앞에 생기는 스페이스를 없앨때 쓰는 임시 구조체
  while ((string_cut = strtok(NULL, token))!=NULL) // 첫 컴마 이후로 나오는 모든 배우들 컴마기준으로 잘라서 구조체에 저장
  {
    move -> actor = string_cut;
    move -> link = NULL;
    move -> next =  (struct m_actor *)calloc(1, sizeof(struct m_actor));//다음 노드 생성
    move = move -> next;
    move -> next = NULL;
  }
  while (space->next != NULL)//배우 이름 맨 처음에 스페이스가 같이 입력되었다면 이를 없애기
   {
      if (*(space->actor) == ' ')
         space->actor = (space->actor) + 1;
      space = space->next;
   }

}
void delete_dlog(director * d_log, char *serial_number, director **d_add)
{ //로그파일 delete 처리

  director * tmp;
  tmp = d_log;

  if (strcmp(((tmp) -> serial_number), serial_number) == 0)
  {
    (*d_add) = (*d_add) -> next;  //첫번째 구조체가 바뀌어야 하는 경우 그 주소를 가져와서 바꿔줌
    return;
  }
  while (1)
  {
    if (strcmp(((tmp) -> next -> serial_number), serial_number) == 0)
    {
      if((tmp) -> next -> next == NULL) //삭제하는 구조체가 마지막인 경우
      {
        (tmp) -> next = NULL;
        break;
      }
      (tmp) -> next = (tmp) -> next -> next;  //삭제하는 구조체가 마지막이 아닌 경우
      break;
    }
    (tmp) = (tmp) -> next;
  }
}
void delete_mlog(movie * m_log, char *serial_number, movie **m_add)
{//로그파일 delete 처리. 방식과 구조는 위 delete_dlog와 동일함

  movie * tmp;
  tmp = m_log;

  if (strcmp(((tmp) -> serial_number), serial_number) == 0)
  {
    (*m_add) = (*m_add) -> next;
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
void delete_alog(actor * a_log, char *serial_number, actor **a_add)
{ //로그파일 delete 처리. 방식과 구조는 위 delete_dlog와 동일함

  actor * tmp;
  tmp = a_log;

  if (strcmp(((tmp) -> serial_number), serial_number) == 0)
  {
    (*a_add) = (*a_add) -> next;
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
void link_struct(movie *m_log, director *d_log, actor *a_log){  //구조체들 포인트하게 하기
  movie *m_tmp = m_log;
  director *d_tmp = d_log;
  actor *a_tmp = a_log;


    while (1){  //link_md에 영화의 구조체를 차례대로 넘겨줌
    link_md(m_tmp -> movie_director, d_log);
    if (m_tmp -> next == NULL)
      break;
    m_tmp = m_tmp -> next;
  }
  m_tmp = m_log;
    while (1){  //link_ma에 영화의 구조체를 차례대로 넘겨줌
    link_ma(m_tmp -> movie_actor, a_log);
    if (m_tmp -> next == NULL)
      break;
    m_tmp = m_tmp -> next;
  }
  m_tmp = m_log;
  while(1){ //link_dm에 감독의 구조체를 차례대로 넘겨줌
    link_dm(d_tmp -> director_title, m_log);
    if (d_tmp -> next == NULL)
      break;
    d_tmp = d_tmp -> next;
    }
    d_tmp = d_log;
    while(1){ //link_am에 배우의 구조체를 차례대로 넘겨줌
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
      if (strcmp(movie_director -> director, d_tmp -> d_name) == 0){  //영화의 감독 이름이 감독 리스트에 있는 경우 연결
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


        if (strcmp(movie_actor -> actor, a_tmp -> a_name) == 0){  //영화의 배우 이름이 배우리스트에 있는 경우 연결
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
        if (strcmp(director_title -> title, m_tmp -> title) == 0){  //감독의 영화제목이 영화리스트에 있는 경우 연결
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

        if (strcmp(actor_title -> title, m_tmp -> title) == 0){ //배우의 영화제목이 영화리스트에 있는 경우 연결

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
{//구조체를 리스트파일에 저장하는 함수
  FILE *movie_p;

  movie * m_tmp = m_log;
  m_actor * m_a_tmp = m_log->movie_actor;

  char * textfile = "./movie_list.txt";
    int f_ok = F_OK;
    char * aft_change;
    aft_change = timefilem();// 시간함수 시행한 문자열을 변수에 저장
    if (access(textfile, f_ok) == 0)// movie_list파일이 이미 존재하면 이름을 시간이 표시된 것으로 바꿔줌
    {
      rename("movie_list.txt", aft_change);
    }

    movie_p = fopen("movie_list.txt", "w");//기존 파일 이름 바꾸고 새로 생성


  while (1)
  {
    //printf("%s:", m_tmp->serial_number);
    fprintf(movie_p,"%s:", m_tmp->serial_number); // 정보들 쭉 프린트
    fprintf(movie_p,"%s:", m_tmp->title);
    fprintf(movie_p,"%s:", m_tmp->genre);
    fprintf(movie_p,"%s:", m_tmp->movie_director->director);
    fprintf(movie_p,"%s:", m_tmp->year);
    fprintf(movie_p,"%s:", m_tmp->run_time);
    m_a_tmp = m_tmp->movie_actor; // 임시 구조체에 배우들 가리키는 첫 포인터 배정
    while(1)
    {
      fprintf(movie_p,"%s", m_a_tmp->actor);

      if ((m_a_tmp-> next -> next) == NULL)//링크드 리스트 안의 링크드 리스트들은 입력받을 데이터가  더 있는지 여부와 관계 엾이 계속 메모리 생성함. next의 next가 null인지 확인해야함
        break;
      else
        fprintf(movie_p,",");

      m_a_tmp = m_a_tmp->next;
    }


    if ((m_tmp->next)== NULL)
      break;
    else
      fprintf(movie_p,"\n");//한 큰 구조체 입력 후 개행
    m_tmp = m_tmp->next;
  }
    fclose(movie_p);
}
void memory_to_listd(director * d_log)//memory_to_listm 함수와 방식 같음
{
  FILE *movie_p;

  director * d_tmp = d_log;
  d_title * d_t_tmp = d_log->director_title;

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
    //printf("%s:", m_tmp->serial_number);
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
    //printf("문제루프 넘어옴\n");

    if ((d_tmp->next)== NULL)
      break;
    else
      fprintf(movie_p,"\n");
    d_tmp = d_tmp->next;
  }
    fclose(movie_p);
}
void memory_to_lista(actor * a_log)//memory_to_listm 함수와 방식 같음
{
  FILE *movie_p;

  actor * a_tmp = a_log;
  a_title * a_t_tmp = a_log->actor_title;

  char * textfile = "./actor_list.txt";
    int f_ok = F_OK;
    char * aft_change;
    aft_change = timefilea();
    if (access(textfile, f_ok) == 0)
    {
      rename("actor_list.txt", aft_change);
    }

    movie_p = fopen("actor_list.txt", "w");


  while (1)
  {
    //printf("%s:", m_tmp->serial_number);
    fprintf(movie_p,"%s:", a_tmp->serial_number);
    fprintf(movie_p,"%s:", a_tmp->a_name);
    fprintf(movie_p,"%s:", a_tmp->s);
    fprintf(movie_p,"%s:", a_tmp->birth);
    a_t_tmp = a_tmp->actor_title;
    while(1)
    {
      fprintf(movie_p,"%s", a_t_tmp->title);

      if ((a_t_tmp-> next -> next) == NULL)
        break;
      else
        fprintf(movie_p,",");

      a_t_tmp = a_t_tmp->next;
    }
    //printf("문제루프 넘어옴\n");

    if ((a_tmp->next)== NULL)
      break;
    else
      fprintf(movie_p,"\n");
    a_tmp = a_tmp->next;
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

  movie * ol_tmp = m_log; //중복여부를 확인할 때 쓰는 오버랩 구조체
  m_actor * ol_a_tmp;
  char * answer = (char*)malloc(sizeof(char)*10); // 계속할 지 여부를 물어본 후 대답을 저장하는 문자열 포인터

  struct m_actor * move;
  struct m_actor * m_a_tmp;
  char * title = (char*)malloc(sizeof(char)*100);
  char * genre = (char*)malloc(sizeof(char)*100);
  char * director = (char*)malloc(sizeof(char)*100);
  char * year = (char*)malloc(sizeof(char)*10);
  char * run_time = (char*)malloc(sizeof(char)*10);
  int comma =0;
  int pass =0;

  int t=0, g=0, d=0, y=0, r=0, a=0; // 옵션 입력 여부가 확인되면 1로 변환
  int t_print =0, g_print =0, d_print =0, y_print =0, r_print =0, a_print =0;
  //옵션 여부 확인 후 프린트 여부 확인시 1로 변환

  tmp.movie_actor = (struct m_actor *)malloc(sizeof(struct m_actor) * 1);

  *(token + 0) = ',';
  *(token + 1) = '\n';

  *(token2+0) = ' ';
  if (('0'<(*(string+0))) && ((*(string+0)) < '9')) // 옵션 없이 숫자만 입력되었을 경우
  {
      num = string;
      while(1)
      {
        if (strcmp(num, m_tmp->serial_number )==0)
          break;
        if ((m_tmp->next) == NULL)
        {
          printf("No such record");// 메모리에 해당 숫자가 없을 시 문구 띄움
          fclose(movie_p);
          return;
        }
        m_tmp = m_tmp -> next;
      }
      flush(); // 버퍼 비워가며 정보들을 사용자들로부터 입력받음
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
        if(strcmp(ol_tmp ->title, title)== 0) // 제목이 같은 함수가 있다면 문구를 띄우고 해당 정보를 출력함
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
            printf("%s", ol_a_tmp -> actor);// 구조체 안의 링크드리스트 출력
            if ((ol_a_tmp -> next -> next) == NULL)
              break;
            printf(", ");
            ol_a_tmp = ol_a_tmp -> next;
          }
          printf("\n@@Do you want to update anyway?(Yes/No)");
          scanf("%s", answer);
          if (strcmp(answer, "Yes")== 0)// pass에 1 입력시 로그파일에 입력하는 부분으로 넘어감
          {
            pass = 1;

          }
          else if (strcmp(answer, "No")== 0)// 명령으로 돌아감
          {
            fclose(movie_p);
            return;
          }
        }
        if (ol_tmp -> next == NULL)// 겹치는 이름 없으면 정상적으로 로그파일에 입력
          break;
        if (pass ==1)// yes입력시 정상적으로 로그파일에 입력
          break;
        ol_tmp = ol_tmp -> next;
      }
      fprintf(movie_p,"\nupdate:"); //정보들 쭉 입략
      fprintf(movie_p,"%s:", m_tmp -> serial_number);
      fprintf(movie_p,"%s:", title);
      fprintf(movie_p,"%s:", genre);
      fprintf(movie_p,"%s:", director);
      fprintf(movie_p,"%s:", year);
      fprintf(movie_p,"%s:", run_time);

      tmp.movie_actor -> actor = strtok(whole_string, token); // 첫 컴마 전 문자열 저장
      tmp.movie_actor -> link = NULL;
      tmp.movie_actor -> next = (struct m_actor *)malloc(sizeof(struct m_actor));
      move = tmp.movie_actor -> next;
      m_a_tmp = tmp.movie_actor;
      while ((string_cut = strtok(NULL, token))!=NULL)// 첫 컴마 이후 문자열들 컴마로 나눠서 저장
    {
      move -> actor = string_cut;
      move -> link = NULL;
      move -> next =  (struct m_actor *)malloc(sizeof(struct m_actor));
      move = move -> next;
      move -> next = NULL;
    }

    while (m_a_tmp->next != NULL)// 나눈 문자열 첫칸에 스페이스 같이 저장시 이를 없애고 컴마와 함께 로그파일 입력
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
      update_mlog(m_log, m_tmp -> serial_number,title,genre,director,year,run_time,all_string);// 커서를 돌린 후 로그파일로 구조체를 만들어 내는 함수 실행
      fclose(movie_p);
      return;


  }
  else
  {
    option = strtok(string, token2);// 옵션이 있을 경우
    num = strtok(NULL, token2);
    while(1)// ((m_tmp->next) != NULL)
    {
      if (strcmp(num, m_tmp->serial_number )==0)
        break;
      if ((m_tmp->next) == NULL)
      {
        printf("No such record");// 해당 번호가 메모리에 없을 경우 문구 띄움
        fclose(movie_p);
        return;
      }
      m_tmp = m_tmp -> next;
    }
    while (*(option+i) != '\0') // 해당 옵션이 입력될 시 변수에  1저장
    {
      switch(*(option+i)){ //문자열 처음부터 널문자까지 검사
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
    while (t+g+d+y+r+a != 0) //옵션이 모두 처리되면 0이됨
    {
      if (t == 1)
      {
        flush();
        printf("title > ");
        scanf("%[^\n]", title);//사용자로부터 입력받음
        changes(title);//콜론처리
        t = 0;
        t_print =1;

      }
      else
      {
        strcpy(title, "=");//입력정보 없을 경우 = 저장
      }
      if (g == 1)// 이후로는 t의 경우와 같음
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
        scanf("%[^\n]", whole_string); //전체 문자열 저장
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
      if(strcmp(ol_tmp ->title, title)== 0)// 타이틀이 겹칠 경우 해당 레코드 출력해줌
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
        if (strcmp(answer, "Yes")==0)// pass에 1저장하면 정상적으로 로그파일에 입력
        {
          pass =1;
        }
        else if (strcmp(answer, "No")==0){// 명령 프롬프트로 돌아감
          fclose(movie_p);
          return;
        }
      }
      if (ol_tmp -> next == NULL)// 겹치지 않으면 정상적으로 입력하는 부분으로 돌아감
        break;
      if (pass ==1)
       break;
      ol_tmp = ol_tmp -> next;
    }


    while (t_print+g_print+d_print+y_print+r_print+a_print != 0) //합이 모두 0이 되면 프린트할것이 처리된 것
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
        tmp.movie_actor -> actor = strtok(whole_string, token); // 첫 컴마 전 문자열 저장
        tmp.movie_actor -> link = NULL;
        tmp.movie_actor -> next = (struct m_actor *)malloc(sizeof(struct m_actor));
        move = tmp.movie_actor -> next;
        m_a_tmp = tmp.movie_actor;
        while ((string_cut = strtok(NULL, token))!=NULL)// 첫 컴마 이후 문자열들 컴마로 쪼개서 저장
      {
        move -> actor = string_cut;
        move -> link = NULL;
        move -> next =  (struct m_actor *)malloc(sizeof(struct m_actor));
        move = move -> next;
        move -> next = NULL;
      }
      while (m_a_tmp->next != NULL) // 맨처음이 스페이스일 시 이를 없애고 컴마를 붙여서 입력
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
      else// 변경사항없을시 = 저장
      {
        fprintf(movie_p, "=");
        a_print = 0;
      }
    }
    fseek(movie_p, 0 ,SEEK_SET);
    update_mlog(m_log, m_tmp -> serial_number,title,genre,director,year,run_time,all_string);// 커서를 돌려 로그파일로 메모리 수정하는 함수 실행
    fclose(movie_p);

  }


}
void updated(director * d_log, char * string)// updatem과 동일
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
      update_dlog(d_log, d_tmp -> serial_number,d_name,sex,birth,all_string);
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
    update_dlog(d_log, d_tmp -> serial_number,d_name,sex,birth,all_string);
    fclose(movie_p);
  }
}
void updatea(actor * a_log, char * string)//updatem과 동일
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
      update_alog(a_log, a_tmp -> serial_number,a_name,sex,birth,all_string);
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
    update_alog(a_log, a_tmp -> serial_number,a_name,sex,birth,all_string);
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
    if (strcmp(s_option, "-f") == 0) // 1.파일이름만 입력된 경우
    {
      space = getchar();
      scanf("%s", filename);

      FILE * movie_p;
      movie_p = fopen("a.txt", "w");// 일단 a.txt 로 저장후 이름을 바꿈

      while (1)
      {
        fprintf(movie_p,"%s:", m_tmp->serial_number); // 정보들 전부 입력
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
      rename("a.txt", filename); // 파일 이름 입력받은걸로 바꿈

    }
    else
    {
      space = getchar();
      FILE * movie_p;

      if (space == '\n') // 2.옵션만 있을 경우
      {
        char * textfile = "./movie_list.txt";
        int f_ok = F_OK;
        char * aft_change;
        aft_change = timefilem();
        if (access(textfile, f_ok) == 0)// 원래 movie_list있으면 시간 포함된 이름으로 수정
        {
          rename("movie_list.txt", aft_change);

        }
        movie_p = fopen("movie_list.txt", "w");


          while (*(s_option+i) != '\0')
          {
            switch(*(s_option+i)){// 옵션 입력 여부를 변수에 1로 저장
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
            if (t ==1)// 정보를 쭉 저장
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
                  fprintf(movie_p, ", "); // 구조체 안에 링크드리스트 순차적으로 입력
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
        movie_p = fopen("a.txt", "w"); // 3. 파일이름과 옵션 둘다 입력
        scanf("%s %s", dump, filename);

        while (*(s_option+i) != '\0')
        {
          switch(*(s_option+i)){ // 옵션 입력 여부 확인
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
          if (t ==1) // 해당된 옵션들 파일에 입력
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
              fprintf(movie_p, "%s", m_a_tmp -> actor); //구조체 안의 링크드리스트 순차적으로 출력
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
        rename("a.txt", filename); // 입력받은파일이름으로 수정



      }

    }
  }
  else // 4. 옵션과 파일이름 둘다 없을 경우
  {
    FILE * movie_p;
    char * textfile = "./movie_list.txt";
    int f_ok = F_OK;
    char * aft_change;
    aft_change = timefilem();
    if (access(textfile, f_ok) == 0)
    {
      rename("movie_list.txt", aft_change); // 원래 파일 존재시 해당 파일 이름 시간 포함된걸로 바꿈

    }
    movie_p = fopen("movie_list.txt", "w");
    while (1)
    {
      fprintf(movie_p,"%s:", m_tmp->serial_number); // 정보들 쭉 입력
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
    rename("movie_list.txt", "movie_list.txt");
  }

}
char * timefilem(void)
{
  char * aft_string; // 변화된 문자열을 저장할 포인터
  aft_string = (char *)malloc(sizeof(char)*50);
  struct tm * t;
  time_t tp; //현재시간
  tp = time(NULL);
  t = localtime(&tp);
  sprintf(aft_string,"movie_list.%d%02d%02d%02d%02d", t -> tm_year + 1900, t -> tm_mon +1, t -> tm_mday, t -> tm_hour, t -> tm_min); //현재시간을 알맞게 배정
  return aft_string;
}
void saved(director * d_log)
{ //방식과 구조는 savem과 동일함
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
{ //방식과 구조는 timefilem과 동일함
  char * aft_string;
  aft_string = (char *)malloc(sizeof(char)*50);
  struct tm * t;
  time_t tp;
  tp = time(NULL);
  t = localtime(&tp);
  sprintf(aft_string,"director_list.%d%02d%02d%02d%02d", t -> tm_year + 1900, t -> tm_mon +1, t -> tm_mday, t -> tm_hour, t -> tm_min);
  return aft_string;
}
void savea(actor * a_log)
{//방식과 구조는 savem과 동일함
  char space;
  char *s_option = (char *)calloc(5, sizeof(char));
  char *filename = (char *)calloc(30, sizeof(char));
  char *dump = (char *)calloc(5, sizeof(char));
  int n=0, s=0, b=0, m=0;
  int i =1;
  int comma = 0;
  actor * a_tmp = a_log;
  a_title * a_t_tmp = a_log -> actor_title;

  space = getchar();
  if (space == ' ')
  {
    scanf("%s", s_option);
    if (strcmp(s_option, "-f") == 0)
    {
      space = getchar();
      scanf("%s", filename);

      FILE * movie_p;
      movie_p = fopen("a.txt", "w");

      while (1)
      {
        fprintf(movie_p,"%s:", a_tmp->serial_number);
        fprintf(movie_p,"%s:", a_tmp->a_name);
        fprintf(movie_p,"%s:", a_tmp->s);
        fprintf(movie_p,"%s:", a_tmp->birth);

        a_t_tmp = a_tmp->actor_title;
        while(1)
        {
          fprintf(movie_p,"%s", a_t_tmp->title);

          if ((a_t_tmp-> next -> next) == NULL)
            break;
          else
            fprintf(movie_p,",");

          a_t_tmp = a_t_tmp->next;
        }

        if ((a_tmp->next)== NULL)
          break;
        else
          fprintf(movie_p,"\n");
        a_tmp = a_tmp->next;
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
        char * textfile = "./actor_list.txt";
        int f_ok = F_OK;
        char * aft_change;
        aft_change = timefilea();
        if (access(textfile, f_ok) == 0)
        {
          rename("actor_list.txt", aft_change);

        }
        movie_p = fopen("actor_list.txt", "w");


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
              fprintf(movie_p,"name : %s\n", a_tmp -> a_name);
            }
            if (s ==1)
            {
              fprintf(movie_p,"sex : %s\n", a_tmp -> s);
            }
            if (b ==1)
            {
              fprintf(movie_p,"birth : %s\n", a_tmp -> birth);
            }

            if (m ==1)
            {
              fprintf(movie_p, "movie : ");
              a_t_tmp = a_tmp -> actor_title;
              while(1)
              {

                if (comma != 0)
                  fprintf(movie_p, ", ");
                fprintf(movie_p, "%s", a_t_tmp -> title);
                comma++;
                if ((a_t_tmp -> next -> next) == NULL)
                  break;
                a_t_tmp = a_t_tmp -> next;
              }
              comma = 0;
              fprintf(movie_p,"\n");
            }
            if (a_tmp -> next == NULL)
              break;
            a_tmp = a_tmp -> next;

          }
          fclose(movie_p);
      }
      else
      {
        movie_p = fopen("a.txt", "w");
        scanf("%s %s", dump, filename);

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
            fprintf(movie_p,"name : %s\n", a_tmp -> a_name);
          }
          if (s ==1)
          {
            fprintf(movie_p,"sex : %s\n", a_tmp -> s);
          }
          if (b ==1)
          {
            fprintf(movie_p,"birth : %s\n", a_tmp -> birth);
          }

          if (m ==1)
          {
            fprintf(movie_p, "movie : ");
            while(1)
            {

              if (comma != 0)
                fprintf(movie_p, ", ");
              fprintf(movie_p, "%s", a_t_tmp -> title);
              comma++;
              if ((a_t_tmp -> next -> next) == NULL)
                break;
              a_t_tmp = a_t_tmp -> next;
            }
            fprintf(movie_p,"\n");
            comma = 0;
          }
          if (a_tmp -> next == NULL)
            break;
          a_tmp = a_tmp -> next;
          a_t_tmp = a_tmp -> actor_title;

        }
        fclose(movie_p);
        rename("a.txt", filename);



      }
    }
  }
  else
  {
    FILE * movie_p;
    char * textfile = "./actor_list.txt";
    int f_ok = F_OK;
    char * aft_change;
    aft_change = timefilea();
    if (access(textfile, f_ok) == 0)
    {
      rename("actor_list.txt", aft_change);

    }
    movie_p = fopen("actor_list.txt", "w");
    while (1)
    {
      fprintf(movie_p,"%s:", a_tmp->serial_number);
      fprintf(movie_p,"%s:", a_tmp->a_name);
      fprintf(movie_p,"%s:", a_tmp->s);
      fprintf(movie_p,"%s:", a_tmp->birth);

      a_t_tmp = a_tmp->actor_title;
      while(1)
      {
        fprintf(movie_p,"%s", a_t_tmp->title);

        if ((a_t_tmp-> next -> next) == NULL)
          break;
        else
          fprintf(movie_p,",");

        a_t_tmp = a_t_tmp->next;
      }

      if ((a_tmp->next)== NULL)
        break;
      else
        fprintf(movie_p,"\n");
      a_tmp = a_tmp->next;
    }

    fclose(movie_p);
    rename("movie_list.txt", "movie_list.txt");

  }// 짧
}
char * timefilea(void)
{//방식과 구조는 timefilem과 동일함
  char * aft_string;
  aft_string = (char *)malloc(sizeof(char)*50);
  struct tm * t;
  time_t tp;
  tp = time(NULL);
  t = localtime(&tp);
  sprintf(aft_string,"actor_list.%d%02d%02d%02d%02d", t -> tm_year + 1900, t -> tm_mon +1, t -> tm_mday, t -> tm_hour, t -> tm_min);
  return aft_string;
}
