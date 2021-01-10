#include "X_cumagic.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <unistd.h>
#include <stdlib.h>

	Display *disp=NULL;
	Window finestra;
	Font f;
	GC gc;
	XEvent evt;
	int pnt;
	XColor color;
	unsigned long negro,blanco;
	char lletra[2];
int kk();
int X_init_w()
{
 	disp=XOpenDisplay(NULL);
//	f=XLoadFont(disp,"-adobe-new century schoolbook-bold-i-normal--24-240-75-75-p-148-iso8859-15");
	pnt=DefaultScreen(disp);
	blanco=WhitePixel(disp,pnt);
	negro=BlackPixel(disp,pnt);


	finestra=XCreateSimpleWindow(disp,DefaultRootWindow(disp),100,100,600,600,2,negro,blanco);
	XSelectInput(disp,finestra,ButtonPressMask | ButtonReleaseMask | KeyPressMask);
	XMapWindow(disp,finestra);

}

void X_fi_w()
{
XCloseDisplay(disp);	
//endwin();
}

int X_CapturaEvent(int *x, int *y){
	XNextEvent(disp,&evt);
	if (evt.type==ButtonPress){
	       *x=evt.xbutton.x;
	       *y=evt.xbutton.y;
	}
	return evt.type;
}

void X_printf(int y, int x, char* cadena){
	XDrawImageString(disp,finestra,gc,x,y,cadena,strlen(cadena));
	XFlush(disp);
}

void X_llegircar(char *car){
int llegircar=1;

	while(llegircar){
		XNextEvent(disp,&evt);
		switch(evt.type){
			case KeyPress:
				lletra[0]=evt.xkey.keycode;
				XDrawString(disp,finestra,gc,evt.xkey.x,evt.xkey.y,lletra,1);
				llegircar=0;
				break;
		}
	}
	*car=lletra[0];
	XFlush(disp);
}

void X_llegirenter(int *num){
int llegirenter=1;

	while(llegirenter){
		XNextEvent(disp,&evt);
		switch(evt.type){
			case KeyPress:
				lletra[0]=evt.xkey.keycode;
				XDrawString(disp,finestra,gc,evt.xkey.x,evt.xkey.y,lletra,1);
				llegirenter=0;
				break;
		}
	}
	*num=(int)lletra[0];
	XFlush(disp);
}

int X_init_color(){
	gc=XCreateGC(disp,finestra,0,NULL);
	color.flags = DoRed | DoGreen | DoBlue;
	XSetForeground(disp,gc,negro);
	XSetBackground(disp,gc,blanco);
  X_Color_Black();
	XFlush(disp);
}

int X_Linia_Grossa(){
	XSetLineAttributes(disp,gc,4,LineSolid,CapNotLast,JoinRound);
}

int X_Linia_Fina(){
	XSetLineAttributes(disp,gc,2,LineSolid,CapNotLast,JoinRound);
}

int X_Color_RGB(unsigned R,unsigned G, unsigned B){
	color.red = R;
	color.green = G;
	color.blue = B;
	XAllocColor(disp,DefaultColormap(disp,DefaultScreen(disp)),&color);
	XSetForeground(disp,gc,color.pixel);
	XFlush(disp);
}
int X_Color_Red(){
	X_Color_RGB(65535,0,0);
}

int X_Color_Blue(){
	X_Color_RGB(0,0,65535);
}

int X_Color_Green(){
	X_Color_RGB(0,65535,0);
}

int X_Color_Black(){
	X_Color_RGB(0,0,0);
}

int X_Color_Selected(){
X_Color_Red();
}

int X_Color_Deselected(){
X_Color_Black();
}

int X_Color_Enreixat(){
X_Color_Blue();
}

void X_dib_enreixat(int y, int x, int n){
int i;
  X_Color_Enreixat();
	X_Linia_Grossa();
	for(i=1;i<=n+1;i++){
		XDrawLine(disp,finestra,gc,x,y,x+n*AMP_C,y);
		y+=ALT_C;
	}
	y=y-(n+1)*ALT_C;
	for(i=1;i<=n+1;i++){
		XDrawLine(disp,finestra,gc,x,y,x,y+n*ALT_C);
		x+=AMP_C;
	}
	XFlush(disp);
	X_Linia_Fina();
}



