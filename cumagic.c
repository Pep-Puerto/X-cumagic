#include "cumagic.h"
#include "cal_cumagic.h"
#include "X_cumagic.h"
#ifndef X_
#define X_
	#include <X11/X.h>
#endif

int main(void)
{
int op,valor,quit=1,key;
int fil,col,fil_orig,col_orig,fil_dest,col_dest;
int val_sel=-1;
t_enreixat *erx_orig,*erx_dest,*erx;
char opc;
int x, y;
int TipusEvent; 

inicialitzar();
kk();
menu_principal(&n,&op);
n=5;
op=3;
//Dibuixa enreixat principal i carrega les estructures amb els valors pertinents
X_dib_enreixat(60,5,n);
ubica_posyx(60,5,n,&cA);
//case principal
switch(op){
	case 1: //Calcula automaticament
		cal_cumagic(n,n*n);
		X_imp_cumagic(n,&cA);
		break;
	
	case 2: //Resoluci manual
		do{
			X_printf(5,10,"Introduir valor (s/n): ");
			X_llegircar(&opc);
			switch(opc){
				case 'n': //No: sortir
					break;
				case 's': //Si: assignar valor i recalcular
					menu_assigna_valor();
					cal_suma(n);
					X_imp_cumagic(n,&cA);
					break;
			}
		}while (op=='s');
		break;

	case 3: //Resoluci amb el ratol
		//Dibuixa i carrega la estructura del enreixat auxiliar amb els valor pertinents
		X_dib_enreixat(60,(n+3)*AMP_C,n);
		ubica_posyx(60,(n+3)*AMP_C,n,&cB);
		cal_emplenar_cB(n);
		X_imp_cumagic(n,&cB);
		//Activa els events del mouse
		X_act_event_mouse();
		while(quit){
			TipusEvent=X_CapturaEvent(&x,&y);
			switch(TipusEvent){
			  case ButtonPress:
			       	if (seleccionar_valor(&erx,&fil,&col,x,y)==_VALOR){
				     		erx_orig=erx;
				     		fil_orig=fil;
				     		col_orig=col;
				     		val_sel=1;
			        }
							if (val_sel && seleccionar_valor(&erx_dest,&fil_dest,&col_dest,x,y)==_ZERO){
				     		insertar_valor(erx_orig,erx_dest,fil_orig,col_orig,fil_dest,col_dest);
				     		val_sel=0;
							}
							break;
			   case KeyPress:
								quit=1;
								break;
			} //switch
		} //while
}   //switch
finalitzar();
}



int inicialitzar(){
	X_init_w();
	X_init_color();
}

int finalitzar(){
	X_fi_w();
	sleep(8);
}

int menu_principal(int *n,int *op){
	X_printf(10,10,"Donam ordre del cuadrat magic: ");

	X_llegirenter(n);
	X_printf(20,10,"Escull opcio: ");
	X_printf(30,50,"1.- Calcul automatic ");
	X_printf(40,50,"2.- Emplenar manualment. ");
	X_printf(50,50,"3.- Emplenar amb el ratoli");
	X_llegirenter(op);
}

int menu_assigna_valor(){
int fila,columna,valor;
	X_printf(25,100,"1.- Donam fila:");
	X_llegirenter(&fila);
	X_printf(5,30,"  ");
	X_printf(5,10,"1.- Donam columna:");
	X_llegirenter(&columna);
	X_printf(5,30,"  ");
	X_printf(5,10,"1.- Donam valor:");
	X_llegirenter(&valor);
	X_printf(5,30,"  ");
	cA.cu[fila][columna].num=valor;
}

void ubica_posyx(int y, int x,int n,t_enreixat *e)
{
int i,j,posy,posx,num,px_cas,py_cas;
	//Ubica les posicions i el tamany del enreixat
	e->pos_erx.y=y;
	e->pos_erx.x=x;
	e->ly=n*ALT_C;
	e->lx=n*AMP_C;
	//Ubica les posicions d'impresi del numero i les posicions i tamany de cada cel.la
	px_cas=x; py_cas=y;
	posy=y+(int)(ALT_C/2);
	posx=x+(int)(AMP_C/4);
	num=1;
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			e->cu[i][j].pos_num.x=posx;
			e->cu[i][j].pos_num.y=posy;
			e->cu[i][j].pos_cas.x=px_cas;
			e->cu[i][j].pos_cas.y=py_cas;
			e->cu[i][j].lx=AMP_C;
			e->cu[i][j].ly=ALT_C;
			posx+=AMP_C;px_cas+=AMP_C;
		}
		posx=x+(int)(AMP_C/4);px_cas=x;
		posy+=ALT_C;py_cas+=ALT_C;
	}
	//Ubica sumX
	for(i=0;i<n;i++){
		e->sumX[i].pos_num.x=e->cu[0][n-1].pos_num.x+AMP_C;
		e->sumX[i].pos_num.y=e->cu[i][n-1].pos_num.y;
	}
	//Ubica sumY
	for(i=0;i<n;i++){
		e->sumY[i].pos_num.x=e->cu[n-1][i].pos_num.x;
		e->sumY[i].pos_num.y=e->cu[n-1][i].pos_num.y+ALT_C;
	}
	//Ubica Diagonal A
	e->DiaA.pos_num.x=e->cu[n-1][n-1].pos_num.x + AMP_C;
	e->DiaA.pos_num.y=e->cu[n-1][n-1].pos_num.y + ALT_C;
	//Ubica Diagonal B
	e->DiaB.pos_num.x=e->cu[n-1][0].pos_num.x - AMP_C;
	e->DiaB.pos_num.y=e->cu[n-1][0].pos_num.y + ALT_C;
}


int mostrar_fc_valor(t_enreixat *e,int f,int c,int valor){
int y,x;
char s[128];
	y=e->pos_erx.y+e->ly+2*ALT_C;
	x=e->pos_erx.x;
	sprintf(s,"Fila: %d  Columna: %d Valor:%d",f,c,valor);
	X_printf(y,x,s);
}

int seleccionar_valor(t_enreixat **e,int *fila,int *columna,int x,int y){
int f,c,dins_zona_cuadres,valor;
static int f_ant,c_ant,cAB;
	switch (cAB){
		case CUADRE_A:
			X_desel_fc(f_ant,c_ant,&cA);
			break;
		case CUADRE_B:
			X_desel_fc(f_ant,c_ant,&cB);
			break;
	}
	if (X_yx_fc(&cA,n,y,x, &f, &c)){
		f_ant=f;c_ant=c;cAB=CUADRE_A;
		X_sel_fc(f,c,&cA,&valor);
		*fila=f,*columna=c;*e=&cA;
		mostrar_fc_valor(&cA,f,c,valor);
		dins_zona_cuadres=1;
	}
	if (X_yx_fc(&cB,n,y,x, &f, &c)){
		f_ant=f;c_ant=c;cAB=CUADRE_B;
		X_sel_fc(f,c,&cB,&valor);
		*fila=f,*columna=c;*e=&cB;
		mostrar_fc_valor(&cB,f,c,valor);
		dins_zona_cuadres=1;
	}
	if (valor) return(_VALOR);
	if (dins_zona_cuadres) return(_ZERO);
	return(0);
}


int insertar_valor(t_enreixat *e_orig,t_enreixat *e_dest,int f_orig,int c_orig,int f_dest,int c_dest){
	e_dest->cu[f_dest][c_dest].num=e_orig->cu[f_orig][c_orig].num;
	e_orig->cu[f_orig][c_orig].num=0;
	cal_suma(n);
	X_imp_cumagic(n,e_dest);
	X_imp_cumagic(n,e_orig);
}
