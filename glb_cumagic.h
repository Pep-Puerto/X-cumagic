#ifndef _CU_H
#define _CU_H
	#define MAX 15
	#define AMP_C 40
	#define ALT_C 40
	#define CUADRE_A 0
	#define CUADRE_B 1
	#define _VALOR 1
	#define _ZERO  2
	
	typedef struct{
		int x;
		int y;
	}t_coord;
	typedef struct {
		int num;
		t_coord pos_num;
		t_coord pos_cas;
		int lx;
		int ly;
	} t_casella;
	typedef struct{
		t_casella cu[MAX][MAX];
		t_casella sumX[MAX];
		t_casella sumY[MAX];
		t_casella DiaA;
		t_casella DiaB;
		t_coord pos_erx;
		int lx;
		int ly;
	} t_enreixat;
	t_enreixat cA,cB;
	int n;
#endif