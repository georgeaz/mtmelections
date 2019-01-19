CC=gcc
OBJS=Candidate.o citizen.o City.o exampleMain.o mayor.o mtm_elections.o mtm_print.o preference.o typedefs_and_general_functions.o Vote.o uniqueOrderedList.o
EXEC=mtmElections
DEBUG_FLAG=# -g
FOLDER=./uniqueOrderedList
CFLAGS=-std=c99 -Wall -Werror -pedantic-errors
$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@ -L. -lmtm
Candidate.o: Candidate.c Candidate.h typedefs_and_general_functions.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) $*.c
citizen.o: citizen.c citizen.h set.h typedefs_and_general_functions.h \
uniqueOrderedList/uniqueOrderedList.h preference.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) $*.c
City.o: City.c City.h citizen.h set.h typedefs_and_general_functions.h \
$(FOLDER)/uniqueOrderedList.h Candidate.h Vote.h preference.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) $*.c
exampleMain.o: exampleMain.c mtm_elections.h \
typedefs_and_general_functions.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) $*.c
mayor.o: mayor.c mayor.h
mtm_elections.o: mtm_elections.c $(FOLDER)/uniqueOrderedList.h \
citizen.h set.h typedefs_and_general_functions.h City.h Candidate.h \
Vote.h preference.h mtm_elections.h mayor.h mtm_print.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) $*.c
mtm_print.o: mtm_print.c mtm_print.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) $*.c
preference.o: preference.c preference.h typedefs_and_general_functions.h
typedefs_and_general_functions.o: typedefs_and_general_functions.c \
typedefs_and_general_functions.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) $*.c
Vote.o: Vote.c Vote.h typedefs_and_general_functions.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) $*.c
uniqueOrderedList.o: $(FOLDER)/uniqueOrderedList.c \
$(FOLDER)/uniqueOrderedList.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) $(FOLDER)/*.c
clean:
	rm -f $(OBJS)
