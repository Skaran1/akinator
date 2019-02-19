#include <stdio.h>
#include <stdlib.h>

struct thing
{
  struct thing* prev;
  struct thing* yes;
  struct thing* no;
  char* str;
};

void fill_thing (struct thing* root);
void tree_output (struct thing* root, FILE * f2);
void tree_output_ (struct thing* root);
void request (struct thing* root);
void copy_str (char* to_str, char* from_str);
void feature (char* smth, struct thing* root, struct thing** pointer);
int compare_str (char* str1, char* str2);
void output_features (struct thing* pointer);
void inside_tree (struct thing * root, int counter, FILE * f1);
struct thing * read_tree (struct thing * root);


int main ()
{

  struct thing* root = (struct thing *)calloc(1,sizeof(struct thing*));
  fill_thing (root);
  root = read_tree (root);
  printf("Lats game!\n");
  char e = 'a';
  while (e == 'a')
  {
    request(root);
    tree_output_(root);
    printf("\nAgan?(a)\n");
    scanf ("\n%c", &e);
  }
  printf ("About what do you want to know info?\n");
  char* info_word = (char*)calloc(100,sizeof(char));
  scanf ("%s", info_word);
  struct thing* new_pointer = (struct thing *)calloc(1,sizeof(struct thing*));
  fill_thing(new_pointer);
  feature (info_word, root, &new_pointer);
  printf ("\n");
  output_features (new_pointer);
  tree_output_(root);
}











void fill_thing (struct thing* root)
{
  root->prev = NULL;
  root->yes = NULL;
  root->no = NULL;
  root->str = (char*)calloc(100,sizeof(char));
}


void tree_output_ (struct thing* root)
{
  FILE * f2 = fopen ("output.txt","w");
  tree_output (root, f2);
  fclose(f2);
}


void tree_output (struct thing* root, FILE * f2)
{
  fprintf(f2, "(");
  if (root->yes != NULL)
    {
      tree_output (root->yes, f2);
    }
  fprintf(f2, "%s",root->str);
  if (root->no != NULL)
    {
      tree_output (root->no, f2);
    }
  fprintf(f2, ")");
}


void request (struct thing* root)
{
  char q = 0;
  char* word = (char*)calloc(100,sizeof(char));
  printf ("Is it %s? (Tell y (yes) or n (no)\n",root->str);
  scanf ("\n%c", &q);
  if (q == 'y')
  {
    if (root->yes != NULL)
    {
      request(root->yes);
    }
    else
    {
      printf ("ha ha ha, I know ur word!\n");
    }
  }
  if (q == 'n')
  {
    if (root->no != NULL)
    {
      request(root->no);
    }
    else
    {
      printf("I do not know anemore words!\nWhat was it?\n");
      scanf ("%s", word);
      struct thing* new_1 = (struct thing *)calloc(1,sizeof(struct thing*));
      fill_thing (new_1);
      struct thing* copy = (struct thing *)calloc(1,sizeof(struct thing*));
      fill_thing (copy);
      new_1->prev = root;
      copy_str (new_1->str, word);
      copy->prev = root;
      copy_str (copy->str, root->str);
      char* vvod = (char*)calloc(100,sizeof(char));
      printf("What feature?(your thing must be yes!)\n");
      scanf ("%s", vvod);
      copy_str (root->str, vvod);
      root->yes = new_1;
      root->no = copy;
    }
  }
}

void copy_str (char* to_str, char* from_str)
{
  for (int i = 1; i <= 100; i++)
  {
    *to_str = *from_str;
    to_str ++;
    from_str ++;
  }
}

int compare_str (char* str1, char* str2)
{
  for (int i = 1; i <= 100; i ++)
  {
    if (*str1 != *str2) return 0;
    str1 ++;
    str2 ++;
  }
  return 1;
}


void feature (char* smth, struct thing* root, struct thing** pointer)
{
  if (compare_str(smth, root->str) == 1)
  {
    *pointer = root;
  }
  else
  {
    if (root->yes != NULL)
      {
        feature (smth, root->yes, pointer);
      }
    if (root->no != NULL)
      {
        feature (smth, root->no, pointer);
      }
  }
}


void output_features (struct thing* pointer)
{
  if (pointer->prev != NULL)
  {
    if (pointer->prev->yes == pointer)
    {
      printf("%s\n", pointer->prev->str);
      output_features (pointer->prev);
    }
    else
    {
      printf("not %s\n", pointer->prev->str);
      output_features (pointer->prev);
    }
  }
}



struct thing * read_tree (struct thing * root)
{
  char q = 0;
  FILE * f1 = fopen("input.txt","r");
  fscanf(f1, "%c", &q);
  inside_tree (root, 1, f1);
  root->yes->prev = NULL;
  fclose(f1);
  return root->yes;
}


void inside_tree (struct thing * root, int counter, FILE * f1)
{
  char q = 0;
  fscanf(f1, "%c", &q);
  struct thing* pointer = (struct thing *)calloc(1,sizeof(struct thing*));
  fill_thing (pointer);
  pointer->prev = root;
  if (counter == 1)
  {
    root->yes = pointer;
  }
  if (counter == -1)
  {
    root->no = pointer;
  }
  if (q == '(')
  {
    inside_tree(pointer, 1, f1);
    fscanf(f1, "%c", &q);
    char* latter = pointer->str;
    while (q != '(')
    {
      *(latter) = q;
      latter ++;
      fscanf(f1, "%c", &q);
    }
    inside_tree(pointer,-1, f1);
    fscanf(f1, "%c", &q);
  }
  else
  {
    char* latter = pointer->str;
    while (q != ')')
    {
      *(latter) = q;
      latter ++;
      fscanf(f1, "%c", &q);
    }
  }
}
