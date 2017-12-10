void savea(actor * a_log)
{
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
      printf("파일이름만");

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
              fprintf(movie_p,"name : %s\n", a_tmp -> d_name);
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
    printf("짧");
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
{
  char * aft_string;
  aft_string = (char *)malloc(sizeof(char)*50);
  struct tm * t;
  time_t tp;
  tp = time(NULL);
  t = localtime(&tp);
  sprintf(aft_string,"actor_list.%d%02d%02d%02d%02d", t -> tm_year + 1900, t -> tm_mon +1, t -> tm_mday, t -> tm_hour, t -> tm_min);
  return aft_string;
}
