D_INCLUDE = .
D_C = xcumagic
PROGRAMES = $(D_C)/cumagic.o $(D_C)/cal_cumagic.o $(D_C)/X_cumagic.o


all : $(PROGRAMES)
	gcc -o cumagic $(PROGRAMES) -L/usr/X11R6/lib -lX11
cumagic.o : cumagic.c cumagic.h glb_cumagic.h cal_cumagic.h X_cumagic.h
	gcc -c $<
cal_cumagic.o : cal_cumagic.c cal_cumagic.h glb_cumagic.h
	gcc -c $<
X_cumagic.o : X_cumagic.c X_cumagic.h glb_cumagic.h
	gcc -c $<
.PHONY : netejar
netejar :
	$(RM) *.o


