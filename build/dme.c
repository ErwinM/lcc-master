
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
generated at Sun Jun  4 10:52:10 2017
by $Id$
*/
static void _kids(NODEPTR_TYPE, int, NODEPTR_TYPE[]);
static void _label(NODEPTR_TYPE);
static int _rule(void*, int);

#define _stmt_NT 1
#define _reg_NT 2
#define _con_NT 3
#define _conIR_NT 4
#define _acon_NT 5
#define _addr_NT 6
#define _jaddr_NT 7
#define _index_NT 8

static char *_ntname[] = {
	0,
	"stmt",
	"reg",
	"con",
	"conIR",
	"acon",
	"addr",
	"jaddr",
	"index",
	0
};

struct _state {
	short cost[9];
	struct {
		unsigned int _stmt:6;
		unsigned int _reg:7;
		unsigned int _con:3;
		unsigned int _conIR:4;
		unsigned int _acon:1;
		unsigned int _addr:2;
		unsigned int _jaddr:1;
		unsigned int _index:2;
	} rule;
};

static short _nts_0[] = { 0 };
static short _nts_1[] = { _reg_NT, 0 };
static short _nts_2[] = { _con_NT, 0 };
static short _nts_3[] = { _reg_NT, _con_NT, 0 };
static short _nts_4[] = { _reg_NT, _reg_NT, 0 };
static short _nts_5[] = { _index_NT, _reg_NT, _reg_NT, 0 };
static short _nts_6[] = { _index_NT, _reg_NT, 0 };
static short _nts_7[] = { _addr_NT, _reg_NT, 0 };
static short _nts_8[] = { _addr_NT, 0 };
static short _nts_9[] = { _reg_NT, _conIR_NT, 0 };
static short _nts_10[] = { _acon_NT, 0 };
static short _nts_11[] = { _jaddr_NT, 0 };

static short *_nts[] = {
	0,	/* 0 */
	_nts_0,	/* 1 */
	_nts_0,	/* 2 */
	_nts_0,	/* 3 */
	_nts_0,	/* 4 */
	_nts_0,	/* 5 */
	_nts_1,	/* 6 */
	_nts_1,	/* 7 */
	_nts_1,	/* 8 */
	_nts_1,	/* 9 */
	_nts_1,	/* 10 */
	_nts_0,	/* 11 */
	_nts_0,	/* 12 */
	_nts_0,	/* 13 */
	_nts_0,	/* 14 */
	_nts_0,	/* 15 */
	_nts_2,	/* 16 */
	_nts_0,	/* 17 */
	_nts_0,	/* 18 */
	_nts_0,	/* 19 */
	_nts_0,	/* 20 */
	_nts_0,	/* 21 */
	_nts_0,	/* 22 */
	_nts_0,	/* 23 */
	_nts_0,	/* 24 */
	_nts_0,	/* 25 */
	_nts_0,	/* 26 */
	_nts_0,	/* 27 */
	_nts_0,	/* 28 */
	_nts_0,	/* 29 */
	_nts_0,	/* 30 */
	_nts_0,	/* 31 */
	_nts_0,	/* 32 */
	_nts_0,	/* 33 */
	_nts_1,	/* 34 */
	_nts_2,	/* 35 */
	_nts_0,	/* 36 */
	_nts_0,	/* 37 */
	_nts_0,	/* 38 */
	_nts_0,	/* 39 */
	_nts_0,	/* 40 */
	_nts_0,	/* 41 */
	_nts_3,	/* 42 */
	_nts_3,	/* 43 */
	_nts_3,	/* 44 */
	_nts_4,	/* 45 */
	_nts_4,	/* 46 */
	_nts_4,	/* 47 */
	_nts_3,	/* 48 */
	_nts_3,	/* 49 */
	_nts_3,	/* 50 */
	_nts_5,	/* 51 */
	_nts_6,	/* 52 */
	_nts_6,	/* 53 */
	_nts_7,	/* 54 */
	_nts_7,	/* 55 */
	_nts_7,	/* 56 */
	_nts_7,	/* 57 */
	_nts_7,	/* 58 */
	_nts_4,	/* 59 */
	_nts_4,	/* 60 */
	_nts_4,	/* 61 */
	_nts_4,	/* 62 */
	_nts_4,	/* 63 */
	_nts_8,	/* 64 */
	_nts_8,	/* 65 */
	_nts_8,	/* 66 */
	_nts_8,	/* 67 */
	_nts_8,	/* 68 */
	_nts_1,	/* 69 */
	_nts_1,	/* 70 */
	_nts_1,	/* 71 */
	_nts_1,	/* 72 */
	_nts_1,	/* 73 */
	_nts_1,	/* 74 */
	_nts_1,	/* 75 */
	_nts_1,	/* 76 */
	_nts_1,	/* 77 */
	_nts_1,	/* 78 */
	_nts_1,	/* 79 */
	_nts_1,	/* 80 */
	_nts_1,	/* 81 */
	_nts_1,	/* 82 */
	_nts_8,	/* 83 */
	_nts_8,	/* 84 */
	_nts_8,	/* 85 */
	_nts_8,	/* 86 */
	_nts_4,	/* 87 */
	_nts_4,	/* 88 */
	_nts_4,	/* 89 */
	_nts_4,	/* 90 */
	_nts_4,	/* 91 */
	_nts_4,	/* 92 */
	_nts_4,	/* 93 */
	_nts_4,	/* 94 */
	_nts_4,	/* 95 */
	_nts_9,	/* 96 */
	_nts_9,	/* 97 */
	_nts_9,	/* 98 */
	_nts_4,	/* 99 */
	_nts_4,	/* 100 */
	_nts_4,	/* 101 */
	_nts_9,	/* 102 */
	_nts_9,	/* 103 */
	_nts_9,	/* 104 */
	_nts_4,	/* 105 */
	_nts_4,	/* 106 */
	_nts_4,	/* 107 */
	_nts_4,	/* 108 */
	_nts_4,	/* 109 */
	_nts_4,	/* 110 */
	_nts_9,	/* 111 */
	_nts_9,	/* 112 */
	_nts_9,	/* 113 */
	_nts_9,	/* 114 */
	_nts_9,	/* 115 */
	_nts_9,	/* 116 */
	_nts_1,	/* 117 */
	_nts_1,	/* 118 */
	_nts_1,	/* 119 */
	_nts_1,	/* 120 */
	_nts_1,	/* 121 */
	_nts_1,	/* 122 */
	_nts_1,	/* 123 */
	_nts_1,	/* 124 */
	_nts_0,	/* 125 */
	_nts_10,	/* 126 */
	_nts_1,	/* 127 */
	_nts_4,	/* 128 */
	_nts_4,	/* 129 */
	_nts_4,	/* 130 */
	_nts_4,	/* 131 */
	_nts_4,	/* 132 */
	_nts_4,	/* 133 */
	_nts_4,	/* 134 */
	_nts_4,	/* 135 */
	_nts_4,	/* 136 */
	_nts_4,	/* 137 */
	_nts_4,	/* 138 */
	_nts_4,	/* 139 */
	_nts_11,	/* 140 */
	_nts_11,	/* 141 */
	_nts_11,	/* 142 */
	_nts_11,	/* 143 */
	_nts_1,	/* 144 */
	_nts_1,	/* 145 */
	_nts_1,	/* 146 */
	_nts_1,	/* 147 */
	_nts_1,	/* 148 */
	_nts_1,	/* 149 */
	_nts_1,	/* 150 */
	_nts_1,	/* 151 */
	_nts_4,	/* 152 */
};

