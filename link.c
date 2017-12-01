#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
void link_input(FILE *file, m_director *movie_director){
  char tmp;
  int size = 0;

  fscanf(file, "%c", &tmp);   //동적 메모리 할당을 위해 입력받는 string의 크기 알아보기
  while ((tmp != '\n') && (feof(file) == 0) && (tmp != ':')) {
    while ((tmp != ':') && (tmp != ',')){
      size++;
      fscanf(file, "%c", &tmp);
    }

      movie_director -> director = (char *)malloc(sizeof(char) * size + 1); //NULL까지 고려하여 동적 메모리 할당
      fseek(file, -(size + 1), SEEK_CUR); //파일 위치 지시자를 읽기 시작했던 곳으로 돌림

      fscanf(file, "%c", &tmp);         // tmp에 먼저 저장하여 :가 나오기 전까지 subject 스트링에 입력
      for (int i = 0; (tmp != ':') && (tmp != ','); i++){
        *(movie_director -> director + i) = tmp;    //**(subject + i)와 *(*subject + i)의 차이점??
        fscanf(file, "%c", &tmp);
      }
      size = 0;
  }
}

void actor_link_input(FILE *file, m_actor *movie_actor){
  char tmp;
  int size = 0;

  fscanf(file, "%c", &tmp);   //동적 메모리 할당을 위해 입력받는 string의 크기 알아보기
    while ((tmp != ':') && (tmp != ',') && (tmp != '\n') && (feof(file) == 0 )){
      size++;
      fscanf(file, "%c", &tmp);
    }

      movie_actor -> actor = (char *)malloc(sizeof(char) * size + 1); //NULL까지 고려하여 동적 메모리 할당

      if (feof(file) == 0)    // 파일의 끝일 경우 ',' 뒤의 스페이스가 문자열에 들어가므로 이를 방지
        fseek(file, -(size + 1), SEEK_CUR);
      else
        fseek(file, -size, SEEK_CUR);

      fscanf(file, "%c", &tmp);         // tmp에 먼저 저장하여 :가 나오기 전까지 subject 스트링에 입력
      for (int i = 0; (tmp != ':') && (tmp != ',') && (tmp != '\n') && (feof(file) == 0); i++){
        *(movie_actor -> actor + i) = tmp;
        fscanf(file, "%c", &tmp);
      }
      printf("%s\n", (movie_actor -> actor));
      size = 0;

  if (tmp == ','){
    fseek(file, 1, SEEK_CUR); // ','뒤의 띄어쓰기 방지
    (movie_actor -> next) = (m_actor *)malloc(sizeof(m_actor));
    movie_actor = movie_actor -> next;
    actor_link_input(file, movie_actor);
  }
}

void title_link_input(FILE *file, m_title *director_title){
  char tmp;
  int size = 0;

  fscanf(file, "%c", &tmp);   //동적 메모리 할당을 위해 입력받는 string의 크기 알아보기
    while ((tmp != ':') && (tmp != ',') && (tmp != '\n') && (feof(file) == 0 )){
      size++;
      fscanf(file, "%c", &tmp);
    }

      director_title -> title = (char *)malloc(sizeof(char) * size + 1); //NULL까지 고려하여 동적 메모리 할당

      if (feof(file) == 0)    // 파일의 끝일 경우 ',' 뒤의 스페이스가 문자열에 들어가므로 이를 방지
        fseek(file, -(size + 1), SEEK_CUR);
      else
        fseek(file, -size, SEEK_CUR);

      fscanf(file, "%c", &tmp);         // tmp에 먼저 저장하여 :가 나오기 전까지 subject 스트링에 입력
      for (int i = 0; (tmp != ':') && (tmp != ',') && (tmp != '\n') && (feof(file) == 0); i++){
        *(director_title -> title + i) = tmp;
        fscanf(file, "%c", &tmp);
      }
      printf("%s\n", (director_title -> title));
      size = 0;

  if (tmp == ','){
    fseek(file, 1, SEEK_CUR);
    (director_title -> next) = (m_title *)malloc(sizeof(m_title)); // 무조건 메모리를 주고 접근해야함
    director_title = director_title -> next;
    title_link_input(file, director_title);
  }
}
