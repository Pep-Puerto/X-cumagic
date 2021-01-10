#include "glb_cumagic.h"

int inicialitzar();
int finalitzar();
int menu_principal(int *n,int *op);
int menu_assigna_valor();
int seleccionar_valor(t_enreixat **e,int *fila,int *columna,int x,int y);
int insertar_valor(t_enreixat *e_orig,t_enreixat *e_dest,int f_orig,int c_orig,int f_dest,int c_dest);
void ubica_posyx(int y, int x,int n,t_enreixat *e);

