// Gupte, Nihar.
// nag6441
// 2020-04-06
//----------------------------------------------------------
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "model.h"

//----------------------------------------------------------
Model *allocModel(int numVertices, int numFaces)
{
  // TODO: Allocate a Model structure.
  //       Initialize its fields using the given number of
  //         vertices and faces.
  //       Return a pointer to the Model structure as the
  //         result of this function.
  // (You can use calloc() to allocate zeroed out memory.  This
  //  is useful when allocating the vertex and face arrays.)

  Model *structure = (Model *)calloc(1, sizeof(Model)); //1 block in memory is allocated to Model structure of size of the type Model
  if (structure == NULL)                                //error in calloc
  {
    perror("Error allocating model.\n");
    exit(1);
  }

  if (numFaces > 0) //allocating only if faces exist
  {
    structure->m_numFaces = numFaces;
    Face *face = (Face *)calloc(numFaces, sizeof(Face)); //numFaces blocks in memory is allocated to type Face
    if (face == NULL)                                    //error in calloc
    {
      perror("Error allocating faces.\n");
      exit(1);
    }
    structure->m_face = face;
  }

  if (numVertices > 0) //allocating only if vertices exist
  {
    structure->m_numVertices = numVertices;
    Vertex *vertex = (Vertex *)calloc(numVertices, sizeof(Vertex)); //numVertices blocks in memory is allocated to type Face
    if (vertex == NULL)                                             //error in calloc
    {
      perror("Error allocating vertices.\n");
      exit(1);
    }
    structure->m_vertex = vertex;
  }

  return structure; //returning Model type after allocations
}

//----------------------------------------------------------
void dumpModel(Model *model)
{
  printf("#- Model parameters --------------------\n");
  printf("Vertex count : %5d\n", model->m_numVertices);
  printf("Face count   : %5d\n", model->m_numFaces);

  printf("\n#- Vertex list -------------------------\n");
  for (int i = 0; i < model->m_numVertices; i++)
  {
    printf("  [%5d]  ", i);
    dumpVertex(&model->m_vertex[i]);
    putc('\n', stdout);
  }

  printf("\n#- Face list ---------------------------\n");
  for (int i = 0; i < model->m_numFaces; i++)
  {
    printf("  [%5d]  ", i);
    dumpFace(&model->m_face[i]);
    putc('\n', stdout);
  }

  printf("#---------------------------------------\n");
}

//----------------------------------------------------------
void freeModel(Model *model)
{
  // TODO: Free the vertex and face data of the given model.
  //       Free the model structure itself.

  if (model->m_face != NULL) //if not already freed, then free
  {
    free(model->m_face);
  }

  if (model->m_vertex != NULL) //if not already freed, then free
  {
    free(model->m_vertex);
  }

  if (model != NULL) //if not already freed, then free
  {
    free(model);
  }
}

//----------------------------------------------------------
Model *loadModel(char *fName)
{
  // TODO: Open the file indicated by fName.
  //       Determine how many vertex lines and how many face
  //         lines it includes.
  //       Allocate a Model structure using the vertex and face
  //         counts as arguments.
  //       Read each vertex line from the file and save its X, Y,
  //         Z coordinates.
  //       Read each face line from the file and save its three
  //         vertex numbers.  Don't forget to subtract one from
  //         each number so it can be used as an index into the
  //         vertex list.
  //       Return a pointer to the allocated model structure as
  //         the value of this function.

  //Open the file indicated by fName.
  FILE *file = fopen(fName, "r");
  if (file == NULL)
  {
    perror("Error in opening file.\n");
    exit(1);
  }

  //Determine how many vertex lines and how many face lines it includes.
  int num_of_vertex = 0;
  int num_of_face = 0;
  char templine[100];

  while (fgets(templine, 100, file) != NULL)
  {
    char ch = templine[0];
    int i = 0;
    while (isspace(ch) && i < 100) //checking for abnormal leading spaces
    {
      ch = templine[i + 1];
      i++;
    }
    ch = templine[i];
    if (ch == 'v')
    {
      num_of_vertex++;
    }
    if (ch == 'f')
    {
      num_of_face++;
    }
  }

  rewind(file);

  //Allocate a Model structure using the vertex and face counts as arguments.
  Model *structure = allocModel(num_of_vertex, num_of_face);
  Vertex *vertex = structure->m_vertex;
  Face *face = structure->m_face;

  //Read each vertex line from the file and save its X, Y, Z coordinates.

  char templine2[1000];
  int line_num=0;

  while (fgets(templine2, 100, file) != NULL)
  {
    line_num++;
    double x1, x2, x3;
    char c1;
    int parameters = sscanf(templine2, "%c %lf %lf %lf", &c1, &x1, &x2, &x3);    
    if(parameters!=4 && c1=='v')
    {
      fprintf(stderr,"line %d has error for a 'v'\n",line_num);
    }

    if (c1 == 'v')
    {
      vertex->x = x1;
      vertex->y = x2;
      vertex->z = x3;
      vertex++;
      //printf("%lf %lf %lf\n", x1, x2, x3);
    }
  }

  rewind(file);
  line_num=0;

  while (fgets(templine2, 100, file) != NULL)
  {
    line_num++;
    int f1, f2, f3;
    char c2;
    int parameters = sscanf(templine2, "%c %d %d %d", &c2, &f1, &f2, &f3);
    if(parameters!=4 && c2=='f')
    {
      fprintf(stderr,"line %d has error for a 'f'\n",line_num);
    }

    if (c2 == 'f')
    {
      face->v1 = --f1;
      face->v2 = --f2;
      face->v3 = --f3;
      face++;
      //printf("%d %d %d\n",f1,f2,f3);
    }
  }
  

  fclose(file); //closing file after reading

  //Return a pointer to the allocated model structure as the value of this function.
  return structure;
}

//----------------------------------------------------------
