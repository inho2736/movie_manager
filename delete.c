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
    delete_mlog(&m_log, num);
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
    delete_dlog(&d_log, num);
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
    delete_alog(&a_log, num);
    printf("첫번쩨ㅐ 액터 : %s\n", a_log -> a_name);
  }
}
