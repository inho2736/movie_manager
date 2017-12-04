
void m_log_print(movie *);


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
