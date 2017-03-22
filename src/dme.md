%{

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
%}
%start stmt

%term CNSTF4=4113 CNSTF8=8209 CNSTF16=16401
%term CNSTI1=1045 CNSTI2=2069 CNSTI4=4117 CNSTI8=8213
%term CNSTP2=2071
%term CNSTU1=1046 CNSTU2=2070 CNSTU4=4118 CNSTU8=8214

%term ARGB=41
%term ARGF4=4129 ARGF8=8225 ARGF16=16417
%term ARGI2=2085 ARGI4=4133 ARGI8=8229
%term ARGP2=2087
%term ARGU2=2086 ARGU4=4134 ARGU8=8230

%term ASGNB=57
%term ASGNF4=4145 ASGNF8=8241 ASGNF16=16433
%term ASGNI1=1077 ASGNI2=2101 ASGNI4=4149 ASGNI8=8245
%term ASGNP2=2103
%term ASGNU1=1078 ASGNU2=2102 ASGNU4=4150 ASGNU8=8246

%term INDIRB=73
%term INDIRF4=4161 INDIRF8=8257 INDIRF16=16449
%term INDIRI1=1093 INDIRI2=2117 INDIRI4=4165 INDIRI8=8261
%term INDIRP2=2119
%term INDIRU1=1094 INDIRU2=2118 INDIRU4=4166 INDIRU8=8262

%term CVFF4=4209 CVFF8=8305 CVFF16=16497
%term CVFI2=2165 CVFI4=4213 CVFI8=8309

%term CVIF4=4225 CVIF8=8321 CVIF16=16513
%term CVII1=1157 CVII2=2181 CVII4=4229 CVII8=8325
%term CVIU1=1158 CVIU2=2182 CVIU4=4230 CVIU8=8326

%term CVPU2=2198

%term CVUI1=1205 CVUI2=2229 CVUI4=4277 CVUI8=8373
%term CVUP2=2231
%term CVUU1=1206 CVUU2=2230 CVUU4=4278 CVUU8=8374

%term NEGF4=4289 NEGF8=8385 NEGF16=16577
%term NEGI2=2245 NEGI4=4293 NEGI8=8389

%term CALLB=217
%term CALLF4=4305 CALLF8=8401 CALLF16=16593
%term CALLI2=2261 CALLI4=4309 CALLI8=8405
%term CALLP2=2263
%term CALLU2=2262 CALLU4=4310 CALLU8=8406
%term CALLV=216

%term RETF4=4337 RETF8=8433 RETF16=16625
%term RETI2=2293 RETI4=4341 RETI8=8437
%term RETP2=2295
%term RETU2=2294 RETU4=4342 RETU8=8438
%term RETV=248

%term ADDRGP2=2311

%term ADDRFP2=2327

%term ADDRLP2=2343

%term ADDF4=4401 ADDF8=8497 ADDF16=16689
%term ADDI2=2357 ADDI4=4405 ADDI8=8501
%term ADDP2=2359
%term ADDU2=2358 ADDU4=4406 ADDU8=8502

%term SUBF4=4417 SUBF8=8513 SUBF16=16705
%term SUBI2=2373 SUBI4=4421 SUBI8=8517
%term SUBP2=2375
%term SUBU2=2374 SUBU4=4422 SUBU8=8518

%term LSHI2=2389 LSHI4=4437 LSHI8=8533
%term LSHU2=2390 LSHU4=4438 LSHU8=8534

%term MODI2=2405 MODI4=4453 MODI8=8549
%term MODU2=2406 MODU4=4454 MODU8=8550

%term RSHI2=2421 RSHI4=4469 RSHI8=8565
%term RSHU2=2422 RSHU4=4470 RSHU8=8566

%term BANDI2=2437 BANDI4=4485 BANDI8=8581
%term BANDU2=2438 BANDU4=4486 BANDU8=8582

%term BCOMI2=2453 BCOMI4=4501 BCOMI8=8597
%term BCOMU2=2454 BCOMU4=4502 BCOMU8=8598

%term BORI2=2469 BORI4=4517 BORI8=8613
%term BORU2=2470 BORU4=4518 BORU8=8614

%term BXORI2=2485 BXORI4=4533 BXORI8=8629
%term BXORU2=2486 BXORU4=4534 BXORU8=8630

%term DIVF4=4545 DIVF8=8641 DIVF16=16833
%term DIVI2=2501 DIVI4=4549 DIVI8=8645
%term DIVU2=2502 DIVU4=4550 DIVU8=8646

