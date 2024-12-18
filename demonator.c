#include "demonator.h"
#include "format.h"

void show_intro();
void show_message(const char *message);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
void go_offset(FILE *file,const unsigned long int offset);
void data_dump(FILE *input,FILE *output,const size_t length);
void fast_data_dump(FILE *input,FILE *output,const size_t length);
void write_output_file(FILE *input,const char *name,const size_t length);
void check_memory(const void *memory);
char *get_string_memory(const size_t length);
char *get_name(const char *path,const char *name);
void check_signature(const char *signature);
unsigned long int read_head(FILE *input);
glb_subhead *read_table(FILE *input,const size_t amount);
unsigned char check_skip(const glb_subhead current);
void extract(FILE *input,const glb_subhead current,const char *path);
void work(const char *name,const char *path);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<3)
 {
  show_message("You must give a target file name and an output path as the command-line arguments!");
 }
 else
 {
  show_message("Extracting a files... Please wait");
  work(argv[1],argv[2]);
  show_message("The work has been finished");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("Demonator. Version 0.9.2");
 puts("DemonStar resource extraction tool by Popov Evgeniy Alekseyevich. 2019-2024 years");
 puts("This software is distributed under GNU GENERAL PUBLIC LICENSE");
}

void show_message(const char *message)
{
 putchar('\n');
 puts(message);
}

FILE *open_input_file(const char *name)
{
 FILE *target;
 target=fopen(name,"rb");
 if (target==NULL)
 {
  puts("Can't open the input file");
  exit(1);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target;
 target=fopen(name,"wb");
 if (target==NULL)
 {
  show_message("Can't create the ouput file");
  exit(2);
 }
 return target;
}

void go_offset(FILE *file,const unsigned long int offset)
{
 if (fseek(file,offset,SEEK_SET)!=0)
 {
  show_message("Can't jump to the target offset");
  exit(3);
 }

}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char data;
 size_t index;
 data=0;
 for (index=0;index<length;++index)
 {
  fread(&data,sizeof(unsigned char),1,input);
  fwrite(&data,sizeof(unsigned char),1,output);
 }

}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 unsigned char *buffer=NULL;
 buffer=(unsigned char*)calloc(length,sizeof(unsigned char));
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  fread(buffer,sizeof(unsigned char),length,input);
  fwrite(buffer,sizeof(unsigned char),length,output);
  free(buffer);
 }

}

void write_output_file(FILE *input,const char *name,const size_t length)
{
 FILE *output;
 output=create_output_file(name);
 fast_data_dump(input,output,length);
 fclose(output);
}

void check_memory(const void *memory)
{
 if(memory==NULL)
 {
  show_message("Can't allocate memory");
  exit(4);
 }

}

char *get_string_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length+1,sizeof(char));
 check_memory(memory);
 return memory;
}

char *get_name(const char *path,const char *name)
{
 char *result;
 size_t length;
 length=strlen(path)+strlen(name);
 result=get_string_memory(length);
 strcpy(result,path);
 return strcat(result,name);
}

void check_signature(const char *signature)
{
 if (strncmp(signature,"GLB2.0",6)!=0)
 {
  puts("Invalid format");
  exit(5);
 }

}

unsigned long int read_head(FILE *input)
{
 glb_head head;
 fread(&head,sizeof(glb_head),1,input);
 check_signature(head.signature);
 return head.amount;
}

glb_subhead *read_table(FILE *input,const size_t amount)
{
 glb_subhead *table;
 table=(glb_subhead*)malloc(amount*sizeof(glb_subhead));
 check_memory(table);
 fread(table,sizeof(glb_subhead),amount,input);
 return table;
}

unsigned char check_skip(const glb_subhead current)
{
 unsigned char result;
 size_t length;
 result=0;
 length=strlen(current.name);
 if ((current.length==0)||(current.name[length-1]==':'))
 {
  result=1;
 }
 return result;
}

void extract(FILE *input,const glb_subhead current,const char *path)
{
 char *name;
 name=get_name(path,current.name);
 go_offset(input,current.offset);
 write_output_file(input,name,(size_t)current.length);
 free(name);
}

void work(const char *name,const char *path)
{
 FILE *input;
 glb_subhead *table;
 size_t index,amount;
 input=open_input_file(name);
 amount=(size_t)read_head(input);
 table=read_table(input,amount);
 for (index=0;index<amount;++index)
 {
  if (check_skip(table[index])==0)
  {
   extract(input,table[index],path);
  }

 }
 fclose(input);
 free(table);
}