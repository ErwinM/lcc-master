
// Register declration enumeration here
enum {R0=0, R1=1, R2=2, R3=3, R4=4, R5=5 };

enum {R_L0=0, R_L1=1, R_L2=2, R_L3=3, R_B=4, R_A=5, R_C=6};
enum {R_F0=0, R_F1=1, R_F2=2, R_F3=3, R_F4=4, R_F5=5, R_F6=6, R_F7=7,
      R_F8=8, R_F9=9, R_F10=10, R_F11=11, R_F12=12, R_F13=13, R_F14=14, R_F15=15};

#include "c.h"

#define NODEPTR_TYPE Node
#define OP_LABEL(p) ((p)->op)
#define LEFT_CHILD(p) ((p)->kids[0])
#define RIGHT_CHILD(p) ((p)->kids[1])
#define STATE_LABEL(p) ((p)->x.state)

// Declare local routines to be used by IR record here
static void address(Symbol, Symbol, long);
static void blkfetch(int, int, int, int);
static void blkloop(int, int, int, int, int, int[]);
static void blkstore(int, int, int, int);
static void defaddress(Symbol);
static void defconst(int, int, Value);
static void defstring(int, char *);
static void defsymbol(Symbol);
static void doarg(Node);
static void emit2(Node);
static void export(Symbol);
static void clobber(Node);
static void function(Symbol, Symbol [], Symbol [], int);
static void global(Symbol);
static void import(Symbol);
static void local(Symbol);
static void progbeg(int, char **);
static void progend(void);
static void segment(int);
static void space(int);
static void target(Node);
static int memop(Node);
static int flip_memop(Node);
static int isfloat4(Node);
static int isgta1(Node);
static int isfloat8(Node);
static int sametree(Node,Node);
static int isfptr(Node n, int iftrue, int iffalse);

// Local vars here

static Symbol longreg[32];
static Symbol intreg[32];
static Symbol fltreg[32];

static int used_longs;
static int used_floats;
static int ever_used_floats;

static Symbol longwldcrd;
static Symbol intwldcrd;
static Symbol cwldcrd;
static Symbol fltwldcrd;

static int current_seg;

static int double_ptr = 0;
/*
generated at Sun Mar 12 21:07:22 2017
by $Id$
*/
static void _kids(NODEPTR_TYPE, int, NODEPTR_TYPE[]);
static void _label(NODEPTR_TYPE);
static int _rule(void*, int);

#define _stmt_NT 1
#define _reg_NT 2
#define _con_NT 3
#define _acon_NT 4
#define _laddr_NT 5
#define _addr_NT 6
#define _jaddr_NT 7
#define _base_NT 8
#define _baddr_NT 9
#define _rc_NT 10
#define _rc5_NT 11
#define _ar_NT 12

static char *_ntname[] = {
	0,
	"stmt",
	"reg",
	"con",
	"acon",
	"laddr",
	"addr",
	"jaddr",
	"base",
	"baddr",
	"rc",
	"rc5",
	"ar",
	0
};

struct _state {
	short cost[13];
	struct {
		unsigned int _stmt:6;
		unsigned int _reg:7;
		unsigned int _con:3;
		unsigned int _acon:2;
		unsigned int _laddr:2;
		unsigned int _addr:2;
		unsigned int _jaddr:1;
		unsigned int _base:3;
		unsigned int _baddr:1;
		unsigned int _rc:2;
		unsigned int _rc5:2;
		unsigned int _ar:2;
	} rule;
};

static short _nts_0[] = { 0 };
static short _nts_1[] = { _reg_NT, 0 };
static short _nts_2[] = { _con_NT, 0 };
static short _nts_3[] = { _laddr_NT, 0 };
static short _nts_4[] = { _jaddr_NT, 0 };
static short _nts_5[] = { _baddr_NT, 0 };
static short _nts_6[] = { _base_NT, 0 };
static short _nts_7[] = { _addr_NT, _reg_NT, 0 };
static short _nts_8[] = { _addr_NT, 0 };
static short _nts_9[] = { _reg_NT, _reg_NT, 0 };
static short _nts_10[] = { _reg_NT, _rc_NT, 0 };
static short _nts_11[] = { _reg_NT, _rc5_NT, 0 };
static short _nts_12[] = { _acon_NT, 0 };
static short _nts_13[] = { _ar_NT, 0 };
static short _nts_14[] = { _rc_NT, 0 };

static short *_nts[] = {
	0,	/* 0 */
	_nts_0,	/* 1 */
	_nts_0,	/* 2 */
	_nts_0,	/* 3 */
	_nts_0,	/* 4 */
	_nts_0,	/* 5 */
	_nts_0,	/* 6 */
	_nts_0,	/* 7 */
	_nts_1,	/* 8 */
	_nts_1,	/* 9 */
	_nts_1,	/* 10 */
	_nts_1,	/* 11 */
	_nts_1,	/* 12 */
	_nts_1,	/* 13 */
	_nts_0,	/* 14 */
	_nts_0,	/* 15 */
	_nts_0,	/* 16 */
	_nts_0,	/* 17 */
	_nts_0,	/* 18 */
	_nts_0,	/* 19 */
	_nts_0,	/* 20 */
	_nts_1,	/* 21 */
	_nts_2,	/* 22 */
	_nts_0,	/* 23 */
	_nts_0,	/* 24 */
	_nts_3,	/* 25 */
	_nts_0,	/* 26 */
	_nts_0,	/* 27 */
	_nts_4,	/* 28 */
	_nts_0,	/* 29 */
	_nts_0,	/* 30 */
	_nts_0,	/* 31 */
	_nts_1,	/* 32 */
	_nts_5,	/* 33 */
	_nts_1,	/* 34 */
	_nts_6,	/* 35 */
	_nts_0,	/* 36 */
	_nts_0,	/* 37 */
	_nts_0,	/* 38 */
	_nts_0,	/* 39 */
	_nts_0,	/* 40 */
	_nts_0,	/* 41 */
	_nts_0,	/* 42 */
	_nts_7,	/* 43 */
	_nts_7,	/* 44 */
	_nts_7,	/* 45 */
	_nts_7,	/* 46 */
	_nts_7,	/* 47 */
	_nts_7,	/* 48 */
	_nts_7,	/* 49 */
	_nts_8,	/* 50 */
	_nts_8,	/* 51 */
	_nts_3,	/* 52 */
	_nts_5,	/* 53 */
	_nts_8,	/* 54 */
	_nts_8,	/* 55 */
	_nts_8,	/* 56 */
	_nts_8,	/* 57 */
	_nts_8,	/* 58 */
	_nts_8,	/* 59 */
	_nts_8,	/* 60 */
	_nts_8,	/* 61 */
	_nts_9,	/* 62 */
	_nts_9,	/* 63 */
	_nts_9,	/* 64 */
	_nts_9,	/* 65 */
	_nts_9,	/* 66 */
	_nts_9,	/* 67 */
	_nts_2,	/* 68 */
	_nts_1,	/* 69 */
	_nts_10,	/* 70 */
	_nts_10,	/* 71 */
	_nts_10,	/* 72 */
	_nts_10,	/* 73 */
	_nts_10,	/* 74 */
	_nts_10,	/* 75 */
	_nts_10,	/* 76 */
	_nts_10,	/* 77 */
	_nts_10,	/* 78 */
	_nts_10,	/* 79 */
	_nts_10,	/* 80 */
	_nts_10,	/* 81 */
	_nts_0,	/* 82 */
	_nts_1,	/* 83 */
	_nts_11,	/* 84 */
	_nts_11,	/* 85 */
	_nts_11,	/* 86 */
	_nts_11,	/* 87 */
	_nts_1,	/* 88 */
	_nts_1,	/* 89 */
	_nts_1,	/* 90 */
	_nts_1,	/* 91 */
	_nts_1,	/* 92 */
	_nts_1,	/* 93 */
	_nts_1,	/* 94 */
	_nts_1,	/* 95 */
	_nts_1,	/* 96 */
	_nts_1,	/* 97 */
	_nts_1,	/* 98 */
	_nts_1,	/* 99 */
	_nts_1,	/* 100 */
	_nts_0,	/* 101 */
	_nts_12,	/* 102 */
	_nts_1,	/* 103 */
	_nts_1,	/* 104 */
	_nts_9,	/* 105 */
	_nts_9,	/* 106 */
	_nts_9,	/* 107 */
	_nts_9,	/* 108 */
	_nts_9,	/* 109 */
	_nts_9,	/* 110 */
	_nts_9,	/* 111 */
	_nts_9,	/* 112 */
	_nts_9,	/* 113 */
	_nts_9,	/* 114 */
	_nts_9,	/* 115 */
	_nts_9,	/* 116 */
	_nts_0,	/* 117 */
	_nts_13,	/* 118 */
	_nts_13,	/* 119 */
	_nts_13,	/* 120 */
	_nts_13,	/* 121 */
	_nts_1,	/* 122 */
	_nts_0,	/* 123 */
	_nts_1,	/* 124 */
	_nts_1,	/* 125 */
	_nts_1,	/* 126 */
	_nts_1,	/* 127 */
	_nts_14,	/* 128 */
	_nts_14,	/* 129 */
	_nts_14,	/* 130 */
	_nts_1,	/* 131 */
	_nts_9,	/* 132 */
};