static char *_templates[] = {
/* 0 */	0,
/* 1 */	"# read register\n",	/* reg: INDIRI1(VREGP) */
/* 2 */	"# read register\n",	/* reg: INDIRU1(VREGP) */
/* 3 */	"# read register\n",	/* reg: INDIRI2(VREGP) */
/* 4 */	"# read register\n",	/* reg: INDIRU2(VREGP) */
/* 5 */	"# read register\n",	/* reg: INDIRP2(VREGP) */
/* 6 */	"# write register\n",	/* stmt: ASGNI1(VREGP,reg) */
/* 7 */	"# write register\n",	/* stmt: ASGNU1(VREGP,reg) */
/* 8 */	"# write register\n",	/* stmt: ASGNI2(VREGP,reg) */
/* 9 */	"# write register\n",	/* stmt: ASGNU2(VREGP,reg) */
/* 10 */	"# write register\n",	/* stmt: ASGNP2(VREGP,reg) */
/* 11 */	"%a",	/* con: CNSTI1 */
/* 12 */	"%a",	/* con: CNSTU1 */
/* 13 */	"%a",	/* con: CNSTI2 */
/* 14 */	"%a",	/* con: CNSTU2 */
/* 15 */	"%a",	/* con: CNSTP2 */
/* 16 */	"\tld16\t%c, %0\n",	/* reg: con */
/* 17 */	"# reg\n",	/* reg: CNSTI1 */
/* 18 */	"# reg\n",	/* reg: CNSTI2 */
/* 19 */	"# reg\n",	/* reg: CNSTU1 */
/* 20 */	"# reg\n",	/* reg: CNSTU2 */
/* 21 */	"# reg\n",	/* reg: CNSTP2 */
/* 22 */	"1",	/* conIR: CNSTI2 */
/* 23 */	"2",	/* conIR: CNSTI2 */
/* 24 */	"4",	/* conIR: CNSTI2 */
/* 25 */	"8",	/* conIR: CNSTI2 */
/* 26 */	"1",	/* conIR: CNSTU2 */
/* 27 */	"2",	/* conIR: CNSTU2 */
/* 28 */	"4",	/* conIR: CNSTU2 */
/* 29 */	"8",	/* conIR: CNSTU2 */
/* 30 */	"-1",	/* conIR: CNSTI2 */
/* 31 */	"-2",	/* conIR: CNSTI2 */
/* 32 */	"-4",	/* conIR: CNSTI2 */
/* 33 */	"-8",	/* conIR: CNSTI2 */
/* 34 */	"",	/* stmt: reg */
/* 35 */	"%0",	/* acon: con */
/* 36 */	"%a(bp)",	/* addr: ADDRFP2 */
/* 37 */	"%a(bp)",	/* addr: ADDRLP2 */
/* 38 */	"\tldi\t%c, %a\n\tadd\t%c, %c, bp\n",	/* reg: ADDRFP2 */
/* 39 */	"\tldi\t%c, %a\n\tadd\t%c, %c, bp\n",	/* reg: ADDRLP2 */
/* 40 */	"\tla16\t%c,%a\n",	/* reg: ADDRGP2 */
/* 41 */	"%a ; jaddr",	/* jaddr: ADDRGP2 */
/* 42 */	"\tshl\t%c, %0, %1\n",	/* reg: LSHI2(reg,con) */
/* 43 */	"\tshl\t%c, %0, %1\n",	/* reg: LSHU2(reg,con) */
/* 44 */	"\tshr\t%c, %0, %1\n",	/* reg: RSHU2(reg,con) */
/* 45 */	"\tshl.r\t%c, %0, %1\n",	/* reg: LSHI2(reg,reg) */
/* 46 */	"\tshl.r\t%c, %0, %1\n",	/* reg: LSHU2(reg,reg) */
/* 47 */	"\tshr.r\t%c, %0, %1\n",	/* reg: RSHU2(reg,reg) */
/* 48 */	"\tshl\t%c, %0, %1 ; [via index]\n",	/* index: LSHI2(reg,con) */
/* 49 */	"\tshl\t%c, %0, %1 ; [via index]\n",	/* index: LSHU2(reg,con) */
/* 50 */	"\tshr\t%c, %0, %1 ; [via index]\n",	/* index: RSHU2(reg,con) */
/* 51 */	"\tstw\t%0(%1),%2\n",	/* stmt: ASGNU2(ADDP2(index,reg),reg) */
/* 52 */	"\tldw\t%c,%0(%1)\n",	/* reg: INDIRI2(ADDP2(index,reg)) */
/* 53 */	"\tldw\t%c,%0(%1)\n",	/* reg: INDIRU2(ADDP2(index,reg)) */
/* 54 */	"\tstb\t%0,%1\n",	/* stmt: ASGNI1(addr,reg) */
/* 55 */	"\tstb\t%0,%1\n",	/* stmt: ASGNU1(addr,reg) */
/* 56 */	"\tstw\t%0,%1\n",	/* stmt: ASGNI2(addr,reg) */
/* 57 */	"\tstw\t%0,%1\n",	/* stmt: ASGNU2(addr,reg) */
/* 58 */	"\tstw\t%0,%1\n",	/* stmt: ASGNP2(addr,reg) */
/* 59 */	"\tstb\tr0(%0),%1\n",	/* stmt: ASGNI1(reg,reg) */
/* 60 */	"\tstb\tr0(%0),%1\n",	/* stmt: ASGNU1(reg,reg) */
/* 61 */	"\tstw\tr0(%0),%1\n",	/* stmt: ASGNI2(reg,reg) */
/* 62 */	"\tstw\tr0(%0),%1\n",	/* stmt: ASGNU2(reg,reg) */
/* 63 */	"\tstw\tr0(%0),%1\n",	/* stmt: ASGNP2(reg,reg) */
/* 64 */	"\tldb\t%c,%0\n",	/* reg: INDIRI1(addr) */
/* 65 */	"\tldb\t%c,%0\n",	/* reg: INDIRU1(addr) */
/* 66 */	"\tldw\t%c,%0\n",	/* reg: INDIRI2(addr) */
/* 67 */	"\tldw\t%c,%0\n",	/* reg: INDIRU2(addr) */
/* 68 */	"\tldw\t%c,%0\n",	/* reg: INDIRP2(addr) */
/* 69 */	"\tldb\t%c,r0(%0)\n",	/* reg: INDIRI1(reg) */
/* 70 */	"\tldb\t%c,r0(%0)\n",	/* reg: INDIRU1(reg) */
/* 71 */	"\tldw\t%c,r0(%0)\n",	/* reg: INDIRI2(reg) */
/* 72 */	"\tldw\t%c,r0(%0)\n",	/* reg: INDIRU2(reg) */
/* 73 */	"\tldw\t%c,r0(%0)\n",	/* reg: INDIRP2(reg) */
/* 74 */	"%0",	/* reg: CVII1(reg) */
/* 75 */	"%0",	/* reg: CVIU1(reg) */
/* 76 */	"%0",	/* reg: CVUI1(reg) */
/* 77 */	"%0",	/* reg: CVUU1(reg) */
/* 78 */	"%0",	/* reg: CVII2(reg) */
/* 79 */	"%0",	/* reg: CVUU2(reg) */
/* 80 */	"%0",	/* reg: CVIU2(reg) */
/* 81 */	"%0",	/* reg: CVUI2(reg) */
/* 82 */	"%0",	/* reg: CVPU2(reg) */
/* 83 */	"\tldb\t%c, %0\n\tsext\t%c, %c\n",	/* reg: CVII2(INDIRI1(addr)) */
/* 84 */	"\tldb\t%c, %0\n",	/* reg: CVII2(INDIRU1(addr)) */
/* 85 */	"\tldw\t%c, %0\n",	/* reg: CVII2(INDIRI2(addr)) */
/* 86 */	"\tldw\t%c, %0\n",	/* reg: CVIU2(INDIRI2(addr)) */
/* 87 */	"DIV16(%c,%0,%1)\n",	/* reg: DIVI2(reg,reg) */
/* 88 */	"DIV16(%c,%0,%1)\n",	/* reg: DIVU2(reg,reg) */
/* 89 */	"MOD16(%c,%0,%1)\n",	/* reg: MODI2(reg,reg) */
/* 90 */	"MOD16(%c,%0,%1)\n",	/* reg: MODU2(reg,reg) */
/* 91 */	"MULT16(%c,%0,%1)\n",	/* reg: MULI2(reg,reg) */
/* 92 */	"mul $%c,$%0,$%1\n",	/* reg: MULU2(reg,reg) */
/* 93 */	"\tadd\t%c,%0,%1\n",	/* reg: ADDI2(reg,reg) */
/* 94 */	"\tadd\t%c,%0,%1\n",	/* reg: ADDP2(reg,reg) */
/* 95 */	"\tadd\t%c,%0,%1\n",	/* reg: ADDU2(reg,reg) */
/* 96 */	"\taddi\t%c,%0,%1\n",	/* reg: ADDI2(reg,conIR) */
/* 97 */	"\taddi\t%c,%0,%1\n",	/* reg: ADDP2(reg,conIR) */
/* 98 */	"\taddi\t%c,%0,%1\n",	/* reg: ADDU2(reg,conIR) */
/* 99 */	"\tsub\t%c,%0,%1\n",	/* reg: SUBI2(reg,reg) */
/* 100 */	"\tsub\t%c,%0,%1\n",	/* reg: SUBP2(reg,reg) */
/* 101 */	"\tsub\t%c,%0,%1\n",	/* reg: SUBU2(reg,reg) */
/* 102 */	"\tsubi\t%c,%0,%1\n",	/* reg: SUBI2(reg,conIR) */
/* 103 */	"\tsubi\t%c,%0,%1\n",	/* reg: SUBP2(reg,conIR) */
/* 104 */	"\tsubi\t%c,%0,%1\n",	/* reg: SUBU2(reg,conIR) */
/* 105 */	"\tand\t%c,%0,%1\n",	/* reg: BANDI2(reg,reg) */
/* 106 */	"\tor\t%c,%0,%1\n",	/* reg: BORI2(reg,reg) */
/* 107 */	"\txor\t%c,%0,%1\n",	/* reg: BXORI2(reg,reg) */
/* 108 */	"\tand\t%c,%0,%1\n",	/* reg: BANDU2(reg,reg) */
/* 109 */	"\tor\t%c,%0,%1\n",	/* reg: BORU2(reg,reg) */
/* 110 */	"\txor\t%c,%0,%1\n",	/* reg: BXORU2(reg,reg) */
/* 111 */	"\tandi\t%c,%0,%1\n",	/* reg: BANDI2(reg,conIR) */
/* 112 */	"\tori\t%c,%0,%1\n",	/* reg: BORI2(reg,conIR) */
/* 113 */	"\txor\t%c,%0,%1\n",	/* reg: BXORI2(reg,conIR) */
/* 114 */	"\tandi\t%c,%0,%1\n",	/* reg: BANDU2(reg,conIR) */
/* 115 */	"\tori\t%c,%0,%1\n",	/* reg: BORU2(reg,conIR) */
/* 116 */	"\txor\t%c,%0,%1\n",	/* reg: BXORU2(reg,conIR) */
/* 117 */	"not $%c,$%0\n",	/* reg: BCOMI2(reg) */
/* 118 */	"not $%c,$%0\n",	/* reg: BCOMU2(reg) */
/* 119 */	"sub\t%c,r0,%c\n",	/* reg: NEGI2(reg) */
/* 120 */	"\tmov\t%c,%0\n",	/* reg: LOADI1(reg) */
/* 121 */	"\tmov\t%c,%0\n",	/* reg: LOADU1(reg) */
/* 122 */	"\tmov\t%c,%0\n",	/* reg: LOADI2(reg) */
/* 123 */	"\tmov\t%c,%0\n",	/* reg: LOADU2(reg) */
/* 124 */	"\tmov\t%c,%0\n",	/* reg: LOADP2(reg) */
/* 125 */	"%a:\n",	/* stmt: LABELV */
/* 126 */	"\tbr %0\n",	/* stmt: JUMPV(acon) */
/* 127 */	"\tbr.r %0\n",	/* stmt: JUMPV(reg) */
/* 128 */	"\tskip.ne\t%0,%1\n\tbr\t%a\n",	/* stmt: EQI2(reg,reg) */
/* 129 */	"\tskip.ne\t%0,%1\n\tbr\t%a\n",	/* stmt: EQU2(reg,reg) */
/* 130 */	"\tskip.lt %0, %1\n\tbr %a\n",	/* stmt: GEI2(reg,reg) */
/* 131 */	"bgeu $%0,$%1,%a\n",	/* stmt: GEU2(reg,reg) */
/* 132 */	"bgt $%0,$%1,%a\n",	/* stmt: GTI2(reg,reg) */
/* 133 */	"bgtu $%0,$%1,%a\n",	/* stmt: GTU2(reg,reg) */
/* 134 */	"\tskip.gt\t%0,%1\n\tbr.r\t%a\n",	/* stmt: LEI2(reg,reg) */
/* 135 */	"bleu $%0,$%1,%a\n",	/* stmt: LEU2(reg,reg) */
/* 136 */	"blt $%0,$%1,%a\n",	/* stmt: LTI2(reg,reg) */
/* 137 */	"skip.ult\t%1,%0\n\tbr.r\t%a\n",	/* stmt: LTU2(reg,reg) */
/* 138 */	"\tskip.eq %0,%1\n\tbr %a\n",	/* stmt: NEI2(reg,reg) */
/* 139 */	"\tskip.eq %0,%1\n\tbr %a\n",	/* stmt: NEU2(reg,reg) */
/* 140 */	"\tla16\tr2,%0\n\taddi\tr1,pc,2\n\tbr.r\tr2\n",	/* reg: CALLI2(jaddr) */
/* 141 */	"\tla16\tr2,%0\n\taddi\tr1,pc,2\n\tbr.r\tr2\n",	/* reg: CALLP2(jaddr) */
/* 142 */	"\tBRANCH UNSIGNED\n",	/* reg: CALLU2(jaddr) */
/* 143 */	"\tla16\tr2,%0\n\taddi\tr1,pc,2\n\tbr.r\tr2\n",	/* stmt: CALLV(jaddr) */
/* 144 */	"# ret\n",	/* stmt: RETI2(reg) */
/* 145 */	"# ret\n",	/* stmt: RETU2(reg) */
/* 146 */	"# ret\n",	/* stmt: RETP2(reg) */
/* 147 */	"# ret\n",	/* stmt: RETV(reg) */
/* 148 */	"\tpush\t%0\n",	/* stmt: ARGI2(reg) */
/* 149 */	"\tpush\t%0\n",	/* stmt: ARGU2(reg) */
/* 150 */	"\tpush\t%0\n",	/* stmt: ARGP2(reg) */
/* 151 */	"# argb %0\n",	/* stmt: ARGB(INDIRB(reg)) */
/* 152 */	"# asgnb %0 %1\n",	/* stmt: ASGNB(reg,INDIRB(reg)) */
};

