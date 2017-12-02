void changes(char *old)
{
  int i=0;
  int j=0;
  char * token_bf;
  char * new;
  token_bf = (char*)malloc(sizeof(char)*1);
  *(token_bf) = ':';
  new = (char*)malloc(sizeof(char)*100);
  while (*(old+i) != '\0')
  {
    if (*(old+i) == ':')
    {
      *(new+j) = '?';
      *(new+(j+1)) = '?';
      *(new+(j+2)) = ';';
      j = j+3;
      i++;
    }
    else
    {
      *(new+j) = *(old+i);
      i++;
      j++;
    }
  }
  *(new+j) = '\0';
  strcpy(old, new);
}
