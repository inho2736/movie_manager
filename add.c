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
