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
      if (s == 1)
      {
        flush();
        printf("sex > ");
        scanf("%[^\n]", sex);
        changes(sex);
        s = 0;
        s_print =1;
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
      if (m == 1)
      {
        flush();
        printf("movies > ");
        scanf("%[^\n]", whole_string);
        m = 0 ;
        m_print =1;
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

  }
}
