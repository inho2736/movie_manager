#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

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
  char * actor;
  char * s;
  char * birth;
  struct a_title * actor_title;
  struct actor * next;
}actor;

void updatem(char*);
void deletem(char *);
void quit(int);
void flush(void);
void start(void);
void addm(void);
void addd(void);
void adda(void);
void command(movie *, director *, actor*);
void changes(char *);
void add_mlog(movie *, char*, char*, char*, char*, char*, char*, char*);
//void movie_test(movie *);
void input_mlog(movie *);
void string_input(FILE *, char **);


int main(void)
{
  signal(SIGINT, (void*)quit);
  movie * m_log = (movie *)malloc(sizeof(movie)*1);
  m_log = NULL;
  director * d_log = (director * )malloc(sizeof(director)*1);
  d_log = NULL;
  actor * a_log = (actor * )malloc(sizeof(actor)*1);
  a_log = NULL;
  movie * tmp_m_log = m_log;
  input_mlog(m_log);
  start();
  command(m_log, d_log, a_log);
  return 0;
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
void command(movie * m_log, director * d_log, actor* a_log)
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
        fprintf(movie_log, "add:");
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
void deletem(char * num, movie * m_log)
{
  FILE * movie_log;
  int check = 0 ;
  movie * tmp_m_log = m_log;
  if ((movie_log = fopen("movie_log.txt", "a")) == NULL)
  {
    printf("오류 : 파일을 열 수 없습니다. \n");
  }
  else
  {
    while (1)
    {
      if ( strcmp(tmp_m_log -> serial_number, num) == 0)
      {
        check = 1;
        break;
      }
      if ((tmp_m_log -> next) == NULL)
      {
        printf("No such record");
        return;
      }
      tmp_m_log = tmp_m_log -> next;
    }
    fprintf(movie_log,"delete:");
    fprintf(movie_log,"%s", num);
    fprintf(movie_log,":=:=:=:=:=:=");
  }
}
void updatem(char * string)
{
  char * token = (char*)malloc(sizeof(char)*2);// actor 입력시 ,와 개행으로 문자열 나누기
  char * string_cut;
  char * title = (char *)malloc(sizeof(char)*50);
  char * genre = (char *)malloc(sizeof(char)*50);
  char * director = (char *)malloc(sizeof(char)*50);
  char * year = (char *)malloc(sizeof(char)*50);
  char * run_time = (char *)malloc(sizeof(char)*50);
  char * whole_string = (char *)malloc(sizeof(char)*100);
  int i=0;
  char * option = (char*)malloc(sizeof(char)*50);
  char * num = (char*)malloc(sizeof(char)*50);
  char * token2 = (char*)malloc(sizeof(char)*2);
  movie tmp;
  struct m_actor * move;
  struct m_actor * m_a_tmp;
  int comma =0;
  tmp.movie_actor = (struct m_actor *)malloc(sizeof(struct m_actor) * 1);

  *(token2+0) = ' ';
  *(token + 0) = ',';
  *(token + 1) = '\n';
  FILE * movie_log;
  if ((movie_log = fopen("movie_log.txt", "a")) == NULL)
  {
    printf("오류 : 파일을 열 수 없습니다. \n");
  }
  else
  {
      if (('0'<(*(string+0))) && ((*(string+0)) < '9'))
      {
          num = string;
          flush();
          fprintf(movie_log, "update:");
          fprintf(movie_log, "%s:", num);
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



      else
      {
          option = strtok(string, token2);
          num = strtok(NULL, token2);

          while((*(option+i)) != '\0')
          {
            switch(*(option+i)){
              case 't' :
                printf("title>");
                scanf("%[^\n]", title);
                changes(title);
                flush();
                i++;
                break;
              case 'g' :
                printf("genre>");
                scanf("%[^\n]", genre);
                changes(genre);
                flush();
                i++;
                break;
              case 'd' :
                printf("director>");
                scanf("%[^\n]", director);
                changes(director);
                flush();
                i++;
                break;
              case 'y' :
                printf("year>");
                scanf("%[^\n]", year);
                changes(year);
                flush();
                i++;
                break;
              case 'r' :
                printf("run_time>");
                scanf("%[^\n]", run_time);
                changes(run_time);
                flush();
                i++;
                break;
              case 'a' :
                printf("actor>");
                scanf("%[^\n]", whole_string);
                changes(whole_string);
                flush();
                i++;
                break;
              }
          }


      }
    }

}
void add_mlog(movie * m_log, char *serial_number,char *title,char *genre,char *movie_director,char *year,char *run_time,char * whole_string) // 인자로 시리얼넘버부터 액터까지 다 받음 char *형으로
{// 앞 m-log는 처음시작 주소, tmp_m_log는 연결해서 구조체 만들때 사용 -> next주소값을 만들때마다 넣어줘야함.

  movie * tmp_m_log;
  char * token = (char*)malloc(sizeof(char)*2);
  char * string_cut;
  struct m_actor * move;
  struct m_actor * m_a_tmp;
  *(token + 0) = ',';
  *(token + 1) = '\n';

  if (m_log == NULL)// tmp_m_log이 마지막 구조체를 가리키게함.
  {
    m_log = (movie *)malloc(sizeof(movie)*1);
    tmp_m_log = m_log;
  }
  else
  {
    tmp_m_log = m_log -> next;
    while(1)
    {
      if((tmp_m_log -> next)== NULL)
      break;
      tmp_m_log = tmp_m_log -> next;
    }
    tmp_m_log -> next = (movie*)malloc(sizeof(movie));
    tmp_m_log = tmp_m_log -> next;
  }

  tmp_m_log -> movie_actor = (m_actor *)malloc(sizeof(m_actor)*1);
  tmp_m_log -> movie_director = (m_director *)malloc(sizeof(m_director)*1);
  tmp_m_log -> serial_number = serial_number;
  tmp_m_log -> title = title;
  tmp_m_log -> genre = genre;
  tmp_m_log -> movie_director -> director = movie_director; // 링크연결
  tmp_m_log -> year = year;
  tmp_m_log -> run_time = run_time;
  tmp_m_log -> next = NULL;

  tmp_m_log -> movie_actor -> actor = strtok(whole_string, token);// whole_string은 배우이름들 통째로
  tmp_m_log -> movie_actor -> link = NULL; // 링크연결
  tmp_m_log -> movie_actor -> next = (struct m_actor *)malloc(sizeof(struct m_actor));
  move = tmp_m_log -> movie_actor -> next;
  m_a_tmp = tmp_m_log-> movie_actor;
  while ((string_cut = strtok(NULL, token))!=NULL)
  {
    move -> actor = string_cut;
    move -> link = NULL;// 링크연결
    move -> next =  (struct m_actor *)malloc(sizeof(struct m_actor));
    move = move -> next;
    move -> next = NULL;
  }


}
/*void movie_test(movie * m_log)
{
  movie * tmp;
  m_actor * m_a_tmp;
  m_a_tmp = m_log -> movie_actor;
  tmp = m_log;
  while(1)// 맨 마지막 무비는 어떻게 출력?
  {
    printf("%s\n", tmp -> serial_number);
    printf("%s\n", tmp -> title);
    printf("%s\n", tmp -> genre);
    printf("%s\n", tmp -> movie_director -> director);
    printf("%s\n", tmp -> year);
    printf("%s\n", tmp -> run_time);
    while (1)
    {
      printf("%s")
    }
    if((tmp -> next)!= NULL);
      break;
      tmp = tmp -> next;
  }
  if ((tmp -> next)== NULL)
  {

  }

}*/
void input_mlog(movie *m_log) {
  FILE *m_file = fopen("movie_log.txt", "r");
  char *tag;
  char *serial_number;
  char *title;
  char *genre;
  char *movie_director;
  char *year;
  char *run_time;
  char *movie_actor;
  int size;
  string_input(m_file, &tag);
  string_input(m_file, &serial_number);
  string_input(m_file, &title);
  string_input(m_file, &genre);
  string_input(m_file, &movie_director);
  string_input(m_file, &year);
  string_input(m_file, &run_time);
  string_input(m_file, &movie_actor);
  if (strcmp(tag,"add"))
  {
    add_log(m_log,serial_number,title,genre,movie_director,year,run_time,movie_actor);
  }
  else if (strcmp(tag,"update"))
  {

  }
  else // delete
  {

  }


}
void string_input(FILE *movie_file, char **subject){
  char tmp;
  int size;

  fscanf(movie_file, "%c", &tmp); //동적 메모리 할당을 위해 입력받는 string의 크기 알아보기
  if (tmp == '\n')                        //첫번째 줄에서 두번째 줄 넘어갈 때 \n이 tag에 들어가는 것 방지
    fscanf(movie_file, "%c", &tmp);
  while ((tmp != ':') && (tmp != '\n') && feof(movie_file) == 0) {
    size++;
    fscanf(movie_file, "%c", &tmp);
  }

    (*subject) = (char *)malloc(sizeof(char) * size + 1); //NULL까지 고려하여 동적 메모리 할당
    fseek(movie_file, -(size + 1), SEEK_CUR); //파일 위치 지시자를 읽기 시작했던 곳으로 돌림

    fscanf(movie_file, "%c", &tmp);         // tmp에 먼저 저장하여 :가 나오기 전까지 subject 스트링에 입력

    if (tmp == '\n')                        //첫번째 줄에서 두번째 줄 넘어갈 때 \n이 tag에 들어가는 것 방지
      fscanf(movie_file, "%c", &tmp);

    for (int i = 0; (tmp != ':') && (tmp != '\n') && feof(movie_file) == 0 ; i++){
      *(*subject + i) = tmp;
      fscanf(movie_file, "%c", &tmp);
    }


    size = 0;
}
