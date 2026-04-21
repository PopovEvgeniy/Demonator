typedef struct
{
 char signature[8];
 unsigned int amount;
 char junk[4];
} glb_head;

#pragma pack(push, 1)
typedef struct
{
 unsigned int offset;
 unsigned int length;
 char name[20];
} glb_subhead;
#pragma pack(pop)