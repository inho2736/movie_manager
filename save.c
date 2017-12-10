void savem(movie * m_log, char * string)
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
        aft_change = timefile();
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
    aft_change = timefile();
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

  }// 짧
}
