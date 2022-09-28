#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED
#define filePath "Points.txt"
//////////////////////////File////////////////////////////////////////////////
void Save_To_File()
{
  int i=0;
  FILE* f = fopen(filePath, "w");
  while(true){
     if(points[i][0]==NULL||i==5) break;
     fprintf(f,"%lf %lf \n",points[i][0],points[i][1]);
     i++;
  }
  fclose(f);

}
//load to file
void LoadFromFile()
{
   // Open file to read region data from
   FILE* f = fopen(filePath, "rb");
   int i=0;
   char line[100];
   //read from file
   while (fgets(line, 100, f))
   {
      if(line[0]==' ') break;
      sscanf(line, "%lf %lf", &points[i][0], &points[i][1]);
      i++;
   }
   index=i;

}


#endif // FILE_H_INCLUDED