static char *_templates[] = {
/* 0 */	0,
/* 1 */	"# read register\n",	/* reg: INDIRI1(VREGP) */
/* 2 */	"# read register\n",	/* reg: INDIRU1(VREGP) */
/* 3 */	"# read register\n",	/* reg: INDIRI2(VREGP) */
/* 4 */	"# read register\n",	/* reg: INDIRU2(VREGP) */
/* 5 */	"# read register\n",	/* reg: INDIRI4(VREGP) */
/* 6 */	"# read register\n",	/* reg: INDIRU4(VREGP) */
/* 7 */	"# read register\n",	/* reg: INDIRP2(VREGP) */
/* 8 */	"# write register\n",	/* stmt: ASGNI1(VREGP,reg) */
/* 9 */	"# write register\n",	/* stmt: ASGNU1(VREGP,reg) */
/* 10 */	"# write register\n",	/* stmt: ASGNI2(VREGP,reg) */
/* 11 */	"# write register\n",	/* stmt: ASGNU2(VREGP,reg) */
/* 12 */	"# write register\n",	/* stmt: ASGNI4(VREGP,reg) */
/* 13 */	"# write register\n",	/* stmt: ASGNU4(VREGP,reg) */
/* 14 */	"%a",	/* con: CNSTI1 */
/* 15 */	"%a",	/* con: CNSTU1 */
/* 16 */	"%a",	/* con: CNSTI2 */
/* 17 */	"%a",	/* con: CNSTU2 */
/* 18 */	"%a",	/* con: CNSTI4 */
/* 19 */	"%a",	/* con: CNSTU4 */
/* 20 */	"%a",	/* con: CNSTP2 */
/* 21 */	"",	/* stmt: reg */
/* 22 */	"%0",	/* acon: con */
/* 23 */	"%a(bp)",	/* laddr: ADDRFP2 */
/* 24 */	"%a(bp)",	/* laddr: ADDRLP2 */
/* 25 */	"%0",	/* addr: laddr */
/* 26 */	"%a XX",	/* acon: ADDRGP2 */
/* 27 */	"%a XX",	/* jaddr: ADDRGP2 */
/* 28 */	"%0",	/* addr: jaddr */
/* 29 */	"%a-9",	/* base: ADDRGP2 */
/* 30 */	"%a-10",	/* base: ADDRLP2 */
/* 31 */	"%a-11",	/* base: ADDRFP2 */
/* 32 */	"%0 ",	/* base: reg */
/* 33 */	"%0",	/* addr: baddr */
/* 34 */	"%0",	/* baddr: reg */
/* 35 */	"\tlda\t$%c,%0>7\n",	/* reg: base */
/* 36 */	"# reg\n",	/* reg: CNSTI1 */
/* 37 */	"# reg\n",	/* reg: CNSTI2 */
/* 38 */	"# reg\n",	/* reg: CNSTI4 */
/* 39 */	"# reg\n",	/* reg: CNSTU1 */
/* 40 */	"# reg\n",	/* reg: CNSTU2 */
/* 41 */	"# reg\n",	/* reg: CNSTU4 */
/* 42 */	"# reg\n",	/* reg: CNSTP2 */
/* 43 */	"sb $%1,%0\n",	/* stmt: ASGNI1(addr,reg) */
/* 44 */	"sb $%1,%0\n",	/* stmt: ASGNU1(addr,reg) */
/* 45 */	"\tstw\t%1,%0\n",	/* stmt: ASGNI2(addr,reg) */
/* 46 */	"\tstw\t%1,%0\n",	/* stmt: ASGNU2(addr,reg) */
/* 47 */	"sw $%1,%0\n",	/* stmt: ASGNI4(addr,reg) */
/* 48 */	"sw $%1,%0\n",	/* stmt: ASGNU4(addr,reg) */
/* 49 */	"sw $%1,%0\n",	/* stmt: ASGNP2(addr,reg) */
/* 50 */	"lb $%c,%0\n",	/* reg: INDIRI1(addr) */
/* 51 */	"lbu $%c,%0\n",	/* reg: INDIRU1(addr) */
/* 52 */	"\tldw\t%c,%0\n",	/* reg: INDIRI2(laddr) */
/* 53 */	"\tldw.i\t%c,%0\n",	/* reg: INDIRI2(baddr) */
/* 54 */	"\tldw\t%c,%0\n",	/* reg: INDIRU2(addr) */
/* 55 */	"lw $%c,%0\n",	/* reg: INDIRI4(addr) */
/* 56 */	"lw $%c,%0\n",	/* reg: INDIRU4(addr) */
/* 57 */	"lw $%c,%0\n",	/* reg: INDIRP2(addr) */
/* 58 */	"lb $%c,%0\n",	/* reg: CVII2(INDIRI1(addr)) */
/* 59 */	"lbu $%c,%0\n",	/* reg: CVUU2(INDIRU1(addr)) */
/* 60 */	"lbu $%c,%0\n",	/* reg: CVUI2(INDIRU1(addr)) */
/* 61 */	"lhu $%c,%0\n",	/* reg: CVUI2(INDIRU2(addr)) */
/* 62 */	"div $%c,$%0,$%1\n",	/* reg: DIVI2(reg,reg) */
/* 63 */	"divu $%c,$%0,$%1\n",	/* reg: DIVU2(reg,reg) */
/* 64 */	"rem $%c,$%0,$%1\n",	/* reg: MODI2(reg,reg) */
/* 65 */	"remu $%c,$%0,$%1\n",	/* reg: MODU2(reg,reg) */
/* 66 */	"mul $%c,$%0,$%1\n",	/* reg: MULI2(reg,reg) */
/* 67 */	"mul $%c,$%0,$%1\n",	/* reg: MULU2(reg,reg) */
/* 68 */	"%0",	/* rc: con */
/* 69 */	"$%0",	/* rc: reg */
/* 70 */	"\taddi\t%c,%0,%1\n",	/* reg: ADDI2(reg,rc) */
/* 71 */	"\taddi\t%c,%0,%1\n",	/* reg: ADDP2(reg,rc) */
/* 72 */	"\taddi\t%c,%0,%1\n",	/* reg: ADDU2(reg,rc) */
/* 73 */	"and $%c,$%0,%1\n",	/* reg: BANDI2(reg,rc) */
/* 74 */	"or $%c,$%0,%1\n",	/* reg: BORI2(reg,rc) */
/* 75 */	"xor $%c,$%0,%1\n",	/* reg: BXORI2(reg,rc) */
/* 76 */	"and $%c,$%0,%1\n",	/* reg: BANDU2(reg,rc) */
/* 77 */	"or $%c,$%0,%1\n",	/* reg: BORU2(reg,rc) */
/* 78 */	"xor $%c,$%0,%1\n",	/* reg: BXORU2(reg,rc) */
/* 79 */	"subu $%c,$%0,%1\n",	/* reg: SUBI2(reg,rc) */
/* 80 */	"subu $%c,$%0,%1\n",	/* reg: SUBP2(reg,rc) */
/* 81 */	"subu $%c,$%0,%1\n",	/* reg: SUBU2(reg,rc) */
/* 82 */	"%a",	/* rc5: CNSTI2 */
/* 83 */	"$%0",	/* rc5: reg */
/* 84 */	"sll $%c,$%0,%1\n",	/* reg: LSHI2(reg,rc5) */
/* 85 */	"sll $%c,$%0,%1\n",	/* reg: LSHU2(reg,rc5) */
/* 86 */	"sra $%c,$%0,%1\n",	/* reg: RSHI2(reg,rc5) */
/* 87 */	"srl $%c,$%0,%1\n",	/* reg: RSHU2(reg,rc5) */
/* 88 */	"not $%c,$%0\n",	/* reg: BCOMI2(reg) */
/* 89 */	"not $%c,$%0\n",	/* reg: BCOMU2(reg) */
/* 90 */	"negu $%c,$%0\n",	/* reg: NEGI2(reg) */
/* 91 */	"move $%c,$%0\n",	/* reg: LOADI1(reg) */
/* 92 */	"move $%c,$%0\n",	/* reg: LOADU1(reg) */
/* 93 */	"move $%c,$%0\n",	/* reg: LOADI2(reg) */
/* 94 */	"move $%c,$%0\n",	/* reg: LOADU2(reg) */
/* 95 */	"move $%c,$%0\n",	/* reg: LOADI4(reg) */
/* 96 */	"move $%c,$%0\n",	/* reg: LOADP2(reg) */
/* 97 */	"move $%c,$%0\n",	/* reg: LOADU4(reg) */
/* 98 */	"sll $%c,$%0,8*(4-%a); sra $%c,$%c,8*(4-%a)\n",	/* reg: CVII2(reg) */
/* 99 */	"and $%c,$%0,(1<<(8*%a))-1\n",	/* reg: CVUI2(reg) */
/* 100 */	"and $%c,$%0,(1<<(8*%a))-1\n",	/* reg: CVUU2(reg) */
/* 101 */	"%a:\n",	/* stmt: LABELV */
/* 102 */	"b %0\n",	/* stmt: JUMPV(acon) */
/* 103 */	".cpadd $%0\nj $%0\n",	/* stmt: JUMPV(reg) */
/* 104 */	"j $%0\n",	/* stmt: JUMPV(reg) */
/* 105 */	"beq $%0,$%1,%a\n",	/* stmt: EQI2(reg,reg) */
/* 106 */	"beq $%0,$%1,%a\n",	/* stmt: EQU2(reg,reg) */
/* 107 */	"bge $%0,$%1,%a\n",	/* stmt: GEI2(reg,reg) */
/* 108 */	"bgeu $%0,$%1,%a\n",	/* stmt: GEU2(reg,reg) */
/* 109 */	"bgt $%0,$%1,%a\n",	/* stmt: GTI2(reg,reg) */
/* 110 */	"bgtu $%0,$%1,%a\n",	/* stmt: GTU2(reg,reg) */
/* 111 */	"ble $%0,$%1,%a\n",	/* stmt: LEI2(reg,reg) */
/* 112 */	"bleu $%0,$%1,%a\n",	/* stmt: LEU2(reg,reg) */
/* 113 */	"blt $%0,$%1,%a\n",	/* stmt: LTI2(reg,reg) */
/* 114 */	"bltu $%0,$%1,%a\n",	/* stmt: LTU2(reg,reg) */
/* 115 */	"bne $%0,$%1,%a\n",	/* stmt: NEI2(reg,reg) */
/* 116 */	"bne $%0,$%1,%a\n",	/* stmt: NEU2(reg,reg) */
/* 117 */	"%a 111",	/* ar: ADDRGP2 */
/* 118 */	"\tpush\tpc\nbr\t%0\n",	/* reg: CALLI2(ar) */
/* 119 */	"jal %0\n",	/* reg: CALLP2(ar) */
/* 120 */	"jal %0\n",	/* reg: CALLU2(ar) */
/* 121 */	"jal %0\n",	/* stmt: CALLV(ar) */
/* 122 */	"$%0",	/* ar: reg */
/* 123 */	"%a",	/* ar: CNSTP2 */
/* 124 */	"# ret\n",	/* stmt: RETI2(reg) */
/* 125 */	"# ret\n",	/* stmt: RETU2(reg) */
/* 126 */	"# ret\n",	/* stmt: RETP2(reg) */
/* 127 */	"# ret\n",	/* stmt: RETV(reg) */
/* 128 */	"\tpush\t%0\n",	/* stmt: ARGI2(rc) */
/* 129 */	"\tpush\t%0\n",	/* stmt: ARGU2(rc) */
/* 130 */	"\tpush\t%0\n",	/* stmt: ARGP2(rc) */
/* 131 */	"# argb %0\n",	/* stmt: ARGB(INDIRB(reg)) */
/* 132 */	"# asgnb %0 %1\n",	/* stmt: ASGNB(reg,INDIRB(reg)) */
};

