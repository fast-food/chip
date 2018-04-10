CC = g++
ODIR = obj
PROG = main
CXXFLAG = -std=c++11 -lnfc

$(PROG) : $(ODIR) $(ODIR)/main.o
	$(CC) -o $@ $(ODIR)/main.o $(CXXFLAG)

$(ODIR)/main.o : ./src/main.cpp ./food/menuUtils.h ./nfc/nfcManager.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR) :
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

.PHONY : clean
clean :
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi
	if [ -f $(PROG) ]; then rm $(PROG); fi
