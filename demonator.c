#include "demonator.h"
#include "format.h"
#include "exitcode.h"

void show_intro();
void show_error(const char *message);
FILE *open_input_file(const char *name);
FILE *create_output_file(const char *name);
void read_data(void *data,const size_t length,const size_t blocks,FILE *input);
void write_data(const void *data,const size_t length,const size_t blocks,FILE *output);
void go_offset(FILE *target,const unsigned long int offset);
void check_memory(const void *memory);
void check_signature(const char *signature);
char *get_memory(const size_t length);
void data_dump(FILE *input,FILE *output,const size_t length);
void fast_data_dump(FILE *input,FILE *output,const size_t length);
void write_output_file(FILE *input,const char *name,const size_t length);
char *get_name(const char *path,const char *name);
size_t read_head(FILE *input);
glb_subhead *read_table(FILE *input,const size_t amount);
unsigned char check_skip(const glb_subhead current);
void extract(FILE *input,const glb_subhead current,const char *path);
void work(const char *name,const char *path);

int main(int argc, char *argv[])
{
 show_intro();
 if (argc<3)
 {
  puts("You must give a target file name and an output path as the command-line arguments!");
  exit(COMMAND_LINE_ARGUMENTS_ERROR);
 }
 else
 {
  puts("Extracting the files... Please wait");
  work(argv[1],argv[2]);
  puts("The work has been finished");
 }
 return 0;
}

void show_intro()
{
 putchar('\n');
 puts("Demonator. Version 1.0.6");
 puts("DemonStar resource extraction tool by Popov Evgeniy Alekseyevich. 2019-2026 years");
 puts("This software is distributed under the GNU GENERAL PUBLIC LICENSE");
 putchar('\n');
}

void show_error(const char *message)
{
 fputc('\n',stderr);
 fputs(message,stderr);
 fputc('\n',stderr);
}

FILE *open_input_file(const char *name)
{
 FILE *target=NULL;
 if (name==NULL)
 {
  show_error("Can't open the input file");
  exit(OPEN_FILE_ERROR);
 }
 target=fopen(name,"rb");
 if (target==NULL)
 {
  show_error("Can't open the input file");
  exit(OPEN_FILE_ERROR);
 }
 return target;
}

FILE *create_output_file(const char *name)
{
 FILE *target=NULL;
 if (name==NULL)
 {
  show_error("Can't create the ouput file");
  exit(CREATE_FILE_ERROR);
 }
 target=fopen(name,"wb");
 if (target==NULL)
 {
  show_error("Can't create the ouput file");
  exit(CREATE_FILE_ERROR);
 }
 return target;
}

void read_data(void *data,const size_t length,const size_t blocks,FILE *input)
{
 if (fread(data,length,blocks,input)<blocks)
 {
  show_error("Can't read data!");
  exit(READ_DATA_ERROR);
 }

}

void write_data(const void *data,const size_t length,const size_t blocks,FILE *output)
{
 if (fwrite(data,length,blocks,output)<blocks)
 {
  show_error("Can't write data!");
  exit(WRITE_DATA_ERROR);
 }

}

void go_offset(FILE *target,const unsigned long int offset)
{
 if (fseek(target,offset,SEEK_SET)!=0)
 {
  show_error("Can't jump to the target offset");
  exit(SET_FILE_POSITION_ERROR);
 }

}

void check_memory(const void *memory)
{
 if(memory==NULL)
 {
  show_error("Can't allocate memory");
  exit(MEMORY_ALLOCATION_ERROR);
 }

}

void check_signature(const char *signature)
{
 if (strncmp(signature,"GLB2.0",6)!=0)
 {
  show_error("The invalid format");
  exit(INVALID_FORMAT_ERROR);
 }

}

char *get_memory(const size_t length)
{
 char *memory=NULL;
 memory=(char*)calloc(length,sizeof(char));
 check_memory(memory);
 return memory;
}

void data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer=NULL;
 size_t current=0;
 size_t elapsed=0;
 size_t block=4096;
 buffer=get_memory(block);
 for (current=0;current<length;current+=block)
 {
  elapsed=length-current;
  if (elapsed<block)
  {
   block=elapsed;
  }
  read_data(buffer,sizeof(char),block,input);
  write_data(buffer,sizeof(char),block,output);
 }
 free(buffer);
}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer=NULL;
 buffer=(char*)malloc(length);
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  read_data(buffer,sizeof(char),length,input);
  write_data(buffer,sizeof(char),length,output);
  free(buffer);
 }

}

void write_output_file(FILE *input,const char *name,const size_t length)
{
 FILE *output=NULL;
 output=create_output_file(name);
 fast_data_dump(input,output,length);
 fclose(output);
}

char *get_name(const char *path,const char *name)
{
 char *result=NULL;
 size_t path_length=0;
 size_t name_length=0;
 if (path!=NULL)
 {
  path_length=strlen(path);
 }
 if (name!=NULL)
 {
  name_length=strlen(name);
 }
 if (path_length>0)
 {
  if (name_length>0)
  {
   result=get_memory(path_length+name_length+1);
   strncpy(result,path,path_length);
   strncat(result,name,name_length);
  }

 }
 return result;
}

size_t read_head(FILE *input)
{
 glb_head head;
 read_data(&head,sizeof(glb_head),1,input);
 check_signature(head.signature);
 return head.amount;
}

glb_subhead *read_table(FILE *input,const size_t amount)
{
 glb_subhead *table=NULL;
 table=(glb_subhead*)calloc(amount,sizeof(glb_subhead));
 check_memory(table);
 read_data(table,sizeof(glb_subhead),amount,input);
 return table;
}

unsigned char check_skip(const glb_subhead current)
{
 unsigned char result=0;
 size_t length=0;
 length=strlen(current.name);
 if (current.length==0)
 {
  result=1;
 }
 else
 {
  if (current.name[length-1]==':')
  {
   result=1;
  }

 }
 return result;
}

void extract(FILE *input,const glb_subhead current,const char *path)
{
 char *name=NULL;
 name=get_name(path,current.name);
 go_offset(input,current.offset);
 write_output_file(input,name,(size_t)current.length);
 free(name);
}

void work(const char *name,const char *path)
{
 FILE *input=NULL;
 glb_subhead *table=NULL;
 size_t index=0;
 size_t amount=0;
 input=open_input_file(name);
 amount=read_head(input);
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