static char _isinstruction[] = {
/* 0 */	0,
/* 1 */	1,	/* # read register\n */
/* 2 */	1,	/* # read register\n */
/* 3 */	1,	/* # read register\n */
/* 4 */	1,	/* # read register\n */
/* 5 */	1,	/* # read register\n */
/* 6 */	1,	/* # write register\n */
/* 7 */	1,	/* # write register\n */
/* 8 */	1,	/* # write register\n */
/* 9 */	1,	/* # write register\n */
/* 10 */	1,	/* # write register\n */
/* 11 */	0,	/* %a */
/* 12 */	0,	/* %a */
/* 13 */	0,	/* %a */
/* 14 */	0,	/* %a */
/* 15 */	0,	/* %a */
/* 16 */	1,	/* \tld16\t%c, %0\n */
/* 17 */	1,	/* # reg\n */
/* 18 */	1,	/* # reg\n */
/* 19 */	1,	/* # reg\n */
/* 20 */	1,	/* # reg\n */
/* 21 */	1,	/* # reg\n */
/* 22 */	0,	/* 1 */
/* 23 */	0,	/* 2 */
/* 24 */	0,	/* 4 */
/* 25 */	0,	/* 8 */
/* 26 */	0,	/* 1 */
/* 27 */	0,	/* 2 */
/* 28 */	0,	/* 4 */
/* 29 */	0,	/* 8 */
/* 30 */	0,	/* -1 */
/* 31 */	0,	/* -2 */
/* 32 */	0,	/* -4 */
/* 33 */	0,	/* -8 */
/* 34 */	0,	/*  */
/* 35 */	0,	/* %0 */
/* 36 */	0,	/* %a(bp) */
/* 37 */	0,	/* %a(bp) */
/* 38 */	1,	/* \tldi\t%c, %a\n\tadd\t%c, %c, bp\n */
/* 39 */	1,	/* \tldi\t%c, %a\n\tadd\t%c, %c, bp\n */
/* 40 */	1,	/* \tla16\t%c,%a\n */
/* 41 */	0,	/* %a ; jaddr */
/* 42 */	1,	/* \tshl\t%c, %0, %1\n */
/* 43 */	1,	/* \tshl\t%c, %0, %1\n */
/* 44 */	1,	/* \tshr\t%c, %0, %1\n */
/* 45 */	1,	/* \tshl.r\t%c, %0, %1\n */
/* 46 */	1,	/* \tshl.r\t%c, %0, %1\n */
/* 47 */	1,	/* \tshr.r\t%c, %0, %1\n */
/* 48 */	1,	/* \tshl\t%c, %0, %1 ; [via index]\n */
/* 49 */	1,	/* \tshl\t%c, %0, %1 ; [via index]\n */
/* 50 */	1,	/* \tshr\t%c, %0, %1 ; [via index]\n */
/* 51 */	1,	/* \tstw\t%0(%1),%2\n */
/* 52 */	1,	/* \tldw\t%c,%0(%1)\n */
/* 53 */	1,	/* \tldw\t%c,%0(%1)\n */
/* 54 */	1,	/* \tstb\t%0,%1\n */
/* 55 */	1,	/* \tstb\t%0,%1\n */
/* 56 */	1,	/* \tstw\t%0,%1\n */
/* 57 */	1,	/* \tstw\t%0,%1\n */
/* 58 */	1,	/* \tstw\t%0,%1\n */
/* 59 */	1,	/* \tstb\tr0(%0),%1\n */
/* 60 */	1,	/* \tstb\tr0(%0),%1\n */
/* 61 */	1,	/* \tstw\tr0(%0),%1\n */
/* 62 */	1,	/* \tstw\tr0(%0),%1\n */
/* 63 */	1,	/* \tstw\tr0(%0),%1\n */
/* 64 */	1,	/* \tldb\t%c,%0\n */
/* 65 */	1,	/* \tldb\t%c,%0\n */
/* 66 */	1,	/* \tldw\t%c,%0\n */
/* 67 */	1,	/* \tldw\t%c,%0\n */
/* 68 */	1,	/* \tldw\t%c,%0\n */
/* 69 */	1,	/* \tldb\t%c,r0(%0)\n */
/* 70 */	1,	/* \tldb\t%c,r0(%0)\n */
/* 71 */	1,	/* \tldw\t%c,r0(%0)\n */
/* 72 */	1,	/* \tldw\t%c,r0(%0)\n */
/* 73 */	1,	/* \tldw\t%c,r0(%0)\n */
/* 74 */	0,	/* %0 */
/* 75 */	0,	/* %0 */
/* 76 */	0,	/* %0 */
/* 77 */	0,	/* %0 */
/* 78 */	0,	/* %0 */
/* 79 */	0,	/* %0 */
/* 80 */	0,	/* %0 */
/* 81 */	0,	/* %0 */
/* 82 */	0,	/* %0 */
/* 83 */	1,	/* \tldb\t%c, %0\n\tsext\t%c, %c\n */
/* 84 */	1,	/* \tldb\t%c, %0\n */
/* 85 */	1,	/* \tldw\t%c, %0\n */
/* 86 */	1,	/* \tldw\t%c, %0\n */
/* 87 */	1,	/* DIV16(%c,%0,%1)\n */
/* 88 */	1,	/* DIV16(%c,%0,%1)\n */
/* 89 */	1,	/* MOD16(%c,%0,%1)\n */
/* 90 */	1,	/* MOD16(%c,%0,%1)\n */
/* 91 */	1,	/* MULT16(%c,%0,%1)\n */
/* 92 */	1,	/* mul $%c,$%0,$%1\n */
/* 93 */	1,	/* \tadd\t%c,%0,%1\n */
/* 94 */	1,	/* \tadd\t%c,%0,%1\n */
/* 95 */	1,	/* \tadd\t%c,%0,%1\n */
/* 96 */	1,	/* \taddi\t%c,%0,%1\n */
/* 97 */	1,	/* \taddi\t%c,%0,%1\n */
/* 98 */	1,	/* \taddi\t%c,%0,%1\n */
/* 99 */	1,	/* \tsub\t%c,%0,%1\n */
/* 100 */	1,	/* \tsub\t%c,%0,%1\n */
/* 101 */	1,	/* \tsub\t%c,%0,%1\n */
/* 102 */	1,	/* \tsubi\t%c,%0,%1\n */
/* 103 */	1,	/* \tsubi\t%c,%0,%1\n */
/* 104 */	1,	/* \tsubi\t%c,%0,%1\n */
/* 105 */	1,	/* \tand\t%c,%0,%1\n */
/* 106 */	1,	/* \tor\t%c,%0,%1\n */
/* 107 */	1,	/* \txor\t%c,%0,%1\n */
/* 108 */	1,	/* \tand\t%c,%0,%1\n */
/* 109 */	1,	/* \tor\t%c,%0,%1\n */
/* 110 */	1,	/* \txor\t%c,%0,%1\n */
/* 111 */	1,	/* \tandi\t%c,%0,%1\n */
/* 112 */	1,	/* \tori\t%c,%0,%1\n */
/* 113 */	1,	/* \txor\t%c,%0,%1\n */
/* 114 */	1,	/* \tandi\t%c,%0,%1\n */
/* 115 */	1,	/* \tori\t%c,%0,%1\n */
/* 116 */	1,	/* \txor\t%c,%0,%1\n */
/* 117 */	1,	/* not $%c,$%0\n */
/* 118 */	1,	/* not $%c,$%0\n */
/* 119 */	1,	/* sub\t%c,r0,%c\n */
/* 120 */	1,	/* \tmov\t%c,%0\n */
/* 121 */	1,	/* \tmov\t%c,%0\n */
/* 122 */	1,	/* \tmov\t%c,%0\n */
/* 123 */	1,	/* \tmov\t%c,%0\n */
/* 124 */	1,	/* \tmov\t%c,%0\n */
/* 125 */	1,	/* %a:\n */
/* 126 */	1,	/* \tbr %0\n */
/* 127 */	1,	/* \tbr.r %0\n */
/* 128 */	1,	/* \tskip.ne\t%0,%1\n\tbr\t%a\n */
/* 129 */	1,	/* \tskip.ne\t%0,%1\n\tbr\t%a\n */
/* 130 */	1,	/* \tskip.lt %0, %1\n\tbr %a\n */
/* 131 */	1,	/* bgeu $%0,$%1,%a\n */
/* 132 */	1,	/* bgt $%0,$%1,%a\n */
/* 133 */	1,	/* bgtu $%0,$%1,%a\n */
/* 134 */	1,	/* \tskip.gt\t%0,%1\n\tbr.r\t%a\n */
/* 135 */	1,	/* bleu $%0,$%1,%a\n */
/* 136 */	1,	/* blt $%0,$%1,%a\n */
/* 137 */	1,	/* skip.ult\t%1,%0\n\tbr.r\t%a\n */
/* 138 */	1,	/* \tskip.eq %0,%1\n\tbr %a\n */
/* 139 */	1,	/* \tskip.eq %0,%1\n\tbr %a\n */
/* 140 */	1,	/* \tla16\tr2,%0\n\taddi\tr1,pc,2\n\tbr.r\tr2\n */
/* 141 */	1,	/* \tla16\tr2,%0\n\taddi\tr1,pc,2\n\tbr.r\tr2\n */
/* 142 */	1,	/* \tBRANCH UNSIGNED\n */
/* 143 */	1,	/* \tla16\tr2,%0\n\taddi\tr1,pc,2\n\tbr.r\tr2\n */
/* 144 */	1,	/* # ret\n */
/* 145 */	1,	/* # ret\n */
/* 146 */	1,	/* # ret\n */
/* 147 */	1,	/* # ret\n */
/* 148 */	1,	/* \tpush\t%0\n */
/* 149 */	1,	/* \tpush\t%0\n */
/* 150 */	1,	/* \tpush\t%0\n */
/* 151 */	1,	/* # argb %0\n */
/* 152 */	1,	/* # asgnb %0 %1\n */
};

