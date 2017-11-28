memory_to_list(struct movie * movie, struct actor * actor, struct director * director)
{
  FILE *movie, *actor, *director;
  movie = fopen("movie_list.txt", "w");
  actor = fopen("actor_list.txt", "w");
  director = fopen("director_list","w");

  struct m_actor * m_a_tmp = movie->movie_actor;
  struct movie * m_tmp = movie

  while (1)
  {

    fprintf("%s:", m_tmp->serial_number);
    fprintf("%s:", m_tmp->title);


    fprintf("%s:", m_tmp->director);
    fprintf("%s:", m_tmp->year);
    fprintf("%s:", m_tmp->time);
    while(1)
    {
      fprintf("%s", m_a_tmp->actor);

      if (tmp->next == NULL)
        break;
      else
        fprintf(",")

      tmp = tmp->next;
    }

    if (m_tmp->next == NULL)
      break;
    else
      fprintf("\n");
    m_tmp = m_tmp->next;

  }

}
