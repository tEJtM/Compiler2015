 #include <stdio.h>
# include<stdlib.h>
# include <assert.h>
int POINTER_SIZE = 4;

int examine = 1;

int infi = 1000000000;

char * newEmptyString() {
	char * res = (char *)malloc(sizeof(char));
	res[0] = 0;
	return res;
}

char __stdio__printf__[888] = 
"void __printf__(char * str, int * argu) { int index = 0; while(*str) { if(*str == '%') { str[0]; str++; if(str[0] == '%') { putchar('%'); }else if(str[0] == 'c') { putchar((char)argu[index++]); }else if(str[0] == 's') { char * s = (char *)argu[index++]; while(*s) { putchar(*s); s++; } }else if(str[0] == 'd') { putint(argu[index++]); }else if(str[0] == '.') { int x = str[1] - '0'; int cnt = 0, tmp, flag = 0; if(argu[index] < 0) { argu[index] = -argu[index]; flag = 1; } tmp = argu[index]; if(flag) { putchar('-'); } cnt = tmp == 0; while(tmp) {cnt++; tmp /= 10;} while(x > cnt) {putchar('0'); x--;} putint(argu[index++]); str += 2; } }else { putchar(*str); } str++; } }\nvoid __memset__(char * a, int len) {while(len) {*a = '\\0'; a++; len--; } } \nvoid __memcpy__(char * a, char * b, int len) {while(len) {*a = *b; a++; b++; len--;} }\n";
//
//ERROR
//

char _c___memcpy__[20] = "__memcpy__";

char * bp, * program;

int errorPainting = 1;

void ERROR(int label) {
	exit(1);
}

void printERROR(char * s) {
	printf("%s", s);
	exit(0);
}

int strcmp(char * a, char * b) {
	int i = 0;
	for( ; a[i] != 0 && b[i] != 0; i++) {
		if(a[i] != b[i]) {
			return 1;
		}
	}
	return a[i] != b[i];
}

//vector of char
void push_back(char ** a, int * length, int * capacity, char c) {
	if(*length == *capacity) {
		*capacity *= 2;
		char * tmp = (char*)malloc(*capacity);
		int i;
		for(i = 0; i < *length; i++) {
			tmp[i] = (*a)[i];
		}
		*a = tmp;
	}
	(*a)[(*length)++] = c;
}

int max(int a, int b) {
	if(a > b) {
		return a;
	}else {
		return b;
	}
}

int min(int a, int b) {
	if(a > b) {
		return b;
	}else {
		return a;
	}
}

//COMMENT TYPE
int NO_COMMENT = 0, ONE_LINE_COMMENT = 1, MULTI_LINE_COMMENT = 2, INCLUDE = 3, IN_STR = 4, IN_CHR = 5;//ignore #include<...>

int nKeywords = 14;

char keyword[14][9] = {//code: 300+
	"typedef",//300
	"void",//301
	"char",//302
	"int",//303
	"struct",//304
	"union",//305
	"if",//306
	"else",//307
	"while",//308
	"for",//309
	"continue",//310
	"break",//311
	"return",//312
	"sizeof"//313
};

int nOpers = 43;

char oper[43][4] = {//code 500+
	"(",//500
	")",//501
	";",//502
	",",//503
	"=",//504
	"{",//505
	"}",//506
	"[",//507
	"]",//508
	"*",//509
	"|",//510
	"^",//511
	"&",//512
	"<",//513
	">",//514
	"+",//515
	"-",//516
	//"*",//517
	"/",//517
	"%",//518
	"~",//519
	"!",//520
	".",//521
	"||",//522
	"&&",//523
	"==",//524
	"!=",//525
	"<=",//526
	">=",//527
	"<<",//528
	">>",//529
	"++",//530
	"--",//531
	"*=",//532
	"/=",//533
	"%=",//534
	"+=",//535
	"-=",//536
	"<<=",//537
	">>=",//538
	"&=",//539
	"^=",//540
	"|=",//541
	"->"//542
};

//TOKEN TYPE
int NO_TOKEN = 0, IDENTIFIER = 400, INT_CONSTANT = 401, CHR_CONSTANT = 402, STR_CONSTANT = 403;

int isNewLine(char c) {
	return c == '\n' || c == '\r';
}