static char *_string[] = {
/* 0 */	0,
/* 1 */	"reg: INDIRI1(VREGP)",
/* 2 */	"reg: INDIRU1(VREGP)",
/* 3 */	"reg: INDIRI2(VREGP)",
/* 4 */	"reg: INDIRU2(VREGP)",
/* 5 */	"reg: INDIRP2(VREGP)",
/* 6 */	"stmt: ASGNI1(VREGP,reg)",
/* 7 */	"stmt: ASGNU1(VREGP,reg)",
/* 8 */	"stmt: ASGNI2(VREGP,reg)",
/* 9 */	"stmt: ASGNU2(VREGP,reg)",
/* 10 */	"stmt: ASGNP2(VREGP,reg)",
/* 11 */	"con: CNSTI1",
/* 12 */	"con: CNSTU1",
/* 13 */	"con: CNSTI2",
/* 14 */	"con: CNSTU2",
/* 15 */	"con: CNSTP2",
/* 16 */	"reg: con",
/* 17 */	"reg: CNSTI1",
/* 18 */	"reg: CNSTI2",
/* 19 */	"reg: CNSTU1",
/* 20 */	"reg: CNSTU2",
/* 21 */	"reg: CNSTP2",
/* 22 */	"conIR: CNSTI2",
/* 23 */	"conIR: CNSTI2",
/* 24 */	"conIR: CNSTI2",
/* 25 */	"conIR: CNSTI2",
/* 26 */	"conIR: CNSTU2",
/* 27 */	"conIR: CNSTU2",
/* 28 */	"conIR: CNSTU2",
/* 29 */	"conIR: CNSTU2",
/* 30 */	"conIR: CNSTI2",
/* 31 */	"conIR: CNSTI2",
/* 32 */	"conIR: CNSTI2",
/* 33 */	"conIR: CNSTI2",
/* 34 */	"stmt: reg",
/* 35 */	"acon: con",
/* 36 */	"addr: ADDRFP2",
/* 37 */	"addr: ADDRLP2",
/* 38 */	"reg: ADDRFP2",
/* 39 */	"reg: ADDRLP2",
/* 40 */	"reg: ADDRGP2",
/* 41 */	"jaddr: ADDRGP2",
/* 42 */	"reg: LSHI2(reg,con)",
/* 43 */	"reg: LSHU2(reg,con)",
/* 44 */	"reg: RSHU2(reg,con)",
/* 45 */	"reg: LSHI2(reg,reg)",
/* 46 */	"reg: LSHU2(reg,reg)",
/* 47 */	"reg: RSHU2(reg,reg)",
/* 48 */	"index: LSHI2(reg,con)",
/* 49 */	"index: LSHU2(reg,con)",
/* 50 */	"index: RSHU2(reg,con)",
/* 51 */	"stmt: ASGNU2(ADDP2(index,reg),reg)",
/* 52 */	"reg: INDIRI2(ADDP2(index,reg))",
/* 53 */	"reg: INDIRU2(ADDP2(index,reg))",
/* 54 */	"stmt: ASGNI1(addr,reg)",
/* 55 */	"stmt: ASGNU1(addr,reg)",
/* 56 */	"stmt: ASGNI2(addr,reg)",
/* 57 */	"stmt: ASGNU2(addr,reg)",
/* 58 */	"stmt: ASGNP2(addr,reg)",
/* 59 */	"stmt: ASGNI1(reg,reg)",
/* 60 */	"stmt: ASGNU1(reg,reg)",
/* 61 */	"stmt: ASGNI2(reg,reg)",
/* 62 */	"stmt: ASGNU2(reg,reg)",
/* 63 */	"stmt: ASGNP2(reg,reg)",
/* 64 */	"reg: INDIRI1(addr)",
/* 65 */	"reg: INDIRU1(addr)",
/* 66 */	"reg: INDIRI2(addr)",
/* 67 */	"reg: INDIRU2(addr)",
/* 68 */	"reg: INDIRP2(addr)",
/* 69 */	"reg: INDIRI1(reg)",
/* 70 */	"reg: INDIRU1(reg)",
/* 71 */	"reg: INDIRI2(reg)",
/* 72 */	"reg: INDIRU2(reg)",
/* 73 */	"reg: INDIRP2(reg)",
/* 74 */	"reg: CVII1(reg)",
/* 75 */	"reg: CVIU1(reg)",
/* 76 */	"reg: CVUI1(reg)",
/* 77 */	"reg: CVUU1(reg)",
/* 78 */	"reg: CVII2(reg)",
/* 79 */	"reg: CVUU2(reg)",
/* 80 */	"reg: CVIU2(reg)",
/* 81 */	"reg: CVUI2(reg)",
/* 82 */	"reg: CVPU2(reg)",
/* 83 */	"reg: CVII2(INDIRI1(addr))",
/* 84 */	"reg: CVII2(INDIRU1(addr))",
/* 85 */	"reg: CVII2(INDIRI2(addr))",
/* 86 */	"reg: CVIU2(INDIRI2(addr))",
/* 87 */	"reg: DIVI2(reg,reg)",
/* 88 */	"reg: DIVU2(reg,reg)",
/* 89 */	"reg: MODI2(reg,reg)",
/* 90 */	"reg: MODU2(reg,reg)",
/* 91 */	"reg: MULI2(reg,reg)",
/* 92 */	"reg: MULU2(reg,reg)",
/* 93 */	"reg: ADDI2(reg,reg)",
/* 94 */	"reg: ADDP2(reg,reg)",
/* 95 */	"reg: ADDU2(reg,reg)",
/* 96 */	"reg: ADDI2(reg,conIR)",
/* 97 */	"reg: ADDP2(reg,conIR)",
/* 98 */	"reg: ADDU2(reg,conIR)",
/* 99 */	"reg: SUBI2(reg,reg)",
/* 100 */	"reg: SUBP2(reg,reg)",
/* 101 */	"reg: SUBU2(reg,reg)",
/* 102 */	"reg: SUBI2(reg,conIR)",
/* 103 */	"reg: SUBP2(reg,conIR)",
/* 104 */	"reg: SUBU2(reg,conIR)",
/* 105 */	"reg: BANDI2(reg,reg)",
/* 106 */	"reg: BORI2(reg,reg)",
/* 107 */	"reg: BXORI2(reg,reg)",
/* 108 */	"reg: BANDU2(reg,reg)",
/* 109 */	"reg: BORU2(reg,reg)",
/* 110 */	"reg: BXORU2(reg,reg)",
/* 111 */	"reg: BANDI2(reg,conIR)",
/* 112 */	"reg: BORI2(reg,conIR)",
/* 113 */	"reg: BXORI2(reg,conIR)",
/* 114 */	"reg: BANDU2(reg,conIR)",
/* 115 */	"reg: BORU2(reg,conIR)",
/* 116 */	"reg: BXORU2(reg,conIR)",
/* 117 */	"reg: BCOMI2(reg)",
/* 118 */	"reg: BCOMU2(reg)",
/* 119 */	"reg: NEGI2(reg)",
/* 120 */	"reg: LOADI1(reg)",
/* 121 */	"reg: LOADU1(reg)",
/* 122 */	"reg: LOADI2(reg)",
/* 123 */	"reg: LOADU2(reg)",
/* 124 */	"reg: LOADP2(reg)",
/* 125 */	"stmt: LABELV",
/* 126 */	"stmt: JUMPV(acon)",
/* 127 */	"stmt: JUMPV(reg)",
/* 128 */	"stmt: EQI2(reg,reg)",
/* 129 */	"stmt: EQU2(reg,reg)",
/* 130 */	"stmt: GEI2(reg,reg)",
/* 131 */	"stmt: GEU2(reg,reg)",
/* 132 */	"stmt: GTI2(reg,reg)",
/* 133 */	"stmt: GTU2(reg,reg)",
/* 134 */	"stmt: LEI2(reg,reg)",
/* 135 */	"stmt: LEU2(reg,reg)",
/* 136 */	"stmt: LTI2(reg,reg)",
/* 137 */	"stmt: LTU2(reg,reg)",
/* 138 */	"stmt: NEI2(reg,reg)",
/* 139 */	"stmt: NEU2(reg,reg)",
/* 140 */	"reg: CALLI2(jaddr)",
/* 141 */	"reg: CALLP2(jaddr)",
/* 142 */	"reg: CALLU2(jaddr)",
/* 143 */	"stmt: CALLV(jaddr)",
/* 144 */	"stmt: RETI2(reg)",
/* 145 */	"stmt: RETU2(reg)",
/* 146 */	"stmt: RETP2(reg)",
/* 147 */	"stmt: RETV(reg)",
/* 148 */	"stmt: ARGI2(reg)",
/* 149 */	"stmt: ARGU2(reg)",
/* 150 */	"stmt: ARGP2(reg)",
/* 151 */	"stmt: ARGB(INDIRB(reg))",
/* 152 */	"stmt: ASGNB(reg,INDIRB(reg))",
};