static char _isinstruction[] = {
/* 0 */	0,
/* 1 */	1,	/* # read register\n */
/* 2 */	1,	/* # read register\n */
/* 3 */	1,	/* # read register\n */
/* 4 */	1,	/* # read register\n */
/* 5 */	1,	/* # read register\n */
/* 6 */	1,	/* # read register\n */
/* 7 */	1,	/* # read register\n */
/* 8 */	1,	/* # write register\n */
/* 9 */	1,	/* # write register\n */
/* 10 */	1,	/* # write register\n */
/* 11 */	1,	/* # write register\n */
/* 12 */	1,	/* # write register\n */
/* 13 */	1,	/* # write register\n */
/* 14 */	0,	/* %a */
/* 15 */	0,	/* %a */
/* 16 */	0,	/* %a */
/* 17 */	0,	/* %a */
/* 18 */	0,	/* %a */
/* 19 */	0,	/* %a */
/* 20 */	0,	/* %a */
/* 21 */	0,	/*  */
/* 22 */	0,	/* %0 */
/* 23 */	0,	/* %a(bp) */
/* 24 */	0,	/* %a(bp) */
/* 25 */	0,	/* %0 */
/* 26 */	0,	/* %a XX */
/* 27 */	0,	/* %a XX */
/* 28 */	0,	/* %0 */
/* 29 */	0,	/* %a-9 */
/* 30 */	0,	/* %a-10 */
/* 31 */	0,	/* %a-11 */
/* 32 */	0,	/* %0  */
/* 33 */	0,	/* %0 */
/* 34 */	0,	/* %0 */
/* 35 */	1,	/* \tlda\t$%c,%0>7\n */
/* 36 */	1,	/* # reg\n */
/* 37 */	1,	/* # reg\n */
/* 38 */	1,	/* # reg\n */
/* 39 */	1,	/* # reg\n */
/* 40 */	1,	/* # reg\n */
/* 41 */	1,	/* # reg\n */
/* 42 */	1,	/* # reg\n */
/* 43 */	1,	/* sb $%1,%0\n */
/* 44 */	1,	/* sb $%1,%0\n */
/* 45 */	1,	/* \tstw\t%1,%0\n */
/* 46 */	1,	/* \tstw\t%1,%0\n */
/* 47 */	1,	/* sw $%1,%0\n */
/* 48 */	1,	/* sw $%1,%0\n */
/* 49 */	1,	/* sw $%1,%0\n */
/* 50 */	1,	/* lb $%c,%0\n */
/* 51 */	1,	/* lbu $%c,%0\n */
/* 52 */	1,	/* \tldw\t%c,%0\n */
/* 53 */	1,	/* \tldw.i\t%c,%0\n */
/* 54 */	1,	/* \tldw\t%c,%0\n */
/* 55 */	1,	/* lw $%c,%0\n */
/* 56 */	1,	/* lw $%c,%0\n */
/* 57 */	1,	/* lw $%c,%0\n */
/* 58 */	1,	/* lb $%c,%0\n */
/* 59 */	1,	/* lbu $%c,%0\n */
/* 60 */	1,	/* lbu $%c,%0\n */
/* 61 */	1,	/* lhu $%c,%0\n */
/* 62 */	1,	/* div $%c,$%0,$%1\n */
/* 63 */	1,	/* divu $%c,$%0,$%1\n */
/* 64 */	1,	/* rem $%c,$%0,$%1\n */
/* 65 */	1,	/* remu $%c,$%0,$%1\n */
/* 66 */	1,	/* mul $%c,$%0,$%1\n */
/* 67 */	1,	/* mul $%c,$%0,$%1\n */
/* 68 */	0,	/* %0 */
/* 69 */	0,	/* $%0 */
/* 70 */	1,	/* \taddi\t%c,%0,%1\n */
/* 71 */	1,	/* \taddi\t%c,%0,%1\n */
/* 72 */	1,	/* \taddi\t%c,%0,%1\n */
/* 73 */	1,	/* and $%c,$%0,%1\n */
/* 74 */	1,	/* or $%c,$%0,%1\n */
/* 75 */	1,	/* xor $%c,$%0,%1\n */
/* 76 */	1,	/* and $%c,$%0,%1\n */
/* 77 */	1,	/* or $%c,$%0,%1\n */
/* 78 */	1,	/* xor $%c,$%0,%1\n */
/* 79 */	1,	/* subu $%c,$%0,%1\n */
/* 80 */	1,	/* subu $%c,$%0,%1\n */
/* 81 */	1,	/* subu $%c,$%0,%1\n */
/* 82 */	0,	/* %a */
/* 83 */	0,	/* $%0 */
/* 84 */	1,	/* sll $%c,$%0,%1\n */
/* 85 */	1,	/* sll $%c,$%0,%1\n */
/* 86 */	1,	/* sra $%c,$%0,%1\n */
/* 87 */	1,	/* srl $%c,$%0,%1\n */
/* 88 */	1,	/* not $%c,$%0\n */
/* 89 */	1,	/* not $%c,$%0\n */
/* 90 */	1,	/* negu $%c,$%0\n */
/* 91 */	1,	/* move $%c,$%0\n */
/* 92 */	1,	/* move $%c,$%0\n */
/* 93 */	1,	/* move $%c,$%0\n */
/* 94 */	1,	/* move $%c,$%0\n */
/* 95 */	1,	/* move $%c,$%0\n */
/* 96 */	1,	/* move $%c,$%0\n */
/* 97 */	1,	/* move $%c,$%0\n */
/* 98 */	1,	/* sll $%c,$%0,8*(4-%a); sra $%c,$%c,8*(4-%a)\n */
/* 99 */	1,	/* and $%c,$%0,(1<<(8*%a))-1\n */
/* 100 */	1,	/* and $%c,$%0,(1<<(8*%a))-1\n */
/* 101 */	1,	/* %a:\n */
/* 102 */	1,	/* b %0\n */
/* 103 */	1,	/* .cpadd $%0\nj $%0\n */
/* 104 */	1,	/* j $%0\n */
/* 105 */	1,	/* beq $%0,$%1,%a\n */
/* 106 */	1,	/* beq $%0,$%1,%a\n */
/* 107 */	1,	/* bge $%0,$%1,%a\n */
/* 108 */	1,	/* bgeu $%0,$%1,%a\n */
/* 109 */	1,	/* bgt $%0,$%1,%a\n */
/* 110 */	1,	/* bgtu $%0,$%1,%a\n */
/* 111 */	1,	/* ble $%0,$%1,%a\n */
/* 112 */	1,	/* bleu $%0,$%1,%a\n */
/* 113 */	1,	/* blt $%0,$%1,%a\n */
/* 114 */	1,	/* bltu $%0,$%1,%a\n */
/* 115 */	1,	/* bne $%0,$%1,%a\n */
/* 116 */	1,	/* bne $%0,$%1,%a\n */
/* 117 */	0,	/* %a 111 */
/* 118 */	1,	/* \tpush\tpc\nbr\t%0\n */
/* 119 */	1,	/* jal %0\n */
/* 120 */	1,	/* jal %0\n */
/* 121 */	1,	/* jal %0\n */
/* 122 */	0,	/* $%0 */
/* 123 */	0,	/* %a */
/* 124 */	1,	/* # ret\n */
/* 125 */	1,	/* # ret\n */
/* 126 */	1,	/* # ret\n */
/* 127 */	1,	/* # ret\n */
/* 128 */	1,	/* \tpush\t%0\n */
/* 129 */	1,	/* \tpush\t%0\n */
/* 130 */	1,	/* \tpush\t%0\n */
/* 131 */	1,	/* # argb %0\n */
/* 132 */	1,	/* # asgnb %0 %1\n */
};

static char *_string[] = {
/* 0 */	0,
/* 1 */	"reg: INDIRI1(VREGP)",
/* 2 */	"reg: INDIRU1(VREGP)",
/* 3 */	"reg: INDIRI2(VREGP)",
/* 4 */	"reg: INDIRU2(VREGP)",
/* 5 */	"reg: INDIRI4(VREGP)",
/* 6 */	"reg: INDIRU4(VREGP)",
/* 7 */	"reg: INDIRP2(VREGP)",
/* 8 */	"stmt: ASGNI1(VREGP,reg)",
/* 9 */	"stmt: ASGNU1(VREGP,reg)",
/* 10 */	"stmt: ASGNI2(VREGP,reg)",
/* 11 */	"stmt: ASGNU2(VREGP,reg)",
/* 12 */	"stmt: ASGNI4(VREGP,reg)",
/* 13 */	"stmt: ASGNU4(VREGP,reg)",
/* 14 */	"con: CNSTI1",
/* 15 */	"con: CNSTU1",
/* 16 */	"con: CNSTI2",
/* 17 */	"con: CNSTU2",
/* 18 */	"con: CNSTI4",
/* 19 */	"con: CNSTU4",
/* 20 */	"con: CNSTP2",
/* 21 */	"stmt: reg",
/* 22 */	"acon: con",
/* 23 */	"laddr: ADDRFP2",
/* 24 */	"laddr: ADDRLP2",
/* 25 */	"addr: laddr",
/* 26 */	"acon: ADDRGP2",
/* 27 */	"jaddr: ADDRGP2",
/* 28 */	"addr: jaddr",
/* 29 */	"base: ADDRGP2",
/* 30 */	"base: ADDRLP2",
/* 31 */	"base: ADDRFP2",
/* 32 */	"base: reg",
/* 33 */	"addr: baddr",
/* 34 */	"baddr: reg",
/* 35 */	"reg: base",
/* 36 */	"reg: CNSTI1",
/* 37 */	"reg: CNSTI2",
/* 38 */	"reg: CNSTI4",
/* 39 */	"reg: CNSTU1",
/* 40 */	"reg: CNSTU2",
/* 41 */	"reg: CNSTU4",
/* 42 */	"reg: CNSTP2",
/* 43 */	"stmt: ASGNI1(addr,reg)",
/* 44 */	"stmt: ASGNU1(addr,reg)",
/* 45 */	"stmt: ASGNI2(addr,reg)",
/* 46 */	"stmt: ASGNU2(addr,reg)",
/* 47 */	"stmt: ASGNI4(addr,reg)",
/* 48 */	"stmt: ASGNU4(addr,reg)",
/* 49 */	"stmt: ASGNP2(addr,reg)",
/* 50 */	"reg: INDIRI1(addr)",
/* 51 */	"reg: INDIRU1(addr)",
/* 52 */	"reg: INDIRI2(laddr)",
/* 53 */	"reg: INDIRI2(baddr)",
/* 54 */	"reg: INDIRU2(addr)",
/* 55 */	"reg: INDIRI4(addr)",
/* 56 */	"reg: INDIRU4(addr)",
/* 57 */	"reg: INDIRP2(addr)",
/* 58 */	"reg: CVII2(INDIRI1(addr))",
/* 59 */	"reg: CVUU2(INDIRU1(addr))",
/* 60 */	"reg: CVUI2(INDIRU1(addr))",
/* 61 */	"reg: CVUI2(INDIRU2(addr))",
/* 62 */	"reg: DIVI2(reg,reg)",
/* 63 */	"reg: DIVU2(reg,reg)",
/* 64 */	"reg: MODI2(reg,reg)",
/* 65 */	"reg: MODU2(reg,reg)",
/* 66 */	"reg: MULI2(reg,reg)",
/* 67 */	"reg: MULU2(reg,reg)",
/* 68 */	"rc: con",
/* 69 */	"rc: reg",
/* 70 */	"reg: ADDI2(reg,rc)",
/* 71 */	"reg: ADDP2(reg,rc)",
/* 72 */	"reg: ADDU2(reg,rc)",
/* 73 */	"reg: BANDI2(reg,rc)",
/* 74 */	"reg: BORI2(reg,rc)",
/* 75 */	"reg: BXORI2(reg,rc)",
/* 76 */	"reg: BANDU2(reg,rc)",
/* 77 */	"reg: BORU2(reg,rc)",
/* 78 */	"reg: BXORU2(reg,rc)",
/* 79 */	"reg: SUBI2(reg,rc)",
/* 80 */	"reg: SUBP2(reg,rc)",
/* 81 */	"reg: SUBU2(reg,rc)",
/* 82 */	"rc5: CNSTI2",
/* 83 */	"rc5: reg",
/* 84 */	"reg: LSHI2(reg,rc5)",
/* 85 */	"reg: LSHU2(reg,rc5)",
/* 86 */	"reg: RSHI2(reg,rc5)",
/* 87 */	"reg: RSHU2(reg,rc5)",
/* 88 */	"reg: BCOMI2(reg)",
/* 89 */	"reg: BCOMU2(reg)",
/* 90 */	"reg: NEGI2(reg)",
/* 91 */	"reg: LOADI1(reg)",
/* 92 */	"reg: LOADU1(reg)",
/* 93 */	"reg: LOADI2(reg)",
/* 94 */	"reg: LOADU2(reg)",
/* 95 */	"reg: LOADI4(reg)",
/* 96 */	"reg: LOADP2(reg)",
/* 97 */	"reg: LOADU4(reg)",
/* 98 */	"reg: CVII2(reg)",
/* 99 */	"reg: CVUI2(reg)",
/* 100 */	"reg: CVUU2(reg)",
/* 101 */	"stmt: LABELV",
/* 102 */	"stmt: JUMPV(acon)",
/* 103 */	"stmt: JUMPV(reg)",
/* 104 */	"stmt: JUMPV(reg)",
/* 105 */	"stmt: EQI2(reg,reg)",
/* 106 */	"stmt: EQU2(reg,reg)",
/* 107 */	"stmt: GEI2(reg,reg)",
/* 108 */	"stmt: GEU2(reg,reg)",
/* 109 */	"stmt: GTI2(reg,reg)",
/* 110 */	"stmt: GTU2(reg,reg)",
/* 111 */	"stmt: LEI2(reg,reg)",
/* 112 */	"stmt: LEU2(reg,reg)",
/* 113 */	"stmt: LTI2(reg,reg)",
/* 114 */	"stmt: LTU2(reg,reg)",
/* 115 */	"stmt: NEI2(reg,reg)",
/* 116 */	"stmt: NEU2(reg,reg)",
/* 117 */	"ar: ADDRGP2",
/* 118 */	"reg: CALLI2(ar)",
/* 119 */	"reg: CALLP2(ar)",
/* 120 */	"reg: CALLU2(ar)",
/* 121 */	"stmt: CALLV(ar)",
/* 122 */	"ar: reg",
/* 123 */	"ar: CNSTP2",
/* 124 */	"stmt: RETI2(reg)",
/* 125 */	"stmt: RETU2(reg)",
/* 126 */	"stmt: RETP2(reg)",
/* 127 */	"stmt: RETV(reg)",
/* 128 */	"stmt: ARGI2(rc)",
/* 129 */	"stmt: ARGU2(rc)",
/* 130 */	"stmt: ARGP2(rc)",
/* 131 */	"stmt: ARGB(INDIRB(reg))",
/* 132 */	"stmt: ASGNB(reg,INDIRB(reg))",
};