%term MULF4=4561 MULF8=8657 MULF16=16849
%term MULI2=2517 MULI4=4565 MULI8=8661
%term MULU2=2518 MULU4=4566 MULU8=8662

%term EQF4=4577 EQF8=8673 EQF16=16865
%term EQI2=2533 EQI4=4581 EQI8=8677
%term EQU2=2534 EQU4=4582 EQU8=8678

%term GEF4=4593 GEF8=8689 GEF16=16881
%term GEI2=2549 GEI4=4597 GEI8=8693
%term GEU2=2550 GEU4=4598 GEU8=8694

%term GTF4=4609 GTF8=8705 GTF16=16897
%term GTI2=2565 GTI4=4613 GTI8=8709
%term GTU2=2566 GTU4=4614 GTU8=8710

%term LEF4=4625 LEF8=8721 LEF16=16913
%term LEI2=2581 LEI4=4629 LEI8=8725
%term LEU2=2582 LEU4=4630 LEU8=8726

%term LTF4=4641 LTF8=8737 LTF16=16929
%term LTI2=2597 LTI4=4645 LTI8=8741
%term LTU2=2598 LTU4=4646 LTU8=8742

%term NEF4=4657 NEF8=8753 NEF16=16945
%term NEI2=2613 NEI4=4661 NEI8=8757
%term NEU2=2614 NEU4=4662 NEU8=8758

%term JUMPV=584
%term LABELV=600

%term LOADI4=4325
%term LOADU4=4326
%term LOADI2=2277
%term LOADU2=2278
%term LOADP2=2279
%term LOADB=233
%term LOADI1=1253
%term LOADU1=1254

%term VREGP=711