static short _decode_stmt[] = {
	0,
	6,
	7,
	8,
	9,
	10,
	34,
	51,
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
	125,
	126,
	127,
	128,
	129,
	130,
	131,
	132,
	133,
	134,
	135,
	136,
	137,
	138,
	139,
	143,
	144,
	145,
	146,
	147,
	148,
	149,
	150,
	151,
	152,
};

static short _decode_reg[] = {
	0,
	1,
	2,
	3,
	4,
	5,
	16,
	17,
	18,
	19,
	20,
	21,
	38,
	39,
	40,
	42,
	43,
	44,
	45,
	46,
	47,
	52,
	53,
	64,
	65,
	66,
	67,
	68,
	69,
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
	82,
	83,
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
	117,
	118,
	119,
	120,
	121,
	122,
	123,
	124,
	140,
	141,
	142,
};

static short _decode_con[] = {
	0,
	11,
	12,
	13,
	14,
	15,
};

static short _decode_conIR[] = {
	0,
	22,
	23,
	24,
	25,
	26,
	27,
	28,
	29,
	30,
	31,
	32,
	33,
};

static short _decode_acon[] = {
	0,
	35,
};

static short _decode_addr[] = {
	0,
	36,
	37,
};

static short _decode_jaddr[] = {
	0,
	41,
};

static short _decode_index[] = {
	0,
	48,
	49,
	50,
};

static int _rule(void *state, int goalnt) {
	if (goalnt < 1 || goalnt > 8)
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
	if (!state)
		return 0;
	switch (goalnt) {
	case _stmt_NT:	return _decode_stmt[((struct _state *)state)->rule._stmt];
	case _reg_NT:	return _decode_reg[((struct _state *)state)->rule._reg];
	case _con_NT:	return _decode_con[((struct _state *)state)->rule._con];
	case _conIR_NT:	return _decode_conIR[((struct _state *)state)->rule._conIR];
	case _acon_NT:	return _decode_acon[((struct _state *)state)->rule._acon];
	case _addr_NT:	return _decode_addr[((struct _state *)state)->rule._addr];
	case _jaddr_NT:	return _decode_jaddr[((struct _state *)state)->rule._jaddr];
	case _index_NT:	return _decode_index[((struct _state *)state)->rule._index];
	default:
		fatal("_rule", "Bad goal nonterminal %d\n", goalnt);
		return 0;
	}
}

static void _closure_reg(NODEPTR_TYPE, int);
static void _closure_con(NODEPTR_TYPE, int);

static void _closure_reg(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_stmt_NT]) {
		p->cost[_stmt_NT] = c + 0;
		p->rule._stmt = 6;
	}
}