static short _decode_stmt[] = {
	0,
	8,
	9,
	10,
	11,
	12,
	13,
	21,
	43,
	44,
	45,
	46,
	47,
	48,
	49,
	101,
	102,
	103,
	104,
	105,
	106,
	107,
	108,
	109,
	110,
	111,
	112,
	113,
	114,
	115,
	116,
	121,
	124,
	125,
	126,
	127,
	128,
	129,
	130,
	131,
	132,
};

static short _decode_reg[] = {
	0,
	1,
	2,
	3,
	4,
	5,
	6,
	7,
	35,
	36,
	37,
	38,
	39,
	40,
	41,
	42,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	58,
	59,
	60,
	61,
	62,
	63,
	64,
	65,
	66,
	67,
	70,
	71,
	72,
	73,
	74,
	75,
	76,
	77,
	78,
	79,
	80,
	81,
	84,
	85,
	86,
	87,
	88,
	89,
	90,
	91,
	92,
	93,
	94,
	95,
	96,
	97,
	98,
	99,
	100,
	118,
	119,
	120,
};

static short _decode_con[] = {
	0,
	14,
	15,
	16,
	17,
	18,
	19,
	20,
};

static short _decode_acon[] = {
	0,
	22,
	26,
};

static short _decode_laddr[] = {
	0,
	23,
	24,
};

static short _decode_addr[] = {
	0,
	25,
	28,
	33,
};

static short _decode_jaddr[] = {
	0,
	27,
};

static short _decode_base[] = {
	0,
	29,
	30,
	31,
	32,
};

static short _decode_baddr[] = {
	0,
	34,
};

static short _decode_rc[] = {
	0,
	68,
	69,
};

static short _decode_rc5[] = {
	0,
	82,
	83,
};

static short _decode_ar[] = {
	0,
	117,
	122,
	123,
};

static int _rule(void *state, int goalnt) {
	if (goalnt < 1 || goalnt > 12)
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
	if (!state)
		return 0;
	switch (goalnt) {
	case _stmt_NT:	return _decode_stmt[((struct _state *)state)->rule._stmt];
	case _reg_NT:	return _decode_reg[((struct _state *)state)->rule._reg];
	case _con_NT:	return _decode_con[((struct _state *)state)->rule._con];
	case _acon_NT:	return _decode_acon[((struct _state *)state)->rule._acon];
	case _laddr_NT:	return _decode_laddr[((struct _state *)state)->rule._laddr];
	case _addr_NT:	return _decode_addr[((struct _state *)state)->rule._addr];
	case _jaddr_NT:	return _decode_jaddr[((struct _state *)state)->rule._jaddr];
	case _base_NT:	return _decode_base[((struct _state *)state)->rule._base];
	case _baddr_NT:	return _decode_baddr[((struct _state *)state)->rule._baddr];
	case _rc_NT:	return _decode_rc[((struct _state *)state)->rule._rc];
	case _rc5_NT:	return _decode_rc5[((struct _state *)state)->rule._rc5];
	case _ar_NT:	return _decode_ar[((struct _state *)state)->rule._ar];
	default:
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
		return 0;
	}
}

static void _closure_reg(NODEPTR_TYPE, int);
static void _closure_con(NODEPTR_TYPE, int);
static void _closure_laddr(NODEPTR_TYPE, int);
static void _closure_jaddr(NODEPTR_TYPE, int);
static void _closure_base(NODEPTR_TYPE, int);
static void _closure_baddr(NODEPTR_TYPE, int);

static void _closure_reg(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_ar_NT]) {
		p->cost[_ar_NT] = c + 0;
		p->rule._ar = 2;
	}
	if (c + 0 < p->cost[_rc5_NT]) {
		p->cost[_rc5_NT] = c + 0;
		p->rule._rc5 = 2;
	}
	if (c + 0 < p->cost[_rc_NT]) {
		p->cost[_rc_NT] = c + 0;
		p->rule._rc = 2;
	}
	if (c + 0 < p->cost[_baddr_NT]) {
		p->cost[_baddr_NT] = c + 0;
		p->rule._baddr = 1;
		_closure_baddr(a, c + 0);
	}
	if (c + 0 < p->cost[_base_NT]) {
		p->cost[_base_NT] = c + 0;
		p->rule._base = 4;
		_closure_base(a, c + 0);
	}
	if (c + 0 < p->cost[_stmt_NT]) {
		p->cost[_stmt_NT] = c + 0;
		p->rule._stmt = 7;
	}
}

static void _closure_con(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_rc_NT]) {
		p->cost[_rc_NT] = c + 0;
		p->rule._rc = 1;
	}
	if (c + 0 < p->cost[_acon_NT]) {
		p->cost[_acon_NT] = c + 0;
		p->rule._acon = 1;
	}
}

static void _closure_laddr(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_addr_NT]) {
		p->cost[_addr_NT] = c + 0;
		p->rule._addr = 1;
	}
}

static void _closure_jaddr(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_addr_NT]) {
		p->cost[_addr_NT] = c + 0;
		p->rule._addr = 2;
	}
}

static void _closure_base(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 0;
		p->rule._reg = 8;
		_closure_reg(a, c + 0);
	}
}

static void _closure_baddr(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_addr_NT]) {
		p->cost[_addr_NT] = c + 0;
		p->rule._addr = 3;
	}
}

