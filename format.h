typedef struct
{
 char signature[8];
 unsigned long int amount:32;
 char junk[4];
} glb_head;

#pragma pack(push, 1)
typedef struct
{
 unsigned long offset:32;
 unsigned long length:32;
 char name[20];
} glb_subhead;
#pragma pack(pop)