static void _closure_con(NODEPTR_TYPE a, int c) {
	struct _state *p = STATE_LABEL(a);
	if (c + 0 < p->cost[_acon_NT]) {
		p->cost[_acon_NT] = c + 0;
		p->rule._acon = 1;
	}
	if (c + 2 < p->cost[_reg_NT]) {
		p->cost[_reg_NT] = c + 2;
		p->rule._reg = 6;
		_closure_reg(a, c + 2);
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
				p->rule._stmt = 41;
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
				p->rule._stmt = 42;
			}
		}
		break;
	case 73: /* INDIRB */
		_label(LEFT_CHILD(a));
		break;
	case 216: /* CALLV */
		_label(LEFT_CHILD(a));
		/* stmt: CALLV(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 33;
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
			p->rule._stmt = 37;
		}
		break;
	case 584: /* JUMPV */
		_label(LEFT_CHILD(a));
		/* stmt: JUMPV(acon) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_acon_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 19;
		}
		/* stmt: JUMPV(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 20;
		}
		break;
	case 600: /* LABELV */
		/* stmt: LABELV */
		if (0 + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = 0 + 0;
			p->rule._stmt = 18;
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
			p->rule._reg = 7;
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
			p->rule._reg = 9;
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
		/* stmt: ASGNI1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 13;
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
		/* stmt: ASGNU1(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 14;
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
				if (q->cost[_conIR_NT] == 0) {
					p->cost[_conIR_NT] = 0;
					p->rule._conIR = q->rule._conIR;
				}
				if (q->cost[_acon_NT] == 0) {
					p->cost[_acon_NT] = 0;
					p->rule._acon = q->rule._acon;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_jaddr_NT] == 0) {
					p->cost[_jaddr_NT] = 0;
					p->rule._jaddr = q->rule._jaddr;
				}
				if (q->cost[_index_NT] == 0) {
					p->cost[_index_NT] = 0;
					p->rule._index = q->rule._index;
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
			p->rule._reg = 23;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 28;
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
				if (q->cost[_conIR_NT] == 0) {
					p->cost[_conIR_NT] = 0;
					p->rule._conIR = q->rule._conIR;
				}
				if (q->cost[_acon_NT] == 0) {
					p->cost[_acon_NT] = 0;
					p->rule._acon = q->rule._acon;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_jaddr_NT] == 0) {
					p->cost[_jaddr_NT] = 0;
					p->rule._jaddr = q->rule._jaddr;
				}
				if (q->cost[_index_NT] == 0) {
					p->cost[_index_NT] = 0;
					p->rule._index = q->rule._index;
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
			p->rule._reg = 24;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 29;
			_closure_reg(a, c + 0);
		}
		break;
	case 1157: /* CVII1 */
		_label(LEFT_CHILD(a));
		/* reg: CVII1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (notarget(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 33;
			_closure_reg(a, c + 0);
		}
		break;
	case 1158: /* CVIU1 */
		_label(LEFT_CHILD(a));
		/* reg: CVIU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (notarget(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 34;
			_closure_reg(a, c + 0);
		}
		break;
	case 1205: /* CVUI1 */
		_label(LEFT_CHILD(a));
		/* reg: CVUI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (notarget(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 35;
			_closure_reg(a, c + 0);
		}
		break;
	case 1206: /* CVUU1 */
		_label(LEFT_CHILD(a));
		/* reg: CVUU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (notarget(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 36;
			_closure_reg(a, c + 0);
		}
		break;
	case 1253: /* LOADI1 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 79;
			_closure_reg(a, c + 0);
		}
		break;
	case 1254: /* LOADU1 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU1(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 80;
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
			p->rule._reg = 8;
			_closure_reg(a, c + 0);
		}
		/* conIR: CNSTI2 */
		c = (range(a, 1, 1));
		if (c + 0 < p->cost[_conIR_NT]) {
			p->cost[_conIR_NT] = c + 0;
			p->rule._conIR = 1;
		}
		/* conIR: CNSTI2 */
		c = (range(a, 2, 2));
		if (c + 0 < p->cost[_conIR_NT]) {
			p->cost[_conIR_NT] = c + 0;
			p->rule._conIR = 2;
		}
		/* conIR: CNSTI2 */
		c = (range(a, 4, 4));
		if (c + 0 < p->cost[_conIR_NT]) {
			p->cost[_conIR_NT] = c + 0;
			p->rule._conIR = 3;
		}
		/* conIR: CNSTI2 */
		c = (range(a, 8, 8));
		if (c + 0 < p->cost[_conIR_NT]) {
			p->cost[_conIR_NT] = c + 0;
			p->rule._conIR = 4;
		}
		/* conIR: CNSTI2 */
		c = (range(a, -1, -1));
		if (c + 0 < p->cost[_conIR_NT]) {
			p->cost[_conIR_NT] = c + 0;
			p->rule._conIR = 9;
		}
		/* conIR: CNSTI2 */
		c = (range(a, -2, -2));
		if (c + 0 < p->cost[_conIR_NT]) {
			p->cost[_conIR_NT] = c + 0;
			p->rule._conIR = 10;
		}
		/* conIR: CNSTI2 */
		c = (range(a, -4, -4));
		if (c + 0 < p->cost[_conIR_NT]) {
			p->cost[_conIR_NT] = c + 0;
			p->rule._conIR = 11;
		}
		/* conIR: CNSTI2 */
		c = (range(a, -8, -8));
		if (c + 0 < p->cost[_conIR_NT]) {
			p->cost[_conIR_NT] = c + 0;
			p->rule._conIR = 12;
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
			p->rule._reg = 10;
			_closure_reg(a, c + 0);
		}
		/* conIR: CNSTU2 */
		c = (range(a, 1, 1));
		if (c + 0 < p->cost[_conIR_NT]) {
			p->cost[_conIR_NT] = c + 0;
			p->rule._conIR = 5;
		}
		/* conIR: CNSTU2 */
		c = (range(a, 2, 2));
		if (c + 0 < p->cost[_conIR_NT]) {
			p->cost[_conIR_NT] = c + 0;
			p->rule._conIR = 6;
		}
		/* conIR: CNSTU2 */
		c = (range(a, 4, 4));
		if (c + 0 < p->cost[_conIR_NT]) {
			p->cost[_conIR_NT] = c + 0;
			p->rule._conIR = 7;
		}
		/* conIR: CNSTU2 */
		c = (range(a, 8, 8));
		if (c + 0 < p->cost[_conIR_NT]) {
			p->cost[_conIR_NT] = c + 0;
			p->rule._conIR = 8;
		}
		break;
	case 2071: /* CNSTP2 */
		/* con: CNSTP2 */
		if (0 + 0 < p->cost[_con_NT]) {
			p->cost[_con_NT] = 0 + 0;
			p->rule._con = 5;
			_closure_con(a, 0 + 0);
		}
		/* reg: CNSTP2 */
		c = (range(a, 0, 0));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 11;
			_closure_reg(a, c + 0);
		}
		break;
	case 2085: /* ARGI2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 38;
		}
		break;
	case 2086: /* ARGU2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 39;
		}
		break;
	case 2087: /* ARGP2 */
		_label(LEFT_CHILD(a));
		/* stmt: ARGP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 40;
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
		/* stmt: ASGNI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 15;
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
		if (	/* stmt: ASGNU2(ADDP2(index,reg),reg) */
			LEFT_CHILD(a)->op == 2359 /* ADDP2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_index_NT] + ((struct _state *)(RIGHT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 7;
			}
		}
		/* stmt: ASGNU2(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 11;
		}
		/* stmt: ASGNU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 16;
		}
		break;
	case 2103: /* ASGNP2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		if (	/* stmt: ASGNP2(VREGP,reg) */
			LEFT_CHILD(a)->op == 711 /* VREGP */
		) {
			c = ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 0;
			if (c + 0 < p->cost[_stmt_NT]) {
				p->cost[_stmt_NT] = c + 0;
				p->rule._stmt = 5;
			}
		}
		/* stmt: ASGNP2(addr,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 12;
		}
		/* stmt: ASGNP2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 17;
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
				if (q->cost[_conIR_NT] == 0) {
					p->cost[_conIR_NT] = 0;
					p->rule._conIR = q->rule._conIR;
				}
				if (q->cost[_acon_NT] == 0) {
					p->cost[_acon_NT] = 0;
					p->rule._acon = q->rule._acon;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_jaddr_NT] == 0) {
					p->cost[_jaddr_NT] = 0;
					p->rule._jaddr = q->rule._jaddr;
				}
				if (q->cost[_index_NT] == 0) {
					p->cost[_index_NT] = 0;
					p->rule._index = q->rule._index;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 3;
				_closure_reg(a, c + 0);
			}
		}
		if (	/* reg: INDIRI2(ADDP2(index,reg)) */
			LEFT_CHILD(a)->op == 2359 /* ADDP2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_index_NT] + ((struct _state *)(RIGHT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg_NT] + 1;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 21;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRI2(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 25;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 30;
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
				if (q->cost[_conIR_NT] == 0) {
					p->cost[_conIR_NT] = 0;
					p->rule._conIR = q->rule._conIR;
				}
				if (q->cost[_acon_NT] == 0) {
					p->cost[_acon_NT] = 0;
					p->rule._acon = q->rule._acon;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_jaddr_NT] == 0) {
					p->cost[_jaddr_NT] = 0;
					p->rule._jaddr = q->rule._jaddr;
				}
				if (q->cost[_index_NT] == 0) {
					p->cost[_index_NT] = 0;
					p->rule._index = q->rule._index;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 4;
				_closure_reg(a, c + 0);
			}
		}
		if (	/* reg: INDIRU2(ADDP2(index,reg)) */
			LEFT_CHILD(a)->op == 2359 /* ADDP2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_index_NT] + ((struct _state *)(RIGHT_CHILD(LEFT_CHILD(a))->x.state))->cost[_reg_NT] + 1;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 22;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRU2(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 26;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 31;
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
				if (q->cost[_conIR_NT] == 0) {
					p->cost[_conIR_NT] = 0;
					p->rule._conIR = q->rule._conIR;
				}
				if (q->cost[_acon_NT] == 0) {
					p->cost[_acon_NT] = 0;
					p->rule._acon = q->rule._acon;
				}
				if (q->cost[_addr_NT] == 0) {
					p->cost[_addr_NT] = 0;
					p->rule._addr = q->rule._addr;
				}
				if (q->cost[_jaddr_NT] == 0) {
					p->cost[_jaddr_NT] = 0;
					p->rule._jaddr = q->rule._jaddr;
				}
				if (q->cost[_index_NT] == 0) {
					p->cost[_index_NT] = 0;
					p->rule._index = q->rule._index;
				}
			}
			c = 0;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 5;
				_closure_reg(a, c + 0);
			}
		}
		/* reg: INDIRP2(addr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_addr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 27;
			_closure_reg(a, c + 0);
		}
		/* reg: INDIRP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 2;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 32;
			_closure_reg(a, c + 0);
		}
		break;
	case 2165: /* CVFI2 */
		break;
	case 2181: /* CVII2 */
		_label(LEFT_CHILD(a));
		/* reg: CVII2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (notarget(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 37;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: CVII2(INDIRI1(addr)) */
			LEFT_CHILD(a)->op == 1093 /* INDIRI1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 42;
				_closure_reg(a, c + 0);
			}
		}
		if (	/* reg: CVII2(INDIRU1(addr)) */
			LEFT_CHILD(a)->op == 1094 /* INDIRU1 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 43;
				_closure_reg(a, c + 0);
			}
		}
		if (	/* reg: CVII2(INDIRI2(addr)) */
			LEFT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 44;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 2182: /* CVIU2 */
		_label(LEFT_CHILD(a));
		/* reg: CVIU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (notarget(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 39;
			_closure_reg(a, c + 0);
		}
		if (	/* reg: CVIU2(INDIRI2(addr)) */
			LEFT_CHILD(a)->op == 2117 /* INDIRI2 */
		) {
			c = ((struct _state *)(LEFT_CHILD(LEFT_CHILD(a))->x.state))->cost[_addr_NT] + 1;
			if (c + 0 < p->cost[_reg_NT]) {
				p->cost[_reg_NT] = c + 0;
				p->rule._reg = 45;
				_closure_reg(a, c + 0);
			}
		}
		break;
	case 2198: /* CVPU2 */
		_label(LEFT_CHILD(a));
		/* reg: CVPU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (notarget(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 41;
			_closure_reg(a, c + 0);
		}
		break;
	case 2229: /* CVUI2 */
		_label(LEFT_CHILD(a));
		/* reg: CVUI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (notarget(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 40;
			_closure_reg(a, c + 0);
		}
		break;
	case 2230: /* CVUU2 */
		_label(LEFT_CHILD(a));
		/* reg: CVUU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (notarget(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 38;
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
			p->rule._reg = 78;
			_closure_reg(a, c + 0);
		}
		break;
	case 2261: /* CALLI2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLI2(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 84;
			_closure_reg(a, c + 0);
		}
		break;
	case 2262: /* CALLU2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLU2(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 86;
			_closure_reg(a, c + 0);
		}
		break;
	case 2263: /* CALLP2 */
		_label(LEFT_CHILD(a));
		/* reg: CALLP2(jaddr) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_jaddr_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 85;
			_closure_reg(a, c + 0);
		}
		break;
	case 2277: /* LOADI2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 81;
			_closure_reg(a, c + 0);
		}
		break;
	case 2278: /* LOADU2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 82;
			_closure_reg(a, c + 0);
		}
		break;
	case 2279: /* LOADP2 */
		_label(LEFT_CHILD(a));
		/* reg: LOADP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + (move(a));
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 83;
			_closure_reg(a, c + 0);
		}
		break;
	case 2293: /* RETI2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 34;
		}
		break;
	case 2294: /* RETU2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 35;
		}
		break;
	case 2295: /* RETP2 */
		_label(LEFT_CHILD(a));
		/* stmt: RETP2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 36;
		}
		break;
	case 2311: /* ADDRGP2 */
		/* reg: ADDRGP2 */
		if (1 + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = 1 + 0;
			p->rule._reg = 14;
			_closure_reg(a, 1 + 0);
		}
		/* jaddr: ADDRGP2 */
		if (0 + 0 < p->cost[_jaddr_NT]) {
			p->cost[_jaddr_NT] = 0 + 0;
			p->rule._jaddr = 1;
		}
		break;
	case 2327: /* ADDRFP2 */
		/* addr: ADDRFP2 */
		c = (range(a, -63, 63));
		if (c + 0 < p->cost[_addr_NT]) {
			p->cost[_addr_NT] = c + 0;
			p->rule._addr = 1;
		}
		/* reg: ADDRFP2 */
		if (2 + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = 2 + 0;
			p->rule._reg = 12;
			_closure_reg(a, 2 + 0);
		}
		break;
	case 2343: /* ADDRLP2 */
		/* addr: ADDRLP2 */
		c = (range(a, -63, 63));
		if (c + 0 < p->cost[_addr_NT]) {
			p->cost[_addr_NT] = c + 0;
			p->rule._addr = 2;
		}
		/* reg: ADDRLP2 */
		if (2 + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = 2 + 0;
			p->rule._reg = 13;
			_closure_reg(a, 2 + 0);
		}
		break;
	case 2357: /* ADDI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 52;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDI2(reg,conIR) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_conIR_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 55;
			_closure_reg(a, c + 0);
		}
		break;
	case 2358: /* ADDU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 54;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDU2(reg,conIR) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_conIR_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 57;
			_closure_reg(a, c + 0);
		}
		break;
	case 2359: /* ADDP2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: ADDP2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 53;
			_closure_reg(a, c + 0);
		}
		/* reg: ADDP2(reg,conIR) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_conIR_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 56;
			_closure_reg(a, c + 0);
		}
		break;
	case 2373: /* SUBI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 58;
			_closure_reg(a, c + 0);
		}
		/* reg: SUBI2(reg,conIR) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_conIR_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 61;
			_closure_reg(a, c + 0);
		}
		break;
	case 2374: /* SUBU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 60;
			_closure_reg(a, c + 0);
		}
		/* reg: SUBU2(reg,conIR) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_conIR_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 63;
			_closure_reg(a, c + 0);
		}
		break;
	case 2375: /* SUBP2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: SUBP2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 59;
			_closure_reg(a, c + 0);
		}
		/* reg: SUBP2(reg,conIR) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_conIR_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 62;
			_closure_reg(a, c + 0);
		}
		break;
	case 2389: /* LSHI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 15;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 18;
			_closure_reg(a, c + 0);
		}
		/* index: LSHI2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_index_NT]) {
			p->cost[_index_NT] = c + 0;
			p->rule._index = 1;
		}
		break;
	case 2390: /* LSHU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: LSHU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 16;
			_closure_reg(a, c + 0);
		}
		/* reg: LSHU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 19;
			_closure_reg(a, c + 0);
		}
		/* index: LSHU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_index_NT]) {
			p->cost[_index_NT] = c + 0;
			p->rule._index = 2;
		}
		break;
	case 2405: /* MODI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: MODI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 48;
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
			p->rule._reg = 49;
			_closure_reg(a, c + 0);
		}
		break;
	case 2421: /* RSHI2 */
		break;
	case 2422: /* RSHU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: RSHU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 17;
			_closure_reg(a, c + 0);
		}
		/* reg: RSHU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 20;
			_closure_reg(a, c + 0);
		}
		/* index: RSHU2(reg,con) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_con_NT] + 1;
		if (c + 0 < p->cost[_index_NT]) {
			p->cost[_index_NT] = c + 0;
			p->rule._index = 3;
		}
		break;
	case 2437: /* BANDI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 64;
			_closure_reg(a, c + 0);
		}
		/* reg: BANDI2(reg,conIR) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_conIR_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 70;
			_closure_reg(a, c + 0);
		}
		break;
	case 2438: /* BANDU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BANDU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 67;
			_closure_reg(a, c + 0);
		}
		/* reg: BANDU2(reg,conIR) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_conIR_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 73;
			_closure_reg(a, c + 0);
		}
		break;
	case 2453: /* BCOMI2 */
		_label(LEFT_CHILD(a));
		/* reg: BCOMI2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 76;
			_closure_reg(a, c + 0);
		}
		break;
	case 2454: /* BCOMU2 */
		_label(LEFT_CHILD(a));
		/* reg: BCOMU2(reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 77;
			_closure_reg(a, c + 0);
		}
		break;
	case 2469: /* BORI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 65;
			_closure_reg(a, c + 0);
		}
		/* reg: BORI2(reg,conIR) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_conIR_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 71;
			_closure_reg(a, c + 0);
		}
		break;
	case 2470: /* BORU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BORU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 68;
			_closure_reg(a, c + 0);
		}
		/* reg: BORU2(reg,conIR) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_conIR_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 74;
			_closure_reg(a, c + 0);
		}
		break;
	case 2485: /* BXORI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 66;
			_closure_reg(a, c + 0);
		}
		/* reg: BXORI2(reg,conIR) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_conIR_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 72;
			_closure_reg(a, c + 0);
		}
		break;
	case 2486: /* BXORU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* reg: BXORU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 69;
			_closure_reg(a, c + 0);
		}
		/* reg: BXORU2(reg,conIR) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_conIR_NT] + 1;
		if (c + 0 < p->cost[_reg_NT]) {
			p->cost[_reg_NT] = c + 0;
			p->rule._reg = 75;
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
			p->rule._reg = 46;
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
			p->rule._reg = 47;
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
			p->rule._reg = 50;
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
			p->rule._reg = 51;
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
			p->rule._stmt = 21;
		}
		break;
	case 2534: /* EQU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: EQU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 22;
		}
		break;
	case 2549: /* GEI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 23;
		}
		break;
	case 2550: /* GEU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GEU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 24;
		}
		break;
	case 2565: /* GTI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 25;
		}
		break;
	case 2566: /* GTU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: GTU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 26;
		}
		break;
	case 2581: /* LEI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 27;
		}
		break;
	case 2582: /* LEU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LEU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 28;
		}
		break;
	case 2597: /* LTI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 29;
		}
		break;
	case 2598: /* LTU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: LTU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 30;
		}
		break;
	case 2613: /* NEI2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEI2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 31;
		}
		break;
	case 2614: /* NEU2 */
		_label(LEFT_CHILD(a));
		_label(RIGHT_CHILD(a));
		/* stmt: NEU2(reg,reg) */
		c = ((struct _state *)(LEFT_CHILD(a)->x.state))->cost[_reg_NT] + ((struct _state *)(RIGHT_CHILD(a)->x.state))->cost[_reg_NT] + 1;
		if (c + 0 < p->cost[_stmt_NT]) {
			p->cost[_stmt_NT] = c + 0;
			p->rule._stmt = 32;
		}
		break;
	case 4113: /* CNSTF4 */
		break;
	case 4117: /* CNSTI4 */
		break;
	case 4118: /* CNSTU4 */
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
		break;
	case 4150: /* ASGNU4 */
		break;
	case 4161: /* INDIRF4 */
		break;
	case 4165: /* INDIRI4 */
		break;
	case 4166: /* INDIRU4 */
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
		break;
	case 4326: /* LOADU4 */
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
	case 125: /* stmt: LABELV */
	case 41: /* jaddr: ADDRGP2 */
	case 40: /* reg: ADDRGP2 */
	case 39: /* reg: ADDRLP2 */
	case 38: /* reg: ADDRFP2 */
	case 37: /* addr: ADDRLP2 */
	case 36: /* addr: ADDRFP2 */
	case 33: /* conIR: CNSTI2 */
	case 32: /* conIR: CNSTI2 */
	case 31: /* conIR: CNSTI2 */
	case 30: /* conIR: CNSTI2 */
	case 29: /* conIR: CNSTU2 */
	case 28: /* conIR: CNSTU2 */
	case 27: /* conIR: CNSTU2 */
	case 26: /* conIR: CNSTU2 */
	case 25: /* conIR: CNSTI2 */
	case 24: /* conIR: CNSTI2 */
	case 23: /* conIR: CNSTI2 */
	case 22: /* conIR: CNSTI2 */
	case 21: /* reg: CNSTP2 */
	case 20: /* reg: CNSTU2 */
	case 19: /* reg: CNSTU1 */
	case 18: /* reg: CNSTI2 */
	case 17: /* reg: CNSTI1 */
	case 15: /* con: CNSTP2 */
	case 14: /* con: CNSTU2 */
	case 13: /* con: CNSTI2 */
	case 12: /* con: CNSTU1 */
	case 11: /* con: CNSTI1 */
	case 5: /* reg: INDIRP2(VREGP) */
	case 4: /* reg: INDIRU2(VREGP) */
	case 3: /* reg: INDIRI2(VREGP) */
	case 2: /* reg: INDIRU1(VREGP) */
	case 1: /* reg: INDIRI1(VREGP) */
		break;
	case 10: /* stmt: ASGNP2(VREGP,reg) */
	case 9: /* stmt: ASGNU2(VREGP,reg) */
	case 8: /* stmt: ASGNI2(VREGP,reg) */
	case 7: /* stmt: ASGNU1(VREGP,reg) */
	case 6: /* stmt: ASGNI1(VREGP,reg) */
		kids[0] = RIGHT_CHILD(p);
		break;
	case 35: /* acon: con */
	case 34: /* stmt: reg */
	case 16: /* reg: con */
		kids[0] = p;
		break;
	case 139: /* stmt: NEU2(reg,reg) */
	case 138: /* stmt: NEI2(reg,reg) */
	case 137: /* stmt: LTU2(reg,reg) */
	case 136: /* stmt: LTI2(reg,reg) */
	case 135: /* stmt: LEU2(reg,reg) */
	case 134: /* stmt: LEI2(reg,reg) */
	case 133: /* stmt: GTU2(reg,reg) */
	case 132: /* stmt: GTI2(reg,reg) */
	case 131: /* stmt: GEU2(reg,reg) */
	case 130: /* stmt: GEI2(reg,reg) */
	case 129: /* stmt: EQU2(reg,reg) */
	case 128: /* stmt: EQI2(reg,reg) */
	case 116: /* reg: BXORU2(reg,conIR) */
	case 115: /* reg: BORU2(reg,conIR) */
	case 114: /* reg: BANDU2(reg,conIR) */
	case 113: /* reg: BXORI2(reg,conIR) */
	case 112: /* reg: BORI2(reg,conIR) */
	case 111: /* reg: BANDI2(reg,conIR) */
	case 110: /* reg: BXORU2(reg,reg) */
	case 109: /* reg: BORU2(reg,reg) */
	case 108: /* reg: BANDU2(reg,reg) */
	case 107: /* reg: BXORI2(reg,reg) */
	case 106: /* reg: BORI2(reg,reg) */
	case 105: /* reg: BANDI2(reg,reg) */
	case 104: /* reg: SUBU2(reg,conIR) */
	case 103: /* reg: SUBP2(reg,conIR) */
	case 102: /* reg: SUBI2(reg,conIR) */
	case 101: /* reg: SUBU2(reg,reg) */
	case 100: /* reg: SUBP2(reg,reg) */
	case 99: /* reg: SUBI2(reg,reg) */
	case 98: /* reg: ADDU2(reg,conIR) */
	case 97: /* reg: ADDP2(reg,conIR) */
	case 96: /* reg: ADDI2(reg,conIR) */
	case 95: /* reg: ADDU2(reg,reg) */
	case 94: /* reg: ADDP2(reg,reg) */
	case 93: /* reg: ADDI2(reg,reg) */
	case 92: /* reg: MULU2(reg,reg) */
	case 91: /* reg: MULI2(reg,reg) */
	case 90: /* reg: MODU2(reg,reg) */
	case 89: /* reg: MODI2(reg,reg) */
	case 88: /* reg: DIVU2(reg,reg) */
	case 87: /* reg: DIVI2(reg,reg) */
	case 63: /* stmt: ASGNP2(reg,reg) */
	case 62: /* stmt: ASGNU2(reg,reg) */
	case 61: /* stmt: ASGNI2(reg,reg) */
	case 60: /* stmt: ASGNU1(reg,reg) */
	case 59: /* stmt: ASGNI1(reg,reg) */
	case 58: /* stmt: ASGNP2(addr,reg) */
	case 57: /* stmt: ASGNU2(addr,reg) */
	case 56: /* stmt: ASGNI2(addr,reg) */
	case 55: /* stmt: ASGNU1(addr,reg) */
	case 54: /* stmt: ASGNI1(addr,reg) */
	case 50: /* index: RSHU2(reg,con) */
	case 49: /* index: LSHU2(reg,con) */
	case 48: /* index: LSHI2(reg,con) */
	case 47: /* reg: RSHU2(reg,reg) */
	case 46: /* reg: LSHU2(reg,reg) */
	case 45: /* reg: LSHI2(reg,reg) */
	case 44: /* reg: RSHU2(reg,con) */
	case 43: /* reg: LSHU2(reg,con) */
	case 42: /* reg: LSHI2(reg,con) */
		kids[0] = LEFT_CHILD(p);
		kids[1] = RIGHT_CHILD(p);
		break;
	case 51: /* stmt: ASGNU2(ADDP2(index,reg),reg) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		kids[1] = RIGHT_CHILD(LEFT_CHILD(p));
		kids[2] = RIGHT_CHILD(p);
		break;
	case 53: /* reg: INDIRU2(ADDP2(index,reg)) */
	case 52: /* reg: INDIRI2(ADDP2(index,reg)) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		kids[1] = RIGHT_CHILD(LEFT_CHILD(p));
		break;
	case 150: /* stmt: ARGP2(reg) */
	case 149: /* stmt: ARGU2(reg) */
	case 148: /* stmt: ARGI2(reg) */
	case 147: /* stmt: RETV(reg) */
	case 146: /* stmt: RETP2(reg) */
	case 145: /* stmt: RETU2(reg) */
	case 144: /* stmt: RETI2(reg) */
	case 143: /* stmt: CALLV(jaddr) */
	case 142: /* reg: CALLU2(jaddr) */
	case 141: /* reg: CALLP2(jaddr) */
	case 140: /* reg: CALLI2(jaddr) */
	case 127: /* stmt: JUMPV(reg) */
	case 126: /* stmt: JUMPV(acon) */
	case 124: /* reg: LOADP2(reg) */
	case 123: /* reg: LOADU2(reg) */
	case 122: /* reg: LOADI2(reg) */
	case 121: /* reg: LOADU1(reg) */
	case 120: /* reg: LOADI1(reg) */
	case 119: /* reg: NEGI2(reg) */
	case 118: /* reg: BCOMU2(reg) */
	case 117: /* reg: BCOMI2(reg) */
	case 82: /* reg: CVPU2(reg) */
	case 81: /* reg: CVUI2(reg) */
	case 80: /* reg: CVIU2(reg) */
	case 79: /* reg: CVUU2(reg) */
	case 78: /* reg: CVII2(reg) */
	case 77: /* reg: CVUU1(reg) */
	case 76: /* reg: CVUI1(reg) */
	case 75: /* reg: CVIU1(reg) */
	case 74: /* reg: CVII1(reg) */
	case 73: /* reg: INDIRP2(reg) */
	case 72: /* reg: INDIRU2(reg) */
	case 71: /* reg: INDIRI2(reg) */
	case 70: /* reg: INDIRU1(reg) */
	case 69: /* reg: INDIRI1(reg) */
	case 68: /* reg: INDIRP2(addr) */
	case 67: /* reg: INDIRU2(addr) */
	case 66: /* reg: INDIRI2(addr) */
	case 65: /* reg: INDIRU1(addr) */
	case 64: /* reg: INDIRI1(addr) */
		kids[0] = LEFT_CHILD(p);
		break;
	case 151: /* stmt: ARGB(INDIRB(reg)) */
	case 86: /* reg: CVIU2(INDIRI2(addr)) */
	case 85: /* reg: CVII2(INDIRI2(addr)) */
	case 84: /* reg: CVII2(INDIRU1(addr)) */
	case 83: /* reg: CVII2(INDIRI1(addr)) */
		kids[0] = LEFT_CHILD(LEFT_CHILD(p));
		break;
	case 152: /* stmt: ASGNB(reg,INDIRB(reg)) */
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
		intreg[R5] = mkreg("bp",R5,1,IREG);

    // Set up sets
    //longwldcrd = mkwildcard(longreg);
    intwldcrd = mkwildcard(intreg);

    // Set up temp regs
    tmask[IREG] = (1<<R1) | (1<<R2) | (1<<R3) | (1<<R4);

    // Set up register temps - none in our case
    vmask[IREG] = 0;

    //print("include(`macros.m4')\n");
    //print("\n");
    print(";	DME assembly file, generated by lcc 4.2\n");
    print("\n");
		print(" ; INT_MAX: %x", UINT_MAX);
		// print(";  temp boiler plate puts SP at 0x2000 and branches to main\n");
