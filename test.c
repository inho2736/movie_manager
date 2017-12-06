#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
static int add_m_number = 0;
static int add_d_number = 0;
static int add_a_number = 0;
void updatem(char*);
void deletem(char *);
void quit(int);
void flush(void);
void start(void);
void addm(void);
void addd(void);
void adda(void);
void command(void);
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

void input_m_log(movie **, FILE *);
void input_log(movie **, actor **, director **);
void string_input(FILE *, char **);
void add_mlog(movie **, char*, char*, char*, char*, char*, char*, char*);
void m_log_print(movie *);
void delete_mlog(movie ** , char *);
void update_mlog(movie ** , char *,char *,char *,char *,char *,char *,char *);
void input_d_log(director **, FILE *);
void add_dlog(director **, char *, char *, char *, char *, char *);
void delete_dlog(director **, char *);
void input_a_log(actor **, FILE *);
void add_alog(actor **, char *, char *, char *, char *, char *);
void delete_alog(actor **, char *);
void update_dlog(director **, char *,char *,char *,char *, char *);
void update_alog(actor ** , char *, char *, char *,char *, char * );

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
  start();
  command();
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
    printf("%d번째 루프 ================\n", count + 1);

    if (count == 0)
      fseek(m_file, 0, SEEK_SET);
    string_input(m_file, &tag);

    //if (count == 0)
      //tag = tag+3;
    printf("%d번째 태그 : %s\n", count + 1, tag);
    printf("태그 사이즈 : %d\n", strlen(tag));
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
      delete_mlog(m_log, serial_number);
    }
    else if (strcmp(tag, "update") == 0){
      update_mlog(m_log, serial_number, title, genre, movie_director, year, run_time, movie_actor);
    }
    count++;

    printf("%d번재 루프 끝 -----------------\n\n", count);
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
    printf("%d번째 루프 ================\n", count + 1);

    if (count == 0)
      fseek(d_file, 0, SEEK_SET);
    string_input(d_file, &tag);
    printf("%d번재 태그 , size : %s\t%d\n", count+1, tag, strlen(tag));

    string_input(d_file, &serial_number);
    printf("%d번째 serial : %s\n", count+1, serial_number);
    string_input(d_file, &d_name);
    string_input(d_file, &s);
    string_input(d_file, &birth);
    string_input(d_file, &director_title);
    if (strcmp(tag, "add") == 0){
      add_dlog(d_log, serial_number, d_name, s, birth, director_title);
      add_d_number ++;
    }

    else if (strcmp(tag, "delete") == 0){
      delete_dlog(d_log, serial_number);
    }
    else if (strcmp(tag, "update") == 0){
      update_dlog(d_log, serial_number, d_name, s, birth, director_title);
    }
    count++;

    printf("%d번재 루프 끝 -----------------\n\n", count);
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
    printf("%d번째 루프 ================\n", count + 1);

    if (count == 0)
      fseek(a_file, 0, SEEK_SET);
    string_input(a_file, &tag);
    printf("%d번재 태그 , size : %s\t%d\n", count+1, tag, strlen(tag));

    string_input(a_file, &serial_number);
    printf("%d번째 serial : %s\n", count+1, serial_number);
    string_input(a_file, &actor);
    string_input(a_file, &s);
    string_input(a_file, &birth);
    string_input(a_file, &actor_title);
    if (strcmp(tag, "add") == 0){
      add_alog(a_log, serial_number, actor, s, birth, actor_title);
      add_a_number ++;
    }
    else if (strcmp(tag, "delete") == 0){
      delete_alog(a_log, serial_number);
    }

    else if (strcmp(tag, "update") == 0){
      update_alog(a_log, serial_number, actor, s, birth, actor_title);
    }
    count++;

    printf("%d번재 루프 끝 -----------------\n\n", count);
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
  printf("add함수내 : %s\n", (*tmp_a_log) -> a_name);

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
  while ((tmp != ':') && (tmp != '\n') && feof(movie_file) == 0) {
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

    for (int i = 0; (tmp != ':') && (tmp != '\n') && feof(movie_file) == 0 ; i++){
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
void command(void)
{
  char *order=(char *)malloc(100);
	char *minopt=(char*)malloc(100);
  char *delete_num=(char*)malloc(50);
  char *update_s = (char*)malloc(50);
	char space,optmda;
	scanf("%s",order);
	space=getchar();
	if((strcmp(order,"search")!=0)&&(strcmp(order,"end")!=0)){//search와 order를 제외한 모든 명령어는 m|d|a하나를 받는 부분
		scanf("%c",&optmda);
	}
	else if(strcmp(order,"search")==0){//search에서 -옵션받는 부분
		scanf("%s",minopt);
	}
	else//명령어 end부분
	{

	}
	if(strcmp(order,"add")==0){//add명령어를 받으면 m|d|a중 골라서 함수 호출
		if(optmda=='m'){
				addm();
		}
		else if(optmda=='d'){
			addd();
		}
		else if(optmda=='a'){
			adda();
		}
	}
	else if(strcmp(order,"update")==0){//update명령어를 받으면 m|d|a중 골라서 함수호출
    getchar();
    scanf("%[^\n]",update_s);
    //if (('0'<(*(update_1+0))) && ((*(update_1+0)) < '9'))

    if(optmda=='m'){
				updatem(update_s);
		}
		else if(optmda=='d'){
			printf("1");
		}
		else if(optmda=='a'){
			printf("2");
		}
	}
	else if(strcmp(order,"print")==0){//print명령어를 받으면 m|d|a를 골라서 함수호출
		if(optmda=='m'){
				printf("3");
		}
		else if(optmda=='d'){
			printf("4");
		}
		else if(optmda=='a'){
			printf("5");
		}
	}
	else if(strcmp(order,"delete")==0){//delete명령어를 받으면 m|d|a중 골라서 함수 호출
    getchar();
    scanf("%s",delete_num);

    if(optmda=='m'){
				deletem(delete_num);
		}
		else if(optmda=='d'){
			printf("7");
		}
		else if(optmda=='a'){
			printf("8");
		}
	}
	else if(strcmp(order,"sort")==0){//sort 명령어를 입력받으면 m|d|a를 골라서 함수호출
		if(optmda=='m'){
				printf("9");
		}
		else if(optmda=='d'){
			printf("10");
		}
		else if(optmda=='a'){
			printf("11");
		}
	}
	else if(strcmp(order,"save")==0){//save명령어를 입력받으면 m|d|a를 ㄹ골라서 함수 호출
		if(optmda=='m'){
				printf("12");
		}
		else if(optmda=='d'){
			printf("13");
		}
		else if(optmda=='a'){
			printf("14");
		}
	}
	else if(strcmp(order,"search")==0){
		if(strchr(minopt,'m')!=NULL){
			printf("15");
		}
		else if(strchr(minopt,'d')!=NULL){
			printf("16");
		}
		else if(strchr(minopt,'a')!=NULL){
			printf("17");
		}
	}

}
void addm(void)
{
    char * whole_string = (char*)malloc(sizeof(char) * 100);
    char * token = (char*)malloc(sizeof(char)*2);// actor 입력시 ,와 개행으로 문자열 나누기
    char * string_cut;
    char * serial_number;//추가
    char * title = (char*)malloc(sizeof(char)*100);
    movie tmp;
    struct m_actor * move;
    struct m_actor * m_a_tmp;
    char * genre = (char*)malloc(sizeof(char)*100);
    char * director = (char*)malloc(sizeof(char)*100);
    char * year = (char*)malloc(sizeof(char)*10);
    char * run_time = (char*)malloc(sizeof(char)*10);
    int comma =0;
    tmp.movie_actor = (struct m_actor *)malloc(sizeof(struct m_actor) * 1);

    *(token + 0) = ',';
    *(token + 1) = '\n';

    FILE * movie_log;
    if ((movie_log = fopen("movie_log.txt", "a")) == NULL)
    {
      printf("오류 : 파일을 열 수 없습니다. \n");
      }
      else
      {
        flush();
        fprintf(movie_log, "\n");
        fprintf(movie_log, "add:");
        add_m_number++;
        fprintf(movie_log, "%d:", add_m_number);
        //fprintf(movie_log, "%s", tmp.serial_number);
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

    	fclose(movie_log);

      }
  }
void addd(void)
{
    char * whole_string = (char*)malloc(sizeof(char) * 100);// movie입력 전체를 한 문자열로 임시로 받음
    char * token = (char*)malloc(sizeof(char)*2);// movie 입력시 ,와 개행으로 문자열 나누기
    char * string_cut;
    char * serial_number;
    char * d_name = (char*)malloc(sizeof(char)*100);
    director tmp;
    struct d_title * move;
    struct d_title * d_t_tmp;
    char * s = (char*)malloc(sizeof(char)*100);
    char * birth = (char*)malloc(sizeof(char)*100);
    int comma =0;
    tmp.director_title = (struct d_title *)malloc(sizeof(struct d_title) * 1);

    *(token + 0) = ',';
    *(token + 1) = '\n';

    FILE * director_log;
    if ((director_log = fopen("director_log.txt", "a")) == NULL)
    {
      printf("오류 : 파일을 열 수 없습니다. \n");
      }
      else
      {
        fprintf(director_log, "add:");
        //fprintf(movie_log, "%s", tmp.serial_number);
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

    	fclose(director_log);

      }
  }
void adda(void)
{
  char * whole_string = (char*)malloc(sizeof(char) * 100);// movie입력 전체를 한 문자열로 임시로 받음
  char * token = (char*)malloc(sizeof(char)*2);// movie 입력시 ,와 개행으로 문자열 나누기
  char * string_cut;
  char * serial_number;
  char * a_name = (char*)malloc(sizeof(char)*100);
  actor tmp;
  struct a_title * move;
  struct a_title * a_t_tmp;
  char * s = (char*)malloc(sizeof(char)*100);
  char * birth = (char*)malloc(sizeof(char)*100);
  int comma =0;
  tmp.actor_title = (struct a_title *)malloc(sizeof(struct a_title) * 1);

  *(token + 0) = ',';
  *(token + 1) = '\n';

  FILE * actor_log;
  if ((actor_log = fopen("actor_log.txt", "a")) == NULL)
  {
    printf("오류 : 파일을 열 수 없습니다. \n");
    }
    else
    {
      fprintf(actor_log, "add:");
      //fprintf(movie_log, "%s", tmp.serial_number);
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
void deletem(char * num)
{
  //printf("%d", 1);
  FILE * movie_log;
  if ((movie_log = fopen("movie_log.txt", "a")) == NULL)
  {
    printf("오류 : 파일을 열 수 없습니다. \n");
  }
  else
  {
    printf("%s", num);

    //fprintf(movie_log,"delete");
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
  (*tmp_m_log) -> movie_actor -> next = (struct m_actor *)malloc(sizeof(struct m_actor));
  move = (*tmp_m_log) -> movie_actor -> next;
  space = (*tmp_m_log)-> movie_actor;
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
   printf("%s\n", (*tmp_m_log) -> title);

}
void delete_dlog(director ** d_log, char *serial_number)
{

  director ** tmp;
  tmp = d_log;

  if (strcmp(((*tmp) -> serial_number), serial_number) == 0)
  {
    *d_log = (*d_log) -> next;
    return;
  }
  while (1)
  {
    if (strcmp(((*tmp) -> next -> serial_number), serial_number) == 0)
    {
      if((*tmp) -> next -> next == NULL)
      {
        (*tmp) -> next = NULL;
        break;
      }
      (*tmp) -> next = (*tmp) -> next -> next;
      break;
    }
    (*tmp) = (*tmp) -> next;
  }
}
void delete_mlog(movie ** m_log, char *serial_number)
{

  movie ** tmp;
  tmp = m_log;
  printf("delete에서의 tmp : %s\n", (*tmp) -> title);
  printf("delete에서의 tmp : %s\n", (*tmp) -> serial_number);

  if (strcmp(((*tmp) -> serial_number), serial_number) == 0)
  {
    *m_log = (*m_log) -> next;
    return;
  }
  while (1)
  {
    printf("첫번째줄 성공\n");
    printf("delete에서의 tmp : %s\n", (*tmp) -> next -> title);
    printf("delete에서의 tmp -> next : %s\n", (*tmp) -> next -> serial_number);
    if (strcmp(((*tmp) -> next -> serial_number), serial_number) == 0)
    {
      if((*tmp) -> next -> next == NULL)
      {
        (*tmp) -> next = NULL;
        printf("두번째줄 성공\n");
        break;
      }
      (*tmp) -> next = (*tmp) -> next -> next;
      printf("두번째줄 성공\n");
      break;
    }
    (*tmp) = (*tmp) -> next;
  }
}
void delete_alog(actor ** a_log, char *serial_number)
{

  actor ** tmp;
  tmp = a_log;

  if (strcmp(((*tmp) -> serial_number), serial_number) == 0)
  {
    *a_log = (*a_log) -> next;
    return;
  }
  while (1)
  {
    if (strcmp(((*tmp) -> next -> serial_number), serial_number) == 0)
    {
      if((*tmp) -> next -> next == NULL)
      {
        (*tmp) -> next = NULL;
        break;
      }
      (*tmp) -> next = (*tmp) -> next -> next;
      break;
    }
    (*tmp) = (*tmp) -> next;
  }
}
void updatem(char * string)
{
  char * option = (char*)malloc(sizeof(char)*50);
  char * num = (char*)malloc(sizeof(char)*50);
  char * token = (char*)malloc(sizeof(char)*2);
  *(token+0) = ' ';
  if (('0'<(*(string+0))) && ((*(string+0)) < '9'))
  {
      num = string;
      printf("%s", num);
  }
  else
  {
    option = strtok(string, token);
    num = strtok(NULL, token);
    printf("%s %s", option, num);
  }

}