static void _label(NODEPTR_TYPE a) {
	int c;
	struct _state *p;

	if (!a)
		fatal("_label", "Null tree\n", 0);
	STATE_LABEL(a) = p = allocate(sizeof *p, FUNC);
	p->rule._stmt = 0;
	p->cost[1] =
	p->cost[2] =
	p->cost[3] =
	p->cost[4] =
	p->cost[5] =
	p->cost[6] =
	p->cost[7] =
	p->cost[8] =
	p->cost[9] =
	p->cost[10] =
	p->cost[11] =
	p->cost[12] =
		0x7fff;
	switch (OP_LABEL(a)) {
	case 41: /* ARGB */
		_label(LEFT_CHILD(a));
		if (	/* stmt: ARGB(INDIRB(reg)) */
			LEFT_CHILD(a)->op == 73 /* INDIRB */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 39;
			}
		}
		break;
	case 57: /* ASGNB */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNB(reg,INDIRB(reg)) */
			RIGHT_CHILD(a)->op == 73 /* INDIRB */
		) {
			c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(LEFT_CHILD(RIGHT_CHILD(a))->x.state))->cost[_reg_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 40;
			}
		}
		break;
	case 73: /* INDIRB */
		_label(LEFT_CHILD(a));
		break;
	case 216: /* CALLV */
		_label(LEFT_CHILD(a));
		/* stmt: CALLV(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 31;
		}
		break;
	case 217: /* CALLB */
		break;
	case 233: /* LOADB */
		break;
	case 248: /* RETV */
		_label(LEFT_CHILD(a));
		/* stmt: RETV(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 35;
		}
		break;
	case 584: /* JUMPV */
		_label(LEFT_CHILD(a));
		/* stmt: JUMPV(acon) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_acon_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 16;
		}
		/* stmt: JUMPV(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 17;
		}
		/* stmt: JUMPV(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 18;
		}
		break;
	case 600: /* LABELV */
		/* stmt: LABELV */
		if (0 + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = 0 + 0;
			p->rule._stmt = 15;
		}
		break;
	case 711: /* VREGP */
		break;
	case 1045: /* CNSTI1 */
		/* con: CNSTI1 */
		if (0 + 0 < p->cost[_con_NT]) {
			p->cost[_con_NT] = 0 + 0;
			p->rule._con = 1;
			_closure_con(a, 0 + 0);
		}
		/* reg: CNSTI1 */
		c = (range(a, 0, 0));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 9;
			_closure_reg(a, c + 0);
		}
		break;
	case 1046: /* CNSTU1 */
		/* con: CNSTU1 */
		if (0 + 0 < p->cost[_con_NT]) {
			p->cost[_con_NT] = 0 + 0;
			p->rule._con = 2;
			_closure_con(a, 0 + 0);
		}
		/* reg: CNSTU1 */
		c = (range(a, 0, 0));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 12;
			_closure_reg(a, c + 0);
		}
		break;
	case 1077: /* ASGNI1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNI1(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 1;
			}
		}
		/* stmt: ASGNI1(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 8;
		}
		break;
	case 1078: /* ASGNU1 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNU1(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 2;
			}
		}
		/* stmt: ASGNU1(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 9;
		}
		break;
	case 1093: /* INDIRI1 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRI1(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_acon_NT] == 0) {
					p->cost[_acon_NT] = 0;
					p->rule._acon = q->rule._acon;
				}
				if (q->cost[_laddr_NT] == 0) {
					p->cost[_laddr_NT] = 0;
					p->rule._laddr = q->rule._laddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_jaddr_NT] == 0) {
					p->cost[_jaddr_NT] = 0;
					p->rule._jaddr = q->rule._jaddr;
				}
				if (q->cost[_base_NT] == 0) {
					p->cost[_base_NT] = 0;
					p->rule._base = q->rule._base;
				}
				if (q->cost[_baddr_NT] == 0) {
					p->cost[_baddr_NT] = 0;
					p->rule._baddr = q->rule._baddr;
				}
				if (q->cost[_rc_NT] == 0) {
					p->cost[_rc_NT] = 0;
					p->rule._rc = q->rule._rc;
				}
				if (q->cost[_rc5_NT] == 0) {
					p->cost[_rc5_NT] = 0;
					p->rule._rc5 = q->rule._rc5;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 1;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRI1(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 16;
			_closure_reg(a, c + 0);
		}
		break;
	case 1094: /* INDIRU1 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRU1(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_acon_NT] == 0) {
					p->cost[_acon_NT] = 0;
					p->rule._acon = q->rule._acon;
				}
				if (q->cost[_laddr_NT] == 0) {
					p->cost[_laddr_NT] = 0;
					p->rule._laddr = q->rule._laddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_jaddr_NT] == 0) {
					p->cost[_jaddr_NT] = 0;
					p->rule._jaddr = q->rule._jaddr;
				}
				if (q->cost[_base_NT] == 0) {
					p->cost[_base_NT] = 0;
					p->rule._base = q->rule._base;
				}
				if (q->cost[_baddr_NT] == 0) {
					p->cost[_baddr_NT] = 0;
					p->rule._baddr = q->rule._baddr;
				}
				if (q->cost[_rc_NT] == 0) {
					p->cost[_rc_NT] = 0;
					p->rule._rc = q->rule._rc;
				}
				if (q->cost[_rc5_NT] == 0) {
					p->cost[_rc5_NT] = 0;
					p->rule._rc5 = q->rule._rc5;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 2;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRU1(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 17;
			_closure_reg(a, c + 0);
		}
		break;
	case 1157: /* CVII1 */
		break;
	case 1158: /* CVIU1 */
		break;
	case 1205: /* CVUI1 */
		break;
	case 1206: /* CVUU1 */
		break;
	case 1253: /* LOADI1 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 53;
			_closure_reg(a, c + 0);
		}
		break;
	case 1254: /* LOADU1 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 54;
			_closure_reg(a, c + 0);
		}
		break;
	case 2069: /* CNSTI2 */
		/* con: CNSTI2 */
		if (0 + 0 < p->cost[_con_NT]) {
			p->cost[_con_NT] = 0 + 0;
			p->rule._con = 3;
			_closure_con(a, 0 + 0);
		}
		/* reg: CNSTI2 */
		c = (range(a, 0, 0));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 10;
			_closure_reg(a, c + 0);
		}
		/* rc5: CNSTI2 */
		c = (range(a,0,31));
		if (c + 0 < p->cost[_rc5_NT]) {
			p->cost[_rc5_NT] = c + 0;
			p->rule._rc5 = 1;
		}
		break;
	case 2070: /* CNSTU2 */
		/* con: CNSTU2 */
		if (0 + 0 < p->cost[_con_NT]) {
			p->cost[_con_NT] = 0 + 0;
			p->rule._con = 4;
			_closure_con(a, 0 + 0);
		}
		/* reg: CNSTU2 */
		c = (range(a, 0, 0));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 13;
			_closure_reg(a, c + 0);
		}
		break;
	case 2071: /* CNSTP2 */
		/* con: CNSTP2 */
		if (0 + 0 < p->cost[_con_NT]) {
			p->cost[_con_NT] = 0 + 0;
			p->rule._con = 7;
			_closure_con(a, 0 + 0);
		}
		/* reg: CNSTP2 */
		c = (range(a, 0, 0));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 15;
			_closure_reg(a, c + 0);
		}
		/* ar: CNSTP2 */
		c = (range(a, 0, 0x0fffffff));
		if (c + 0 < p->cost[_ar_NT]) {
			p->cost[_ar_NT] = c + 0;
			p->rule._ar = 3;
		}
		break;
	case 2085: /* ARGI2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGI2(rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 36;
		}
		break;
	case 2086: /* ARGU2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGU2(rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 37;
		}
		break;
	case 2087: /* ARGP2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGP2(rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 38;
		}
		break;
	case 2101: /* ASGNI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNI2(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 3;
			}
		}
		/* stmt: ASGNI2(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 10;
		}
		break;
	case 2102: /* ASGNU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNU2(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 4;
			}
		}
		/* stmt: ASGNU2(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 11;
		}
		break;
	case 2103: /* ASGNP2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: ASGNP2(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 14;
		}
		break;
	case 2117: /* INDIRI2 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRI2(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_acon_NT] == 0) {
					p->cost[_acon_NT] = 0;
					p->rule._acon = q->rule._acon;
				}
				if (q->cost[_laddr_NT] == 0) {
					p->cost[_laddr_NT] = 0;
					p->rule._laddr = q->rule._laddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_jaddr_NT] == 0) {
					p->cost[_jaddr_NT] = 0;
					p->rule._jaddr = q->rule._jaddr;
				}
				if (q->cost[_base_NT] == 0) {
					p->cost[_base_NT] = 0;
					p->rule._base = q->rule._base;
				}
				if (q->cost[_baddr_NT] == 0) {
					p->cost[_baddr_NT] = 0;
					p->rule._baddr = q->rule._baddr;
				}
				if (q->cost[_rc_NT] == 0) {
					p->cost[_rc_NT] = 0;
					p->rule._rc = q->rule._rc;
				}
				if (q->cost[_rc5_NT] == 0) {
					p->cost[_rc5_NT] = 0;
					p->rule._rc5 = q->rule._rc5;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 3;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRI2(laddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_laddr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 18;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRI2(baddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_baddr_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 19;
			_closure_reg(a, c + 0);
		}
		break;
	case 2118: /* INDIRU2 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRU2(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_acon_NT] == 0) {
					p->cost[_acon_NT] = 0;
					p->rule._acon = q->rule._acon;
				}
				if (q->cost[_laddr_NT] == 0) {
					p->cost[_laddr_NT] = 0;
					p->rule._laddr = q->rule._laddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_jaddr_NT] == 0) {
					p->cost[_jaddr_NT] = 0;
					p->rule._jaddr = q->rule._jaddr;
				}
				if (q->cost[_base_NT] == 0) {
					p->cost[_base_NT] = 0;
					p->rule._base = q->rule._base;
				}
				if (q->cost[_baddr_NT] == 0) {
					p->cost[_baddr_NT] = 0;
					p->rule._baddr = q->rule._baddr;
				}
				if (q->cost[_rc_NT] == 0) {
					p->cost[_rc_NT] = 0;
					p->rule._rc = q->rule._rc;
				}
				if (q->cost[_rc5_NT] == 0) {
					p->cost[_rc5_NT] = 0;
					p->rule._rc5 = q->rule._rc5;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 4;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRU2(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 20;
			_closure_reg(a, c + 0);
		}
		break;
	case 2119: /* INDIRP2 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRP2(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_acon_NT] == 0) {
					p->cost[_acon_NT] = 0;
					p->rule._acon = q->rule._acon;
				}
				if (q->cost[_laddr_NT] == 0) {
					p->cost[_laddr_NT] = 0;
					p->rule._laddr = q->rule._laddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_jaddr_NT] == 0) {
					p->cost[_jaddr_NT] = 0;
					p->rule._jaddr = q->rule._jaddr;
				}
				if (q->cost[_base_NT] == 0) {
					p->cost[_base_NT] = 0;
					p->rule._base = q->rule._base;
				}
				if (q->cost[_baddr_NT] == 0) {
					p->cost[_baddr_NT] = 0;
					p->rule._baddr = q->rule._baddr;
				}
				if (q->cost[_rc_NT] == 0) {
					p->cost[_rc_NT] = 0;
					p->rule._rc = q->rule._rc;
				}
				if (q->cost[_rc5_NT] == 0) {
					p->cost[_rc5_NT] = 0;
					p->rule._rc5 = q->rule._rc5;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 7;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRP2(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 23;
			_closure_reg(a, c + 0);
		}
		break;
	case 2165: /* CVFI2 */
		break;
	case 2181: /* CVII2 */
		_label(LEFT_CHILD(a));
		if (	/* reg: CVII2(INDIRI1(addr)) */
			LEFT_CHILD(a)->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 24;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: CVII2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 60;
			_closure_reg(a, c + 0);
		}
		break;
	case 2182: /* CVIU2 */
		break;
	case 2198: /* CVPU2 */
		break;
	case 2229: /* CVUI2 */
		_label(LEFT_CHILD(a));
		if (	/* reg: CVUI2(INDIRU1(addr)) */
			LEFT_CHILD(a)->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 26;
				_closure_reg(a, c + 0);
			}
		}
		if (	/* reg: CVUI2(INDIRU2(addr)) */
			LEFT_CHILD(a)->op == 2118 /* INDIRU2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 27;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: CVUI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 61;
			_closure_reg(a, c + 0);
		}
		break;
	case 2230: /* CVUU2 */
		_label(LEFT_CHILD(a));
		if (	/* reg: CVUU2(INDIRU1(addr)) */
			LEFT_CHILD(a)->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 25;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: CVUU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 62;
			_closure_reg(a, c + 0);
		}
		break;
	case 2231: /* CVUP2 */
		break;
	case 2245: /* NEGI2 */
		_label(LEFT_CHILD(a));
		/* reg: NEGI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 52;
			_closure_reg(a, c + 0);
		}
		break;
	case 2261: /* CALLI2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLI2(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 63;
			_closure_reg(a, c + 0);
		}
		break;
	case 2262: /* CALLU2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLU2(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 65;
			_closure_reg(a, c + 0);
		}
		break;
	case 2263: /* CALLP2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLP2(ar) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_ar_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 64;
			_closure_reg(a, c + 0);
		}
		break;
	case 2277: /* LOADI2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 55;
			_closure_reg(a, c + 0);
		}
		break;
	case 2278: /* LOADU2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 56;
			_closure_reg(a, c + 0);
		}
		break;
	case 2279: /* LOADP2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 58;
			_closure_reg(a, c + 0);
		}
		break;
	case 2293: /* RETI2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 32;
		}
		break;
	case 2294: /* RETU2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 33;
		}
		break;
	case 2295: /* RETP2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 34;
		}
		break;
	case 2311: /* ADDRGP2 */
		/* acon: ADDRGP2 */
		if (0 + 0 < p->cost[_acon_NT]) {
			p->cost[_acon_NT] = 0 + 0;
			p->rule._acon = 2;
		}
		/* jaddr: ADDRGP2 */
		if (0 + 0 < p->cost[_jaddr_NT]) {
			p->cost[_jaddr_NT] = 0 + 0;
			p->rule._jaddr = 1;
			_closure_jaddr(a, 0 + 0);
		}
		/* base: ADDRGP2 */
		if (0 + 0 < p->cost[_base_NT]) {
			p->cost[_base_NT] = 0 + 0;
			p->rule._base = 1;
			_closure_base(a, 0 + 0);
		}
		/* ar: ADDRGP2 */
		if (0 + 0 < p->cost[_ar_NT]) {
			p->cost[_ar_NT] = 0 + 0;
			p->rule._ar = 1;
		}
		break;
	case 2327: /* ADDRFP2 */
		/* laddr: ADDRFP2 */
		c = (range(a, -63, 63));
		if (c + 0 < p->cost[_laddr_NT]) {
			p->cost[_laddr_NT] = c + 0;
			p->rule._laddr = 1;
			_closure_laddr(a, c + 0);
		}
		/* base: ADDRFP2 */
		if (0 + 0 < p->cost[_base_NT]) {
			p->cost[_base_NT] = 0 + 0;
			p->rule._base = 3;
			_closure_base(a, 0 + 0);
		}
		break;
	case 2343: /* ADDRLP2 */
		/* laddr: ADDRLP2 */
		c = (range(a, -63, 63));
		if (c + 0 < p->cost[_laddr_NT]) {
			p->cost[_laddr_NT] = c + 0;
			p->rule._laddr = 2;
			_closure_laddr(a, c + 0);
		}
		/* base: ADDRLP2 */
		if (0 + 0 < p->cost[_base_NT]) {
			p->cost[_base_NT] = 0 + 0;
			p->rule._base = 2;
			_closure_base(a, 0 + 0);
		}
		break;
	case 2357: /* ADDI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDI2(reg,rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 34;
			_closure_reg(a, c + 0);
		}
		break;
	case 2358: /* ADDU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDU2(reg,rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 36;
			_closure_reg(a, c + 0);
		}
		break;
	case 2359: /* ADDP2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDP2(reg,rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 35;
			_closure_reg(a, c + 0);
		}
		break;
	case 2373: /* SUBI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBI2(reg,rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 43;
			_closure_reg(a, c + 0);
		}
		break;
	case 2374: /* SUBU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBU2(reg,rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 45;
			_closure_reg(a, c + 0);
		}
		break;
	case 2375: /* SUBP2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBP2(reg,rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 44;
			_closure_reg(a, c + 0);
		}
		break;
	case 2389: /* LSHI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHI2(reg,rc5) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc5_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 46;
			_closure_reg(a, c + 0);
		}
		break;
	case 2390: /* LSHU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHU2(reg,rc5) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc5_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 47;
			_closure_reg(a, c + 0);
		}
		break;
	case 2405: /* MODI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 30;
			_closure_reg(a, c + 0);
		}
		break;
	case 2406: /* MODU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 31;
			_closure_reg(a, c + 0);
		}
		break;
	case 2421: /* RSHI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHI2(reg,rc5) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc5_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 48;
			_closure_reg(a, c + 0);
		}
		break;
	case 2422: /* RSHU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHU2(reg,rc5) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc5_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 49;
			_closure_reg(a, c + 0);
		}
		break;
	case 2437: /* BANDI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDI2(reg,rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 37;
			_closure_reg(a, c + 0);
		}
		break;
	case 2438: /* BANDU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDU2(reg,rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 40;
			_closure_reg(a, c + 0);
		}
		break;
	case 2453: /* BCOMI2 */
		_label(LEFT_CHILD(a));
		/* reg: BCOMI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 50;
			_closure_reg(a, c + 0);
		}
		break;
	case 2454: /* BCOMU2 */
		_label(LEFT_CHILD(a));
		/* reg: BCOMU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 51;
			_closure_reg(a, c + 0);
		}
		break;
	case 2469: /* BORI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORI2(reg,rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 38;
			_closure_reg(a, c + 0);
		}
		break;
	case 2470: /* BORU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORU2(reg,rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 41;
			_closure_reg(a, c + 0);
		}
		break;
	case 2485: /* BXORI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORI2(reg,rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 39;
			_closure_reg(a, c + 0);
		}
		break;
	case 2486: /* BXORU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORU2(reg,rc) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_rc_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 42;
			_closure_reg(a, c + 0);
		}
		break;
	case 2501: /* DIVI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 28;
			_closure_reg(a, c + 0);
		}
		break;
	case 2502: /* DIVU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: DIVU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 29;
			_closure_reg(a, c + 0);
		}
		break;
	case 2517: /* MULI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 32;
			_closure_reg(a, c + 0);
		}
		break;
	case 2518: /* MULU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MULU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 33;
			_closure_reg(a, c + 0);
		}
		break;
	case 2533: /* EQI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 19;
		}
		break;
	case 2534: /* EQU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 20;
		}
		break;
	case 2549: /* GEI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 21;
		}
		break;
	case 2550: /* GEU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 22;
		}
		break;
	case 2565: /* GTI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 23;
		}
		break;
	case 2566: /* GTU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 24;
		}
		break;
	case 2581: /* LEI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 25;
		}
		break;
	case 2582: /* LEU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 26;
		}
		break;
	case 2597: /* LTI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 27;
		}
		break;
	case 2598: /* LTU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 28;
		}
		break;
	case 2613: /* NEI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 29;
		}
		break;
	case 2614: /* NEU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 30;
		}
		break;
	case 4113: /* CNSTF4 */
		break;
	case 4117: /* CNSTI4 */
		/* con: CNSTI4 */
		if (0 + 0 < p->cost[_con_NT]) {
			p->cost[_con_NT] = 0 + 0;
			p->rule._con = 5;
			_closure_con(a, 0 + 0);
		}
		/* reg: CNSTI4 */
		c = (range(a, 0, 0));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 11;
			_closure_reg(a, c + 0);
		}
		break;
	case 4118: /* CNSTU4 */
		/* con: CNSTU4 */
		if (0 + 0 < p->cost[_con_NT]) {
			p->cost[_con_NT] = 0 + 0;
			p->rule._con = 6;
			_closure_con(a, 0 + 0);
		}
		/* reg: CNSTU4 */
		c = (range(a, 0, 0));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 14;
			_closure_reg(a, c + 0);
		}
		break;
	case 4129: /* ARGF4 */
		break;
	case 4133: /* ARGI4 */
		break;
	case 4134: /* ARGU4 */
		break;
	case 4145: /* ASGNF4 */
		break;
	case 4149: /* ASGNI4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNI4(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 5;
			}
		}
		/* stmt: ASGNI4(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 12;
		}
		break;
	case 4150: /* ASGNU4 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNU4(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 6;
			}
		}
		/* stmt: ASGNU4(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 13;
		}
		break;
	case 4161: /* INDIRF4 */
		break;
	case 4165: /* INDIRI4 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRI4(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_acon_NT] == 0) {
					p->cost[_acon_NT] = 0;
					p->rule._acon = q->rule._acon;
				}
				if (q->cost[_laddr_NT] == 0) {
					p->cost[_laddr_NT] = 0;
					p->rule._laddr = q->rule._laddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_jaddr_NT] == 0) {
					p->cost[_jaddr_NT] = 0;
					p->rule._jaddr = q->rule._jaddr;
				}
				if (q->cost[_base_NT] == 0) {
					p->cost[_base_NT] = 0;
					p->rule._base = q->rule._base;
				}
				if (q->cost[_baddr_NT] == 0) {
					p->cost[_baddr_NT] = 0;
					p->rule._baddr = q->rule._baddr;
				}
				if (q->cost[_rc_NT] == 0) {
					p->cost[_rc_NT] = 0;
					p->rule._rc = q->rule._rc;
				}
				if (q->cost[_rc5_NT] == 0) {
					p->cost[_rc5_NT] = 0;
					p->rule._rc5 = q->rule._rc5;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 5;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRI4(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 21;
			_closure_reg(a, c + 0);
		}
		break;
	case 4166: /* INDIRU4 */
		_label(LEFT_CHILD(a));
		if (	/* reg: INDIRU4(VREGP) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			if (mayrecalc(a)) {
				struct _state *q = a->syms[RX]->u.t.cse->x.state;
				if (q->cost[_stmt_NT] == 0) {
					p->cost[_stmt_NT] = 0;
					p->rule._stmt = q->rule._stmt;
				}
				if (q->cost[_reg_NT] == 0) {
					p->cost[_reg_NT] = 0;
					p->rule._reg = q->rule._reg;
				}
				if (q->cost[_con_NT] == 0) {
					p->cost[_con_NT] = 0;
					p->rule._con = q->rule._con;
				}
				if (q->cost[_acon_NT] == 0) {
					p->cost[_acon_NT] = 0;
					p->rule._acon = q->rule._acon;
				}
				if (q->cost[_laddr_NT] == 0) {
					p->cost[_laddr_NT] = 0;
					p->rule._laddr = q->rule._laddr;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_jaddr_NT] == 0) {
					p->cost[_jaddr_NT] = 0;
					p->rule._jaddr = q->rule._jaddr;
				}
				if (q->cost[_base_NT] == 0) {
					p->cost[_base_NT] = 0;
					p->rule._base = q->rule._base;
				}
				if (q->cost[_baddr_NT] == 0) {
					p->cost[_baddr_NT] = 0;
					p->rule._baddr = q->rule._baddr;
				}
				if (q->cost[_rc_NT] == 0) {
					p->cost[_rc_NT] = 0;
					p->rule._rc = q->rule._rc;
				}
				if (q->cost[_rc5_NT] == 0) {
					p->cost[_rc5_NT] = 0;
					p->rule._rc5 = q->rule._rc5;
				}
				if (q->cost[_ar_NT] == 0) {
					p->cost[_ar_NT] = 0;
					p->rule._ar = q->rule._ar;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 6;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRU4(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 22;
			_closure_reg(a, c + 0);
		}
		break;
	case 4209: /* CVFF4 */
		break;
	case 4213: /* CVFI4 */
		break;
	case 4225: /* CVIF4 */
		break;
	case 4229: /* CVII4 */
		break;
	case 4230: /* CVIU4 */
		break;
	case 4277: /* CVUI4 */
		break;
	case 4278: /* CVUU4 */
		break;
	case 4289: /* NEGF4 */
		break;
	case 4293: /* NEGI4 */
		break;
	case 4305: /* CALLF4 */
		break;
	case 4309: /* CALLI4 */
		break;
	case 4310: /* CALLU4 */
		break;
	case 4325: /* LOADI4 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 57;
			_closure_reg(a, c + 0);
		}
		break;
	case 4326: /* LOADU4 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU4(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 59;
			_closure_reg(a, c + 0);
		}
		break;
	case 4337: /* RETF4 */
		break;
	case 4341: /* RETI4 */
		break;
	case 4342: /* RETU4 */
		break;
	case 4401: /* ADDF4 */
		break;
	case 4405: /* ADDI4 */
		break;
	case 4406: /* ADDU4 */
		break;
	case 4417: /* SUBF4 */
		break;
	case 4421: /* SUBI4 */
		break;
	case 4422: /* SUBU4 */
		break;
	case 4437: /* LSHI4 */
		break;
	case 4438: /* LSHU4 */
		break;
	case 4453: /* MODI4 */
		break;
	case 4454: /* MODU4 */
		break;
	case 4469: /* RSHI4 */
		break;
	case 4470: /* RSHU4 */
		break;
	case 4485: /* BANDI4 */
		break;
	case 4486: /* BANDU4 */
		break;
	case 4501: /* BCOMI4 */
		break;
	case 4502: /* BCOMU4 */
		break;
	case 4517: /* BORI4 */
		break;
	case 4518: /* BORU4 */
		break;
	case 4533: /* BXORI4 */
		break;
	case 4534: /* BXORU4 */
		break;
	case 4545: /* DIVF4 */
		break;
	case 4549: /* DIVI4 */
		break;
	case 4550: /* DIVU4 */
		break;
	case 4561: /* MULF4 */
		break;
	case 4565: /* MULI4 */
		break;
	case 4566: /* MULU4 */
		break;
	case 4577: /* EQF4 */
		break;
	case 4581: /* EQI4 */
		break;
	case 4582: /* EQU4 */
		break;
	case 4593: /* GEF4 */
		break;
	case 4597: /* GEI4 */
		break;
	case 4598: /* GEU4 */
		break;
	case 4609: /* GTF4 */
		break;
	case 4613: /* GTI4 */
		break;
	case 4614: /* GTU4 */
		break;
	case 4625: /* LEF4 */
		break;
	case 4629: /* LEI4 */
		break;
	case 4630: /* LEU4 */
		break;
	case 4641: /* LTF4 */
		break;
	case 4645: /* LTI4 */
		break;
	case 4646: /* LTU4 */
		break;
	case 4657: /* NEF4 */
		break;
	case 4661: /* NEI4 */
		break;
	case 4662: /* NEU4 */
		break;
	case 8209: /* CNSTF8 */
		break;
	case 8213: /* CNSTI8 */
		break;
	case 8214: /* CNSTU8 */
		break;
	case 8225: /* ARGF8 */
		break;
	case 8229: /* ARGI8 */
		break;
	case 8230: /* ARGU8 */
		break;
	case 8241: /* ASGNF8 */
		break;
	case 8245: /* ASGNI8 */
		break;
	case 8246: /* ASGNU8 */
		break;
	case 8257: /* INDIRF8 */
		break;
	case 8261: /* INDIRI8 */
		break;
	case 8262: /* INDIRU8 */
		break;
	case 8305: /* CVFF8 */
		break;
	case 8309: /* CVFI8 */
		break;
	case 8321: /* CVIF8 */
		break;
	case 8325: /* CVII8 */
		break;
	case 8326: /* CVIU8 */
		break;
	case 8373: /* CVUI8 */
		break;
	case 8374: /* CVUU8 */
		break;
	case 8385: /* NEGF8 */
		break;
	case 8389: /* NEGI8 */
		break;
	case 8401: /* CALLF8 */
		break;
	case 8405: /* CALLI8 */
		break;
	case 8406: /* CALLU8 */
		break;
	case 8433: /* RETF8 */
		break;
	case 8437: /* RETI8 */
		break;
	case 8438: /* RETU8 */
		break;
	case 8497: /* ADDF8 */
		break;
	case 8501: /* ADDI8 */
		break;
	case 8502: /* ADDU8 */
		break;
	case 8513: /* SUBF8 */
		break;
	case 8517: /* SUBI8 */
		break;
	case 8518: /* SUBU8 */
		break;
	case 8533: /* LSHI8 */
		break;
	case 8534: /* LSHU8 */
		break;
	case 8549: /* MODI8 */
		break;
	case 8550: /* MODU8 */
		break;
	case 8565: /* RSHI8 */
		break;
	case 8566: /* RSHU8 */
		break;
	case 8581: /* BANDI8 */
		break;
	case 8582: /* BANDU8 */
		break;
	case 8597: /* BCOMI8 */
		break;
	case 8598: /* BCOMU8 */
		break;
	case 8613: /* BORI8 */
		break;
	case 8614: /* BORU8 */
		break;
	case 8629: /* BXORI8 */
		break;
	case 8630: /* BXORU8 */
		break;
	case 8641: /* DIVF8 */
		break;
	case 8645: /* DIVI8 */
		break;
	case 8646: /* DIVU8 */
		break;
	case 8657: /* MULF8 */
		break;
	case 8661: /* MULI8 */
		break;
	case 8662: /* MULU8 */
		break;
	case 8673: /* EQF8 */
		break;
	case 8677: /* EQI8 */
		break;
	case 8678: /* EQU8 */
		break;
	case 8689: /* GEF8 */
		break;
	case 8693: /* GEI8 */
		break;
	case 8694: /* GEU8 */
		break;
	case 8705: /* GTF8 */
		break;
	case 8709: /* GTI8 */
		break;
	case 8710: /* GTU8 */
		break;
	case 8721: /* LEF8 */
		break;
	case 8725: /* LEI8 */
		break;
	case 8726: /* LEU8 */
		break;
	case 8737: /* LTF8 */
		break;
	case 8741: /* LTI8 */
		break;
	case 8742: /* LTU8 */
		break;
	case 8753: /* NEF8 */
		break;
	case 8757: /* NEI8 */
		break;
	case 8758: /* NEU8 */
		break;
	case 16401: /* CNSTF16 */
		break;
	case 16417: /* ARGF16 */
		break;
	case 16433: /* ASGNF16 */
		break;
	case 16449: /* INDIRF16 */
		break;
	case 16497: /* CVFF16 */
		break;
	case 16513: /* CVIF16 */
		break;
	case 16577: /* NEGF16 */
		break;
	case 16593: /* CALLF16 */
		break;
	case 16625: /* RETF16 */
		break;
	case 16689: /* ADDF16 */
		break;
	case 16705: /* SUBF16 */
		break;
	case 16833: /* DIVF16 */
		break;
	case 16849: /* MULF16 */
		break;
	case 16865: /* EQF16 */
		break;
	case 16881: /* GEF16 */
		break;
	case 16897: /* GTF16 */
		break;
	case 16913: /* LEF16 */
		break;
	case 16929: /* LTF16 */
		break;
	case 16945: /* NEF16 */
		break;
	default:
		fatal("_label", "Bad terminal %d\n", OP_LABEL(a));
	}
}