//     print("\tld16\tr1, 0x2000\n");
//     print("\tmov\tsp, r1\n");
//     print("\taddi\tr1, pc, 2\n");
//     print("\tbr\t_main\n");
//     print("\thlt\n");
//print("\n\n");
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
			print(";\t.code\n");
    else if (n == DATA)
			// FIXME: 0x1000 is just for LCC retargeting efforts
			print("\t.data 0x1000\n");
    else if (n == LIT)
			// FIXME: 0x1000 is just for LCC retargeting efforts
			print("\t.data\n");
    else if (n == BSS)
			print("\t.bss\n");
    else
			print("\tERROR - unknown segment %d\n",n);
    	current_seg = n;
}

// NOTE - remove these when I have a real linker.  It will take care of
// defining these symbols.
static void progend(void) {
    print(";\t.end\n");
}

int iscvt(Node p) {
    return ((generic(p->op)==CVI) || (generic(p->op)==CVU));
}

static void target(Node p) {
    assert(p);

    switch (specific(p->op)) {
		case MUL+I:
		case DIV+I:
		case DIV+U:
		case MOD+I:
		case MOD+U:
		// limit register usage for pseudo ops
		  setreg(p, intreg[R1]);
			break;
    case CNST+I:
    case CNST+U:
    case CNST+P:
      if (range(p, 0, 0) == 0) {
        setreg(p, intreg[0]);
        p->x.registered = 1;
      }
      break;
    case CALL+I:
    case CALL+U:
    case CALL+P:
    case CALL+V:
      setreg(p, intreg[R1]);
      break;
    case RET+I:
    case RET+U:
    case RET+P:
		  rtarget(p, 0, intreg[R1]);
      break;
	}
}