int X_imp_cumagic(int n,t_enreixat *e)
{
int i,j,y,x;
char numstr[4];

//attron(COLOR_PAIR(NOMBRES));
	X_Color_Deselected();
	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			y=e->cu[i][j].pos_num.y;x=e->cu[i][j].pos_num.x;
			sprintf(numstr,"%3d",e->cu[i][j].num);
			if (e->cu[i][j].num) X_printf(y,x,numstr);
			if (!e->cu[i][j].num) X_printf(y,x,"   ");
		}
//attroff(COLOR_PAIR(NOMBRES));
	X_Color_Blue();
	//Imprimir sumX i sumY
	for(i=0;i<n;i++){
		y=e->sumX[i].pos_num.y;x=e->sumX[i].pos_num.x;
		if (e->sumX[i].num) {sprintf(numstr,"%3d",e->sumX[i].num);X_printf(y,x,numstr);}
		if (!e->sumX[i].num) X_printf(y,x,"    ");
		y=e->sumY[i].pos_num.y;x=e->sumY[i].pos_num.x;
		if (e->sumY[i].num) {sprintf(numstr,"%3d",e->sumY[i].num);X_printf(y,x,numstr);}
		if (!e->sumY[i].num) X_printf(y,x,"    ");
	}
	//Imprimir diagonals
	y=e->DiaA.pos_num.y;x=e->DiaA.pos_num.x;
	if (e->DiaA.num) {sprintf(numstr,"%3d",e->DiaA.num);X_printf(y,x,numstr);}
	if (!e->DiaA.num) X_printf(y,x,"    ");
	y=e->DiaB.pos_num.y;x=e->DiaB.pos_num.x;
	if (e->DiaB.num) {sprintf(numstr,"%3d",e->DiaB.num);X_printf(y,x,numstr);}
	if (!e->DiaB.num) X_printf(y,x,"    ");
	XFlush(disp);
}

int X_sel_fc(int fila,int columna,t_enreixat *e,int *valor)
{
char s[128];
  X_Color_Selected();
	*valor=e->cu[fila][columna].num;
	sprintf(s,"%3d",e->cu[fila][columna].num);
	X_printf(e->cu[fila][columna].pos_num.y,e->cu[fila][columna].pos_num.x,s);
	X_Color_Deselected();
}

int X_desel_fc(int fila,int columna,t_enreixat *e)
{
int valor;
char s[128];
	valor=e->cu[fila][columna].num;
	X_Color_Green();
	if (valor > 0){sprintf(s,"%3d",valor);X_printf(e->cu[fila][columna].pos_num.y,e->cu[fila][columna].pos_num.x,s);}
	if (valor <=0){sprintf(s,"   ");X_printf(e->cu[fila][columna].pos_num.y,e->cu[fila][columna].pos_num.x,s);}
}


int X_act_event_mouse()
{
/*
	raw();
	keypad(stdscr,TRUE);
	mousemask(ALL_MOUSE_EVENTS,0);
*/
}

int X_yx_fc(t_enreixat *e,int n,int y, int x, int *fila, int *columna)
{
int i,j,x_ini,x_fi,y_ini,y_fi,ok=1;
if ((y <= e->pos_erx.y) || (y >= (e->pos_erx.y + e->ly)) || (x <= e->pos_erx.x) || (x >= (e->pos_erx.x + e->lx))) return(0);
for (i=0;i<n;i++)
	for (j=0;j<n;j++)
	{
		x_ini=e->cu[i][j].pos_cas.x;
		x_fi=x_ini+e->cu[i][j].lx;
		y_ini=e->cu[i][j].pos_cas.y;
		y_fi=y_ini+e->cu[i][j].ly;
		if ((x >= x_ini) && (x <= x_fi) && (y >= y_ini) && (y <= y_fi))
		{
			*fila=i;
			*columna=j;
			return(1);
		}
	}
return(0);
}

int kk(){
char **llistaFonts;
int cf=1,i,fila=1;
char s[256];


  llistaFonts=XListFonts(disp,"*",3000,&cf);
	for (i=1;i<2000;i++){
		//sprintf(s,"%3d",cf);
		f=XLoadFont(disp,*(llistaFonts+i));
		X_printf(++fila*15,15,*(llistaFonts+i));
		f=XUnloadFont(disp,*(llistaFonts+i));
		if (fila==40){sleep(1);fila=1;}
	}
}