static void _kids(NODEPTR_TYPE p, int eruleno, NODEPTR_TYPE kids[]) {
	if (!p)
		fatal("_kids", "Null tree\n", 0);
	if (!kids)
		fatal("_kids", "Null kids\n", 0);
	switch (eruleno) {
	case 123: /* ar: CNSTP2 */
	case 117: /* ar: ADDRGP2 */
	case 101: /* stmt: LABELV */
	case 82: /* rc5: CNSTI2 */
	case 42: /* reg: CNSTP2 */
	case 41: /* reg: CNSTU4 */
	case 40: /* reg: CNSTU2 */
	case 39: /* reg: CNSTU1 */
	case 38: /* reg: CNSTI4 */
	case 37: /* reg: CNSTI2 */
	case 36: /* reg: CNSTI1 */
	case 31: /* base: ADDRFP2 */
	case 30: /* base: ADDRLP2 */
	case 29: /* base: ADDRGP2 */
	case 27: /* jaddr: ADDRGP2 */
	case 26: /* acon: ADDRGP2 */
	case 24: /* laddr: ADDRLP2 */
	case 23: /* laddr: ADDRFP2 */
	case 20: /* con: CNSTP2 */
	case 19: /* con: CNSTU4 */
	case 18: /* con: CNSTI4 */
	case 17: /* con: CNSTU2 */
	case 16: /* con: CNSTI2 */
	case 15: /* con: CNSTU1 */
	case 14: /* con: CNSTI1 */
	case 7: /* reg: INDIRP2(VREGP) */
	case 6: /* reg: INDIRU4(VREGP) */
	case 5: /* reg: INDIRI4(VREGP) */
	case 4: /* reg: INDIRU2(VREGP) */
	case 3: /* reg: INDIRI2(VREGP) */
	case 2: /* reg: INDIRU1(VREGP) */
	case 1: /* reg: INDIRI1(VREGP) */
		break;
	case 13: /* stmt: ASGNU4(VREGP,reg) */
	case 12: /* stmt: ASGNI4(VREGP,reg) */
	case 11: /* stmt: ASGNU2(VREGP,reg) */
	case 10: /* stmt: ASGNI2(VREGP,reg) */
	case 9: /* stmt: ASGNU1(VREGP,reg) */
	case 8: /* stmt: ASGNI1(VREGP,reg) */
		kids[0] = RIGHT_CHILD(p);
		break;
	case 122: /* ar: reg */
	case 83: /* rc5: reg */
	case 69: /* rc: reg */
	case 68: /* rc: con */
	case 35: /* reg: base */
	case 34: /* baddr: reg */
	case 33: /* addr: baddr */
	case 32: /* base: reg */
	case 28: /* addr: jaddr */
	case 25: /* addr: laddr */
	case 22: /* acon: con */
	case 21: /* stmt: reg */
		kids[0] = p;
		break;
	case 116: /* stmt: NEU2(reg,reg) */
	case 115: /* stmt: NEI2(reg,reg) */
	case 114: /* stmt: LTU2(reg,reg) */
	case 113: /* stmt: LTI2(reg,reg) */
	case 112: /* stmt: LEU2(reg,reg) */
	case 111: /* stmt: LEI2(reg,reg) */
	case 110: /* stmt: GTU2(reg,reg) */
	case 109: /* stmt: GTI2(reg,reg) */
	case 108: /* stmt: GEU2(reg,reg) */
	case 107: /* stmt: GEI2(reg,reg) */
	case 106: /* stmt: EQU2(reg,reg) */
	case 105: /* stmt: EQI2(reg,reg) */
	case 87: /* reg: RSHU2(reg,rc5) */
	case 86: /* reg: RSHI2(reg,rc5) */
	case 85: /* reg: LSHU2(reg,rc5) */
	case 84: /* reg: LSHI2(reg,rc5) */
	case 81: /* reg: SUBU2(reg,rc) */
	case 80: /* reg: SUBP2(reg,rc) */
	case 79: /* reg: SUBI2(reg,rc) */
	case 78: /* reg: BXORU2(reg,rc) */
	case 77: /* reg: BORU2(reg,rc) */
	case 76: /* reg: BANDU2(reg,rc) */
	case 75: /* reg: BXORI2(reg,rc) */
	case 74: /* reg: BORI2(reg,rc) */
	case 73: /* reg: BANDI2(reg,rc) */
	case 72: /* reg: ADDU2(reg,rc) */
	case 71: /* reg: ADDP2(reg,rc) */
	case 70: /* reg: ADDI2(reg,rc) */
	case 67: /* reg: MULU2(reg,reg) */
	case 66: /* reg: MULI2(reg,reg) */
	case 65: /* reg: MODU2(reg,reg) */
	case 64: /* reg: MODI2(reg,reg) */
	case 63: /* reg: DIVU2(reg,reg) */
	case 62: /* reg: DIVI2(reg,reg) */
	case 49: /* stmt: ASGNP2(addr,reg) */
	case 48: /* stmt: ASGNU4(addr,reg) */
	case 47: /* stmt: ASGNI4(addr,reg) */
	case 46: /* stmt: ASGNU2(addr,reg) */
	case 45: /* stmt: ASGNI2(addr,reg) */
	case 44: /* stmt: ASGNU1(addr,reg) */
	case 43: /* stmt: ASGNI1(addr,reg) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = RIGHT_CHILD(p);
		break;
	case 130: /* stmt: ARGP2(rc) */
	case 129: /* stmt: ARGU2(rc) */
	case 128: /* stmt: ARGI2(rc) */
	case 127: /* stmt: RETV(reg) */
	case 126: /* stmt: RETP2(reg) */
	case 125: /* stmt: RETU2(reg) */
	case 124: /* stmt: RETI2(reg) */
	case 121: /* stmt: CALLV(ar) */
	case 120: /* reg: CALLU2(ar) */
	case 119: /* reg: CALLP2(ar) */
	case 118: /* reg: CALLI2(ar) */
	case 104: /* stmt: JUMPV(reg) */
	case 103: /* stmt: JUMPV(reg) */
	case 102: /* stmt: JUMPV(acon) */
	case 100: /* reg: CVUU2(reg) */
	case 99: /* reg: CVUI2(reg) */
	case 98: /* reg: CVII2(reg) */
	case 97: /* reg: LOADU4(reg) */
	case 96: /* reg: LOADP2(reg) */
	case 95: /* reg: LOADI4(reg) */
	case 94: /* reg: LOADU2(reg) */
	case 93: /* reg: LOADI2(reg) */
	case 92: /* reg: LOADU1(reg) */
	case 91: /* reg: LOADI1(reg) */
	case 90: /* reg: NEGI2(reg) */
	case 89: /* reg: BCOMU2(reg) */
	case 88: /* reg: BCOMI2(reg) */
	case 57: /* reg: INDIRP2(addr) */
	case 56: /* reg: INDIRU4(addr) */
	case 55: /* reg: INDIRI4(addr) */
	case 54: /* reg: INDIRU2(addr) */
	case 53: /* reg: INDIRI2(baddr) */
	case 52: /* reg: INDIRI2(laddr) */
	case 51: /* reg: INDIRU1(addr) */
	case 50: /* reg: INDIRI1(addr) */
		kids[0] = LEFT_CHILD(p);
		break;
	case 131: /* stmt: ARGB(INDIRB(reg)) */
	case 61: /* reg: CVUI2(INDIRU2(addr)) */
	case 60: /* reg: CVUI2(INDIRU1(addr)) */
	case 59: /* reg: CVUU2(INDIRU1(addr)) */
	case 58: /* reg: CVII2(INDIRI1(addr)) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		break;
	case 132: /* stmt: ASGNB(reg,INDIRB(reg)) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = LEFT_CHILD(RIGHT_CHILD(p));
		break;
	default:
		fatal("_kids", "Bad rule number %d\n", eruleno);
	}
}


// Emitters
static void progbeg(int argc, char *argv[]) {
    {
	union {
	    char c;
	    int i;
	} u;
	u.i = 0;
	u.c = 1;
	swap = ((int)(u.i == 1)) != IR->little_endian;
    }
    parseflags(argc,argv);

    // Long reg symbols
    // longreg[R_L0] = mkreg("L0",R_L0,1,IREG);
    //     longreg[R_L1] = mkreg("L1",R_L1,1,IREG);
    //     longreg[R_L2] = mkreg("L2",R_L2,1,IREG);
    //     longreg[R_L3] = mkreg("L3",R_L3,1,IREG);

    // Reg symbols
    intreg[R0] = mkreg("r0",R0,1,IREG);
    intreg[R1] = mkreg("r1",R1,1,IREG);
    intreg[R2] = mkreg("r2",R2,1,IREG);
    intreg[R3] = mkreg("r3",R3,1,IREG);
    intreg[R4] = mkreg("r4",R4,1,IREG);

    // Set up sets
    //longwldcrd = mkwildcard(longreg);
    intwldcrd = mkwildcard(intreg);

    // Set up temp regs
    tmask[IREG] = (1<<R1) | (1<<R3) | (1<<R4);

    // Set up register temps - none in our case
    vmask[IREG] = 0;

    //print("include(`macros.m4')\n");
    //print("\n");
    print(";	DME assembly file, generated by lcc 4.2\n");
    print("\n");
    print(";  temp boiler plate puts SP at 0x64\n");
    print("\n");
    print("\t ldi sp, 0x64");
/*
 * FIXME - enable this when we have a linker
    print("	.extern	$global$\n");
*/

    current_seg = 0;
}

static Symbol rmap(int opk) {
    switch (optype(opk)) {
	case B:
	case P:
	    return intwldcrd;
	case I:
	case U:
	    if (opsize(opk) <= 2) {
	        return intwldcrd;
	    } else {
		return 0;
	    }
	case F:
	    return 0;
	default:
	    return 0;
    }
}

static void segment(int n) {
    if (n==current_seg)
	return;
    if (n == CODE)
	print("\t.cseg\n");
    else if (n == LIT)
#if 1 // combine lit with dseg
	print("\t.dseg\n");
#else
	print("\t.lit\n");
#endif
    else if (n == DATA)
	print("\t.dseg\n");
    else if (n == BSS)
	print("\t.bss\n");
    else
	print("\tERROR - unknown segment %d\n",n);
    current_seg = n;
}

// NOTE - remove these when I have a real linker.  It will take care of
// defining these symbols.
static void progend(void) {
    if (ever_used_floats) {
	// Emit dummy ref to bring in floating point support code
	print("\t.dseg\n");
	printf("\t.extern\t__fp_hook\n");
	print("\t.defw\t__fp_hook\n");
    }
    print("\t.end\n");
}

int iscvt(Node p) {
    return ((generic(p->op)==CVI) || (generic(p->op)==CVU));
}

static void target(Node p) {
    assert(p);

    switch (specific(p->op)) {
    case CNST+I:
    case CNST+U:
    case CNST+P:
      if (range(p, 0, 0) == 0) {
        setreg(p, intreg[0]);
        p->x.registered = 1;
      }
      break;
    }
}

// Only real registers can be clobbered.  If we've already done a setreg
// for the result, make sure we don't clobber it here.
// Shouldn't we clobber for 16-bit MUL/DIV?
static void clobber(Node p) {

}




int isfloat8(Node p) {
        assert(p);
	assert(p->kids[0]);
	if (opsize(p->kids[0]->op)==8)
	    return 3;
	else
	    return LBURG_MAX;
}

int isfloat4(Node p) {
        assert(p);
	assert(p->kids[0]);
	if (opsize(p->kids[0]->op)==4)
	    return 3;
	else
	    return LBURG_MAX;
}




// Looks for a a = b <op> a cases
int flip_memop(Node p) {
        assert(p);
        assert(generic(p->op) == ASGN);
        assert(p->kids[0]);
        assert(p->kids[1]);
	if (generic(p->kids[1]->kids[1]->op) == INDIR
        && sametree(p->kids[0], p->kids[1]->kids[1]->kids[0])) {
                return 3;
	} else
                return LBURG_MAX;
}

// Looks for a <op>= b or a = a <op> b cases
int memop(Node p) {
        assert(p);
        assert(generic(p->op) == ASGN);
        assert(p->kids[0]);
        assert(p->kids[1]);
        if (generic(p->kids[1]->kids[0]->op) == INDIR
        && sametree(p->kids[0], p->kids[1]->kids[0]->kids[0]))
                return 3;
        else
                return LBURG_MAX;
}
int sametree(Node p, Node q) {
  return p == NULL && q == NULL
  || p && q && p->op == q->op && p->syms[0] == q->syms[0]
  && sametree(p->kids[0], q->kids[0])
  && sametree(p->kids[1], q->kids[1]);
}

int isfptr(Node n, int iftrue, int iffalse) {
   if (!n->syms[0]->generated && isfunc(n->syms[0]->type))
       return iftrue;
   else
       return iffalse;
}

static void emit2(Node p) {
    int op = specific(p->op);

}
static void doarg(Node p) {
        assert(p && p->syms[0]);
        mkactual(2, p->syms[0]->u.c.v.i);
}

// Block operators not needed
static void blkfetch(int k, int off, int reg, int tmp) {}
static void blkstore(int k, int off, int reg, int tmp) {}
static void blkloop(int dreg, int doff, int sreg, int soff,int size, int tmps[]) {}

static void local(Symbol p) {
#if 0
    // FIXME - why am I doing this?   The x86 had to differentiate, but
    // I don't.
    if (isfloat(p->type)) {
	p->sclass = AUTO;
    }
#endif
    if (askregvar(p,(*IR->x.rmap)(ttob(p->type)))==0) {
	    mkauto(p);
    }
}


static void function(Symbol f, Symbol caller[], Symbol callee[], int n) {
    int i;

    used_longs = used_floats = 0;

    double_ptr = 0;

    print("%s:\n",f->x.name);
    usedmask[0] = usedmask[1] = 0;
    freemask[0] = freemask[1] = ~(unsigned)0;
    offset = 8;
    for (i=0; callee[i]; i++) {
    	Symbol p = callee[i];
    	Symbol q = caller[i];
    	assert(q);
    	p->x.offset = q->x.offset = offset; /* + A_T0_STORE_SIZE; */
    	p->x.name = q->x.name = stringf("%d",p->x.offset);
    	p->sclass = q->sclass = AUTO;
    	offset += roundup(q->type->size,2);
    }
    assert(caller[i] == 0);

    offset = maxoffset = 0;
    gencode(caller, callee);
    framesize = roundup(maxoffset, 2);
    //print("Framesize: %d", framesize);

    // Gen entry code
    // push old framepointer onto the stack and replace by current SP
    print("\tpush\tbp\n");
    print("\tmov\tbp, sp\n");
    // make room for the new frame
    if (framesize > 0) {
      // we cant be sure off the frame size
      print("\tldi\tr4, %d\n", framesize);
      print("\tsub\tsp, r4, sp\n");
    }

    // if (isstruct(freturn(f->type))) {
//        print("\tst.16\t-2+%d(sp),a\n",framesize);
//     }
//     if (double_ptr) {
//        print("\tst.16\t%d+%d(sp),a\n",double_ptr,framesize);
//     }
    emitcode();
    if (framesize > 0) {
      //restore SP
      printf("\tldw\tsp, (-2, dp)\n");
    }
    // restore DP
    // printf("\tldw\t")
    // return
    printf("\tpop\tpc\n");
    printf("\n");
}

static void defsymbol(Symbol p) {
    if (p->scope >= LOCAL && p->sclass == STATIC)
	p->x.name = stringf("L%d", genlabel(1));
    else if (p->generated)
	p->x.name = stringf("L%s", p->name);
    else if (p->scope == GLOBAL || p->sclass == EXTERN)
	p->x.name = stringf("_%s",p->name);
    else if (p->scope == CONSTANTS
	    && (isint(p->type) || isptr(p->type))
	    && p->name[0] == '0' && p->name[1] == 'x')
	p->x.name = stringf("0%sH", &p->name[2]);
    else
	p->x.name = p->name;
}

static void address(Symbol q, Symbol p, long n) {
        if (p->scope == GLOBAL
        || p->sclass == STATIC || p->sclass == EXTERN)
                q->x.name = stringf("%s%s%D",
                        p->x.name, n >= 0 ? "+" : "", n);
        else {
                assert(n <= INT_MAX && n >= INT_MIN);
                q->x.offset = p->x.offset + n;
                q->x.name = stringd(q->x.offset);
        }
}

static void defconst(int suffix, int size, Value v) {
        if (suffix == I && size == 1)
                print("	.defb 0x%x\n",   v.u & 0xff);
        else if (suffix == I && size == 2)
                print("	.defw 0x%x\n",   v.i & 0xffff);
        else if (suffix == U && size == 1)
                print("	.defb 0x%x\n", v.u & 0xff);
        else if (suffix == U && size == 2)
                print("	.defw 0x%x\n",   v.i & 0xffff);
        else if (suffix == P && size == 2)
                print("	.defw 0x%x\n", v.u & 0xffff);
        else if (suffix == F && size == 4) {
                float f = (float)v.d;
		unsigned short *p = (unsigned short*)&f;
                print("	.defw 0x%x\n", p[1]);
                print("	.defw 0x%x\n", p[0]);
	} else if (suffix == F && size == 8) {
	        double d = (double)v.d;
		unsigned short *f = (unsigned short*)&d;
                print("	.defw 0x%x\n", f[3]);
                print("	.defw 0x%x\n", f[2]);
                print("	.defw 0x%x\n", f[1]);
                print("	.defw 0x%x\n", f[0]);
        } else if (suffix == I && size == 4) {
                print("	.defw 0x%x\n",   (v.i>>16) & 0xffff);
                print("	.defw 0x%x\n",   v.i & 0xffff);
        } else if (suffix == U && size == 4) {
                print("	.defw 0x%x\n",   (v.u>>16) & 0xffff);
                print("	.defw 0x%x\n",   v.u & 0xffff);
	}
        else assert(0);
}

static void defaddress(Symbol p) {
        print("	.defw %s\n", p->x.name);
}

static void defstring(int n, char *str) {
        char *s;
        for (s = str; s < str + n; s++)
                print("	.defb %d\n", (*s)&0377);
}

static void export(Symbol p) {
    print("\t.global %s\n", p->x.name);
}

static void import(Symbol p) {
    print("\t.extern %s\n", p->x.name);
}

static void global(Symbol p) {
        //assert(p->type->align == 1);
        print("%s:\n", p->x.name);
        if (p->u.seg == BSS)
                print("	.defs %d\n", p->type->size);
}

static void space(int n) {
        if (current_seg != BSS)
                print("	.defs %d\n", n);
}


Interface dmeIR = {
        1, 1, 0,  /* char */
        2, 2, 0,  /* short */
        2, 2, 0,  /* int */
        4, 2, 1,  /* long */
        4, 2, 1,  /* long long */
        4, 2, 1,  /* float */
        8, 2, 1,  /* double */
        8, 2, 1,  /* long double */
        2, 2, 0,  /* T * */
        0, 2, 0,  /* struct */
        0,        /* little_endian */
        0,        /* mulops_calls */
        1,        /* wants_callb */
        1,        /* wants_argb */
        0,        /* left_to_right */
        0,        /* wants_dag */
        0,        /* unsigned_char */
        address,
        blockbeg,
        blockend,
        defaddress,
        defconst,
        defstring,
        defsymbol,
        emit,
        export,
        function,
        gen,
        global,
        import,
        local,
        progbeg,
        progend,
        segment,
        space,
        0, 0, 0, 0, 0, 0, 0,
        {1, rmap,
            blkfetch, blkstore, blkloop,
            _label,
            _rule,
            _nts,
            _kids,
            _string,
            _templates,
            _isinstruction,
            _ntname,
            emit2,
            doarg,
            target,
            clobber,
}
};
static char rcsid[] = "$Id: m1.md,v 1.15 2006/10/11 01:05:49 buzbee Exp buzbee $";



