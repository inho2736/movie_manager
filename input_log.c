

void input_log(movie *, actor *, director *);
void string_input(FILE *, char **);

int main(void)
{
  movie *m_log = (movie *)malloc(sizeof(movie));
  actor *a_log = (actor *)malloc(sizeof(actor));
  director *d_log = (director *)malloc(sizeof(director));
  input_log(m_log, a_log, d_log);
  return 0;
}

void input_log(movie *m_log, actor *a_log, director *d_log) {
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
  printf("%s\n", tag);
  printf("%s\n", serial_number);
  printf("%s\n", title);
  printf("%s\n", genre);
  printf("%s\n", movie_director);
  printf("%s\n", year);
  printf("%s\n", run_time);
  printf("%s\n", movie_actor);



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