// Only real registers can be clobbered.  If we've already done a setreg
// for the result, make sure we don't clobber it here.
// Shouldn't we clobber for 16-bit MUL/DIV?
static void clobber(Node p) {
  assert(p);

	switch(specific(p->op)) {
	case MUL+I:
	case DIV+I:
	case DIV+U:
	case MOD+I:
	case MOD+U:
		spill( (1<<R2) | (1<<R3) | (1<<R4), IREG, p);
		break;
	case CALL+I:
	case CALL+P:
	case CALL+U:
	// Would normally kill both, but if we're returning result
	// in A we've already done a setreg on it so don't spill.
		if (opsize(p->op > 2)) {
			spill( (1<<R1) | (1<<R2) | (1<<R3) | (1<<R4), IREG, p);
	  } else {
			spill( (1<<R2) | (1<<R3) | (1<<R4), IREG, p);
	  }
	  break;
	case ASGN+B:
	case CALL+V:
	// case ARG+B:
// 	// always spill bp and r1 and r2
// 		spill( (1<<R1) | (1<<R2 | 1<<R5) ,IREG,p);
// 	  break;
	//case CALL+B:
	//// I don't really understand this.  I want to show that
	//// both A and B are killed, but if I spill A here I get the
	//// spill assert as if A had been setreg'd - but I don't.
	//    spill( (1<<R_B) , IREG , p);
	//    break;
	//case CVF+I:
	//    // We've done setreg on A, kill B
	//    spill( (1<<R_B) , IREG , p);
	//    break;
	default:
	// spill everything for generic long operation.
		if (opsize(p->op) > 2) {
			spill((1<<R2) | (1<<R3) | (1<<R4),IREG,p);
	  }
	  break;
	}
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
  switch (p->op) {
  case ASGN+B: {
    static int tmpregs[] = { 1, 2, 3 };
		dalign = 2; // stack is always aligned
    salign = p->syms[1]->u.c.v.i;
		// calculate the offset
		blkcopy(getregnum(p->x.kids[0]), 0,
            getregnum(p->x.kids[1]), 0,
            p->syms[0]->u.c.v.i, tmpregs);
		break;
  }
  }
}
static void doarg(Node p) {
        assert(p && p->syms[0]);
        mkactual(2, p->syms[0]->u.c.v.i);
}

// Block operators - building of of SPARC code...

static void blkfetch(int k, int off, int reg, int tmp) {
  //print("; blkfetch: %d, %d, %d, %d\n", k,reg, off, tmp);
	assert(k == 1 || k == 2 );
  assert(salign >= k);
  if (k == 1)
  	print("ldb %r%d, %d[%r%d]\n", tmp, off, reg);
  else // k==2
    print("ldw %r%d, %d[%r%d]\n", tmp, off, reg);
}

static void blkstore(int k, int off, int reg, int tmp) {
	//print("; blkstore: %d, %d\n",k,off);
	assert(k == 1 || k == 2 );
  assert(salign >= k);
  if (k == 1)
  	print("stb %d[%r%d], r%d\n", off, reg, tmp);
  else // k==2
    print("stw %d[%r%d], r%d\n", off, reg, tmp);
}

static void blkloop(int dreg, int doff, int sreg, int soff,int size, int tmps[]) {
	print("blkloop\n");
}

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
    offset = 4;
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
    //printf("MAX: %d", maxoffset);
    framesize = roundup(maxoffset, 2);
    //print("Framesize: %d", framesize);

    // Gen entry code
    // push old framepointer onto the stack and replace by current SP
    print("\tpush\tr1\n"); // push the return address (saved in R1 by call)
		print("\tpush\tbp\n");
    print("\tmov\tbp, sp\n");
    // make room for the new frame
    if (framesize > 0) {
      // we cant be sure off the frame size
      print("\tldi\tr4, %d\n", framesize);
      print("\tsub\tsp, sp, r4\n");
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
      print("\tmov\tsp, bp\n");
    }
    print("\tpop\tbp\n");
    print("\tpop\tpc\n");
    print("\n");
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
	p->x.name = stringf("0x%s", &p->name[2]);
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
                print("defb 0x%x\n",   v.u & 0xff);
        else if (suffix == I && size == 2)
                print("defw 0x%x\n",   v.i & 0xffff);
        else if (suffix == U && size == 1)
                print("defb 0x%x\n", v.u & 0xff);
        else if (suffix == U && size == 2)
                print("defw 0x%x\n",   v.i & 0xffff);
        else if (suffix == P && size == 2)
                print("defw 0x%x\n", v.u & 0xffff);
        else assert(0);
}

static void defaddress(Symbol p) {
        print("	.defw %s\n", p->x.name);
}

static void defstring(int n, char *str) {
	char *s;
	print("\tdefstr %c%s%c\n", '"', str, '"');
	//for (s = str; s < str + n; s++)
	//	print("	.defb %d\n", (*s)&0377);
}

static void export(Symbol p) {
    print(";\t.global %s\n", p->x.name);
}

static void import(Symbol p) {
    print(";\t.extern %s\n", p->x.name);
}

static void global(Symbol p) {
        //assert(p->type->align == 1);
        print("%s:\n", p->x.name);
        if (p->u.seg == BSS)
                print("	defs %d\n", p->type->size);
}

static void space(int n) {
        if (current_seg != BSS)
                print("	defs %d\n", n);
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
        0,        /* wants_callb */
        0,        /* wants_argb */
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