%%

  reg:  INDIRI1(VREGP)     "# read register\n"
  reg:  INDIRU1(VREGP)     "# read register\n"

  reg:  INDIRI2(VREGP)     "# read register\n"
  reg:  INDIRU2(VREGP)     "# read register\n"

  reg:  INDIRI4(VREGP)     "# read register\n"
  reg:  INDIRU4(VREGP)     "# read register\n"


  reg:  INDIRP2(VREGP)     "# read register\n"

  stmt: ASGNI1(VREGP,reg)  "# write register\n"
  stmt: ASGNU1(VREGP,reg)  "# write register\n"

  stmt: ASGNI2(VREGP,reg)  "# write register\n"
  stmt: ASGNU2(VREGP,reg)  "# write register\n"

  stmt: ASGNI4(VREGP,reg)  "# write register\n"
  stmt: ASGNU4(VREGP,reg)  "# write register\n"

  con: CNSTI1  "%a"
  con: CNSTU1  "%a"

  con: CNSTI2  "%a"
  con: CNSTU2  "%a"

  con: CNSTI4  "%a"
  con: CNSTU4  "%a"
  con: CNSTP2  "%a"

  regc: con "\tldi\t%c, %0\n" 1
  reg: regc "%0"

  conIR:  CNSTI2  "1"  range(a, 1, 1)
  conIR:  CNSTI2  "2"  range(a, 2, 2)
  conIR:  CNSTI2  "4"  range(a, 4, 4)
  conIR:  CNSTI2  "8"  range(a, 8, 8)

  conIR:  CNSTU2  "1"  range(a, 1, 1)
  conIR:  CNSTU2  "2"  range(a, 2, 2)
  conIR:  CNSTU2  "4"  range(a, 4, 4)
  conIR:  CNSTU2  "8"  range(a, 8, 8)

  conIR:  CNSTI2  "-1"  range(a, -1, -1)
  conIR:  CNSTI2  "-2"  range(a, -2, -2)
  conIR:  CNSTI2  "-4"  range(a, -4, -4)
  conIR:  CNSTI2  "-8"  range(a, -8, -8)

  con: conIR "%0"


  stmt: reg  ""

  acon: con  "%0"

  laddr: ADDRFP2  "%a(bp)" range(a, -63, 63)
  laddr: ADDRLP2  "%a(bp)" range(a, -63, 63)
  addr: laddr "%0"

  jaddr: ADDRGP2  "%a XX"
  addr: jaddr "%0"

  base: ADDRGP2  "%a[BASE]"
  base: ADDRLP2  "%a[BASE]"
  base: ADDRFP2  "%a[bp]"

  base: reg  "%0"
  addr: baddr "%0"

  baddr: reg "%0"

  reg: base  "\tlda\t%c,%0[BASE]\n" 1


	index: LSHI2(reg, conIR) "shl %c, %1, %0\n" 1

	reg: INDIRI2(ADDP2(index, reg)) "ldwb %c, (%0, %1)\n" 1

  stmt: ASGNI1(addr,reg)  "sb $%1,%0\n"  1
  stmt: ASGNU1(addr,reg)  "sb $%1,%0\n"  1
  stmt: ASGNI2(laddr,reg)  "\tstw\t%1,%0\n"  1
  stmt: ASGNI2(baddr,reg)  "\tstwb\t%1,%0,r0\n"  1
  stmt: ASGNU2(addr,reg)  "\tstw\t%1,%0\n"  1
  stmt: ASGNP2(addr,reg)  "sw $%1,%0\n"  1
  reg:  INDIRI1(addr)     "lb $%c,%0\n"  1
  reg:  INDIRU1(addr)     "lbu $%c,%0\n"  1
  reg:  INDIRI2(laddr)     "\tldw\t%c,%0\n" 1
  reg:  INDIRI2(baddr)     "\tldwb\t%c,%0,r0\n" 2
  reg:  INDIRU2(addr)     "\tldw\t%c,%0\n"  1
  reg:  INDIRP2(addr)     "lw $%c,%0\n"  1


  reg:  CVII2(INDIRI1(addr))     "lb $%c,%0\n"  1
  reg:  CVUU2(INDIRU1(addr))     "lbu $%c,%0\n"  1
  reg:  CVUI2(INDIRU1(addr))     "lbu $%c,%0\n"  1
  reg:  CVUI2(INDIRU2(addr))     "lhu $%c,%0\n"  1

  reg: DIVI2(reg,reg)  "div $%c,$%0,$%1\n"   1
  reg: DIVU2(reg,reg)  "divu $%c,$%0,$%1\n"  1
  reg: MODI2(reg,reg)  "rem $%c,$%0,$%1\n"   1
  reg: MODU2(reg,reg)  "remu $%c,$%0,$%1\n"  1
  reg: MULI2(reg,reg)  "mul $%c,$%0,$%1\n"   1
  reg: MULU2(reg,reg)  "mul $%c,$%0,$%1\n"   1

  reg: ADDI2(reg,reg)   "\tadd\t%c,%0,%1\n"  1
  reg: ADDP2(reg,reg)   "\tadd\t%c,%0,%1\n"  1
  reg: ADDU2(reg,reg)   "\tadd\t%c,%0,%1\n"  1

  reg: ADDI2(reg,conIR)  "\taddi\t%c,%0,%1\n"  1
  reg: ADDP2(reg,conIR)  "\taddi\t%c,%0,%1\n"  1
  reg: ADDU2(reg,conIR)  "\taddi\t%c,%0,%1\n"  1

  reg: SUBI2(reg,reg)   "\tsub\t%c,%0,%1\n"  1
  reg: SUBP2(reg,reg)   "\tsub\t%c,%0,%1\n"  1
  reg: SUBU2(reg,reg)   "\tsub\t%c,%0,%1\n"  1

  reg: SUBI2(reg,conIR)   "\tsubi\t%c,$%1,%0\n"  1
  reg: SUBP2(reg,conIR)   "\tsubi\t%c,$%1,%0\n"  1
  reg: SUBU2(reg,conIR)   "\tsubi\t%c,$%1,%0\n"  1

  reg: BANDI2(reg,reg)  "\tand\t%c,$%0,%1\n"   1
  reg: BORI2(reg,reg)   "\tor\t%c,$%0,%1\n"    1
  reg: BXORI2(reg,reg)  "\txor\t%c,$%0,%1\n"   1
  reg: BANDU2(reg,reg)  "\tand\t%c,$%0,%1\n"   1
  reg: BORU2(reg,reg)   "\tor\t%c,$%0,%1\n"    1
  reg: BXORU2(reg,reg)  "\txor\t%c,$%0,%1\n"   1


  reg: BANDI2(reg,conIR)  "\tand\t%c,%1,%0\n"   1
  reg: BORI2(reg,conIR)   "\tor\t%c,%1,%0\n"    1
  reg: BXORI2(reg,conIR)  "\txor\t%c,%1,%0\n"   1
  reg: BANDU2(reg,conIR)  "\tand\t%c,%1,%0\n"   1
  reg: BORU2(reg,conIR)   "\tor\t%c,%1,%0\n"    1
  reg: BXORU2(reg,conIR)  "\txor\t%c,%1,%0\n"   1



  reg: BCOMI2(reg)  "not $%c,$%0\n"   1
  reg: BCOMU2(reg)  "not $%c,$%0\n"   1
  reg: NEGI2(reg)   "negu $%c,$%0\n"  1
  reg: LOADI1(reg)  "\tmov\t%c,%0\n"  move(a)
  reg: LOADU1(reg)  "\tmov\t%c,%0\n"  move(a)
  reg: LOADI2(reg)  "\tmov\t%c,%0\n"  move(a)
  reg: LOADU2(reg)  "\tmov\t%c,%0\n"  move(a)
  reg: LOADI4(reg)  "\tmov\t%c,%0\n"  move(a)
  reg: LOADP2(reg)  "\tmov\t%c,%0\n"  move(a)
  reg: LOADU4(reg)  "\tmov\t%c,%0\n"  move(a)

  reg: CVII2(reg)  "sll $%c,$%0,8*(4-%a); sra $%c,$%c,8*(4-%a)\n"  2
  reg: CVUI2(reg)  "and $%c,$%0,(1<<(8*%a))-1\n"  1
  reg: CVUU2(reg)  "and $%c,$%0,(1<<(8*%a))-1\n"  1

  stmt: LABELV  "%a:\n"
  stmt: JUMPV(acon)  "\tbr\t%0\n"   1
  stmt: JUMPV(reg)   ".cpadd $%0\nj $%0\n"
  stmt: JUMPV(reg)   "j $%0\n"

  stmt: EQI2(reg,reg)  "beq $%0,$%1,%a\n"   1
  stmt: EQU2(reg,reg)  "beq $%0,$%1,%a\n"   1
  stmt: GEI2(reg,reg)  "bge $%0,$%1,%a\n"   1
  stmt: GEU2(reg,reg)  "bgeu $%0,$%1,%a\n"  1
  stmt: GTI2(reg,reg)  "bgt $%0,$%1,%a\n"   1
  stmt: GTU2(reg,reg)  "bgtu $%0,$%1,%a\n"  1
  stmt: LEI2(reg,reg)  "ble $%0,$%1,%a\n"   1
  stmt: LEU2(reg,reg)  "bleu $%0,$%1,%a\n"  1
  stmt: LTI2(reg,reg)  "blt $%0,$%1,%a\n"   1
  stmt: LTU2(reg,reg)  "bltu $%0,$%1,%a\n"  1
  stmt: NEI2(reg,reg)  "bne $%0,$%1,%a\n"   1
  stmt: NEU2(reg,reg)  "bne $%0,$%1,%a\n"   1




  reg:  CALLI2(jaddr)  "\taddi\tr1,pc,4\n\tpush\tr1\n\tbr\t%0\n"  1
  reg:  CALLP2(jaddr)  "jal %0\n"  1
  reg:  CALLU2(jaddr)  "\tBRANCH UNSIGNED\n"  1
  stmt: CALLV(jaddr)  "jal %0\n"  1

  stmt: RETI2(reg)  "# ret\n"  1
  stmt: RETU2(reg)  "# ret\n"  1
  stmt: RETP2(reg)  "# ret\n"  1
  stmt: RETV(reg)   "# ret\n"  1





  stmt: ARGI2(regc)  "\tpush\t%0\n" 1
  stmt: ARGU2(regc)  "\tpush\t%0\n" 1
  stmt: ARGP2(regc)  "\tpush\t%0\n" 1



  stmt: ARGB(INDIRB(reg))       "# argb %0\n"      1
  stmt: ASGNB(reg,INDIRB(reg))  "# asgnb %0 %1\n"  1


%%

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
    tmask[IREG] = (1<<R1) | (1<<R2) | (1<<R3) | (1<<R4);

    // Set up register temps - none in our case
    vmask[IREG] = 0;

    //print("include(`macros.m4')\n");
    //print("\n");
    print(";	DME assembly file, generated by lcc 4.2\n");
    print("\n");
    print(";  temp boiler plate puts SP at 0x64 and branches to main\n");
    print("\tldi\tsp, 0x64\n");
    print("\tbr\t_main\n");
    print("\n\n");
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
                print("	defw 0x%x\n",   v.i & 0xffff);
        else if (suffix == U && size == 1)
                print("	.defb 0x%x\n", v.u & 0xff);
        else if (suffix == U && size == 2)
                print("	.defw 0x%x\n",   v.i & 0xffff);
        else if (suffix == P && size == 2)
                print("	.defw 0x%x\n", v.u & 0xffff);
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



