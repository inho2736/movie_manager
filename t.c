#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct director{
  int serial_number;
  char * d_name;
  char s;
  char * birth;
  struct d_title director_title;
  struct director * next;
};
struct d_title{
  char * title;
  struct movie * link;
  struct d_title * next;
};
struct movie{
  int serial_number;
  char * title;
  char * genre;
  char * director;
  struct m_actor movie_title;
  struct movie * next;
};
struct m_actor{
  char * actor;
  struct actor * link;
  struct m_actor * next;
};
struct actor{
  int serial_number;
  char * actor;
  char s;
  char * birth;
  struct a_title actor_title;
  struct actor * next;
};
struct a_title{
  char * title;
  struct movie * link;
  struct a_title * next;
}
int main(void){
  //FILE *movie_l =
  return 0;
}

void start(void){
  printf(">>Welcome to My Movie <<\n");
  printf("File Loading...\n");
  printf("You can use add, update, delate, search, sort, save, end commands.\n");
  printf("(movie)");
}