int isLetter(char c) {
	return c == '_' || c == '$' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

int isDigit(char c) {
	return c >= '0' && c <= '9';
}

int isOp() {
	int i = 0;
	for( ; i < nOpers; i++) {
		int j = 0;
		int flag = 1;
		for( ; oper[i][j]; j++) {
			if(program[j] != oper[i][j]) {
				flag = 0;
				break;
			}
		}
		if(flag) {
			return 1;
		}
	}
	return 0;
}

int op() {
	int i = 0;
	int ans = 0;
	int res = 0;
	for( ; i < nOpers; i++) {
		int j = 0;
		int flag = 1;
		for( ; oper[i][j]; j++) {
			if(program[j] != oper[i][j]) {
				flag = 0;
				break;
			}
		}
		if(flag && j > ans) {
			res = i;
			ans = j;
		}
	}
	program += ans;
	return res + 500;
}

int hex(char c) {
	if('0' <= c && c <= '9') {
		return c - '0';
	}else if('a' <= c && c <= 'f') {
		return c - 'a' + 10;
	}else if('A' <= c && c <= 'F') {
		return c - 'A' + 10;
	}else {
		return -1;
	}
}

int isHex(char c) {
	return hex(c) != -1;
}

int oct(char c) {
	if('0' <= c && c <= '7') {
		return c - '0';
	}else {
		return -1;
	}
}

int isOct(char c) {
	return oct(c) != -1;
}

int nextChar() {
	if(*program == '\\') {
		program++;
		int res;
		if(*program == 'a') {
			res = 7;
		}else if(*program == 'b') {
			res = 8;
		}else if(*program == 'f') {
			res = 12;
		}else if(*program == 'n') {
			res = 10;
		}else if(*program == 'r') {
			res = 13;
		}else if(*program == 't') {
			res = 9;
		}else if(*program == 'v') {
			res = 11;
		}else if(*program == 'x') {
			if(isHex(program[1])) {
				int x = 0;
				while(isHex(program[1])) {
					x = x * 16 + hex(program[1]);
					program++;
				}
				res = x;
			}else {
				ERROR(1);
			}
		}else if(isOct(*program)) {
			int x = oct(program[0]);
			while(isOct(program[1])) {
				x = x * 8 + oct(program[1]);
				program++;
			}
			res = x;
		}else {
			res = *program;
		}
		program++;
		return res;
	}else {
		if(isNewLine(*program)) {
			ERROR(3);
		}
		return *(program++);
	}
}

struct Token {
	int type;
	char * name;
	int value;
};

int beginOfLine;

struct Token nextToken() {
	//printf("[%c]\n", *program);
	struct Token res;
	res.name = newEmptyString();
	for(;;) {
		int flag = 1;
		while(*program != 0 && isNewLine(*program)) {
			program++;
			beginOfLine = 1;
			flag = 0;
		}
		if(*program == 0) {
			break;
		}
		while(*program != 0 && (*program == ' ' || *program == '\t')) {
			program++;
			flag = 0;
		}
		if(*program == 0) {
			break;
		}
		if(*program == '#') {
			if(!beginOfLine) {
				ERROR(90);
			}
			while(*program != 0 && !isNewLine(*program)) {
				program++;
			}
			if(*program == 0) {
				break;
			}
			flag = 0;
		}
		beginOfLine = 0;
		if(*program == '/' && program[1] == '/') {
			program += 2;
			while(*program != 0 && !isNewLine(*program)) {
				program++;
			}
			if(*program == 0) {
				break;
			}
			program++;
			flag = 0;
		}
		if(*program == '/' && program[1] == '*') {
			program += 2;
			int prev = -1;
			while(*program != 0 && !(prev == '*' && *program == '/')) {
				prev = *program;
				program++;
			}
			if(*program == 0) {
				break;
			}
			program++;
			flag = 0;
		}
		if(flag) {
			break;
		}
	}
	if(*program == 0) {
		res.type = NO_TOKEN;
		return res;
	}
	if(isLetter(*program)) {
		char * bak = program;
		while(isLetter(*program) || isDigit(*program)) {
			program++;
		}
		int i;
		res.type = IDENTIFIER;
		for(i = 0; i < nKeywords; i++) {
			int eq = 1;
			int j = 0;
			for( ; keyword[i][j]; j++) {
				if(bak[j] != keyword[i][j]) {
					eq = 0;
					break;
				}
			}
			if(eq && bak + j == program) {
				res.type = 300 + i;
				break;
			}
		}
		if(res.type == IDENTIFIER) {
			res.name = (char*)malloc(program - bak + 1);
			int i = 0;
			for( ; i < program - bak; i++) {
				res.name[i] = bak[i];
			}
			res.name[program - bak] = 0;
		}
		return res;
	}else if(isDigit(*program)) {
		int base = 10;
		int x = 0;
		if(program[0] == '0' && (program[1] == 'x' || program[1] == 'X')) {
			program += 2;
			base = 16;
		}else if(program[0] == '0') {
			program += 1;
			base = 8;
		}
		while(isHex(*program)) {
			if(isOct(*program)) {
				x = x * base + *program - '0';
			}else if(base == 8) {
				//printf("!!!\n");
				//printf("!!%c%c%c%c\n", program[0], program[1], program[2], program[3]);
				ERROR(4);
			}else if(isDigit(*program)) {
				x = x * base + *program - '0';
			}else if(base == 10) {
				ERROR(5);
			}else if(isHex(*program)) {
				x = x * base + hex(*program);
			}else {
				ERROR(6);
			}
			program++;
		}
		if(isLetter(*program)) {
			ERROR(7);//etc. 123aa
		}
		res.type = INT_CONSTANT;
		res.value = x;
		return res;
	}else if(*program == '\'') {
		program++;
		if(*program == '\'') {
			ERROR(8);
		}
		int x = nextChar();
		//		res.value = nextChar();
		while(*program != '\'') {//\D7ַ\FB\B3\A3\C1\BF\B3\A4\B6\C8\D2\E7\B3\F6, ֱ\BDӺ\F6\C2\D4.
			if(isNewLine(*program)) {
				ERROR(9);
			}else {
				x = x * 256 + nextChar();
			}
			program++;
		}
		res.value = x;
		program++;
		res.type = CHR_CONSTANT;
		return res;
	}else if(*program == '"') {
		program++;
		char * bak = program;
		int cnt = 0;
		for(;;) {
			if(*program == '"') {
				res.name = (char*)malloc(cnt + 1);
				char * bak2 = program;
				program = bak;
				int index = 0;
				while(program != bak2) {
					res.name[index++] = nextChar();
				}
				program++;
				res.name[cnt] = 0;
				res.type = STR_CONSTANT;
				return res;
			}else if(*program == '\n' || *program == '\r' || *program == 0) {
				ERROR(10);
			}else {
				cnt++;
				int x = nextChar();
				if(x == 0) {
					ERROR(11);
				}
			}
		}
	}else if(isOp()) {
		res.type = op(res);
		return res;
	}else {
		ERROR(12);
	}

}

struct List {
	int value;
	int mul;
	struct List * next, * prev;
} TMP;

struct List * newList() {
	struct List * res = (struct List *)malloc(sizeof(struct List));
	res->value = 0;
	res->mul = 0;
	res->prev = 0;
	res->next = 0;
	return res;
}

struct Type;

int totIndex = 0;

struct Variable {
	char * name;
	int level;//count of '*'
	struct Type * type;//basic type
	struct List * list;//dimensions of array
	struct Variable * next;
	int index;
} * INT_VARIABLE, * VOID_VARIABLE;

struct SymbolList;

struct Function {
	char * name;
	struct Variable * rtn;//return type
	struct Variable * argu;//arguments type
	struct Instruction * insts;
	struct Function * next;
	struct SymbolList * symbolList;
	struct List * occupy;
}* chief, * bucket;

struct Function * newFunction() {
	struct Function * f = (struct Function *)malloc(sizeof(struct Function));
	f->next = 0;
	f->argu = 0;
	f->rtn = 0;
	f->insts = 0;
	f->name = newEmptyString();
	f->symbolList = 0;
	f->occupy = 0;
	return f;
}

struct Type {
	char * name;
	int type;//0 int, 1 char, 2 struct, 3 union, 4 void, 5 function
	struct Type * next;//used for SymbolList
	struct Variable * vars;//members
	int size;
	struct List * posi;
} * CHAR_TYPE, * INT_TYPE, * VOID_TYPE, * FUNC_TYPE;

struct Type * newType() {
	struct Type * res = (struct Type *)malloc(sizeof(struct Type));
	res->name = newEmptyString();
	res->type = 0;
	res->next = 0;
	res->vars = 0;
	res->size = 0;
	return res;
}

struct Variable * newVariable() {
	struct Variable * res = (struct Variable *)malloc(sizeof(struct Variable));
	res->name = newEmptyString();
	res->level = 0;
	res->type = INT_TYPE;
	res->list = 0;
	res->next = 0;
	res->index = totIndex++;
	return res;
}

void copyType(struct Variable * a, struct Variable * b) {
	a->level = b->level;
	a->type = b->type;
	a->list = b->list;
}

void initModVariables() {
	INT_VARIABLE = newVariable();
	INT_VARIABLE->type = INT_TYPE;
	VOID_VARIABLE = newVariable();
	VOID_VARIABLE->type = VOID_TYPE;
}

void initBasicTypeName() {
	CHAR_TYPE = newType();
	CHAR_TYPE->type = 1;
	CHAR_TYPE->size = 1;
	INT_TYPE = newType();
	INT_TYPE->size = 4;
	VOID_TYPE = newType();
	VOID_TYPE->type = 4;
	VOID_TYPE->size = 1;//!!!
	FUNC_TYPE = newType();
	FUNC_TYPE->type = 5;
}

struct Token look, look1;

void move() {

	look = look1;
	look1 = nextToken();
	while(look.type == STR_CONSTANT && look1.type == STR_CONSTANT) {
		int cnt = 0;
		int i = 0;
		while(look.name[i]) {
			i++;
			cnt++;
		}
		i = 0;
		while(look1.name[i]) {
			i++;
			cnt++;
		}
		char * name1 = (char *)malloc(sizeof(char) * (cnt + 1));
		int l = 0;
		i = 0;
		while(look.name[i]) {
			name1[l++] = look.name[i++];
		}
		i = 0;
		while(look1.name[i]) {
			name1[l++] = look1.name[i++];
		}
		name1[l] = 0;
		look.name = name1;
		look1 = nextToken();
	}
}

void match(int type) {
	if(look.type == type) {
		move();
	}else {
		printf("[%d]\n", type);
		ERROR(13);
	}
}

struct SymbolList {
	struct SymbolList * prev;
	struct Variable * vars;
	struct Function * funcs;
	struct Type * QaQ;//structs & unions
} * top;

struct SymbolList * newSymbolList(struct SymbolList * top) {
	struct SymbolList * res = (struct SymbolList *)malloc(sizeof(struct SymbolList));
	res->vars = 0;
	res->funcs = 0;
	res->QaQ = 0;
	res->prev = top;
	return res;
}

struct Operand {
	int constant;//\B1\E0\D2\EBʱ\B3\A3\CA\FD?
	int value;//\C8\E7\B9\FB\CAǱ\E0\D2\EBʱ\B3\A3\CA\FD, ֵ?
	int type;//0 ֱ\BD\D3\D7\F3ֵ, 1 \BD\E2\D2\FD\D3\C3\D7\F3ֵ, 2 \D3\D2ֵ
	struct Variable * var;//\B2\D9\D7\F7\CA\FD\BAͱ\E4\C1\BF\C0\E0\D0\CD
	int loadable;
	int offset;
};

int nLabel = 0;

int newLabel() {
	return nLabel++;
}

struct Instruction {
	int type;//
	int n;
	struct Operand * a;
	struct Operand * b;
	struct Operand * c;
	struct Instruction * next;
	struct Function * f;
} * assignInst = 0;

struct Operand * newOperand(struct Variable * var, int type, int constant, int value) {
	struct Operand * res = (struct Operand *)malloc(sizeof(struct Operand));
	res->constant = constant;
	res->type = type;
	res->value = value;
	res->var = var;
	res->loadable = 0;
	res->offset = 0;
	return res;
}

struct Instruction * newInstruction(int type, struct Operand * a, struct Operand * b, struct Operand * c) {
	struct Instruction * inst = (struct Instruction *)malloc(sizeof(struct Instruction));
	inst->f = 0;
	inst->n = 0;
	inst->a = a;
	inst->b = b;
	inst->c = c;
	inst->type = type;
	return inst;
}

struct FuncList {
	struct Function * f;
	struct FuncList * next;
	struct Block * blocks;
	int cnt;
	int numReg;
	int cntArgu;
	int * regAlloc;
} * funcList;

struct FuncList * newFuncList(struct Function * f, struct FuncList * next) {
	struct FuncList * res = (struct FuncList *)malloc(sizeof(struct FuncList));
	res->f = f;
	res->blocks = 0;
	res->next = next;
	res->cnt = 0;
	return res;
}

int isAssignmentOperator(int x) {
	return x == 504 || (x >= 532 && x <= 541);
}

struct Operand * constIntOrChar(int i) {
	struct Operand * res = (struct Operand *)malloc(sizeof(struct Operand));
	res->type = 2;
	res->constant = 1;
	res->value = i;
	res->var = newVariable();
	res->var->index = -1;
	totIndex--;
	//res->loadable = 1;
	/*	res->var = (struct Variable *)malloc(sizeof(struct Variable));
		res->var->level = 0;
		res->var->name = newEmptyString();
		res->var->next = 0;
		res->var->list = 0;
		res->var->index = -1;*/
	return res;
}

struct Operand * constInt(int i) {//\B7\B5\BB\D8һ\B8\F6\B3\A3\C1\BFi
	struct Operand * res = constIntOrChar(i);
	res->var->type = INT_TYPE;
	return res;
}

struct Operand * constChar(int i) {//\B7\B5\BB\D8һ\B8\F6\B3\A3\C1\BFi
	struct Operand * res = constIntOrChar(i);
	res->var->type = CHAR_TYPE;
	return res;
}

struct Type * find(char * );

struct Variable * findVariable(char * );

struct Operand * parseAssignmentExpression(struct Function * );

struct Operand * parseExpression(struct Function * env);

int
	GET_ARGU = 0,
	DECL_POINTER = 1,
	DECL_CHAR = 2,
	DECL_INT = 3,
	MALLOC = 4,
	GETCHAR = 5,
	PUTCHAR = 6,
	NOP = 7,
	ASSIGN_ADD = 8,
	GOTO = 9,
	LABEL = 10,
	IF_GOTO = 11,
	IF_FALSE_GOTO = 12,
	ASSIGN_LOGICAL_NOT = 13,
	ASSIGN_NOT = 14,
	ASSIGN_NEGATE = 15,
	ASSIGN = 16,
	ASSIGN_CHAR = 17,
	ASSIGN_ADDRESS = 18,
	ASSIGN_INCLUSIVE_OR = 19,
	ASSIGN_EXCLUSIVE_OR = 20,
	ASSIGN_AND = 21,
	ASSIGN_SHR = 22,
	ASSIGN_SHL = 23,
	ASSIGN_SUB = 24,
	CALL = 25,
	ASSIGN_MOD = 26,
	ASSIGN_DIV = 27,
	ASSIGN_MUL = 28,
	ASSIGN_NOT_EQUAL_TO = 29,
	ASSIGN_EQUAL_TO = 30,
	ASSIGN_GREATER_THAN_OR_EQUAL_TO = 31,
	ASSIGN_LESS_THAN_OR_EQUAL_TO = 32,
	ASSIGN_GREATER_THAN = 33,
	ASSIGN_LESS_THAN = 34,
	ASSIGN_LOGIC_OR = 35,
	ASSIGN_LOGIC_AND = 36,
	ASSIGN_DEREF = 37,
	INT_TO_CHAR = 38,
	CHAR_TO_INT = 39,
	DEREF_ASSIGN_ADDRESS = 40,
	DEREF_ASSIGN = 41,
	DEREF_ASSIGN_CHAR = 42,
	RETURN = 43,
	ASSIGN_ADDRESS_OF = 44,
	ARGU = 45,
	EXIT = 46,
	VOID_RETURN = 47,
	ASSIGN_DEREF_ADDRESS = 48,
	ASSIGN_DEREF_CHAR = 49,
	PUTINT = 50,
	PHI = 51,
	LD = 52,
	LD_CHAR = 53,
	ST = 54,
	ST_CHAR = 55, 
	ASSIGN_DATA = 56, 
	ASSIGN_STR = 57;

void push(struct Function * env, struct Instruction * inst) {
	inst->next = env->insts;
	env->insts = inst;
}

void occupy(struct Function * env, struct Operand * ope) {
	struct List * new = newList();
	new->value = ope->var->index;
	new->next = env->occupy;
	env->occupy = new;
	//printf("%d %d\n", new->value, totIndex);
	//struct List * tmp = env->occupy;
	//	while(tmp) {
	//		printf("%s %d\n", env->name, tmp->value);
	//		tmp = tmp->next;
	//	}
}

struct Operand * printCast(struct Function * env, struct Variable * a, struct Operand * b);

int isStruct(struct Variable * v) {
	return v->list == 0 && v->level == 0 && (v->type->type == 2 || v->type->type == 3);
}

struct Operand * getValue(struct Function * env, struct Operand * a) {
	if(!isStruct(a->var) && !a->var->list && a->type == 1) {
		struct Instruction * inst = newInstruction(0, newOperand(newVariable(), 2, 0, 0), a, 0);
		occupy(env, inst->a);
		copyType(inst->a->var, a->var);
		if(!a->var->level && a->var->type == CHAR_TYPE) {
			inst->type = LD_CHAR;
		}else if(a->var->level || a->var->type == INT_TYPE) {
			inst->type = LD;
		}else {
			printf("Why Error??\n");
			ERROR(14);
		}
		push(env, inst);
		return inst->a;
	}else {
		return a;
	}
}

struct Operand * printMemberAccess(struct Function * env, struct Operand * a, char * name);

int calcElementSize(struct Variable * var) {
	if(var->level == 0) {
		return var->type->size;
	}else {
		return POINTER_SIZE;
	}
}

int calcSize(struct Variable * var) {
	if(var->list == 0) {
		return calcElementSize(var);
	}else {
		return calcElementSize(var) * var->list->mul;
	}
}

void printArgu(struct Function * env, struct Operand * a);

struct Function * findFunc(char * a);

struct Operand * printAddressOf(struct Function * , struct Operand * );

void printAssign(struct Function * env, struct Operand * a, struct Operand * b) {//Ҫ\B4\A6\C0\ED\CA\C7\C6\D5ͨ\D7\F3ֵ\BB\B9\CAǽ\E2\D2\FD\D3\C3\D7\F3ֵ
	if(a->var->list) {
		ERROR(15);
	}
	if(a->type == 2) {
		ERROR(85);
	}
	struct Operand * c = printCast(env, a->var, b);
	//printf("assign %s %d\n", a->var->name, a->var->level);
	if(isStruct(a->var)) {
		/*
		struct Operand * aa = newOperand(newVariable(), 0, 0, 0);
		struct Operand * cc = newOperand(newVariable(), 0, 0, 0);
		aa->var->type = CHAR_TYPE;
		cc->var->type = CHAR_TYPE;
		aa->var->level = 1;
		cc->var->level = 1;
		aa->var->index = a->var->index;
		cc->var->index = c->var->index;
		totIndex -= 2;
		printArgu(env, aa);
		printArgu(env, cc);
		printArgu(env, constInt(calcSize(a->var)));
		struct Instruction * inst = newInstruction(CALL, newOperand(newVariable(), 0, 0, 0), 0, 0);
		inst->a->var->type = VOID_TYPE;
		inst->f = findFunc(_c___memcpy__);
		inst->n = 3;
		push(env, inst);
		*/
		int i = 0, s = calcSize(a->var);
		for( ; i < s; ) {
			struct Operand * a1 = newOperand(newVariable(), 1, 0, 0), * c1 = newOperand(newVariable(), 1, 0, 0);
			a1->var->index = a->var->index;
			c1->var->index = c->var->index;
			totIndex -= 2;
			a1->offset = a->offset + i;
			c1->offset = c->offset + i;
			if(i + 4 <= s) {
				i += 4;
				printAssign(env, a1, c1);
			}else {
				i += 1;
				a1->var->type = CHAR_TYPE;
				c1->var->type = CHAR_TYPE;
				printAssign(env, a1, c1);
			}
		}
	}else {
		struct Instruction * inst = newInstruction(0, a, c, 0);
		if(a->type == 0) {
			if(!a->var->level && a->var->type == CHAR_TYPE) {
				inst->type = ASSIGN_CHAR;
			}else {
				inst->type = ASSIGN;//a = b;
			}
		}else if(a->type == 1) {
			if(!a->var->level && a->var->type == CHAR_TYPE) {
				inst->type = ST_CHAR;
			}else {
				//printf("STORE!\n");
				inst->type = ST;//*a = b;
			}
		}
		push(env, inst);
	}
}

int isIntOrChar(struct Variable * var) {
	return (var->type == INT_TYPE || var->type == CHAR_TYPE) && var->level == 0 && var->list == 0;
}

struct Operand * printAssignOp(struct Function * env, struct Operand * b, struct Operand * c, int op);

struct Operand * printAccess(struct Function * env, struct Operand * a, struct Operand * b) {
	b = printCast(env, INT_VARIABLE, b);
//	if(!isIntOrChar(b->var)) {
//		ERROR(16);
//	}
	a = getValue(env, a);
	if(a->var->list || a->var->level) {
		if(b->constant) {
			if(a->constant) {
				struct Operand * tmp = newOperand(newVariable(), 2, 0, 0);
				struct Instruction * inst = newInstruction(ASSIGN, tmp, constInt(a->value), 0);
				occupy(env, tmp);
				push(env, inst);
				copyType(tmp->var, a->var);
				a = tmp;
			}
			struct Operand * res = newOperand(newVariable(), 1, 0, 0);
			copyType(res->var, a->var);
			//occupy(env, res);
			if(a->var->list) {
				res->var->list = a->var->list->next;
			}else {
				res->var->level = a->var->level - 1;
			}
			res->var->index = a->var->index;
			totIndex--;
			res->loadable = a->loadable && b->constant;
			res->offset = a->offset + b->value * calcSize(res->var);
			return res;
		}else {
			struct Instruction * inst = newInstruction(ASSIGN_ADD, newOperand(newVariable(), 1, 0, 0), a, 0);
			occupy(env, inst->a);
			copyType(inst->a->var, a->var);
			if(a->var->list) {
				inst->a->var->list = a->var->list->next;
			}else {
				inst->a->var->level = a->var->level - 1;
			}
			inst->c = printAssignOp(env, b, constInt(calcSize(inst->a->var)), 532);
			push(env, inst);
			inst->a->loadable = a->loadable && b->constant;
			inst->a->offset = a->offset;
			return inst->a;
		}
	}else {
		ERROR(17);
	}
}

struct Operand * printMalloc(struct Function * env, struct Operand * a);

struct Operand * printCopy(struct Function * env, struct Operand * a) {
	if(a->var->list) {
		ERROR(18);
	}
	//printf("parsePostfix++\n");
	struct Operand * ope = newOperand(newVariable(), 0, 0, 0);
	//printf("parsePostfix++ %d\n", env);
	occupy(env, ope);
	//	printf("parsePostfix++\n");
	if(isStruct(a->var)) {
		ope->type = 1;
		printMalloc(env, constInt(calcSize(a->var)));
		env->insts->a = ope;
	}
	copyType(ope->var, a->var);
	printAssign(env, ope, a);
	ope->type = 2;
	//printf("copy Complete %s %d\n", a->var->name, a->var->level);
	return ope;
}

void printArgu(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction(ARGU, 0, 0, 0);
	if(isStruct(a->var)) {
		inst->a = printCopy(env, a);
	}else if(a->var->list) {
		inst->a = a;
	}else {
		inst->a = getValue(env, a);
	}
	push(env, inst);
}

int compArray(struct List * p, struct List * q) {//\B1Ƚ\CF\CA\FD\D7\E9ά\B6\C8
	if(!p && !q) {//ά\CA\FD\CF\E0ͬ, \B7\B6Χ\B6\D4Ӧ\CF\E0ͬ
		return 1;
	}
	if(!p || !q) {
		return 0;
	}
	if(p->value != q->value) {
		return 0;
	}
	return compArray(p->next, q->next);
}

int compType(struct Variable * a, struct Variable * b) {//\B1Ƚ\CF\C0\E0\D0\CD
	if(a->level != b->level) {//\B1Ƚ\CFָ\D5\EB\BD\D7\CA\FD
		return 0;
	}
	if(a->type != b->type) {//\B1Ƚϻ\F9\B1\BE\C0\E0\D0\CD
		return 0;
	}
	if(!compArray(a->list, b->list)) {//\B1Ƚ\CF\CA\FD\D7\E9ά\B6\C8
		return 0;
	}
	return 1;
}

int calcDepth(struct List * p) {
	int res = 0;
	while(p) {
		p = p->next;
		res++;
	}
	return res;
}

int isVoid(struct Variable * v) {
	return v->type == VOID_TYPE && !v->list && !v->level;
}

int isChar(struct Variable * v) {
	return v->type == CHAR_TYPE && !v->list && !v->level;
}

struct Operand * directLvalue(struct Variable * v) {//\BD\AB\B1\E4\C1\BFת\BB\BBΪֱ\BD\D3\D7\F3ֵ
	struct Operand * res = newOperand(v, !(v->list == 0 && !isStruct(v)), 0, 0);
	if(v->list || isStruct(v)) {
		res->loadable = 1;
	}
	return res;
}

int isPointer(struct Variable * v) {
	return v->list == 0 && v->level >= 1;
}

struct Operand * printCast(struct Function * env, struct Variable * b, struct Operand * a) {
	if(a->type == 1) {
		a = getValue(env, a);
	}
	if(isVoid(b)) {
		return directLvalue(VOID_VARIABLE);
	}
	if(isVoid(a->var)) {
		ERROR(20);
	}
	if(compType(b, a->var)) {
		return a;
	}
	if(isStruct(a->var) || isStruct(b)) {
		ERROR(19);
	}
	int s1 = isChar(b), s2 = isChar(a->var);
	struct Instruction * inst;
	if(0 && s1 && !s2) {
		if(a->constant) {
			return constChar(a->value);
		}else {
			printf("!!?\n");
			inst = newInstruction(INT_TO_CHAR, newOperand(newVariable(), 2, a->constant, a->value), a, 0);
			occupy(env, inst->a);
			inst->a->var->type = CHAR_TYPE;
			assignInst = inst;
			push(env, inst);
			return inst->a;
		}
	}else {
		if(0 && s2 && !s1) {
			if(a->constant) {
				return constInt(a->value);
			}else {
				inst = newInstruction(CHAR_TO_INT, newOperand(newVariable(), 2, a->constant, a->value), a, 0);
				occupy(env, inst->a);
				copyType(inst->a->var, b);
				assignInst = inst;
				push(env, inst);
				return inst->a;
			}
		}else {
			//printf("!!\n");
			struct Operand * res = newOperand(newVariable(), 2, a->constant, a->value);
			//printf("%d %d\n", a->constant, a->value);
			copyType(res->var, b);
			//occupy(env, res);
			res->var->index = a->var->index;
			totIndex--;
			return res;
		}
	}
}

struct Operand * printCall(struct Function * env, struct Function * f, int n) {
	struct Instruction * inst = newInstruction(CALL, newOperand(newVariable(), 2, 0, 0), 0, 0);
	occupy(env, inst->a);
	copyType(inst->a->var, f->rtn);
	inst->f = f;
	inst->n = n;
	push(env, inst);
	return inst->a;
}

struct Variable * findMem(struct Variable * vars, char * name) ;

struct Operand * printMemberAccess(struct Function * env, struct Operand * a, char * name) {
	if(!isStruct(a->var)) {
		ERROR(22);
	}else {
		if(a->var->type->type == 3) {
			struct Operand * res = newOperand(newVariable(), 2 - (a->type == 1), 0, 0);
			//occupy(env, res);
			copyType(res->var, findMem(a->var->type->vars, name));
			res->var->index = a->var->index;
			totIndex--;
			res->loadable = a->loadable;
			res->offset = a->offset;
			return res;
		}else if(a->var->type->type == 2) {
			struct Variable * p = a->var->type->vars;
			struct List * l = a->var->type->posi;
			while(p) {
				if(!strcmp(p->name, name)) {
					/*if(l->value) {
						struct Instruction * inst = newInstruction(ASSIGN_ADD, newOperand(newVariable(), 2 - (a->type == 1), 0, 0), a, constInt(l->value));
						occupy(env, inst->a);
						copyType(inst->a->var, p);
						push(env, inst);
						inst->a->loadable = a->loadable;
						return inst->a;
					}else {*/
					struct Operand * res = newOperand(newVariable(), 2 - (a->type == 1), 0, 0);
					//occupy(env, res);
					copyType(res->var, p);
					res->var->index = a->var->index;
					totIndex--;
					res->loadable = a->loadable;
					res->offset = a->offset + l->value;
					return res;
					//}
				}
				p = p->next;
				l = l->next;
			}
			ERROR(91);
		}else {
			ERROR(23);
		}
	}
}

struct Operand * printDeref(struct Function * env, struct Operand * a) {
	if(a->var->list == 0 && a->var->level == 0) {
		ERROR(24);
	}
	//struct Instruction * inst = newInstruction(ASSIGN_ADDRESS, newOperand(newVariable(), 1, 0, 0), 0, 0);
	a = getValue(env, a);
	if(a->constant) {
		struct Operand * tmp = newOperand(newVariable(), 2, 0, 0);
		struct Instruction * inst = newInstruction(ASSIGN, tmp, constInt(a->value), 0);
		occupy(env, tmp);
		push(env, inst);
		copyType(tmp->var, a->var);
		a = tmp;
	}
	struct Operand * res = newOperand(newVariable(), 1, 0, 0);
	copyType(res->var, a->var);
	//occupy(env, res);
	res->var->index = a->var->index;
	if(a->var->list) {
		res->var->list = res->var->list->next;
	}else {
		res->var->level--;
	}
	totIndex--;
	res->loadable = a->loadable || a->constant;
	return res;
/*	if(a->var->list) {
		copyType(inst->a->var, a->var);
		inst->a->var->list = a->var->list->next;
		inst->b = a;
	}else {
		inst->b = getValue(env, a);
		*inst->a->var = *a->var;
		inst->a->var->level--;
	}
	push(env, inst);
	return inst->a;*/
}

struct Operand * printAssignOp(struct Function * env, struct Operand * b, struct Operand * c, int op) {
	if(op == 522 || op == 523) {
		if(b->loadable && (b->var->list || b->type != 1)) {
			b = constInt(1);
		}
		if(c->loadable && (c->var->list || c->type != 1)) {
			c = constInt(1);
		}
	}
	if(b->constant && c->constant) {
		int res;
		if(op == 523) {
			res = b->value && c->value;
		}else if(op == 522) {
			res = b->value || c->value;
		}else if(op == 513) {
			res = b->value < c->value;
		}else if(op == 514) {
			res = b->value > c->value;
		}else if(op == 526) {
			res = b->value <= c->value;
		}else if(op == 527) {
			res = b->value >= c->value;
		}else if(op == 524) {
			res = b->value == c->value;
		}else if(op == 525) {
			res = b->value != c->value;
		}else if(op == 532) {
			res = b->value * c->value;
		}else if(op == 533) {
			res = b->value / c->value;
		}else if(op == 534) {
			res = b->value % c->value;
		}else if(op == 535) {
			res = b->value + c->value;
		}else if(op == 536) {
			res = b->value - c->value;
		}else if(op == 537) {
			res = b->value << c->value;
		}else if(op == 538) {
			res = b->value >> c->value;
		}else if(op == 539) {
			res = b->value & c->value;
		}else if(op == 540) {
			res = b->value ^ c->value;
		}else if(op == 541) {
			res = b->value | c->value;
		}
		//printf("const operation %d\n", res);
		return constInt(res);
	}
	if(op == 532 && (b->constant && b->value == 0 || c->constant && c->value == 0)) {
		return constInt(0);
	}
	if(op == 522 && (b->constant && b->value || c->constant && c->value)) {
		return constInt(1);
	}
	if(op == 523 && (b->constant && !b->value || c->constant && !c->value)) {
		return constInt(0);
	}
	//printf("%s %s %d %d %d %d\n", b->var->name, c->var->name, isVoid(b->var), isVoid(c->var), isStruct(b->var), isStruct(c->var));
	if(isVoid(b->var) || isVoid(c->var) || isStruct(b->var) || isStruct(c->var)) {
		ERROR(25);
	}
	struct Instruction * inst;
	int loadable = b->loadable && c->loadable;
	if(op == 535 || op == 536) {
		if(isIntOrChar(b->var) && isIntOrChar(c->var)) {
			b = printCast(env, INT_VARIABLE, b);
			c = printCast(env, INT_VARIABLE, c);
			if(op == 536 && b->var->index == c->var->index) {
				return constInt(0);
			}
			inst = newInstruction(0, newOperand(newVariable(), 2, 0, 0), b, c);
			occupy(env, inst->a);
			if(op == 535) {
				inst->type = ASSIGN_ADD;
			}else {
				inst->type = ASSIGN_SUB;
			}
			/*if(b->constant && c->constant) {
				inst->a->constant = 1;
				if(op == 535) {
					inst->a->value = b->value + c->value;
				}else {
					inst->a->value = b->value - c->value;
				}
			}*/
			push(env, inst);
			assignInst = inst;
			return inst->a;
		}else if(isPointer(b->var) || isPointer(c->var) || b->var->list || c->var->list) {
			//printf("Pointer operation\n");
			if(compType(b->var, c->var) && op == 536) {
//				printf("!!\n");
				if(b->var->index == c->var->index) {
//				printf("!!\n");
					struct Operand * ope = newOperand(newVariable(), 2, 0, 0);
					//copyType(ope->var, b->var);
					ope->var->index = -1;
					totIndex--;
					ope->constant = 1;
					ope->value = 0;
					return ope;
				}
				inst = newInstruction(ASSIGN_SUB, newOperand(newVariable(), 2, 0, 0), b, c);//ָ\D5\EB\CF\E0\BC\F5
				occupy(env, inst->a);
				push(env, inst);
				struct List * bak = b->var->list;
				if(bak) {
					b->var->list = bak->next;	
				}else {
					b->var->level--;
				}
				struct Operand * ope = constInt(calcSize(b->var));
				if(bak) {
					b->var->list = bak;
				}else {
					b->var->level++;
				}
				if(ope->value != 1) {
					return printAssignOp(env, inst->a, ope, 533);
				}else {
					assignInst = inst;
					return inst->a;
				}
			}else {
				inst = newInstruction(0, 0, 0, 0);
				if(op == 535) {
					inst->type = ASSIGN_ADD;
				}else {
					inst->type = ASSIGN_SUB;
				}
				if(isPointer(c->var) || c->var->list) {
					if(op == 536) {
						ERROR(26);
					}
					struct Operand * tmp = b;
					b = c;
					c = tmp;
				}
				if(isPointer(c->var) || c->var->list) {
					ERROR(27);
				}
				inst->a = newOperand(newVariable(), 2, 0, 0);
				occupy(env, inst->a);
				copyType(inst->a->var, b->var);
				inst->b = b;
				struct List * bak = b->var->list;
				if(bak) {
					b->var->list = bak->next;	
				}else {
					b->var->level--;
				}
				//printf("%s %d\n", b->var->name, b->var->level);
				inst->c = printAssignOp(env, constInt(calcSize(b->var)), printCast(env, INT_VARIABLE, c), 532);
				//printf("%s %d\n", b->var->name, b->var->level);
				if(bak) {
					b->var->list = bak;
				}else {
					b->var->level++;
				}
				//printf("%s %d\n", b->var->name, b->var->level);
				push(env, inst);
				assignInst = inst;
				inst->a->loadable = b->loadable && c->constant;
				return inst->a;
			}
		}else {
			ERROR(28);
		}
	}else {
		b = printCast(env, INT_VARIABLE, b);
		c = printCast(env, INT_VARIABLE, c);
		inst = newInstruction(0, newOperand(newVariable(), 2, 0, 0), b, c); 
		occupy(env, inst->a);
		if((isPointer(b->var) || isPointer(c->var)) && op != 524 && op != 525 && op != 523 && op != 522 && op != 513 && op != 514 && op != 526 && op != 527) {//ָ\D5\EB\BF\C9\D2Խ\F8\D0е\C4\CB\E3\CA\F5\B2\D9\D7\F7, \B3\FD\C1˸ղŵ\C4ָ\D5\EB\BCӼ\F5\D5\FB\CA\FD, \D5\FB\CA\FD\BC\D3ָ\D5\EB, ָ\D5\EB\BC\F5ָ\D5\EB, \BB\B9\D3\D0<=, >=, <, >, ==, !=, &&, ||
			ERROR(29);
		}
		if(op == 523) {
			inst->type = ASSIGN_LOGIC_AND;
		}else if(op == 522) {
			inst->type = ASSIGN_LOGIC_OR;
		}else if(op == 513) {
			inst->type = ASSIGN_LESS_THAN;
		}else if(op == 514) {
			inst->type = ASSIGN_GREATER_THAN;
		}else if(op == 526) {
			inst->type = ASSIGN_LESS_THAN_OR_EQUAL_TO;
		}else if(op == 527) {
			inst->type = ASSIGN_GREATER_THAN_OR_EQUAL_TO;
		}else if(op == 524) {
			inst->type = ASSIGN_EQUAL_TO;
		}else if(op == 525) {
			inst->type = ASSIGN_NOT_EQUAL_TO;
		}else if(op == 532) {
			inst->type = ASSIGN_MUL;
		}else if(op == 533) {
			inst->type = ASSIGN_DIV;
		}else if(op == 534) {
			inst->type = ASSIGN_MOD;
		}else if(op == 535) {
			inst->type = ASSIGN_ADD;
		}else if(op == 536) {
			inst->type = ASSIGN_SUB;
		}else if(op == 537) {
			inst->type = ASSIGN_SHL;
		}else if(op == 538) {
			inst->type = ASSIGN_SHR;
		}else if(op == 539) {
			inst->type = ASSIGN_AND;
		}else if(op == 540) {
			inst->type = ASSIGN_EXCLUSIVE_OR;
		}else if(op == 541) {
			inst->type = ASSIGN_INCLUSIVE_OR;
		}
		push(env, inst);
		assignInst = inst;
		inst->a->loadable = loadable;
		return inst->a;
	}
}

struct Operand * printAddressOf(struct Function * env, struct Operand * a) {
	if(a->var->list) {// || isVoid(a->var)) {
		ERROR(30);//\D1˸\EE\B0\E6,\B2\BB\D4\CA\D0\ED\B6\D4\CA\FD\D7\E9ȡ\B5\D8ַ, \B1\A3֤\B4\A6\C0\ED\B5ı\E4\C1\BFȫ\B6\BC\CAǻ\F9\B1\BE\C0\E0\D0͵\C4ָ\D5\EB\B5\C4\CA\FD\D7\E9.
	}
	if(a->type == 0) {
		struct Instruction * inst = newInstruction(0, newOperand(newVariable(), 2, 0, 0), a, 0);
		occupy(env, inst->a);
		inst->type = ASSIGN_ADDRESS_OF;
		copyType(inst->a->var, a->var);
		inst->a->var->level++;
		push(env, inst);
		assignInst = inst;
		if(a->var->name[0]) {
			inst->a->loadable = 1;
		}
		return inst->a;
	}else if(a->type == 1) {
		struct Operand * res = newOperand(newVariable(), 2, 0, 0);
		copyType(res->var, a->var);
		//occupy(env, res);
		res->var->level++;
		res->var->index = a->var->index;
		totIndex--;
		res->loadable = a->loadable;
		if(a->offset) {
			struct Instruction * inst = newInstruction(ASSIGN_ADD, newOperand(newVariable(), 2, 0, 0), res, constInt(a->offset));
			copyType(inst->a->var, a->var);
			occupy(env, inst->a);
			inst->a->loadable = a->loadable;
			push(env, inst);
			return inst->a;
		}else {
			return res;
		}
	}else {
		ERROR(31);
	}
}

void printNNP(struct Function * env, struct Operand * a) {
	if(!isIntOrChar(a->var)) {
		ERROR(32);
	}
	struct Instruction * inst = newInstruction(0, newOperand(newVariable(), 2, 0, 0), printCast(env, INT_VARIABLE, a), 0);
	occupy(env, inst->a);
	assignInst = inst;
	push(env, inst);
}

struct Operand * printPosite(struct Function * env, struct Operand * a) {
	if(a->constant) {
		return constInt(a->value);
	}
	printNNP(env, a);
/*	if(env->insts->b->constant) {
		env->insts->a->constant = 1;
		env->insts->a->value = env->insts->b->value;
	}*/
	env->insts->type = ASSIGN;
	return env->insts->a;
}

struct Operand * printNegate(struct Function * env, struct Operand * a) {
	if(a->constant) {
		return constInt(-a->value);
	}
	printNNP(env, a);
/*	if(env->insts->b->constant) {
		env->insts->a->constant = 1;
		env->insts->a->value = -env->insts->b->value;
	}*/
	env->insts->type = ASSIGN_NEGATE;
	return env->insts->a;
}

struct Operand * printNot(struct Function * env, struct Operand * a) {
	if(a->constant) {
		return constInt(~a->value);
	}
	printNNP(env, a);
/*	if(env->insts->b->constant) {
		env->insts->a->constant = 1;
		env->insts->a->value = ~env->insts->b->value;
	}*/
	env->insts->type = ASSIGN_NOT;
	return env->insts->a;
}

struct Operand * printLogicalNot(struct Function * env, struct Operand * a) {
	if(a->constant) {
		return constInt(!a->value);
	}
	if(a->loadable && (a->var->list || a->type != 1)) {
		return constInt(1);
	}
	struct Instruction * inst = newInstruction(ASSIGN_LOGICAL_NOT, newOperand(newVariable(), 2, 0, 0), printCast(env, INT_VARIABLE, a), 0);
	occupy(env, inst->a);
	//if(inst->b->constant) {
	//	inst->a->constant = 1;
	//	inst->a->value = !inst->b->value;
	//}
	push(env, inst);
	assignInst = inst;
	inst->a->loadable = a->loadable;
	return inst->a;
}

void printGoto(struct Function * env, int label);

void printIfFalseGoto(struct Function * env, struct Operand * a, int label) {
	a = getValue(env, a);
	if(a->constant) {
		if(a->value) {
			return;
		}else {
			printGoto(env, label);
		}
	}else {	
		struct Instruction * inst = newInstruction(IF_FALSE_GOTO, printCast(env, INT_VARIABLE, a), 0, 0);
		inst->n = label;
		push(env, inst);
	}
}

void printIfGoto(struct Function * env, struct Operand * a, int label) {
	a = getValue(env, a);
	if(a->constant) {
		if(!a->value) {
			return;
		}else {
			printGoto(env, label);
		}
	}else {	
		struct Instruction * inst = newInstruction(IF_GOTO, printCast(env, INT_VARIABLE, a), 0, 0);
		inst->n = label;
		push(env, inst);
	}
}

void printLabel(struct Function * env, int label) {
	struct Instruction * inst = newInstruction(LABEL, 0, 0, 0);
	inst->n = label;
	push(env, inst);
}

void printGoto(struct Function * env, int label) {
	struct Instruction * inst = newInstruction(GOTO, 0, 0, 0);
	inst->n = label;
	push(env, inst);
}

char _c___memset__[20] = "__memset__";

struct Function * findFunc(char * name);

/*void printFillZero(struct Function * env, struct Operand * a) {
	if(a->type == 0) {
		struct Instruction * inst = newInstruction(0, a, 0, 0);
		if(isChar(a->var)) {
			inst->type = ASSIGN_CHAR;
			inst->b = constChar(0);
		}else{
			inst->type = ASSIGN;
			inst->b = constInt(0);
		}
		push(env, inst);
	}else {
		printArgu(env, a);
		printArgu(env, constInt(calcSize(a->var)));
		struct Instruction * inst = newInstruction(CALL, newOperand(newVariable(), 0, 0, 0), 0, 0);
		inst->a->var->type = VOID_TYPE;
		inst->n = 2;
		inst->f = findFunc(_c___memset__);
		push(env, inst);
		struct Instruction * inst = 
		int i = 0, s = calcSize(a->var);
		for( ; i < s; ) {
			struct Operand * ope = newOperand(newVariable(), 1, 0, 0);
			ope->var->index = a->var->index;
			totIndex--;
			ope->offset = a->offset + i;
			if(i + 4 <= s) {
				printAssign(env, ope, constInt(0));
				i += 4;
			} else {
				ope->var->type = CHAR_TYPE;
				printAssign(env, ope, constChar(0));
				i += 1;
			}
		}
	}
}*/

void printNOP(struct Function * env) {
	struct Instruction * inst = newInstruction(NOP, 0, 0, 0);
	push(env, inst);
}

struct Operand * printPutchar(struct Function * env, struct Operand * a) {//\CE\F1\B1ط\B5\BB\D8void
	if(isVoid(a->var) || isStruct(a->var)) {
		ERROR(33);
	}
	struct Instruction * inst = newInstruction(PUTCHAR, getValue(env, a), 0, 0);
	push(env, inst);
	return directLvalue(VOID_VARIABLE);
}

struct Operand * printPutint(struct Function * env, struct Operand * a) {//\CE\F1\B1ط\B5\BB\D8void
	if(isVoid(a->var) || isStruct(a->var)) {
		ERROR(33);
	}
	struct Instruction * inst = newInstruction(PUTINT, getValue(env, a), 0, 0);
	push(env, inst);
	return directLvalue(VOID_VARIABLE);
}

struct Operand * printGetchar(struct Function * env) {
	struct Instruction * inst = newInstruction(GETCHAR, newOperand(newVariable(), 2, 0, 0), 0, 0);
	occupy(env, inst->a);
	assignInst = inst;
	push(env, inst);
	return inst->a;
}

struct Operand * printMalloc(struct Function * env, struct Operand * a) {
	if(isVoid(a->var) || isStruct(a->var)) {
		ERROR(34);
	}
	struct Instruction * inst = newInstruction(MALLOC, newOperand(newVariable(), 2, 0, 0), getValue(env, a), 0);
	occupy(env, inst->a);
	inst->a->var->type = VOID_TYPE;
	inst->a->var->level = 1;
	push(env, inst);
	return inst->a;
}

void printDeclInt(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction(DECL_INT, a, 0, 0);
	push(env, inst);
}

void printDeclChar(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction(DECL_CHAR, a, 0, 0);
	push(env, inst);
}

void printDeclPointer(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction(DECL_POINTER, a, 0, 0);
	push(env, inst);
}

void printGetArgu(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction(GET_ARGU, a, 0, 0);
	push(env, inst);
}

void printReturn(struct Function * env, struct Operand * a) {
	if(isVoid(a->var)) {
		ERROR(35);
	}
	struct Instruction * inst = newInstruction(RETURN, getValue(env, a), 0, 0);
	push(env, inst);
}

void printVoidReturn(struct Function * env) {
	struct Instruction * inst = newInstruction(VOID_RETURN, 0, 0, 0);
	push(env, inst);
}

struct Operand * printExit(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction(EXIT, printCast(env, INT_VARIABLE, a), 0, 0);
	push(env, inst);
	return directLvalue(VOID_VARIABLE);
}

struct StringList {
	char * name;
	struct StringList * next;
} * strings = 0;
int nString = 0;
struct StringList * newStringList() {
	struct StringList * res = (struct StringList *)malloc(sizeof(struct StringList));
	res->name = 0;
	res->next = 0;
	return res;
}

struct Operand * parsePrimaryExpression(struct Function * env) {
	//printf("primary %d\n", env);
	//printf("%d %s\n", look.type, look.name, program[0], program[1], program[2], program[3]);
	if(look.type == IDENTIFIER) {
		char * bak = look.name;
		//printf("%s\n", look.name);
		move();
		struct Variable * v = findVariable(bak);
		//printf("%d\n", v);
		//printf("%d\n", v->type);
		
		if(v) {
		//	printf("%d\n", v);
			//printf("IDENTIFIER %s %d\n", v->name, v->level);
			return directLvalue(v);
		}else {
			v = newVariable();
			v->name = bak;
			v->type = FUNC_TYPE;
			return directLvalue(v);
		}
	}else if(look.type == INT_CONSTANT) {
		int bak = look.value;
		move();
		return constInt(bak);
	}else if(look.type == CHR_CONSTANT) {
		int bak = look.value;
		move();
		return constChar(bak);
	}else if(look.type == STR_CONSTANT) {
		struct Instruction * inst = newInstruction(ASSIGN_STR, newOperand(newVariable(), 2, 0, 0), 0, 0);
		assignInst = inst;
		inst->a->var->type = CHAR_TYPE;
		inst->a->var->level = 1;
		//printf("%s ssss %d\n", env->name, inst->a->var->index);
		occupy(env, inst->a);
		//printf("%d\n", env->occupy->value);
		inst->n = nString++;
		push(env, inst);
		struct StringList * sl = newStringList();
		sl->name = look.name;
		sl->next = strings;
		strings = sl;
		//struct List * tmp = env->occupy;
	//	while(tmp) {
		//	printf("%s %d\n", env->name, tmp->value);
	//		tmp = tmp->next;
	//	}
		/*
		int len = 0;
		while(look.name[len]) {
			len++;
		}
		printMalloc(env, constInt(len + 1));
		struct Operand * res = newOperand(newVariable(), 1, 0, 0);
		res->var->type = CHAR_TYPE;
		res->var->list = newList();
		struct Instruction * inst = env->insts;
		inst->a = res;
		occupy(env, inst->a);
		int i = 0;
		for( ; look.name[i]; i++) {
			printAssign(env, printAccess(env, inst->a, constInt(i)), constChar(look.name[i]));
		}
		printAssign(env, printAccess(env, inst->a, constInt(len)), constChar(0));
		res->var->list->value = i + 1;
		res->var->list->prev = res->var->list;*/
		move();
		return inst->a;
	}else if(look.type == 500) {//'('
		move();
		struct Operand * res = parseExpression(env);
		match(501);//')'
		return res;
	}else {
		ERROR(36);
	}
}

char _c_putchar__[8] = "putchar";

char _c_putint__[8] = "putint";

char _c_malloc__[8] = "malloc";

char _c_getchar__[8] = "getchar";

char _c_printf__[8] = "printf";

char _c___printf____[12] = "__printf__";

char _c_exit__[8] = "exit";

struct Function * findFunc(char * name);

struct Operand * parseActualArgument(struct Function * env, struct Operand * p) {
	struct Operand * res;
		//printf("!!%s\n", p->var->name);
	
	if(!strcmp(p->var->name, _c_putchar__)) {
		res = printPutchar(env, parseAssignmentExpression(env));
		if(look.type != 501) {
			ERROR(37);
		}
		return res;
	}else if(!strcmp(p->var->name, _c_putint__)) {
		res = printPutint(env, parseAssignmentExpression(env));
		if(look.type != 501) {
			ERROR(86);
		}
		return res;
	}else if(!strcmp(p->var->name, _c_malloc__)) {
		res = printMalloc(env, parseAssignmentExpression(env));
		occupy(env, res);
		if(look.type != 501) {
			ERROR(38);
		}
		return res;
	}else if(!strcmp(p->var->name, _c_getchar__)) {
		res = printGetchar(env);
		if(look.type != 501) {
			ERROR(39);
		}
		return res;
	}else if(!strcmp(p->var->name, _c_exit__)) {
		res = printExit(env, parseAssignmentExpression(env));
		if(look.type != 501) {
			ERROR(40);
		}
		return res;
	}else if(!strcmp(p->var->name, _c_printf__)) {
		struct Variable * v = newVariable();
		v->type = CHAR_TYPE;
		v->level = 1;
		printArgu(env, printCast(env, v, parseAssignmentExpression(env)));
		struct Operand * ope = newOperand(newVariable(), 0, 0, 0);
		occupy(env, ope);
		ope->var->level = 1;//\CAֶ\AFint*
		int cnt = 0;
		printMalloc(env, constInt(cnt * POINTER_SIZE));
		struct Instruction * inst = env->insts;
		inst->a = ope;
		while(look.type != 501) {//')'
			match(503);//','
			struct Operand * res;
			res = parseAssignmentExpression(env);
			if(isStruct(res->var)) {
				res = constInt(0);
			}else {
				res = printCast(env, INT_VARIABLE, res);
			}
			printAssign(env, printAccess(env, ope, constInt(cnt)), res	);
			cnt++;
		}
		inst->b->value = cnt * POINTER_SIZE;
		printArgu(env, ope);
		return printCall(env, findFunc(_c___printf____), 2);
	}else {
		struct Function * f = findFunc(p->var->name);
		if(!f) {
			printf("function %s unfound\n", p->var->name);
			ERROR(41);
		}
		struct Variable * v = f->argu;
		int n = 0;
		if(v == 0) {
			while(look.type != 501) {//')'
				parseAssignmentExpression(env);
				if(look.type != 501) {
					match(503);//','
				}
			}
		}else {
			while(v) {
				n++;
				printArgu(env, printCast(env, v, parseAssignmentExpression(env)));
				v = v->next;
				if(v) {
					match(503);//','
				}
			}
		}
		return printCall(env, f, n);
	}
}

struct Variable * parseTypeName() {
	struct Variable * v = newVariable();
	if(look.type == 301) {//void
		v->type = VOID_TYPE;
		move();
	}else if(look.type == 302) {//char
		move();
		v->type = CHAR_TYPE;
	}else if(look.type == 303) {//int
		move();
		v->type = INT_TYPE;
	}else if(look.type == 304 || look.type == 305) {//struct union
		move();
		if(look.type != IDENTIFIER) {
			ERROR(42);
		}
		v->type = find(look.name);
		if(v->type == 0) {
			ERROR(43);
		}
		move();
	}
	while(look.type == 509) {//'*'
		v->level++;
		move();
	}
	return v;
}

struct Operand * parsePostfix(struct Function * env, struct Operand * p) {
	struct Operand * res;
	//printf("post %d\n", env);
	if(p->var->type == FUNC_TYPE && look.type != 500) {
		ERROR(44);
	}
	if(look.type == 507) {//'['
		move();
		//printf("parsePostfixAccess %s %d %d\n", p->var->name, p->type, p->var->level);
		res = printAccess(env, p, parseExpression(env));
		match(508);//']'
		return parsePostfix(env, res);
	}else if(look.type == 500) {//'('
		move();
		if(p->var->type != FUNC_TYPE) {
			ERROR(97);
		}
		res = parseActualArgument(env, p);
		match(501);
		return parsePostfix(env, res);
	}else if(look.type == 521) {//'.'
		move();
		if(look.type != IDENTIFIER) {
			ERROR(45);
		}
		res = printMemberAccess(env, p, look.name);
		move();
		return parsePostfix(env, res);
	}else if(look.type == 542) {//'->'
		move();
		res = printDeref(env, p);
		if(look.type != IDENTIFIER) {
			ERROR(46);
		}
		res = printMemberAccess(env, res, look.name);
		move();
		res = parsePostfix(env, res);
		return res;
	}else if(look.type == 530) {//'++'
		move();
		//printf("parsePostfix++ %d\n", env);
		res = printCopy(env, p);
		//printf("parsePostfix++\n");
		struct Operand * tmp = printAssignOp(env, p, constInt(1), 535);
		printAssign(env, p, tmp);
		return parsePostfix(env, res);
	}else if(look.type == 531) {//'--'
		move();
		res = printCopy(env, p);
		struct Operand * tmp = printAssignOp(env, p, constInt(1), 536);
		printAssign(env, p, tmp);
		return parsePostfix(env, res);
	}else {
		//printf("return %d\n", env);
		return p;
	}
}

struct Operand * parsePostfixExpression(struct Function * env) {
	struct Operand * res = parsePrimaryExpression(env);
	//printf("pp %d\n", env);
	return parsePostfix(env, res);
}

struct Operand * parseCastExpression(struct Function * env);

struct Operand * parseUnaryExpression(struct Function * env) {
	if(look.type == 530) {//'++'
		move();
		struct Operand * tmp = parseUnaryExpression(env), *tmp1;
		if(tmp->type != 0 && tmp->type != 1) {//DIRECT LEFT VALUE OR DEREF LEFT VALUE
			ERROR(47);
		}
		tmp1 = printAssignOp(env, tmp, constInt(1), 535);
		printAssign(env, tmp, tmp1);
		return tmp;
	}else if(look.type == 531) {//'--'
		move();
		struct Operand * tmp = parseUnaryExpression(env), * tmp1;
		if(tmp->type != 0 && tmp->type != 1) {
			ERROR(48);
		}
		tmp1 = printAssignOp(env, tmp, constInt(1), 536);
		printAssign(env, tmp, tmp1);
		return tmp;
	}else if(look.type == 512) {//'&'
		move();
		struct Operand * tmp = parseCastExpression(env);
		return printAddressOf(env, tmp);
	}else if(look.type == 509) {//'*'
		move();
		//printf("U %d\n", env);
		struct Operand * tmp = parseCastExpression(env);
	//	printf("U %d\n", env);
		return printDeref(env, tmp);//\B1\F0\CD\FC\C1\CB\C0\EF\C3\E6\B5\C4\C0\E0\D0ͼ\EC\B2\E9
	}else if(look.type == 515) {//'+'
		move();
		struct Operand * tmp = parseCastExpression(env);
		return printPosite(env, tmp);
	}else if(look.type == 516) {//'-'
		move();
		struct Operand * tmp = parseCastExpression(env);
		return printNegate(env, tmp);
	}else if(look.type == 519) {//'~'
		move();
		struct Operand * tmp = parseCastExpression(env);
		return printNot(env, tmp);
	}else if(look.type == 520) {//'!'
		move();
		struct Operand * tmp = parseCastExpression(env);
		return printLogicalNot(env, tmp);
	}else if(look.type == 313) {//sizeof
		move();
		if(look.type == 500) {//'('
			move();
			if(look.type >= 301 && look.type <= 305) {//void int char union struct
				struct Variable * v = parseTypeName();
				match(501);//')'
				if(v->level) {
					return constInt(POINTER_SIZE);
				}else {
					if(v->type->size == -1) {
						ERROR(49);
					}
					return constInt(v->type->size);
				}
			}else {
				struct Operand * tmp = parseExpression(env);
				match(501);
				tmp = parsePostfix(env, tmp);
				return constInt(calcSize(tmp->var));
			}
		}else {
			struct Operand * tmp = parseUnaryExpression(env);
			return constInt(calcSize(tmp->var));
		}
	}else {
		return parsePostfixExpression(env);
	}
}

struct Operand * parseCastExpression(struct Function * env) {
	if(look.type == 500) {//'('
		move();
		if(look.type == 303 || look.type == 304 || look.type == 305 || look.type == 302 || look.type == 301) {
			struct Variable * v = parseTypeName();
			match(501);//')'
			return printCast(env, v, parseCastExpression(env));
		}else {
			struct Operand * res = parseExpression(env);
			match(501);
			return parsePostfix(env, res);
		}
	}else {
		return parseUnaryExpression(env);
	}
}

struct Operand * parseMultiplicativeExpression(struct Function * env) {
	struct Operand * res = parseCastExpression(env);
	for(;;) {
		if(look.type == 509) {//'*'
			move();
			res = printAssignOp(env, res, parseCastExpression(env), 532);
		}else if(look.type == 517) {//'/'
			move();
			res = printAssignOp(env, res, parseCastExpression(env), 533);
		}else if(look.type == 518) {//'%'
			move();
			res = printAssignOp(env, res, parseCastExpression(env), 534);
		}else {
			return res;
		}
	}
}

struct Operand * parseAdditiveExpression(struct Function * env) {
	struct Operand * res = parseMultiplicativeExpression(env);
	for(;;) {
		if(look.type == 515) {//'+'
			move();
			res = printAssignOp(env, res, parseMultiplicativeExpression(env), 535);
		}else if(look.type == 516) {//'-'
			move();
			res = printAssignOp(env, res, parseMultiplicativeExpression(env), 536);
		}else {
			return res;
		}
	}
}

struct Operand * parseShiftExpression(struct Function * env) {
	struct Operand * res = parseAdditiveExpression(env);
	for(;;) {
		if(look.type == 528) {//'<<'
			move();
			res = printAssignOp(env, res, parseAdditiveExpression(env), 537);
		}else if(look.type == 529) {//'>>'
			move();
			res = printAssignOp(env, res, parseAdditiveExpression(env), 538);
		}else {
			return res;
		}
	}
}

struct Operand * parseRelationalExpression(struct Function * env) {
	struct Operand * res = parseShiftExpression(env);
	for(;;) {
		if(look.type == 513) {//'<'
			move();
			res = printAssignOp(env, res, parseShiftExpression(env), 513);
		}else if(look.type == 514) {//'>'
			move();
			res = printAssignOp(env, res, parseShiftExpression(env), 514);
		}else if(look.type == 526) {//'<='
			move();
			res = printAssignOp(env, res, parseShiftExpression(env), 526);
		}else if(look.type == 527) {//'>='
			move();
			res = printAssignOp(env, res, parseShiftExpression(env), 527);
		}else {
			return res;
		}
	}
}

struct Operand * parseEqualityExpression(struct Function * env) {
	struct Operand * res = parseRelationalExpression(env);
	for(;;) {
		if(look.type == 524) {//'=='
			move();
			res = printAssignOp(env, res, parseRelationalExpression(env), 524);
		}else if(look.type == 525) {//'!='
			move();
			res = printAssignOp(env, res, parseRelationalExpression(env), 525);
		}else {
			return res;
		}
	}
}

struct Operand * parseAndExpression(struct Function * env) {
	struct Operand * res = parseEqualityExpression(env);
	for(;;) {
		if(look.type == 512) {//'&'
			move();
			res = printAssignOp(env, res, parseEqualityExpression(env), 539);
		}else {
			return res;
		}
	}
}

struct Operand * parseExclusiveOrExpression(struct Function * env) {
	struct Operand * res = parseAndExpression(env);
	for(;;) {
		if(look.type == 511) {//'^'
			move();
			res = printAssignOp(env, res, parseAndExpression(env), 540);
		}else {
			return res;
		}
	}
}

struct Operand * parseInclusiveOrExpression(struct Function * env) {
	struct Operand * res = parseExclusiveOrExpression(env);
	for(;;) {
		if(look.type == 510) {//'|'
			move();
			res = printAssignOp(env, res, parseExclusiveOrExpression(env), 541);
		}else {
			return res;
		}
	}
}

struct Operand * parseLogicalAndExpression(struct Function * env) {
	struct Operand * res = parseInclusiveOrExpression(env);
	int x = -1;
	if(look.type == 523) {
		x = newLabel();
	}else {
		return res;
	}
	for(;;) {
		if(look.type == 523) {//'&&'
			move();
			printIfFalseGoto(env, res, x);
			struct Operand * ope = parseInclusiveOrExpression(env);
			res = printAssignOp(env, res, ope, 523);
		}else {
			break;
		}
	}
	if(res->constant) {
		printLabel(env, x);
		return res;
	}
	struct Operand * rtn = newOperand(newVariable(), 0, 0, 0);
	printAssign(env, rtn, res);
	int y = newLabel();
	printGoto(env, y);
	printLabel(env, x);
	printAssign(env, rtn, constInt(0));
	printLabel(env, y);
	rtn->type = 2;
	rtn->constant = res->constant;
	rtn->value = res->value;
	return rtn;
}


struct Operand * parseLogicalOrExpression(struct Function * env) {
	struct Operand * res = parseLogicalAndExpression(env);
	int x = -1;
	if(look.type == 522) {
		x = newLabel();
	}else {
		//printf("LO %d\n", env);
		return res;
	}
	for(;;) {
		if(look.type == 522) {//'||'
			move();
			printIfGoto(env, res, x);
			struct Operand * ope = parseLogicalAndExpression(env);
			res = printAssignOp(env, res, ope, 522);
		}else {
			break;
		}
	}
	if(res->constant) {
		printLabel(env, x);	
		return res;
	}
	struct Operand * rtn = newOperand(newVariable(), 0, 0, 0);
	printAssign(env, rtn, res);
	int y = newLabel();
	printGoto(env, y);
	printLabel(env, x);
	printAssign(env, rtn, constInt(1));
	printLabel(env, y);
	rtn->type = 2;
	rtn->constant = res->constant;
	rtn->value = res->value;
	return rtn;
}

struct Operand * parseConstantExpression(struct Function * env) {
	struct Operand * res = parseLogicalOrExpression(env);
	if(!res->constant) {
		ERROR(82);
	}
	return res;
}

struct Operand * parseAssignmentExpression(struct Function * env) {
	struct Operand * res = parseLogicalOrExpression(env);
	if(isAssignmentOperator(look.type)) {
		int assignType = look.type;
		move();
		if(res->type != 0 && res->type != 1 || res->var->list) {//DIRECT LVALUE or DEREF LVALUE.
			ERROR(50);
		}//TO BE CONTINUED
		if(assignType == 504) {
			struct Operand * tmp = parseAssignmentExpression(env);
			//printf("%d %d %d %d %d\n", assignInst, tmp, assignInst->a, isChar(tmp->var), isChar(res->var));
			if(assignInst && tmp == assignInst->a && tmp->type == 2 && isChar(tmp->var) == isChar(res->var) && res->type == 0) {
				assignInst->a = res;
			}else {
				printAssign(env, res, tmp);
			}
		}else {
			struct Operand * tmp = printAssignOp(env, res, parseAssignmentExpression(env), assignType);
			if(assignInst && tmp == assignInst->a && tmp->type == 2 && isChar(tmp->var) == isChar(res->var) && res->type == 0) {
				assignInst->a = res;//\D3Ż\AF: \B1\ED\B4\EFʽƴ\BD\D3 such as a = b + c => t1 = b + c, a = t1 => a = b + c
			}else {
				printAssign(env, res, tmp);
			}
		}
		return res;
	}else {
		//printf("AE %d\n", env);
		
		return res;
	}
}

struct Operand * parseExpression(struct Function * env) {
	struct Operand * res;
	for(;;) {
		res = parseAssignmentExpression(env);
		if(look.type == 503) {//','
			move();
			continue;
		}else {
			//printf("E %d\n", env);
		
			break;
		}
	}
	return res;
}


struct List * parseArray() {//\B7\D6\CE\F6\CA\FD\D7\E9
	struct List * v = 0;
	while(look.type == 507) {//'['
		move();
		struct Operand * ope = parseConstantExpression(bucket);//\B7\D6\CE\F6\B3\A3\C1\BF\B1\ED\B4\EFʽ
		if(ope->constant == 0 || ope->constant && ope->value < 0 || !isIntOrChar(ope->var)) {
			ERROR(51);
		}
		struct List * a = newList();
		a->value = ope->value;
		a->next = 0;
		if(v == 0) {
			v = a;
			a->prev = a;
		}else {
			a->prev = v->prev;
			v->prev = a;
			a->prev->next = a;
		}
		match(508);
	}
	struct List * a = v->prev;
	while(1) {
		if(a->next == 0) {
			a->mul = a->value;
		}else {
			a->mul = a->next->mul * a->value;
		}
		if(a == v) {
			break;
		}
		a = a->prev;
	}
	return v;
}

struct Variable * parsePlainDeclarator(int enableAnony) {//\B7\D6\CE\F6ָ\D5\EB\BD\D7\CA\FD\BAͱ\E4\C1\BF\C3\FB!
	struct Variable * v = newVariable();
	//printf("%d\n", look.type);
	while(look.type == 509) {//'*'
		v->level++;
		//printf("*\n");
		move();
	}
	if(look.type == IDENTIFIER) {
		v->name = look.name;
		move();
	}else {
		if(!enableAnony) {
			ERROR(52);
		}else {
			v->name = newEmptyString();
		}
	}
	//printf("%s\n", v->name);
	return v;
}

struct Type * find(char * name) {//\B2\E9\D5\D2union\BB\F2\D5\DFstruct\C3\FB\D7\D6, û\D3е\BD\C9ϲ\E3\B7\FB\BAű\ED\D6\D0\D5\D2.
	struct SymbolList * p = top;
	for(; p;) {
		struct Type * itr = p->QaQ;
		while(itr) {
			if(!strcmp(itr->name, name)) {
				return itr;
			}
			itr = itr->next;
		}
		p = p->prev;
	}
	return 0;
}

struct Type * findTop(char * name) {
	//printf("findTop %d %d\n", top, top->QaQ);
	struct Type * itr = top->QaQ;
	while(itr) {
		//printf("%s %s\n", itr->name, name);
		if(!strcmp(itr->name, name)) {
			return itr;
		}
		//printf("%s %s\n", itr->name, name);
		itr = itr->next;
	}
	return 0;
}

struct Variable * findMem(struct Variable * vars, char * name) {//\D5ҳ\C9Ա\B1\E4\C1\BF
	struct Variable * p = vars;
	while(p) {
		if(!strcmp(p->name, name)) {
			return p;
		}
		p = p->next;
	}
	return 0;
}

struct Type * parseTypeSpecifier() {//\B7\D6\CE\F6\C0\E0\D0\CD
	if(look.type == 304 || look.type == 305) {//'struct' 'union'\C0\E0\D0\CD
		int s_or_u = look.type;
		move();
		struct Token structName = look;
		if(structName.type != IDENTIFIER) {
			if(structName.type != 505) {
				ERROR(53);
			}else {
				structName.name = newEmptyString();
			}
		}else {
			move();
		}
		//printf("Typename %s\n", structName.name);
		if(look.type == 505) {//'{'˵\C3\F7Ҫ\CFȶ\A8\D2\E5
			struct Type * a;
			a = findTop(structName.name);
			if(structName.name[0] == 0 || a == 0) {
				a = (struct Type *)malloc(sizeof(struct Type));
				a->next = top->QaQ;
				top->QaQ = a;
			}else {
				if(a->size != -1 || a->type != s_or_u - 302) {
					ERROR(54);
				}
			}
			a->size = 0;
			a->vars = 0;
			a->type = s_or_u - 302;
			a->name = structName.name;
			move();
//			struct SymbolList * newTop = newSymbolList(top);
//			top = newTop;
			for(; look.type != 506;) {//'}'
				struct Type * t = parseTypeSpecifier();//\B7\D6\CE\F6\B3\C9Ա\B5\C4\C0\E0\D0\CD
				int flag = 0;
				for( ; look.type != 502; ) {//';'
					if(look.type == 506) {//'}', struct A {int x};\D5\E2\D1\F9\BF\C9\D2Ե\C4.
						break;
					}
					flag = 1;
					struct Variable * v = parsePlainDeclarator(0);//\B3\C9Ա\B5\C4\C3\FB\D7ֺ\CD\CA\FD\D7\E9\BD\D7\CA\FD
					if(findMem(a->vars, v->name)) {//\B3\C9Ա\B2\BB\C4\DC\D6\D8\C3\FB
						ERROR(55);
					}
					if(look.type == 507) {//'['˵\C3\F7\CA\C7\CA\FD\D7\E9\B3\C9Ա
						v->list = parseArray();
					}
					v->type = t;
					if(v->level == 0 && v->type->size == -1) {
						ERROR(56);//δ\CD\EA\B3\C9\C0\E0\D0\CD
					}
					v->next = a->vars;
					a->vars = v;
					struct List * l = newList();
					l->value = a->size;
					l->next = a->posi;
					a->posi = l;
					int s = calcSize(v);
					if(s % 4) {
						s += 4 - s % 4;
					}
					if(s_or_u == 304) {//struct, Ҫȫ\B2\BF\B7\D6\C5\E4\C4ڴ\E6
						a->size += s;
					}else {//union, ֻ\D0\E8Ҫ\D7\EE\B4\F3\B5\C4\C4ڴ\E6
						a->size = max(a->size, s);
					}
					if(look.type == 503) {//','
						move();
					}
				}
//				printf("%s t %d %d\n", a->name, t->vars, t->name);
				
				if(look.type == 502) {
					move();
				}
				if((t->type == 3 || t->type == 2) && t->name[0] == 0 && flag == 0) {//struct{struct{int a, b;}} x; x.a; x.b;\D5\E2\D1\F9\B5Ĵ\FA\C2\EB.
					struct Variable * v = t->vars, * v1;
					int cur = 0;
					while(v) {
						if(findMem(a->vars, v->name)) {
							ERROR(57);
						}
						v1 = v->next;
						v->next = a->vars;
						a->vars = v;
						struct List * l = newList();
						l->value = a->size + cur;
						l->next = a->posi;
						a->posi = l;
						if(t->type == 2) {
							int tmp = calcSize(v);
							if(tmp % 4) {
								tmp += 4 - tmp % 4;
							}
							cur += tmp;
						}
						v = v1;
					}
					if(a->type == 2) {
						a->size += t->size;
					}else {
						a->size = max(a->size, t->size);
					}
				}
			}
//			top = top->prev;
			move();
			return a;
		}else {
			struct Type * t = find(structName.name);//\B2\BB\B8\F8\B3\F6\B6\A8\D2\E5\B5\C4struct
			if(!t) {
				struct Type * a = (struct Type *)malloc(sizeof(struct Type));//\B3\F5ʼ\BB\AFһ\B8\F6\C0\E0
				a->next = top->QaQ;
				top->QaQ = a;
				a->size = -1;
				a->vars = 0;
				a->type = s_or_u - 302;
				a->name = structName.name;
				return a;
			}else {
				if(t->type != s_or_u - 302) {
					ERROR(58);
				}
				return t;
			}
		}
	}else {
		if(look.type == 302) {//char
			move();
			//printf("char type\n");
			return CHAR_TYPE;
		}else if(look.type == 303) {//int
			move();
			//printf("int type\n");
			return INT_TYPE;
		}else if(look.type == 301) {//void
			move();
			//printf("void type\n");
			return VOID_TYPE;
		}else {
			ERROR(59);
		}
	}

}

struct Variable * findVariable(char * name) {//\D4ڱ\E4\C1\BF\B1\ED\D6\D0\D5\D2\C3\FB\D7\D6, \D5Ҳ\BB\B5\BD\B5\BD\C9ϲ\E3\B7\FB\BAű\ED\D6\D0\D5\D2!
	struct SymbolList * s = top;
	while(s) {
		struct Variable * p = s->vars;
		while(p) {
			if(!strcmp(p->name, name)) {
				return p;
			}
			p = p->next;
		}
		s = s->prev;
	}
	return 0;
}

struct Function * findFunc(char * name) {//\D4ں\AF\CA\FD\B1\ED\D6\D0\D5\D2\C3\FB\D7\D6
	struct SymbolList * s = top;
	while(s) {
		struct Function * p = s->funcs;
		while(p) {
			if(!strcmp(p->name, name)) {
				return p;
			}
			p = p->next;
		}
		s = s->prev;
	}
	return 0;
}


struct Variable * findTopVariable(char * name) {
	struct Variable * p = top->vars;
	while(p) {
		if(!strcmp(p->name, name)) {
			return p;
		}
		p = p->next;
	}
	return 0;
}

struct Function * findTopFunc(char * name) {
	struct Function * p = top->funcs;
	while(p) {
		if(!strcmp(p->name, name)) {
			return p;
		}
		p = p->next;
	}
	return 0;
}

int compFunc(struct Function * p, struct Function * q) {//\B1ȽϺ\AF\CA\FD\B6\A8\D2\E5
	if(!compType(p->rtn, q->rtn)) {//\B1ȽϷ\B5\BB\D8ֵ\C0\E0\D0\CD
		return 0;
	}
	struct Variable * v = p->argu, * u = q->argu;
	for(;;) {//\B1Ƚϲ\CE\CA\FD\B8\F6\CA\FD\BA\CD\C0\E0\D0\CD
		if(!v && !u) {
			return 1;
		}
		if(!v || !u) {
			return 0;
		}
		if(!compType(v, u)) {
			return 0;
		}
		v = v->next;
		u = u->next;
	}
}

void printStringAssign(struct Function * env, struct Operand * v) {
	int len = 0;
	while(len == 0 || look.name[len - 1]) {
		if(!v->var->list || len < v->var->list->value) {
			struct Operand * ope = newOperand(newVariable(), 1, 0, 0);
			ope->var->index = v->var->index;
			totIndex--;
			ope->offset = len + v->offset;
			ope->var->type = CHAR_TYPE;
			printAssign(env, ope, constChar(look.name[len]));
		}
		len++;
	}
//	totIndex++;
	move();
}

void parseElementInitialization(struct Function * env, struct Operand * v, int flag, int first) {
	if(look.type == 505) {
		move();
		parseElementInitialization(env, v, flag, 1);
		if(look.type != 506) {
			match(503);
		}
		while(look.type != 506) {
			parseElementInitialization(env, v, 0, 0);
			if(look.type != 506) {
				match(503);
			}
		}
		move();
	}else {
		if(!flag) {
			struct Operand * res = parseAssignmentExpression(bucket);
			if(first && env == chief && (v->var->level && !(res->loadable || res->constant) || !v->var->level && !res->constant)) {
				ERROR(96);
			}
		}else {
			if(v->var->level && look.type == STR_CONSTANT) {

				parsePrimaryExpression(env);
				env->insts->a = getValue(env, v);
/*				int len = 0;
				while(look.name[len]) {
					len++;
				}
				struct Operand * res = printMalloc(env, constInt(sizeof(char) * (len + 1)));
				if(v->type == 0) {
					env->insts->a = v;
				}else {
					printAssign(env, v, res);
				}
				printStringAssign(env, getValue(env, v));*/
			}else {
				struct Operand * res = parseAssignmentExpression(env);
				if(env == chief && (v->var->level && !(res->loadable || res->constant) || !v->var->level && !res->constant)) {
					ERROR(95);
				}
				printAssign(env, v, res);
			}
		}
	}
}

void parseInitialization(struct Function * env, struct Operand * v) {
	if(v->var->list) {
		int isCharArray = v->var->type == CHAR_TYPE && v->var->list && !v->var->list->next && !v->var->level;
		if(look.type == 505) {
			move();
			if(isCharArray && look.type == STR_CONSTANT) {
				printStringAssign(env, v);
			}else {
				int tot = 0;
				while(look.type == 505 || look.type == STR_CONSTANT && v->var->list->next && !v->var->list->next->next) {

					if(tot < v->var->list->value) {
						parseInitialization(env, printAccess(env, v, constInt(tot)));
					}else {
						parseElementInitialization(env, v, 0, tot == 0);
					}

					tot++;
					if(look.type == 506) {
						break;
					}else {
						match(503);//','
					}
				}
				tot *= v->var->list->mul / v->var->list->value;
				while(look.type != 506) {
					struct Operand * ope = newOperand(newVariable(), 1, 0, 0);
					ope->var->index = v->var->index;
					totIndex--;
					ope->offset = v->offset + tot * calcElementSize(v->var);
					ope->var->type = v->var->type;
					ope->var->level = v->var->level;
					parseElementInitialization(env, ope, tot < v->var->list->mul, tot == 0);
					tot++;
					if(look.type == 506) {
						break;
					}else {
						match(503);
					}
				}
			}
			match(506);
		}else if(look.type == STR_CONSTANT && isCharArray) {
			printStringAssign(env, v);
		}else {
			ERROR(93);
		}
	}else {
		parseElementInitialization(env, v, 1, 1);
	}
}

void parseDeclaractionOrFunctionDefinition(struct Function * env);

void parseStatement(int b, int a, struct Function * env) {//\B7\D6\CE\F6\D3\EF\BE\E4.
	//b: before, a:after
	//printf("STA %d\n", env);
	if(look.type == 505) {//'{'\B8\B4\BA\CF\D3\EF\BE\E4
		move();
		top = newSymbolList(top);
		while(look.type != 506) {//'}'
			if(look.type >= 301 && look.type <= 305) {
				parseDeclaractionOrFunctionDefinition(env);
			}else {
				//printf("CS %d\n", env);
				parseStatement(b, a, env);
				//printf("CS %d\n", env);
			}
		}
		move();
		top = top->prev;
	}else if(look.type == 306) { //if\D3\EF\BE\E4
		move();
		match(500);//'('
		int after = newLabel();//\B1\EA\BC\C7else֮ǰ\B5\C4λ\D6\C3

		printIfFalseGoto(env, parseExpression(env), after);//\B2\BB\C2\FA\D7\E3\BE\CD\CC\F8!
		match(501);//')'
		//printf("ifStatement\n");
		parseStatement(b, a, env);//\C2\FA\D7\E3ʱִ\D0е\C4\D3\EF\BE\E4
		//printf("ifStatement\n");
		if(look.type == 307) {//else\D3\EF\BE\E4
			move();
			int last = newLabel();//else\BD\E1\CA\F8\B5\C4λ\D6\C3
			printGoto(env, last);//\C2\FA\D7\E3ʱ\CC\F8\B9\FDelse
			printLabel(env, after);//\B1\EA\BC\C7else֮ǰ\B5\C4λ\D6\C3
			parseStatement(b, a, env);//\B2\BB\C2\FA\D7\E3ʱִ\D0е\C4\D3\EF\BE\E4
			printLabel(env, last);//\B1\EA\BC\C7else\BD\E1\CA\F8\B5\C4λ\D6\C3
		}else {
			printLabel(env, after);//û\D3\D0else, ֱ\BDӱ\EA\BCǽ\E1\CA\F8λ\D6\C3.
		}
	}else if(look.type == 309) {//for
		move();
		match(500);//'('
		int body = newLabel(), begin = newLabel(), after = newLabel();//ѭ\BB\B7k\BF\D8\D6\C6λ\D6\C3, ѭ\BB\B7\B1\E4\C1\BF\B1\E4\B8\FCλ\D6\C3, ѭ\BB\B7\BD\E1\CA\F8λ\D6\C3
		if(look.type == 502) {
			//֧\B3ֲ\BB\B3\F5ʼ\BB\AF!
		}else {
			parseExpression(env);//\B7\D6\CE\F6ѭ\BB\B7\B3\F5ʼ\BB\AF\B1\ED\B4\EFʽ
		}
		match(502);//';'
		printLabel(env, body);//\B1\EA\BC\C7ѭ\BB\B7\BF\D8\D6\C6λ\D6\C3
		if(look.type == 502) {
			printIfFalseGoto(env, constInt(1), after);//֧\B3\D6\CB\C0ѭ\BB\B7
		}else {
			printIfFalseGoto(env, parseExpression(env), after);//\B7\D6\CE\F6ѭ\BB\B7\BF\D8\D6Ʊ\ED\B4\EFʽ, \B2\BB\C2\FA\D7\E3\BEͽ\E1\CA\F8
		}
		match(502);//';'
		struct Function * tmp = (struct Function *)malloc(sizeof(struct Function));//\B8\B4\D6ƺ\AF\CA\FD\BB\B7\BE\B3
		*tmp = *env;
		tmp->insts = 0;
		tmp->occupy = 0;
		if(look.type == 501) {//')'
			//֧\B3\D6\CB\C0ѭ\BB\B7
		}else {
			parseExpression(tmp);//\B7\D6\CE\F6ѭ\BB\B7\B1\E4\C1\BF\B1\E4\B8\FC\B1\ED\B4\EFʽ
		}
		match(501);//')'
		parseStatement(begin, after, env);//\B7\D6\CE\F6ѭ\BB\B7\CC\E5
		printLabel(env, begin);//ѭ\BB\B7\B1\E4\C1\BF\B1\E4\B8\FC\BF\AAʼ
		if(tmp->insts) {
			struct Instruction * p = tmp->insts;//\B8\B4\D6\C6ѭ\BB\B7\B1\E4\C1\BF\B1\E4\B8\FC\B4\FA\C2\EB
			while(p->next) {
				p = p->next;
			}
			p->next = env->insts;
			env->insts = tmp->insts;
		}
		if(tmp->occupy) {
			struct List * p = tmp->occupy;
			while(p->next) {
				p = p->next;
			}
			p->next = env->occupy;
			env->occupy = tmp->occupy;
		}
		printGoto(env, body);//\CC\F8\B5\BDѭ\BB\B7\BF\D8\D6\C6λ\D6\C3
		printLabel(env, after);//\B1\EA\BC\C7ѭ\BB\B7\BD\E1\CA\F8
	}else if(look.type == 308) {//while
		move();
		match(500);//'('
		int begin = newLabel(), after = newLabel();//ѭ\BB\B7\BF\D8\D6\C6λ\D6\C3, ѭ\BB\B7\BD\E1\CA\F8λ\D6\C3
		printLabel(env, begin);//\B1\EA\BC\C7ѭ\BB\B7\BF\D8\D6ƿ\AAʼλ\D6\C3
		if(look.type == 501) {//')'
			ERROR(71);//֧\B3\D6\CB\C0ѭ\BB\B7\B2Ź\D6!
			printIfFalseGoto(env, constInt(1), after);//֧\B3\D6\CB\C0ѭ\BB\B7\B2Ź\D6!
		}else {
			printIfFalseGoto(env, parseExpression(env), after);//\B2\BB\C2\FA\D7\E3\BEͽ\E1\CA\F8
		}
		match(501);//')'
		parseStatement(begin, after, env);//\B7\D6\CE\F6ѭ\BB\B7\CC\E5
		printGoto(env, begin);
		printLabel(env, after);//\B1\EA\BCǽ\E1\CA\F8λ\D6\C3
	}else if(look.type == 311) {//break
		if(a == -1) {
			ERROR(72);
		}
		move();
		printGoto(env, a);//\CC\F8\B5\BDafter\B4\A6, \BC\B4for\BA\CDwhile\B5Ľ\E1\CA\F8λ\D6\C3
		match(502);//';'
	}else if(look.type == 310) {//continue
		if(b == -1) {
			ERROR(73);
		}
		move();
		printGoto(env, b);//\CC\F8\B5\BDbegin\B4\A6, \BC\B4for\B5\C4ѭ\BB\B7\B1\E4\C1\BF\B1\E4\B8\FCλ\D6\C3, while\B5\C4ѭ\BB\B7\BF\D8\D6\C6λ\D6\C3.
		match(502);//';'
	}else if(look.type == 312) {//return!
		move();
		if(env->rtn->type != VOID_TYPE) {
			printReturn(env, parseExpression(env));
		}else {
			printVoidReturn(env); 
		}
		match(502);
	}else {//\B1\ED\B4\EFʽ\D3\EF\BE\E4.
		//printf("expSta %d\n", env);
		if(look.type == 502) {
			move();
			return;
		}
		parseExpression(env);
		//printf("staExp %d\n", env);
		match(502);//';'
		//printf("staExp %d\n", env);

	}
}

void parseFunctionBody(struct Function * env) {
//	printf("parse Function %s\n", env->name);
	top = env->symbolList;
	struct Variable * p = env->argu, * p1;//\B8\B4\D6Ʋ\CE\CA\FDΪ\B3\F5ʼ\B1\E4\C1\BF\B1\ED
	env->argu = 0;
	while(p) {
		p1 = p->next;
		p->next = env->argu;
		env->argu = p;
		p = p1;
	}

	p = env->argu;
	while(p) {
		printGetArgu(env, directLvalue(p));//
		occupy(env, directLvalue(p));
		//printf("get_argument %s %s %d\n", env->name, p->name, env->insts->a->var->level);
		p = p->next;
	}
	//printf("abc\n");

	p = env->argu;
	env->argu = 0;
	while(p) {
		p1 = p->next;
		p->next = env->argu;
		env->argu = p;
		p = p1;
	}	
	//printf("abc\n");
	move();
	while(look.type != 506) {//'}'
		if(look.type >= 301 && look.type <= 305) {//\CA\C7void char int struct union\D6е\C4һ\B8\F6
		//	printf("decl\n");
			parseDeclaractionOrFunctionDefinition(env);
		}else {
		//	printf("state\n");
			//printf("FB %d\n", env);
			parseStatement(-1, -1, env);//\B7\F1\D4\F2.
			//printf("FB %d\n", env);
		}
	}
	//printf("abc\n");
	move();
	top = top->prev;
}

struct Function * parseArguments(struct Function * env) {
	move();//'('
	struct Function * f = newFunction();
	f->symbolList = newSymbolList(top);
	top = f->symbolList;
	for(; look.type != 501;) { //')'
		struct Type * p = parseTypeSpecifier();
		struct Variable * v = parsePlainDeclarator(1);//\D4\CA\D0\ED\C4\E4\C3\FB
		if(v->level == 0 && v->type == VOID_TYPE || v->name[0] != 0 && findTopVariable(v->name)) {
			ERROR(74);
		}
		if(look.type == 507) {//'['
			v->list = parseArray();
		}
		//occupy(env, directLvalue(v));
		v->type = p;
		v->next = top->vars;
		top->vars = v;//\B7\B4\CF\F2\B2\CE\CA\FD\B1\ED!!!!!!!!!!!!!!!!!!!!!!!!!
		if(look.type == 503) {//','
			move();
		}
	}
	move();//')'
	struct Variable * tmp, * tmp1;
	tmp = top->vars;
	top->vars = 0;
	while(tmp) {
		tmp1 = tmp->next;
		tmp->next = top->vars;
		top->vars = tmp;
		tmp = tmp1;
	}
	f->argu = top->vars;//\B7\FB\BAű\ED\B0\FC\BA\ACf\B5Ĳ\CE\CA\FD!
	top = top->prev;//!!
	return f;
}

struct List * data = 0, * data1 = 0;//.data数据段
int nData = 0;

void printFillZero(struct Function * env, struct Operand * ope) {
	if(ope->var->list || isStruct(ope->var)) {
		struct Instruction * inst = newInstruction(MALLOC, ope, constInt(calcSize(ope->var)), 0);
		push(env, inst);
//		inst->n = nData++;
//		struct List * tmp = newList();
//		tmp->value = calcSize(ope->var);
//		tmp->mul = nData - 1;
//		tmp->next = data1;
//		data1 = tmp;
	}
	struct List * tmp = newList();
	tmp->value = 4;//calcSize(ope->var);
	tmp->mul = ope->var->index;
	tmp->next = data;
	data = tmp;
}

void parseDeclaractionOrFunctionDefinition(struct Function * env) {
	int i = 0;
	//printf("Func Def");
	struct Type * t = parseTypeSpecifier();//\B7\D6\CE\F6\C0\E0\D0\CD
	//	if(t->size == -1) {
	//		match(502);//';'
	//		return;
	//	}
	for(;look.type != 502;) {//';'
		i++;
		//printf("Func Def");
		struct Variable * v = parsePlainDeclarator(0);//\B7\D6\CE\F6\C1\CBָ\D5\EB\B5Ĳ\E3\CA\FD, \B2\BB\D4\CA\D0\ED\C4\E4\C3\FB
		if(t->size == -1 && !v->level) {
			ERROR(92);
		}
		//printf("Func Def3\n");
		//printf("parse FUNCTION\n");
		v->type = t;
		if(look.type == 500) {//'('˵\C3\F7\CAǺ\AF\CA\FD
			//printf("parse FUNCTION\n");
			if(findTopVariable(v->name)) {//\BA\AF\CA\FD\B2\BB\C4ܺͱ\E4\C1\BF\D6\D8\C3\FB
				ERROR(150000);
			}
			//printf("parse FUNCTION\n");
			//printf("Func Def");
			struct Function * f = parseArguments(env);//\B7\D6\CE\F6\BA\AF\CA\FD\B5Ĳ\CE\CA\FD
			f->name = v->name;//\BA\AF\CA\FD\B5\C4\C3\FB\D7\D6
			//printf("Func Def %s\n", f->name);
			f->rtn = v;//\BA\AF\CA\FD\B5ķ\B5\BB\D8ֵ\C0\E0\D0\CD
			struct Function * p = findTopFunc(f->name);//Ѱ\D5ҵ\B1ǰ\B2㺯\CA\FD\B1\ED, \D3\D0û\D3\D0һ\D1\F9\B5ĺ\AF\CA\FD

			//printf("p = %d\n", p);
			if(p && !compFunc(p, f)) {//\B2\BB\C4\DC\C3\FB\D7\D6һ\D1\F9\B6\A8\D2\E5ȴ\B2\BBͬ
				ERROR(76);
			}
			if(!p) {//û\D3\D0\D6\D8\C3\FB\B5ĺ\AF\CA\FD
				f->next = top->funcs;
				top->funcs = f;
				funcList = newFuncList(f, funcList);
			}else {
				p->argu = f->argu;
				p->symbolList = f->symbolList;
				f = p;
			}
			if(look.type == 505) {//'{'˵\C3\F7\CAǺ\AF\CA\FD\B6\A8\D2\E5
				//printf("REAL DEF\n");
				if(f->insts || i != 1) {//\B2\BB\C4\DC\D6ظ\B4\B6\A8\D2庯\CA\FD, \BA\AF\CA\FD\B6\A8\D2\E5\B1\D8\D0\EB\B6\C0ռtype-specifier.
					ERROR(77);
				}
				printNOP(f);
				//printf("REAL DEF\n");
				//printf("parseFunctionBody%s\n", f->name);
				parseFunctionBody(f);//\B7\D6\CE\F6\BA\AF\CA\FD\B9\FD\B3\CC.
				//printf("REAL DEF\n");
				return;//\BA\AF\CA\FD\B6\A8\D2\E5\B1\D8\D0\EB\B6\C0ռtype-specifier
			}else {
				//\D6ظ\B4\C9\F9\C3\F7\BA\AF\CA\FD, ʲôҲ\B2\BB\D7\F6.
			}
		}else {//\B2\BB\CAǺ\AF\CA\FD
			if(findTopVariable(v->name) || findTopFunc(v->name)) {
				ERROR(78);
			}
			v->next = top->vars;
			top->vars = v;
			if(look.type == 507) {//'['˵\C3\F7\CA\C7\CA\FD\D7\E9\C0\E0\D0\CD
				v->list = parseArray();//\B7\D6\CE\F6\CA\FD\D7\E9\B5\C4ά\B6\C8
			}
			if(v->type == VOID_TYPE && v->level == 0) {//\B2\BB\C4ܶ\A8\D2\E5void\C0\E0\D0͵ı\E4\C1\BF
				ERROR(79);
			}
			if(v->list || isStruct(v)) {
				printDeclPointer(env, directLvalue(v));
				if(env != chief) {
					printMalloc(env, constInt(calcSize(v)));
					env->insts->a = directLvalue(v);
				}
			}else if(v->level) {
				printDeclPointer(env, directLvalue(v));
			}else if(v->type == CHAR_TYPE) {
				printDeclChar(env, directLvalue(v));
			}else if(v->type == INT_TYPE) {
				printDeclInt(env, directLvalue(v));
			}
			//printf("occupy %s %d %s\n", env->name, v->index, v->name);
			occupy(env, directLvalue(v));
			//printf("!!\n");
			/*			if(env == chief) {//˵\C3\F7\CA\C7ȫ\BEֱ\E4\C1\BF

						printFillZero(env, directLvalue(v));//\BD\ABv\CB\F9ռȫ\B2\BF\C4ڴ\E6\C7\E50
			//printf("!!2\n");

			}*/
			if(look.type == 504) {//'='˵\C3\F7\D3г\F5ʼ\BB\AF
				if(env == chief) {// && (v->list || isstruct(v))) {
					printFillZero(env, directLvalue(v));
				}
				move();//'='
				parseInitialization(env, directLvalue(v));//\B7\D6\CE\F6\B1\E4\C1\BFv\B5ĳ\F5ʼ\BB\AF
			}else if(env == chief) {
				printFillZero(env, directLvalue(v));
			}
		}
		if(look.type != 502) {//','˵\C3\F7\BB\B9\D3к\F3\D0\F8\C9\F9\C3\F7
			match(503);
		}
	}
	move();
}	

char CHIEF[6] = "chief";

void parseProgram() {
	TMP.value = TMP.mul = 1;
	chief = newFunction();//\D6\F7\B9\FD\B3\CC
	funcList = newFuncList(chief, 0);
	chief->name = CHIEF;
	chief->symbolList = newSymbolList(top);
	top = chief->symbolList;
	bucket = newFunction();//\C0\AC\BB\F8Ͱ
	printNOP(chief);//\D0½\A8һ\B8\F6\BFղ\D9\D7\F7.
	printNOP(bucket);
	int begin = newLabel(), end = newLabel();//\D6\F7\B3\CC\D0\F2\B5Ŀ\AAʼ\BAͽ\E1\CA\F8\B1\EAǩ
	printLabel(chief, begin);
	look1 = nextToken();
	move();
	//printf("WoW\n");
	while(look.type != NO_TOKEN) {
		//printf("fuck you");
		parseDeclaractionOrFunctionDefinition(chief);
	}
	//printf("Oh\n");
	printLabel(chief, end);
	//chief->insts\BC\B4Ϊ\D6\F7\B3\CC\D0\F2\B5\C4ָ\C1\EE\D0\F2\C1\D0(\B5\B9\D0\F2)
}

struct Instruction ** jumpTo;

struct List * arguStack;

void reverse(struct Function * f) {//\B7\B4\CF\F2ָ\C1\EE\B1\ED, fetch label
	struct Instruction * tmp = f->insts, * tmp1;
	f->insts = 0;
	while(tmp) {
		if(tmp->type == CALL && tmp->f->insts == 0) {
			ERROR(98);//UNDEFINED FUNCTION
		}
		tmp1 = tmp->next;
		tmp->next = f->insts;
		f->insts = tmp;
		tmp = tmp1;

	}
	tmp = f->insts;
	while(tmp) {
		if(tmp->type == LABEL) {
			jumpTo[tmp->n] = tmp;
		}
		tmp = tmp->next;
	}
}

struct Instruction * inst;

int halt, result;

struct InterCodeOperand {
	int var;
	int idx;
};
struct InterCodeOperand * newInterCodeOperand() {
	struct InterCodeOperand * res = (struct InterCodeOperand *)malloc(sizeof(struct InterCodeOperand));
	res->var = 0;
	res->idx = -1;
	return res;
}

struct InterCode {
	int type;
	struct InterCodeOperand * a, * b, * c;
	struct InterCode * next;
	int n;
	int * liveness;
	int * regValid;
	struct Function * func;
};
struct InterCode * newInterCode() {
	struct InterCode * res = (struct InterCode *)malloc(sizeof(struct InterCode));
	res->type = 0;
	res->a = 0;
	res->b = 0;
	res->c = 0;
	res->next = 0;
	res->n = -1;
	res->func = 0;
	res->liveness = 0;
	return res;
}

int nBlocks = 0, clck = 0;

struct Block;

struct Edge {
	struct Block * y;
	struct Edge * next;
};

struct Edge * newEdge() {
	struct Edge * res = (struct Edge *)malloc(sizeof(struct Edge));
	res->y = 0;
	res->next = 0;
	return res;
}

struct Block {
	int visit;
	int index;
	int used;
	int rtn;
	struct InterCode * incs, * phis;
	struct Block * next;
	struct List * sources;
	struct Edge * pres;
};
struct Block * newBlock() {
	struct Block * res = (struct Block *)malloc(sizeof(struct Block));
	res->visit = 0;
	res->index = ++nBlocks;
	res->incs = res->phis = 0;
	res->pres = 0;
	return res;
}

void pushEdge(struct Block * blk, int d, struct Block * y) {
	if(y) {
		struct Edge * tmp = newEdge();
		tmp->y = blk;
		tmp->next = y->pres;
		y->pres = tmp;
	}
}

struct InterCode * convertToInterCode(struct Instruction * inst) {
	struct InterCode * res = newInterCode();
	res->type = inst->type;
	if(inst->a) {
		res->a = newInterCodeOperand();
		res->a->var = inst->a->var->index;
		if(inst->a->constant) {
			res->a->idx = inst->a->value;
		}
	}
	if(inst->b) {
		res->b = newInterCodeOperand();
		res->b->var = inst->b->var->index;
		if(inst->b->constant) {
			res->b->idx = inst->b->value;
		}
	}
	if(inst->c) {
		res->c = newInterCodeOperand();
		res->c->var = inst->c->var->index;
		if(inst->c->constant) {
			res->c->idx = inst->c->value;
		}
	}
	res->n = inst->n;
	res->func = inst->f;
	if(inst->type == LD || inst->type == LD_CHAR) {
		res->n = inst->b->offset;
	}else if(inst->type == ST || inst->type == ST_CHAR) {
		res->n = inst->a->offset;
	}
	return res;
}

struct Block ** jumpToBlock;
int isJump(int x) {
	return x == IF_GOTO || x == IF_FALSE_GOTO || x == GOTO;
}
int isAssign(int x) {
	return x == GET_ARGU || x == MALLOC || x == GETCHAR
	|| x == ASSIGN_DEREF_CHAR || x == ASSIGN_DEREF || x == ASSIGN_DEREF_ADDRESS 
	|| x == ASSIGN || x == ASSIGN_LOGICAL_NOT || x == ASSIGN_NOT || x == ASSIGN_NEGATE || x == ASSIGN_CHAR
	|| x == ASSIGN_ADDRESS || x == ASSIGN_INCLUSIVE_OR || x == ASSIGN_EXCLUSIVE_OR || x == ASSIGN_AND
	|| x == ASSIGN_SHR || x == ASSIGN_SHL || x == ASSIGN_SUB || x == CALL || x == ASSIGN_MOD || x == ASSIGN_DIV
	|| x == ASSIGN_MUL || x == ASSIGN_NOT_EQUAL_TO || x == ASSIGN_EQUAL_TO || x == ASSIGN_GREATER_THAN_OR_EQUAL_TO
	|| x == ASSIGN_LESS_THAN_OR_EQUAL_TO || x == ASSIGN_GREATER_THAN || x == ASSIGN_LESS_THAN || x == ASSIGN_LOGIC_OR
	|| x == ASSIGN_LOGIC_AND || x == INT_TO_CHAR || x == CHAR_TO_INT || x == ASSIGN_ADDRESS_OF || x == ASSIGN_ADD
	|| x == LD || x == LD_CHAR || x == ASSIGN_DATA || x == ASSIGN_STR;
}

void printData() {
	printf(".data\n");
	struct List * p = data;
	int cnt = nData;
	while(p) {
		printf("d%d: .byte", p->mul);
		int i = 0;
		for( ; i < p->value; i++) {
			printf(" 0,");
		}
		printf("\n");
		p = p->next;
	}
	p = data1;
	while(p) {
		printf("data%d: .byte", p->mul);
		int i = 0;
		for(; i < p->value; i++) {
			printf(" 0,");
		}
		printf("\n");
		p = p->next;
	}
	cnt = nString;
	struct StringList * q = strings;
	while(q) {
		printf("str%d: .byte", --cnt);
		int len = 0;
		while(q->name[len]) {
			printf(" %d,", q->name[len]);
			len++;
		}
		printf(" 0\n");
		q = q->next;
	}
}

int * mapReg;

int maxReg = 25;

int * dangerous;

int * memoryLocate;

int * regAssign;

int * regAlloc;

int oo;

int load(struct FuncList * p, int idx, int * liveness) {
	int reg;
	int memLoc = memoryLocate[idx];
	//printf("%d %d\n",idx, memLoc);
	if(memLoc > 0) {
		reg = regAlloc[memLoc - 1];
	}else {
		reg = p->regAlloc[-memLoc];
	}
	//printf("%d\n",reg);
	if(reg == -1) {
		if(oo == 0) {
			if(memLoc > 0) { 
				printf("\tlw $a0, d%d\n", idx);
			}else {
				printf("\tlw $a0, %d($sp)\n", -memLoc * 4);
			}
			oo++;
			return 4;//a0
		}else if(oo == 1) {
			if(memLoc > 0) { 
				printf("\tlw $v0, d%d\n", idx);
			}else {
				printf("\tlw $v0, %d($sp)\n", -memLoc * 4);
			}
			oo++;
			return 2;//v0
		}else {
			printf("54749110\n");
		}
	}else {
		return mapReg[reg];
	}
}

int locateTarget(struct FuncList * p, int idx, int * liveness) {
	int reg;
	int memLoc = memoryLocate[idx];
	if(memLoc > 0) {
		reg = regAlloc[memLoc - 1];
	}else {
		reg = p->regAlloc[-memLoc];
	}
	if(reg == -1) {
		return 2;//v0
	}else {
		return mapReg[reg];
	}
}

int stopAtLexer = 0, outputInterCode = 0;

int DEBUG = 0;

int main() {
	//freopen("basicopt1-hetianxing.c", "r", stdin);
	examine = 1;
	initBasicTypeName();
	initModVariables();
	program = (char*)malloc(sizeof(char) * 10);
	int length = 0;
	int capacity = 10;
	char c;	
	int i = 0;
	for(; __stdio__printf__[i]; i++) {//\B1\EA׼\BF\E2printf
		push_back(&program, &length, &capacity, __stdio__printf__[i]);
	}
	if(DEBUG) {
		printf("loading...");
	}
	while(-1 != (c = getchar())) {
		//intf("%c\n", c);
		if(c == 64) {
			break;
		}
		push_back(&program, &length, &capacity, c);
	}
	for(i = 0; i < 5; i++) {
		push_back(&program, &length, &capacity, 0);
	}
	int len = 0;
	for(i = 0; program[i]; i++) {
		if(program[i] != '\r') {
			program[len++] = program[i];
		}
	}
	program[len] = 0;
	len = 0;
	for(i = 0; program[i]; i++) {
		if(program[i] == '\\\
') {
			int j = 0;
			while(program[i + j + 1] == ' ' || program[i + j + 1] == '\t') {
				j++;
			}
			if(program[i + j + 1] == '\n') {
				i = i + j + 1;
				continue;
			}
		}
		program[len++] = program[i];
	}
	program[len] = 0;
	beginOfLine = 1;
	bp = program;
	if(stopAtLexer) {
	}else {
		if(DEBUG) {
			printf("load complete\n");
		}
		parseProgram();
		if(DEBUG) {
			printf("parse  complete\n");
		}
		struct FuncList * funcMain = 0;
		//printf("parseProgramComplete\n");
		jumpTo = (struct Instruction **)malloc(sizeof(struct Instruction *) * nLabel);
		struct FuncList * p = funcList;
		while(p) {
			reverse(p->f);
			p = p->next;
		}
		p = funcList;
//        int nBlock = 0;
		memoryLocate = (int *)malloc(sizeof(int) * totIndex);
		//printf("totIndex = %d\n", totIndex);
		int globalVars;
		jumpToBlock = (struct Block **)malloc(sizeof(struct Block *) * nLabel);
		if(DEBUG) {
			printf("constructing basic blocks...\n");
		}
		while(p) {//分开basic block!
			//printf("%s %d\n", p->f->name, strcmp(p->f->name, "main"));
			//printf("%s %s\n", p->f->name, "main");
			if(!strcmp(p->f->name, "main")) {
				funcMain = p;
				//printf("main %d %s\n", p->f, p->f->name);
			}
			struct Instruction * inst = p->f->insts;
		//	printf("%d\n", inst);
			while(inst) {
//                nBlock++;
				//printf("%d\n", inst);
				struct Block * blk = newBlock();
				blk->next = p->blocks;
				p->blocks = blk;
				//printf("%d\n", inst);
				while(inst && inst->type == LABEL) {
					//printf("%d %d\n", inst->n, blk->index);
					jumpToBlock[inst->n] = blk;
					//printf("%d\n", inst);
					inst = inst->next;
				//	printf("%d\n", inst);
				}
				//printf("%d\n", inst);
				while(inst && !isJump(inst->type) && inst->type != LABEL) {
					struct InterCode * inc = convertToInterCode(inst);
					if(inc->type != NOP) {
						inc->next = blk->incs;
						blk->incs = inc;
					}
					inst = inst->next;
				}
				if(inst && inst->type != LABEL) {
					struct InterCode * inc = convertToInterCode(inst);
					if(inc->type != NOP) {
						inc->next = blk->incs;
						blk->incs = inc;
 					}
					inst = inst->next;
				}
				if(blk->incs == 0) {
					blk->incs = newInterCode();
					blk->incs->type = 7;
				}
 			}
			struct List * q = p->f->occupy;
			p->cnt = 0;
			while(q) {
				//printf("%s occupy %d\n", p->f->name, q->value);
				//if(p->f == chief) {
				//	memoryLocate[q->value] = ++p->cnt;//全局变量>0
				//}else {
					memoryLocate[q->value] = -(p->cnt++);//局部变量<=0
					//printf("locate %d %d\n", q->value, -(p->cnt-1));
				//}
				q = q->next;
			}
			if(p->f == chief) {
				globalVars = p->cnt;
				q = data;
				while(q) {
					memoryLocate[q->mul] = -memoryLocate[q->mul] + 1;
					q = q->next;
				}
			}

			struct Variable * var = p->f->argu;
			p->cntArgu = 0;
			while(var) {
				p->cnt++;
				p->cntArgu++;
				var = var->next;
			}
			int cnt1 = 0;
			var = p->f->argu;
			while(var) {
				cnt1++;
				memoryLocate[var->index] = -(p->cnt - cnt1);
				//printf("%d %d\n", var->index, -(p->cnt - cnt1));
				var = var->next;
			}//参数在栈帧的最上部, 直接使用caller push进来的参数. sp在函数体中不变, 函数开始和结束时移动该函数使用的栈帧大小; fp在argu操作时push, callee开始时会把fp顶端自己的参数部分pop(相当于直接用于自己的栈帧). 这样sp和fp都不用备份(?!)
			//printf("%s %d\n", p->f->name, p->cnt);
			p = p->next;
		}
		if(funcMain == 0) {
			ERROR(99);
		}
		if(DEBUG) {
			printf("constructing cfg...\n");
		}
		
		p = funcList;//给basic block连边, 做cfg.
		while(p) {
			//printf("block\n");

			struct Block * blk = p->blocks,  * prevBlock = 0;
			//printf("block!\n");

			while(blk) {
				//printf("block %d\n", blk->index);
				if(blk->incs) {
					if(blk->incs->type == IF_GOTO || blk->incs->type == IF_FALSE_GOTO) {
						pushEdge(blk, 0, jumpToBlock[blk->incs->n]);
						pushEdge(blk, 1, prevBlock);
					}else if(blk->incs->type == GOTO) {
						pushEdge(blk, 0, jumpToBlock[blk->incs->n]);
					}else {
						pushEdge(blk, 0, prevBlock);
					}
				}
				//printf("block %d\n", blk->index);
				prevBlock = blk;
				blk = blk->next;
			}
			blk = p->blocks;

			while(blk) {
				struct InterCode * inc = blk->incs;
				while(inc) {
					inc->liveness = (int *)malloc(sizeof(int) * p->cnt);
					inc = inc->next;
				}
				blk = blk->next;
			}
			if(DEBUG) {
				printf("liveness && deadCode Elim for %s\n", p->f->name);
			}
			int deadCode = 1;
			while(deadCode) {
				if(DEBUG) {
					printf("deadCode round\n");
				}
				deadCode = 0;
				int changed = 1;
				blk = p->blocks;
				while(blk) {
					struct InterCode * inc = blk->incs;
					while(inc) {
						int i;
						for(i = 0; i < p->cnt; i++) {
							inc->liveness[i] = 1;
						}
				
						inc = inc->next;
					}
					blk = blk->next;
				}
				/*
				while(changed) {//做局部变量活性分析.
					changed = 0;
					blk = p->blocks;
					while(blk) {
						struct InterCode * inc = blk->incs;
						while(inc) {
							int memLocA, flaga = 0;
							if(inc->a && inc->a->var != -1) {
								flaga = 1;
								memLocA = memoryLocate[inc->a->var];
							}
							int memLocB, flagb = 0;
							if(inc->b && inc->b->var != -1) {
								flagb = 1;
								memLocB = memoryLocate[inc->b->var];
							}
							int memLocC, flagc = 0;
							if(inc->c && inc->c->var != -1) {
								flagc = 1;
								memLocC = memoryLocate[inc->c->var];
							}
							if(inc->next) {
								int i = 0;
								for(; i < p->cnt; i++) {
									inc->next->liveness[i] = inc->liveness[i];
								}
								if(isAssign(inc->type) && flaga && memLocA <= 0) {
									inc->next->liveness[-memLocA] = 0;
								}
								if(!isAssign(inc->type) && flaga && memLocA <= 0) {
									inc->next->liveness[-memLocA] = 1;
								}
								if(flagb && memLocB <= 0) {
									inc->next->liveness[-memLocB] = 1;
								}
								if(flagc && memLocC <= 0) {
									inc->next->liveness[-memLocC] = 1;
								}
							}else {
								if(blk->pres && blk->pres->y->incs) {
									if(!isAssign(inc->type) && flaga && memLocA <= 0) {
										struct Edge * edge = blk->pres;
										while(edge) {
											if(edge->y->incs->liveness[-memLocA] == 0) {
												edge->y->incs->liveness[-memLocA] = 1;
												changed = 1;
											}
											edge = edge->next;
										}

									}
									if(flagb && memLocB <= 0) {
										struct Edge * edge = blk->pres;
										while(edge) {
											if(edge->y->incs->liveness[-memLocB] == 0) {
												edge->y->incs->liveness[-memLocB] = 1;
												changed = 1;
											}
											edge = edge->next;
										}

									}
									if(flagc && memLocC <= 0) {
										struct Edge * edge = blk->pres;
										while(edge) {
											if(edge->y->incs->liveness[-memLocC] == 0) {
												edge->y->incs->liveness[-memLocC] = 1;
												changed = 1;
											}
											edge = edge->next;
										}

									}
								}
								struct Edge * edge = blk->pres;
								while(edge) {
									int i = 0;
									for(; i < p->cnt; i++) {
										if(edge->y->incs->liveness[i] == 0 && inc->liveness[i] == 1) {
											edge->y->incs->liveness[i] = 1;
											changed = 1;
										}
									}
									edge = edge->next;
								}
							}
							inc = inc->next;
						}
						blk = blk->next;
					}
				}
				*/	
				blk = p->blocks;
				while(blk) {
					struct InterCode * inc = blk->incs, * prev = 0;
					while(inc) {
						if(inc->type == DECL_INT || inc->type == DECL_CHAR || inc->type == DECL_POINTER || inc->type == GET_ARGU || isAssign(inc->type) && inc->type != CALL && inc->type != GETCHAR && inc->a && inc->a->var != -1 && memoryLocate[inc->a->var] <= 0 && inc->liveness[-memoryLocate[inc->a->var]] == 0) {
							deadCode = 1;
							if(prev == 0) {

								blk->incs = inc->next;
							}else {
								prev->next = inc->next;
							}
							inc = inc->next;
						}else {
							prev = inc;
							inc = inc->next;
						}
					}
					if(blk->incs == 0) {
						blk->incs = newInterCode();
						blk->incs->type = NOP;
						blk->incs->liveness = (int *)malloc(sizeof(int) * p->cnt);
					}
					blk = blk->next;
				}
			}
			p = p->next;
		}
		p = funcList;
		dangerous = (int *)malloc(sizeof(int) * totIndex);
		for(i = 0; i < totIndex; i++) {
			dangerous[i] = 0;
		}
		if(DEBUG) {
			printf("analysing dangerous information\n");
		}
		while(p) {
			struct Block * blk = p->blocks, * prevBlock = 0;
			while(blk) {
				struct InterCode * inc = blk->incs, *inc1;//把指令顺序正过来
				blk->incs = 0;
				while(inc) {

					if(inc->type == ASSIGN_ADDRESS_OF) {
						dangerous[inc->b->var] = 1;
					}

					inc1 = inc->next;
					inc->next = blk->incs;
					blk->incs = inc;
					inc = inc1;
				}
				prevBlock = blk;
				blk = blk->next;
			}
			blk = p->blocks;
			p->blocks = 0;
			while(blk) {//把blocks的顺序正过来
				prevBlock = blk->next;
				blk->next = p->blocks;
				p->blocks = blk;
				blk = prevBlock;
			}
			p = p->next;
		}
		int * intervalL = (int *)malloc(sizeof(int) * totIndex), * intervalR = (int *)malloc(sizeof(int) * totIndex);
		int * o = (int *)malloc(sizeof(int) * totIndex);
		int * inUse = (int *)malloc(sizeof(int) * maxReg);
		p = funcList;
		int localMaxReg = 0;//函数最多使用几个寄存器.
		while(p) {
			if(DEBUG) {
				printf("linear scaning for %s\n", p->f->name);
			}
			p->regAlloc = (int *)malloc(sizeof(int) * p->cnt);
			for(i = 0; i < p->cnt; i++) {
				p->regAlloc[i] = -1;
			}
			p = p->next;
			continue;
			struct Block * blk = p->blocks;
			p->numReg = -1;//用到的寄存器数量
			int stamp = 0;//时间.
			for(i = 0; i < p->cnt; i++) {
				intervalL[i] = infi;
				intervalR[i] = -infi;
			}
			while(blk) {
				struct InterCode * inc = blk->incs;
				while(inc) {
					stamp++;
					for(i = 0; i < p->cnt; i++) {
						if(inc->liveness[i]) {
							intervalL[i] = min(intervalL[i], stamp);
							intervalR[i] = max(intervalR[i], stamp);
						}
					}
					inc = inc->next;
				}
				blk = blk->next;
			}
			struct List * q = p->f->occupy;
			while(q) {
				int memLoc = memoryLocate[q->value];
				if(memLoc > 0) {
					intervalL[memLoc - 1] = infi;
				}else if(dangerous[q->value]) {
					intervalL[-memLoc] = infi;
				}
				q = q->next;
			}
			for(i = 0; i < p->cnt; i++) {
				o[i] = i;
			}
			for(i = 0; i < p->cnt; i++) {
				int j;
				for(j = i + 1; j < p->cnt; j++) {
					if(intervalL[o[i]] > intervalL[o[j]]) {
						int tmp = o[i];
						o[i] = o[j];
						o[j] = tmp;
					}
				}
			}
			for(i = 0; i < maxReg; i++) {
				inUse[i] = -1;
			}
			for(i = 0; i < p->cnt; i++) {
				if(intervalL[o[i]] == infi) {
					continue;
				}
				int ok = 0;
				int j;
				for(j = 0; j < maxReg; j++) {
					if(inUse[j] && intervalR[inUse[j]] < intervalL[o[i]]) {
						inUse[j] = -1;
					}
					if(inUse[j] == -1) {
						inUse[j] = o[i];
						p->regAlloc[o[i]] = j;
						ok = 1;
						p->numReg = max(p->numReg, j);
						break;
					}
				}
				if(ok == 0) {
					int spill = 0;
					for(j = 0; j < maxReg; j++) {
						if(intervalR[inUse[j]] > intervalR[inUse[spill]]) {
							spill = j;
						}
					}
					if(intervalR[inUse[spill]] > intervalR[o[i]]) {
						p->regAlloc[inUse[spill]] = -1;
						inUse[spill] = o[i];
						p->regAlloc[o[i]] = spill;
					}else {
						p->regAlloc[o[i]] = -1;
					}
				}
			}
			p->numReg++;
			localMaxReg = max(localMaxReg, p->numReg);
			p = p->next;
		}
		if(DEBUG) {
			printf("distributing regs for global vars...\n");
		}

		regAlloc = (int *)malloc(sizeof(int) * globalVars);
		for(i = 0; i < globalVars; i++) {
			regAlloc[i] = -1;
		}
		struct List * tmp = data;
		int localRegLim = localMaxReg;
		while(tmp && localMaxReg < maxReg) {
			int i = tmp->mul;
			if(!dangerous[i] && memoryLocate[i] > 0) {
				regAlloc[memoryLocate[i] - 1] = localMaxReg;
				localMaxReg++;
			}
			tmp = tmp->next;
		}
		p = funcList;
		int * valid;
		valid = (int *)malloc(sizeof(int) * localRegLim);
		while(p) {
			if(DEBUG) {
				printf("secondary regs alloc for %s\n", p->f->name);
			}

			struct Block * blk = p->blocks;
			while(blk) {
				struct InterCode * inc = blk->incs;
				while(inc) {
					inc->regValid = (int *)malloc(sizeof(int) * localRegLim);
					for(i = 0; i < localRegLim; i++) {
						inc->regValid[i] = 1;
					}
					inc = inc->next;
				}
				blk = blk->next;
			}
			struct List * q = p->f->occupy;
			while(q) {
				int memLoc = -memoryLocate[q->value];
				if(memLoc < 0) {
					q = q->next;
					continue;
				}
				int reg = p->regAlloc[memLoc];
				if(reg == -1) {
					q = q->next;
					continue;
				}
				blk = p->blocks;
				while(blk) {
					struct InterCode * inc = blk->incs;
					while(inc) {
						inc->regValid[reg] &= !inc->liveness[memLoc];
						inc = inc->next;
					}
					blk = blk->next;
				}
				q = q->next;
			}
			q = p->f->occupy;
			while(q) {
				int memLoc = -memoryLocate[q->value];
				if(memLoc < 0 || p->regAlloc[memLoc] != -1 || dangerous[q->value]) {
					q = q->next;
					continue;
				}
				for(i = 0; i < localRegLim; i++) {
					valid[i] = 1;
				}
				struct Block * blk = p->blocks;
				int appear = 0;
				while(blk) {
					struct InterCode * inc = blk->incs;
					while(inc) {
						if(inc->liveness[memLoc]) {
							appear = 1;
							for(i = 0; i < localRegLim; i++) {
								valid[i] &= inc->regValid[i];
							}
						}
						inc = inc->next;
					}
					blk = blk->next;
				}
				int regChoose = -1;
				for(i = 0; i < localRegLim; i++) {
					if(valid[i]) {
						regChoose = i;
						break;
					}
				}
				if(regChoose == -1 || !appear) {
					q = q->next;
					continue;
				}
				p->regAlloc[memLoc] = regChoose;
				blk = p->blocks;
				while(blk) {
					struct InterCode * inc = blk->incs;
					while(inc) {
						if(inc->liveness[memLoc]) {
							inc->regValid[regChoose] = 0;
						}
						inc = inc->next;
					}
					blk = blk->next;
				}
				q = q->next;
			}
			p = p->next;
		}
		if(DEBUG) {
			printf("output .s file:\n");
			return 0;
		}
		mapReg = (int *)malloc(sizeof(int) * maxReg);
		//mapReg[0] = 3, 5, 6, 
		mapReg[0] = 3;
		for(i = 1; i < maxReg; i++) {
			mapReg[i] = i + 4;
		}
		printf(".text\n");
		p = funcList;
		regAssign = (int *)malloc(sizeof(int) * maxReg);
		while(p) {
			if(strcmp(p->f->name, CHIEF)) {
				printf("func%d%s:\n", p->f, p->f->name);
				////////////////$sp, $fp
				printf("\taddiu $fp, $fp, %d\n", -(p->cnt - p->cntArgu + p->numReg + 2) * 4);//fp = gp
				
				int i = 0;
				for(; i < p->numReg; i++) {
					printf("\tsw $%d, %d($fp)\n", mapReg[i], i * 4);//顶部备份寄存器!
				}
				printf("\tsw $31, %d($fp)\n", p->numReg * 4);
				printf("\tsw $sp, %d($fp)\n", p->numReg * 4 + 4);
				printf("\taddiu $sp, $fp, %d\n", (p->numReg + 2) * 4);
				struct Variable * var = p->f->argu;
				while(var) {
					int memLoc = memoryLocate[var->index];
					if(p->regAlloc[-memLoc] != -1) {
						printf("\tlw $%d, %d($sp)\n", mapReg[p->regAlloc[-memLoc]], -memLoc * 4);
					}
					var = var->next;
				}
				
			}else {
				printf("\t.globl main\nmain:\n\tmove $fp, $sp\n");
				struct List * tmp = data;
				while(tmp) {
					if(regAlloc[memoryLocate[tmp->mul] - 1] != -1) {
						printf("\tla $%d, d%d\n", mapReg[regAlloc[memoryLocate[tmp->mul] - 1]], tmp->mul);
					}
					tmp = tmp->next;
				}
			}
			for(i = 0; i < maxReg; i++) {
				regAssign[i] = -1;
			}
			struct Block * blk = p->blocks;
			while(blk) {
				printf("block%d:\n", blk->index);
				struct InterCode * inc = blk->incs;
				while(inc) {

					int a = -1, b = -1, c = -1;
					if(inc->type == ASSIGN_ADDRESS_OF) {
						if(isAssign(inc->type)) {
							a = locateTarget(p, inc->a->var, inc->liveness);
						}
						if(memoryLocate[inc->b->var] > 0) {
							printf("\tla $%d, d%d\n", a, inc->b->var);
						}else {
							printf("\taddiu $%d, $sp, %d\n", a, -memoryLocate[inc->b->var] * 4);
						}
					}else {
						oo = 0;
						if(!isAssign(inc->type) && inc->a && inc->a->var != -1) {
							a = load(p, inc->a->var, inc->liveness);
						}
						if(inc->b && inc->b->var != -1) {
							b = load(p, inc->b->var, inc->liveness);
						}
						if(inc->c && inc->c->var != -1) {
							c = load(p, inc->c->var, inc->liveness);
						}
						if(isAssign(inc->type)) {
							a = locateTarget(p, inc->a->var, inc->liveness);
						}
					}
					int t = inc->type;
					if(t == MALLOC) {
						printf("\tli $v0, 9\n");
						if(inc->b->var == -1) {
							printf("\tli $a0, %d\n", inc->b->idx);
						}else {
							printf("\tmove $a0, $%d\n", b);
						}
						printf("\tsyscall\n");
						if(a != 2) {
							printf("\tmove $%d, $v0\n", a);
						}
					}else if(t == GETCHAR) {
						printf("\tli $v0, 12\n\tsyscall\n");
						if(a != 2) {
							printf("\tmove $%d, $v0\n", a);
						}
					}else if(t == PUTCHAR) {
						printf("\tli $v0, 11\n");
						if(inc->a->var != -1) {
							printf("\tmove $a0, $%d\n", a);
						}else {
							printf("\tli $a0, %d\n", inc->a->idx);
						}
						printf("\tsyscall\n");
					}else if(t == NOP) {
						printf("\tnop\n");
					}else if(t == ASSIGN_ADD) {
						if(inc->b->var == -1) {
							struct InterCodeOperand * tmp = inc->b;
							inc->b = inc->c;
							inc->c = tmp;
							int tmp1 = b;
							b = c;
							c = tmp1;
						}
						if(inc->c->var == -1 && inc->b->var == -1) {
							ERROR(100);
						}
						if(inc->c->var != -1) {
							printf("\tadd $%d, $%d, $%d\n", a, b, c);
						}else {
							printf("\taddiu $%d, $%d, %d\n", a, b, inc->c->idx);
						}
					}else if(t == GOTO) {
						printf("\tb block%d\n", jumpToBlock[inc->n]->index);
					}else if(t == LABEL) {
						printf("!!!!LABEL!!!!\n");
					}else if(t == IF_GOTO) {
						if(inc->a->var == -1) {
							ERROR(101);
						}
						printf("\tbne $0, $%d, block%d\n", a, jumpToBlock[inc->n]->index);
					}else if(t == IF_FALSE_GOTO) {
						if(inc->a->var == -1) {
							ERROR(102);
						}
						printf("\tbeq $0, $%d, block%d\n", a, jumpToBlock[inc->n]->index);
					}else if(t == ASSIGN_LOGICAL_NOT) {
						if(inc->b->var == -1) {
							printf("\tli $%d, %d\n", a, !inc->b->idx);
						}else {
							printf("\tseq $%d, $0, $%d\n", a, b);
						}
					}else if(t == ASSIGN_NOT) {
						if(inc->b->var == -1) {
							printf("\tli $%d, %d\n", a, ~inc->b->idx);
						}else {
							printf("\tnot $%d, $%d\n", a, b);
						}
					}else if(t == ASSIGN_NEGATE) {
						if(inc->b->var == -1) {
							printf("\tli $%d, %d\n", a, -inc->b->idx);
						}else {
							printf("\tsub $%d, $0, $%d\n", a, b);
						}
					}else if(t == ASSIGN || t == ASSIGN_CHAR || t == ASSIGN_ADDRESS || t == INT_TO_CHAR || t == CHAR_TO_INT) {
						if(inc->b->var == -1) {
							printf("\tli $%d, %d\n", a, inc->b->idx);
						}else {
							if(a != b) {
								printf("\tmove $%d, $%d\n", a, b);
							}
						}
					}else if(t == ASSIGN_INCLUSIVE_OR) {
						if(inc->b->var == -1) {
							struct InterCodeOperand * tmp = inc->b;
							inc->b = inc->c;
							inc->c = tmp;
							int tmp1 = b;
							b = c;
							c = tmp1;
						}
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(103);
						}
						if(inc->c->var == -1) {
							printf("\tori $%d, $%d, %d\n", a, b, inc->c->idx);
						}else {
							printf("\tor $%d, $%d, $%d\n", a, b, c);
						}
					}else if(t == ASSIGN_EXCLUSIVE_OR) {
						if(inc->b->var == -1) {
							struct InterCodeOperand * tmp = inc->b;
							inc->b = inc->c;
							inc->c = tmp;
							int tmp1 = b;
							b = c;
							c = tmp1;
						}
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(104);
						}
						if(inc->c->var == -1) {
							printf("\txori $%d, $%d, %d\n", a, b, inc->c->idx);
						}else {
							printf("\txor $%d, $%d, $%d\n", a, b, c);
						}
					}else if(t == ASSIGN_AND) {
						if(inc->b->var == -1) {
							struct InterCodeOperand * tmp = inc->b;
							inc->b = inc->c;
							inc->c = tmp;
							int tmp1 = b;
							b = c;
							c = tmp1;
						}
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(105);
						}
						if(inc->c->var == -1) {
							printf("\tandi $%d, $%d, %d\n", a, b, inc->c->idx);
						}else {
							printf("\tand $%d, $%d, $%d\n", a, b, c);
						}
	
					}else if(t == ASSIGN_SHR) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(106);
						}
						if(inc->c->var == -1) {
							printf("\tsra $%d, $%d, %d\n", a, b, inc->c->idx);
						}else {
							if(inc->b->var == -1) {
								printf("\tli $v0, %d\n", inc->b->idx);
								b = 2;
							}
							printf("\tsrav $%d, $%d, $%d\n", a, b, c);
						}
					}else if(t == ASSIGN_SHL) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(107);
						}
						if(inc->c->var == -1) {
							printf("\tsll $%d, $%d, %d\n", a, b, inc->c->idx);
						}else {
							if(inc->b->var == -1) {
								printf("\tli $v0, %d\n", inc->b->idx);
								b = 2;
							}
							printf("\tsllv $%d, $%d, $%d\n", a, b, c);
						}
					}else if(t == ASSIGN_SUB) {
						if(inc->c->var == -1) {
							printf("\taddiu $%d, $%d, %d\n", a, b, -inc->c->idx);
						}else {
							if(inc->b->var == -1 && inc->c->var == -1) {
								ERROR(108);
							}
							if(inc->b->var == -1) {
								printf("\tli $v0, %d\n", inc->b->idx);
								b = 2;
							}
							printf("\tsub $%d, $%d, $%d\n", a, b, c);
						}
					}else if(t == CALL) {
						printf("\tjal func%d%s\n", inc->func, inc->func->name);
						//printf("a = %d\n", a);
						if(a != 2 && !isVoid(inc->func->rtn)) {
							printf("\tmove $%d, $v0\n", a);
						}
					}else if(t == ASSIGN_MOD) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(109);
						}
						if(inc->c->var == -1) {
							printf("\tli $v0, %d\n", inc->c->idx);
							c = 2;
						}else if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\trem $%d, $%d, $%d\n", a, b, c);
					}else if(t == ASSIGN_DIV) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(110);
						}
						
						if(inc->c->var == -1) {
							printf("\tli $v0, %d\n", inc->c->idx);
							c = 2;
						}else if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\tdiv $%d, $%d, $%d\n", a, b, c);
					}else if(t == ASSIGN_MUL) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(111);
						}
						
						if(inc->c->var == -1) {
							printf("\tli $v0, %d\n", inc->c->idx);
							c = 2;
						}else if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\tmul $%d, $%d, $%d\n", a, b, c);
					}else if(t == ASSIGN_NOT_EQUAL_TO) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(112);
						}
						
						if(inc->c->var == -1) {
							printf("\tli $v0, %d\n", inc->c->idx);
							c = 2;
						}else if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\tsne $%d, $%d, $%d\n", a, b, c);
					}else if(t == ASSIGN_EQUAL_TO) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(113);
						}
						
						if(inc->c->var == -1) {
							printf("\tli $v0, %d\n", inc->c->idx);
							c = 2;
						}else if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\tseq $%d, $%d, $%d\n", a, b, c);
					}else if(t == ASSIGN_GREATER_THAN_OR_EQUAL_TO) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(114);
						}
						if(inc->c->var == -1) {
							printf("\tli $v0, %d\n", inc->c->idx);
							c = 2;
						}
						if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\tsge $%d, $%d, $%d\n", a, b, c);
					}else if(t == ASSIGN_GREATER_THAN) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(115);
						}
						if(inc->b->var == -1) {
							printf("\tslti $%d, $%d, %d\n", a, c, inc->b->idx);
						}else {
							if(inc->c->var == -1) {
								printf("\tli $v0, %d\n", inc->c->idx);
								c = 2;
							}
							printf("\tsgt $%d, $%d, $%d\n", a, b, c);
						}
					}else if(t == ASSIGN_LESS_THAN_OR_EQUAL_TO) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(116);
						}
						if(inc->c->var == -1) {
							printf("\tli $v0, %d\n", inc->c->idx);
							c = 2;
						}else if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\tsle $%d, $%d, $%d\n", a, b, c);
					}else if(t == ASSIGN_LESS_THAN) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(117);
						}
						if(inc->c->var == -1 && inc->c->idx >= -32768 && inc->c->idx < 32768) {
							printf("\tslti $%d, $%d, %d\n", a, b, inc->c->idx);
						}else {
							if(inc->c->var == -1) {
								printf("\tli $v0, %d\n", inc->c->idx);
								c = 2;
							}
							if(inc->b->var == -1) {
								printf("\tli $v0, %d\n", inc->b->idx);
								b = 2;
							}
							printf("\tslt $%d, $%d, $%d\n", a, b, c);
						}
					}else if(t == ASSIGN_LOGIC_OR) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(118);
						}
						if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						if(inc->c->var == -1) {
							printf("\tli $v0, %d\n", inc->c->idx);
							c = 2;
						}
						printf("\tor $%d, $%d, $%d\n", a, b, c);
						printf("\tsne $%d, $%d, $0\n", a, a);
					}else if(t == ASSIGN_LOGIC_AND) {
						if(inc->b->var == -1 && inc->c->var == -1) {
							ERROR(119);
						}
						if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						if(inc->c->var == -1) {
							printf("\tli $v0, %d\n", inc->c->idx);
							c = 2;
						}
						if(b == 4) {
							printf("\tsne $a0, $%d, $0\n", b);
							printf("\tsne $v0, $%d, $0\n", c);
						}else {
							printf("\tsne $a0, $%d, $0\n", c);
							printf("\tsne $v0, $%d, $0\n", b);	
						}
						printf("\tand $%d, $a0, $v0\n", a);
					}else if(t == ASSIGN_DEREF || t == ASSIGN_DEREF_ADDRESS) {
						if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\tlw $%d, 0($%d)\n", a, b);
					}else if(t == DEREF_ASSIGN || t == DEREF_ASSIGN_ADDRESS) {
						if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\tsw $%d, 0($%d)\n", b, a);
					}else if(t == DEREF_ASSIGN_CHAR) {
						if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\tsb $%d, 0($%d)\n", b, a);
					}else if(t == RETURN) {
						if(inc->a->var == -1) {
							printf("\tli $v0, %d\n", inc->a->idx);
						}else {
							if(a != 2) {
								printf("\tmove $v0, $%d\n", a);
							}
						}
						printf("\tb return%d%s\n", p->f, p->f->name);
					}else if(t == ASSIGN_ADDRESS_OF) {
						//do nothing
					}else if(t == ARGU) {
						if(inc->a->var == -1) {
							printf("\tli $v0, %d\n", inc->a->idx);
							a = 2;
						}
						printf("\taddiu $fp, $fp, -4\n");
						printf("\tsw $%d, 0($fp)\n", a);
					}else if(t == EXIT) {
						printf("\tli $v0, 10\n");
						printf("syscall\n");
					}else if(t == VOID_RETURN) {
						printf("b return%d%s\n", p->f, p->f->name);
					}else if(t == ASSIGN_DEREF_CHAR) {
						if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\tlb $%d, 0($%d)\n", a, b);
					}else if(t == PUTINT) {
						printf("\tli $v0, 1\n");
						if(inc->a->var == -1) {
							printf("\tli $a0, %d\n", inc->a->idx);
						}else {
							if(a != 4) {
								printf("\tmove $a0, $%d\n", a);
							}
						}
						printf("\tsyscall\n");
					}else if(t == LD) {
						if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\tlw $%d, %d($%d)\n", a, inc->n, b);
					}else if(t == LD_CHAR) {
						if(inc->b->var == -1) {
							printf("\tli $v0, %d\n", inc->b->idx);
							b = 2;
						}
						printf("\tlb $%d, %d($%d)\n", a, inc->n, b);
					}else if(t == ST) {
						if(inc->a->var == -1) {
							printf("\tli $v0, %d\n", inc->a->idx);
							a = 2;
						}
						if(inc->b->var == -1) {
							if(oo == 1) {
								printf("\tli $v0, %d\n", inc->b->idx);
								b = 2;
							}else {
								printf("\tli $a0, %d\n", inc->b->idx);
								b = 4;
							}
						}
						printf("\tsw $%d, %d($%d)\n", b, inc->n, a);
					}else if(t == ST_CHAR) {
						if(inc->a->var == -1) {
							printf("\tli $v0, %d\n", inc->a->idx);
							a = 2;
						}
						if(inc->b->var == -1) {
							if(oo == 1) {
								printf("\tli $v0, %d\n", inc->b->idx);
								b = 2;
							}else {
								printf("\tli $a0, %d\n", inc->b->idx);
								b = 4;
							}
						}
						printf("\tsb $%d, %d($%d)\n", b, inc->n, a);
					}else if(t == ASSIGN_STR) {
						printf("\tla $%d, str%d\n", a, inc->n);
					}else if(t == ASSIGN_DATA) {
						printf("\tla $v0, data%d\n", inc->n);
					}else {
						//printf("wtf\n");
					}
					if(isAssign(inc->type) && a == 2 && !(inc->type == CALL && isVoid(inc->func->rtn))) {
						int memLoc = memoryLocate[inc->a->var];
						if(memLoc > 0) {
							printf("\tsw $%d, d%d\n", a, inc->a->var);
						}else {
							printf("\tsw $%d, %d($sp)\n", a, -memLoc * 4);
						}
					}
					inc = inc->next;
				}
				blk = blk->next;
			}
			if(strcmp(p->f->name, CHIEF)) {
				int i = 0;
				printf("return%d%s:\n", p->f, p->f->name);
				for(; i < p->numReg; i++) {
					printf("\tlw $%d, %d($fp)\n", mapReg[i], i * 4);
				}
				printf("\tlw $ra, %d($fp)\n", p->numReg * 4);
				printf("\tlw $sp, %d($fp)\n", p->numReg * 4 + 4);
				printf("\taddiu $fp, $fp, %d\n", (p->cnt + p->numReg + 2) * 4);
				printf("\tjr $ra\n");
			}else {
				printf("\tjal func%d%s\n", funcMain->f, funcMain->f->name);
			
				printf("\tli $v0, 10\n\tsyscall\n");
				printf("\tjr $ra\n");
			}
			p = p->next;
		}
		printData();
	}

	//fclose(stdin);
	return 0;
}
//totERROR = 1 ~ 99p->numReg = max(p->numReg, j);@
