#include <stdio.h>
#include <iostream>

#include "semantico.h"
#include "regras.h"

Semantico::Semantico(Lexico* analisadorLexico){
	this->analisadorLexico = analisadorLexico;
	this->functionVarPos = 0;
	this->nFuncs = 0;

	this->out = fopen("ssl.ftw","w+");
	if(this->out == NULL){
		printf("There was an error when creating the this->output file.\n");;
	}
}

Semantico::~Semantico(){
	// fclose(this->out);
	// this->out = NULL;
}

int Semantico::new_label(){
	static int label_number = 0;
	return label_number++;
}

void Semantico::parseRule(int rule){
	static int name,n,l,l1,l2;
	static PObject p,t,f;
	static t_attrib IDD_static,IDU_static,ID_static,T_static,LI_static,LI0_static,LI1_static,TRU_static,FALS_static,STR_static,CHR_static,NUM_static,DC_static,DC0_static,DC1_static,LP_static,LP0_static,LP1_static,E_static,E0_static,E1_static,L_static,L0_static,L1_static,R_static,R0_static,R1_static,Y_static,Y0_static,Y1_static,F_static,F0_static,F1_static,LV_static,LV0_static,LV1_static,MC_static,LE_static,LE0_static,LE1_static,MT_static,ME_static,MW_static,NB_static;

	Regras regra = static_cast<Regras>(rule);

	// printf("calling for rule %d\n", rule);
	// RegraOperator regOp = RegraOperator();
	// string regraString = regOp.getRegraString(regra);
	// cout << "regra " << regraString << endl;

	switch(regra){
		case P0:
			break;
		case LDE0:
			break;
		case LDE1:
			break;
		case DE0:
			break;
		case DE1:
			break;
		case T0: // T-> 'integer'
			T_static.T.type = pInt;
			T_static.type = T;
			T_static.nSize = 1;
			this->semanticoStack.push(T_static);
			break;
		case T1: // T -> 'char'
			T_static.T.type = pChar;
			T_static.type = T;
			T_static.nSize = 1;
			this->semanticoStack.push(T_static);
			break;
		case T2: // T -> 'boolean'
			T_static.T.type = pBool;
			T_static.type = T;
			T_static.nSize = 1;
			this->semanticoStack.push(T_static);
			break;
		case T3: // T -> 'string'
			T_static.T.type = pString;
			T_static.type = T;
			T_static.nSize = 1;
			this->semanticoStack.push(T_static);
			break;
		case T4: // T -> IDU
			IDU_static = this->semanticoStack.top();
			p = IDU_static.ID.obj;
			this->semanticoStack.pop();

			if(IS_TYPE_KIND(p->kind) || p->kind == KindUniversal){
				T_static.T.type = p;
				if(p->kind == KindAliasType){
					T_static.nSize = p->Alias.nSize;
				}
				else if(p->kind == KindArrayType){
					T_static.nSize = p->Array.nSize;
				}
				else if(p->kind == KindStructType){
					T_static.nSize = p->Struct.nSize;
				}
			}
			else{
				T_static.T.type = pUniversal;
				T_static.nSize = 0;
			}
			T_static.type = T;
			this->semanticoStack.push(T_static);
			break;
		case DT0: // DT -> 'type' IDD '=' 'array' '[' NUM ']' 'of' T
			T_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			NUM_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			IDD_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			p = IDD_static.ID.obj;
			n = NUM_static.NUM.val;
			t = T_static.T.type;

			p->kind = KindArrayType;
			p->Array.nNumElems = n;
			p->Array.pElemType = t;
			p->Array.nSize = n * T_static.nSize;
			break;
		case DT1: // DT -> 'type' IDD '=' 'struct' NB '{' DC '}'
			DC_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			IDD_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			p = IDD_static.ID.obj;
			p->kind = KindStructType;
			p->Struct.pFields = DC_static.DC.list;
			p->Struct.nSize = DC_static.nSize;
			end_block();
			break;
		case DT2: // DT -> 'type' IDD '=' T
			T_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			IDD_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			p = IDD_static.ID.obj;
			t = T_static.T.type;

			p->kind = KindAliasType;
			p->Alias.pBaseType = t;
			p->Alias.nSize = T_static.nSize;
			break;
		case DC0: // DC -> DC ';' LI ':' T
			T_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			LI_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			DC1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			p = LI_static.LI.list;
			t = T_static.T.type;
			n = DC1_static.nSize;

			while( p != NULL && p->kind == KindUndefined){
				p->kind = KindField;
				p->Field.pType = t;
				p->Field.nIndex = n;
				p->Field.nSize = T_static.nSize;
				n = n + T_static.nSize;
				p = p->next;
			}

			DC0_static.DC.list = DC1_static.DC.list;
			DC0_static.nSize = n;
			DC0_static.type = DC;
			this->semanticoStack.push(DC0_static);
			break;
		case DC1: // DC -> LI ':' T
			T_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			LI_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			p = LI_static.LI.list;
			t = T_static.T.type;
			n = 0;
			while( p != NULL && p->kind == KindUndefined){
				p->kind = KindField;
				p->Field.pType = t;
				p->Field.nSize = T_static.nSize;
				p->Field.nIndex = n;
				n = n + T_static.nSize;
				p = p->next;
			}
			DC_static.DC.list = LI_static.LI.list;
			DC_static.nSize = n;
			DC_static.type = DC;
			this->semanticoStack.push(DC_static);
			break;
		case DF0: // DF -> 'function' IDD NF '(' LP ')' ':' T MF B
			end_block();
			break;
		case LP0: // LP -> LP ',' IDD ':' T
			T_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			IDD_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			LP1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			p = IDD_static.ID.obj;
			t = T_static.T.type;
			n = LP1_static.nSize;

			p->kind = KindParam;
			p->Param.pType = t;
			p->Param.nIndex = n;
			p->Param.nSize = T_static.nSize;

			LP0_static.LP.list = LP1_static.LP.list;
			LP0_static.nSize = n + T_static.nSize;
			LP0_static.type = LP;
			this->semanticoStack.push(LP0_static);
			break;
		case LP1: // LP -> IDD ':' T
			T_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			IDD_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			p = IDD_static.ID.obj;
			t = T_static.T.type;
			p->kind = KindParam;
			p->Param.pType = t;
			p->Param.nIndex = 0;
			p->Param.nSize = T_static.nSize;
			LP_static.LP.list = p;
			LP_static.nSize = T_static.nSize;
			LP_static.type = LP;

			this->semanticoStack.push(LP_static);
			break;
		case B0: // B -> '{' LDV LS '}'
			{
				fprintf(this->out,"END_FUNC\n");

				int currentPos = ftell(this->out);
				fseek(this->out, this->functionVarPos, SEEK_SET);
				fprintf(this->out, "%02d",f->Function.nVars);
				fseek(this->out, currentPos, SEEK_SET);
				break;
			}
		case LDV0: // LDV -> LDV DV
		case LDV1: // LDV -> DV
		case LS0: // LS -> LS S
		case LS1: // LS -> S
			break;
		case DV0: // DV -> 'var' LI ':' T ';'
			T_static = this->semanticoStack.top();
			t = T_static.T.type;
			this->semanticoStack.pop();
			LI_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			p = LI_static.LI.list;
			n = this->curFunction->Function.nVars;

			while(p != NULL && p->kind == KindUndefined){
				p->kind = KindVar;
				p->Var.pType = t;
				p->Var.nSize = T_static.nSize;
				p->Var.nIndex = n;

				n += T_static.nSize;
				p = p->next;
			}

			this->curFunction->Function.nVars = n;
			break;
		case LI0: // LI -> LI ',' IDD
			IDD_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			LI1_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			LI0_static.LI.list = LI1_static.LI.list;
			LI0_static.type = LI;
			this->semanticoStack.push(LI0_static);
			break;
		case LI1: // LI -> IDD
			IDD_static = this->semanticoStack.top();
			LI_static.LI.list = IDD_static.ID.obj;
			LI_static.type = LI;
			this->semanticoStack.pop();
			this->semanticoStack.push(LI_static);
			break;
		case S0: // S -> M
			break;
		case S1: // S -> U
			break;
		case U0: // U -> 'if' '(' E ')' MT S
			MT_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			E_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			t = E_static.E.type;
			if( !check_types(t,pBool)){printf("error2\n");}

			fprintf(this->out,"L%d\n",MT_static.MT.label);
			break;
		case U1: // U -> 'if' '(' E ')' MT M 'else' ME U
			ME_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			MT_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			E_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			l = ME_static.ME.label;

			t = E_static.E.type;
			if( !check_types(t,pBool)){printf("error3\n");}
			fprintf(this->out,"L%d\n",l);
			break;
		case M0: // M -> 'if' '(' E ')' MT M 'else' ME M
			ME_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			MT_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			E_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			l = ME_static.ME.label;

			t = E_static.E.type;
			if( !check_types(t,pBool)){printf("error4\n");}
			fprintf(this->out,"L%d\n",l);
			break;
		case M1: // M -> 'while' MW '(' E ')' MT M
			MT_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			E_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			MW_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			l1 = MW_static.MW.label;
			l2 = MT_static.MT.label;

			t = E_static.E.type;
			if( !check_types(t,pBool)){printf("error5\n");}

			fprintf(this->out,"\tJMP_BW L%d\nL%d\n",l1,l2);
			break;
		case M2: // M -> 'do' MW M 'while' '(' E ')' ';'
			E_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			MW_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			l = MW_static.MW.label;

			t = E_static.E.type;
			if( !check_types(t,pBool)){printf("error6\n");}

			fprintf(this->out,"\tNOT\n\tTJMP_BW L%d\n",l);
			break;
		case M3: // M -> NB B
			end_block();
			break;
		case M4: // M -> LV '=' E ';'
			E_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			LV_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			t = LV_static.LV.type;

			//if(!check_types(LV_static.LV.type, E_static.E.type)){//Error}
			fprintf(this->out,"\tSTORE_REF %d\n",t->Type.nSize);
			break;

		case M5: // M -> 'break' ';'
		case M6: // M -> 'continue' ';'
			break;
		case E0: // E -> E '&&' L
			L_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			E1_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			//if( !check_types(E1_static.E.type,pBool)){//Error}

			//if( !check_types(L_static.L.type,pBool)){//Error}

			E0_static.E.type = pBool;
			E0_static.type = E;
			this->semanticoStack.push(E0_static);
			fprintf(this->out,"\tAND\n");
			break;
		case E1: // E -> E '||' L
			L_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			E1_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			//if( !check_types(E1_._.E.type,pBool)){Error(ERR_BOOL_TYPE_EXPECTED);}

			//if( !check_types(L_._.L.type,pBool)){Error(ERR_BOOL_TYPE_EXPECTED);}

			E0_static.E.type = pBool;
			E0_static.type = E;
			this->semanticoStack.push(E0_static);
			fprintf(this->out,"\tOR\n");
			break;
		case E2: // E -> L
			L_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			E_static.E.type = L_static.L.type;
			E_static.type = E;
			this->semanticoStack.push(E_static);
			break;
		case L0: // L -> L '<' R
			R_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			L1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			//if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
			L0_static.L.type = pBool;
			L0_static.type = L;
			this->semanticoStack.push(L0_static);

			fprintf(this->out,"\tLT\n");
			break;
		case L1: // L -> L '>' R
			R_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			L1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			//if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
			L0_static.L.type = pBool;
			L0_static.type = L;
			this->semanticoStack.push(L0_static);
			fprintf(this->out,"\tGT\n");
			break;
		case L2: // L -> L '<=' R
			R_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			L1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			//if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
			L0_static.L.type = pBool;
			L0_static.type = L;
			this->semanticoStack.push(L0_static);
			fprintf(this->out,"\tLE\n");
			break;
		case L3: // L -> L '>=' R
			R_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			L1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			//if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
			L0_static.L.type = pBool;
			L0_static.type = L;
			this->semanticoStack.push(L0_static);
			fprintf(this->out,"\tGE\n");
			break;
		case L4: // L -> L '==' R
			R_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			L1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			//if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
			L0_static.L.type = pBool;
			L0_static.type = L;
			this->semanticoStack.push(L0_static);
			fprintf(this->out,"\tEQ\n");
			break;
		case L5: // L -> L '!=' R
			R_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			L1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			//if( !check_types(L1_._.L.type,R_._.R.type)){Error(ERR_TYPE_MISMATCH);}
			L0_static.L.type = pBool;
			L0_static.type = L;
			this->semanticoStack.push(L0_static);
			fprintf(this->out,"\tNE\n");
			break;
		case L6: // L -> R
			R_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			L_static.L.type = R_static.R.type;
			L_static.type = L;
			this->semanticoStack.push(L_static);
			break;
		case R0: // R -> R '+' Y
			Y_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			R1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			//if( ! check_types(R1_._.R.type,K_._.K.type)){Error(ERR_TYPE_MISMATCH);}

			//if( !check_types(R1_._.R.type,pInt) && !check_types(R1_._.R.type,pString)){Error(ERR_INVALID_TYPE);}

			R0_static.R.type = R1_static.R.type;
			R0_static.type = R;
			this->semanticoStack.push(R0_static);
			fprintf(this->out,"\tADD\n");
			break;
		case R1: // R -> R '-' Y
			Y_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			R1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			//if( ! check_types(R1_._.R.type,K_._.K.type)){Error(ERR_TYPE_MISMATCH);}

			//if( !check_types(R1_._.R.type,pInt)){Error(ERR_INVALID_TYPE);}

			R0_static.R.type = R1_static.R.type;
			R0_static.type = R;
			this->semanticoStack.push(R0_static);
			fprintf(this->out,"\tSUB\n");
			break;
		case R2: // R -> Y
			Y_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			R_static.R.type = Y_static.Y.type;
			R_static.type = R;
			this->semanticoStack.push(R_static);
			break;
		case Y0: // Y -> Y '*' F
			F_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			Y1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			//if( !check_types(K1_._.K.type,F_._.F.type)){Error(ERR_TYPE_MISMATCH);}

			//if( !check_types(K1_._.K.type,pInt)){Error(ERR_INVALID_TYPE);}

			Y0_static.Y.type = Y1_static.Y.type;
			Y0_static.type = Y;
			this->semanticoStack.push(Y0_static);
			fprintf(this->out,"\tMUL\n");
			break;
		case Y1: // Y -> Y '/' F
			F_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			Y1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			//if( !check_types(K1_._.K.type,F_._.F.type)){Error(ERR_TYPE_MISMATCH);}

			//if( !check_types(K1_._.K.type,pInt)){Error(ERR_INVALID_TYPE);}

			Y0_static.Y.type = Y1_static.Y.type;
			Y0_static.type = Y;
			this->semanticoStack.push(Y0_static);
			fprintf(this->out,"\tDIV\n");
			break;
		case Y2: // Y -> F
			F_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			Y_static.Y.type = F_static.F.type;
			Y_static.type = Y;
			this->semanticoStack.push(Y_static);
			break;
		case F0: // F -> LV
			LV_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			n = LV_static.LV.type->Type.nSize;

			F_static.F.type = LV_static.LV.type;
			F_static.type = F;
			this->semanticoStack.push(F_static);
			fprintf(this->out,"\tDE_REF %d\n",n);
			break;
		case F1: // F -> '++' LV
			LV_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			t = LV_static.LV.type;
			//if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}

			F_static.F.type = pInt;
			F_static.type = F;
			fprintf(this->out,"\tDUP\n\tDUP\n\tDE_REF 1\n");
			fprintf(this->out,"\tINC\n\tSTORE_REF 1\n\tDE_REF 1\n");
			this->semanticoStack.push(F_static);
			break;
		case F2: // F -> '--' LV
			LV_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			t = LV_static.LV.type;
			//if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}

			F_static.F.type = LV_static.LV.type;
			F_static.type = F;
			this->semanticoStack.push(F_static);
			fprintf(this->out,"\tDUP\n\tDUP\n\tDE_REF 1\n");
			fprintf(this->out,"\tDEC\n\tSTORE_REF 1\n\tDE_REF 1\n");
			break;
		case F3: // F -> LV '++'
			LV_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			t = LV_static.LV.type;
			//if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}

			F_static.F.type = LV_static.LV.type;
			F_static.type = F;
			this->semanticoStack.push(F_static);
			fprintf(this->out,"\tDUP\n\tDUP\n\tDE_REF 1\n");
			fprintf(this->out,"\tINC\n\tSTORE_REF 1\n\tDE_REF 1\n");
			fprintf(this->out,"\tDEC\n");
			break;
		case F4: // F -> LV '--'
			LV_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			t = LV_static.LV.type;
			//if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}

			F_static.F.type = t;
			F_static.type = F;
			this->semanticoStack.push(F_static);
			fprintf(this->out,"\tDUP\n\tDUP\n\tDE_REF 1\n");
			fprintf(this->out,"\tDEC\n\tSTORE_REF 1\n\tDE_REF 1\n");
			fprintf(this->out,"\tINC\n");
			break;
		case F5: // F -> '(' E ')'
			E_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			F_static.F.type = E_static.E.type;
			F_static.type = F;
			this->semanticoStack.push(F_static);
			break;
		case F6: // F -> IDU MC '(' LE ')'
			LE_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			MC_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			IDU_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			f = IDU_static.ID.obj;
			F_static.F.type = MC_static.MC.type;
			//if(!LE_static.LE.err){
				//if(LE_._.LE.n-1 < f->_.Function.nParams && LE_._.LE.n != 0){
					//Error(ERR_TOO_FEW_ARGS);
				//}
				//else if(LE_._.LE.n-1 > f->_.Function.nParams){
					//Error(ERR_TOO_MANY_ARGS);
				//}
			//}
			F_static.type = F;
			this->semanticoStack.push(F_static);
			fprintf(this->out,"\tCALL %d\n",f->Function.nIndex);
			break;
		case F7: // F -> '-' F
			F1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			t = F1_static.F.type;
			//if( !check_types(t,pInt)){Error(ERR_INVALID_TYPE);}

			F0_static.F.type = t;
			F0_static.type = F;
			this->semanticoStack.push(F0_static);
			fprintf(this->out,"\tNEG\n");
			break;
		case F8: // F -> '!' F
			F1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			t = F1_static.F.type;
			//if( !check_types(t,pBool)){Error(ERR_INVALID_TYPE);}

			F0_static.F.type = t;
			F0_static.type = F;
			this->semanticoStack.push(F0_static);
			fprintf(this->out,"\tNOT\n");
			break;
		case F9: // F -> TRUE
			TRU_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			F_static.F.type = pBool;
			F_static.type = F;
			this->semanticoStack.push(F_static);

			fprintf(this->out,"\tLOAD_CONST %d\n",this->analisadorLexico->tokenSecundario);
			break;
		case F10: // F -> FALSE
			FALS_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			F_static.F.type = pBool;
			F_static.type = F;
			this->semanticoStack.push(F_static);

			fprintf(this->out,"\tLOAD_CONST %d\n",this->analisadorLexico->tokenSecundario);
			break;
		case F11: // F -> CHR
			CHR_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			F_static.F.type = pChar;
			F_static.type = F;
			this->semanticoStack.push(F_static);
			n = this->analisadorLexico->tokenSecundario;
			fprintf(this->out,"\tLOAD_CONST %d\n",n);
			break;
		case F12: // F -> STR
			STR_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			F_static.F.type = pString;
			F_static.type = F;
			this->semanticoStack.push(F_static);
			n = this->analisadorLexico->tokenSecundario;
			fprintf(this->out,"\tLOAD_CONST %d\n",n);
			break;
		case F13: // F -> NUM
			NUM_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			F_static.F.type = pInt;
			F_static.type = F;
			this->semanticoStack.push(F_static);
			n = this->analisadorLexico->tokenSecundario;
			fprintf(this->out,"\tLOAD_CONST %d\n",n);
			break;
		case LE0: // LE -> LE ',' E
			E_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			LE1_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			LE0_static.LE.param = NULL;
			LE0_static.LE.err = L1_static.LE.err;

			n = LE1_static.LE.n;
			if(!LE1_static.LE.err){
				p = LE1_static.LE.param;
				if(p == NULL){
					//Error(ERR_TOO_MANY_ARGS);
					LE0_static.LE.err = true;
				}
				else{
					//if(!check_types(p->_.Param.pType,E_._.E.type)){Error(ERR_PARAM_TYPE);}
					LE0_static.LE.param = p->next;
					LE0_static.LE.n = n + 1;
				}
			}
			LE0_static.type = LE;
			this->semanticoStack.push(LE0_static);
			break;
		case LE1: // LE -> E
			E_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			MC_static = this->semanticoStack.top();

			LE_static.LE.param = NULL;
			LE_static.LE.err = MC_static.MC.err;
			n = 1;
			if( !MC_static.MC.err){
				p = MC_static.MC.param;
				if(p == NULL){
					//Error(ERR_TOO_MANY_ARGS);
					LE_static.LE.err = true;
				}
				else{
					//if(!check_types(p->_.Param.pType,E_._.E.type)){Error(ERR_PARAM_TYPE);}
					LE_static.LE.param = p->next;
					LE_static.LE.n = n+1;
				}
			}
			LE_static.type = LE;
			this->semanticoStack.push(LE_static);
      		break;
		case LV0: // LV -> LV '.' IDU
			ID_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			LV1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			t = LV1_static.LV.type;
			if( t-> kind != KindStructType){
				if(t->kind != KindUniversal){
					//Error( ERR_KIND_NOT_STRUCT);
				}
				LV0_static.LV.type = pUniversal;
			}
			else{
				p = t->Struct.pFields;
				while(p!=NULL){
					if(p->name == ID_static.ID.name){
						break;
					}
					p = p->next;
				}
				if(p == NULL){
					//Error(ERR_FIELD_NOT_DECL);
					LV0_static.LV.type = pUniversal;
				}
				else{
					LV0_static.LV.type = p->Field.pType;
					LV0_static.LV.type->Type.nSize = p->Field.nSize;
					fprintf(this->out,"\tADD %d\n",p->Field.nIndex);
				}
			}

			LV0_static.type = LV;
			this->semanticoStack.push(LV0_static);
			break;
		case LV1: // LV -> LV '[' E ']'
			E_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			LV1_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			t = LV1_static.LV.type;
			if(check_types(t,pString)){
				LV0_static.LV.type = pChar;
			}
			else if(t->kind != KindArrayType){
				if(t->kind != KindUniversal){
					//Error(ERR_KIND_NOT_ARRAY);
				}
				LV0_static.LV.type = pUniversal;
			}
			else{
				LV0_static.LV.type = t->Array.pElemType;
				n = t->Array.pElemType->Type.nSize;
				fprintf(this->out,"\tMUL %d\n\tADD\n",n);
			}

			if( !check_types(E_static.E.type,pInt)){
				//Error(ERR_INVALID_INDEX_TYPE);
			}

			LV0_static.type = LV;
			this->semanticoStack.push(LV0_static);
			break;
		case LV2: // LV -> IDU
			IDU_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			p = IDU_static.ID.obj;
			if(p->kind != KindVar && p->kind != KindParam){
				if(p->kind != KindUniversal){
				//Error(ERR_KIND_NOT_VAR);
				}
				LV_static.LV.type = pUniversal;
			}
			else{
				LV_static.LV.type = p->Var.pType;
				LV_static.LV.type->Type.nSize = p->Var.nSize;
				fprintf(this->out,"\tLOAD_REF %d\n",p->Var.nIndex);
			}
			LV_static.type = LV;

			t = LV_static.LV.type;

			this->semanticoStack.push(LV_static);
			break;
		case IDD0: // IDD -> Id
			name = this->analisadorLexico->tokenSecundario;
			IDD_static.ID.name = name;
			if((p = search_symbol_in_scope(name)) != NULL){
				printf("error IDD0");
			}
			else
				p = define_symbol(name);
			IDD_static.ID.obj = p;
			this->semanticoStack.push(IDD_static);
			break;
		case IDU0: // IDU -> Id
			name = this->analisadorLexico->tokenSecundario;
			IDU_static.ID.name = name;
			if((p = search_symbol_globally(name)) == NULL){
				printf("Could not find symbol globally, exiting\n");
				exit(0);
				p = define_symbol(name);
			}
			IDU_static.ID.obj = p;
			this->semanticoStack.push(IDU_static);
			break;
		case ID0: // ID -> Id
			name = this->analisadorLexico->tokenSecundario;
			ID_static.ID.name = name;
			ID_static.ID.obj = NULL;
			this->semanticoStack.push(ID_static);
			break;
		case TRUE0: // TRUE ->  'true'
			TRU_static.type = TRUE1;
			TRU_static.TRU.val = true;
			TRU_static.TRU.type = pBool;
			this->semanticoStack.push(TRU_static);
			break;
		case FALSE0: // FALSE -> 'false'
			FALS_static.type = FALSE1;
			FALS_static.FALS.val = false;
			FALS_static.FALS.type = pBool;
			this->semanticoStack.push(FALS_static);
			break;
		case CHR0: // CHR -> c
			CHR_static.type = CHR;
			CHR_static.CHR.type = pChar;
			CHR_static.CHR.pos = this->analisadorLexico->tokenSecundario;
			CHR_static.CHR.val = this->analisadorLexico->getCharConstant(this->analisadorLexico->tokenSecundario);
			this->semanticoStack.push(CHR_static);
			break;
		case STR0: // STR -> s
			{
				STR_static.type = STR;
				STR_static.STR.type = pString;
				STR_static.STR.pos = this->analisadorLexico->tokenSecundario;
				string value = this->analisadorLexico->getStringConstant(this->analisadorLexico->tokenSecundario);
				char char_array[value.length() + 1]; 
				strcpy(char_array, value.c_str()); 
				STR_static.STR.val = char_array;
				this->semanticoStack.push(STR_static);
				break;
			}
		case NUM0: // NUM -> n
			NUM_static.type = NUM;
			NUM_static.NUM.type = pInt;
			NUM_static.NUM.pos = this->analisadorLexico->tokenSecundario;
			NUM_static.NUM.val = this->analisadorLexico->getIntConstant(this->analisadorLexico->tokenSecundario);
			this->semanticoStack.push(NUM_static);
			break;
		case NB0: // NB -> ''
			new_block();
			break;
		case MF0: // MF -> ''
			T_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			LP_static = this->semanticoStack.top();
			this->semanticoStack.pop();
			IDD_static = this->semanticoStack.top();
			this->semanticoStack.pop();

			f = IDD_static.ID.obj;
			f->kind = KindFunction;
			f->Function.pRetType = T_static.T.type;
			f->Function.pParams = LP_static.LP.list;
			f->Function.nParams = LP_static.nSize;
			f->Function.nVars = 0;
			this->curFunction = f;

			fprintf(this->out,"BEGIN_FUNC %d, %d, %02d\n",f->Function.nIndex,
				f->Function.nParams,0);
			this->functionVarPos = ftell(this->out) - 3;
			break;
		case MC0: // MC -> ''
			IDU_static = this->semanticoStack.top();
			f = IDU_static.ID.obj;

			if(f->kind != KindFunction){
 				//Error(ERR_KIND_NOT_FUNCTION);
				MC_static.MC.type = pUniversal;
				MC_static.MC.param = NULL;
				MC_static.MC.err = true;
			}
			else{
				MC_static.MC.type = f->Function.pRetType;
				MC_static.MC.param = f->Function.pParams;
				MC_static.MC.err = false;
			}
			MC_static.type = MC;
			this->semanticoStack.push(MC_static);
			break;
		case NF0: // NF -> ''
			IDD_static = this->semanticoStack.top();
			// TODO Não tem pop??
			f = IDD_static.ID.obj;
			f->kind = KindFunction;
			f->Function.nParams = 0;
			f->Function.nVars = 0;
			f->Function.nIndex = nFuncs++;
			new_block();
			break;
		case MT0: // MT -> ''
			l = this->new_label();
			MT_static.MT.label = l;
			MT_static.type = MT;
			fprintf(this->out,"\tTJMP_FW L%d\n",l);
			this->semanticoStack.push(MT_static);
			break;
		case ME0: // ME -> ''
			MT_static = this->semanticoStack.top();
			l1 = MT_static.MT.label;
			l2 = this->new_label();
			ME_static.ME.label = l2;
			ME_static.type = ME;
			this->semanticoStack.push(ME_static);

			fprintf(this->out,"\tTJMP_FW L%d\nL%d\n",l2,l1);
			break;
		case MW0: // MW -> ''
			l = this->new_label();
			MW_static.MW.label = l;
			this->semanticoStack.push(MW_static);
			fprintf(this->out,"L%d\n",l);
			break;
		default:
			printf("no case\n");
			break;
	}

}