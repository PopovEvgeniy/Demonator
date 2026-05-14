#include "demonator.h"
#include "format.h"

void show_intro();
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
 puts("Demonator. Version 1.0.2");
 puts("DemonStar resource extraction tool by Popov Evgeniy Alekseyevich. 2019-2026 years");
 puts("This software is distributed under the GNU GENERAL PUBLIC LICENSE");
 putchar('\n');
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
  puts("Can't create the ouput file");
  exit(2);
 }
 return target;
}

void read_data(void *data,const size_t length,const size_t blocks,FILE *input)
{
 fread(data,length,blocks,input);
 if (ferror(input)!=0)
 {
  puts("Can't read data!");
  exit(3);
 }

}

void write_data(const void *data,const size_t length,const size_t blocks,FILE *output)
{
 fwrite(data,length,blocks,output);
 if (ferror(output)!=0)
 {
  puts("Can't write data!");
  exit(4);
 }

}

void go_offset(FILE *target,const unsigned long int offset)
{
 if (fseek(target,offset,SEEK_SET)!=0)
 {
  puts("Can't jump to the target offset");
  exit(5);
 }

}

void check_memory(const void *memory)
{
 if(memory==NULL)
 {
  puts("Can't allocate memory");
  exit(6);
 }

}

void check_signature(const char *signature)
{
 if (strncmp(signature,"GLB2.0",6)!=0)
 {
  puts("The invalid format");
  exit(7);
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
 char *buffer;
 size_t current,elapsed,block;
 elapsed=0;
 block=4096;
 buffer=get_memory(block);
 for (current=0;current<length;current+=block)
 {
  elapsed=length-current;
  if (elapsed<block)
  {
   block=elapsed;
  }
  read_data(buffer,block,sizeof(char),input);
  write_data(buffer,block,sizeof(char),output);
 }
 free(buffer);
}

void fast_data_dump(FILE *input,FILE *output,const size_t length)
{
 char *buffer;
 buffer=(char*)malloc(length);
 if (buffer==NULL)
 {
  data_dump(input,output,length);
 }
 else
 {
  read_data(buffer,length,sizeof(char),input);
  write_data(buffer,length,sizeof(char),output);
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

char *get_name(const char *path,const char *name)
{
 char *result;
 size_t length;
 length=strlen(path)+strlen(name);
 result=get_memory(length+1);
 sprintf(result,"%s%s",path,name);
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
 glb_subhead *table;
 table=(glb_subhead*)calloc(amount,sizeof(glb_subhead));
 check_memory(table);
 read_data(table,sizeof(glb_subhead),amount,input);
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