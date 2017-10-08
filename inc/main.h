/**********************************************************

	Sound Bank Compiler

 **********************************************************/



#define MAX_FILES 50
#define FILE_NAME_SIZE 50
#define MAX_LINE_LENGH 255
#define MAX_NUM_OF_ERRORS 20
#define VAR_NAME_SIZE 50
#define MAX_CTL_SIZE 65536
#define MAX_LIST_SIZE 10000

/**********************************************************
	������ �� ������ ������
 **********************************************************/


typedef char tname[FILE_NAME_SIZE];	// ��� �����
 
typedef struct sfilelist
{
	FILE          *f;					// ��� ����
	unsigned long  lnum;				// ����� ������ ��� �������
	tname	       name;				// ��� �����
} tfilelist;

int push_file( char *name );
int pop_file( void );

extern tfilelist *flist;
extern unsigned long fidx;				// ��������� �� ����

/**********************************************************
	��������� �� �������
 **********************************************************/

extern long numErrors, numWarnings;

void print_e( char *sym, char *message);
void print_w( char *sym, char *message);
void prit_end( void );

/**********************************************************
	����������
 **********************************************************/

extern char var[VAR_NAME_SIZE];
extern char val[VAR_NAME_SIZE];

extern char *ctl;
extern _int32 pos;

int get_params( char *par1, char  *par2, char *par3 );
void compille_file( void );

#define IS(x) (strcmp( var , x ) ==0)
#define XR(x) ((u32)x-(u32)ctl)


/**********************************************************
	���� ��� ��������
 **********************************************************/

typedef struct
{
	char obj;						// ��� �������
	char name[VAR_NAME_SIZE ];		// ��� �������
	long ptr;						// �������� �� ������ �����
} tlist;

#define NOP			0
#define BFILE		1
#define BANK		2
#define INSTRUMENT	3
#define SOUND		4
#define SOUNDOLD	5
#define KEYMAP		6
#define ENVELOPEOLD	7
#define ENVELOPE	8
#define WAVE		9


extern tlist *list;//, *listpos;
extern  unsigned long listidx;

void add_2_list( char objtype, char *name, long val );
tlist *find_in_list( char objtype, char *name );

/**********************************************************
	�������������� � �������� ���
 **********************************************************/

unsigned long long2msb( unsigned long x );
unsigned short short2msb( unsigned short x );

          char  s8val( char *v);
         short  s16val( char *v);
          long  s32val( char *v);
unsigned  char  u8val( char *v);
unsigned short  u16val( char *v);
unsigned  long  u32val( char *v);
unsigned  long  pctlval( char objtype, char *name );
u16			noteval( char *v );
/**********************************************************
	������ � tbl ������
 **********************************************************/

extern unsigned int tblpos;
int opent_tbl(void );
int write_tbl( char *ptr, unsigned int size);
int close_tbl( void);

void write_ctl(void);
void save_list( void );