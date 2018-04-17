CC = g++
ODIR = obj
PROG = main
CXXFLAG = -std=c++11 -lcurl -lnfc

$(PROG) : $(ODIR) $(ODIR)/network.o $(ODIR)/apdu.o $(ODIR)/nfcManager.o $(ODIR)/nfcUtils.o $(ODIR)/main.o
	$(CC) -o $@ $(ODIR)/network.o $(ODIR)/apdu.o $(ODIR)/nfcManager.o $(ODIR)/nfcUtils.o $(ODIR)/main.o $(CXXFLAG)

$(ODIR)/network.o : ./network/src/network.cpp ./network/include/network.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/apdu.o : ./nfc/src/apdu.cpp ./nfc/include/apdu.h ./nfc/include/nfcUtils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/nfcManager.o : ./nfc/src/nfcManager.cpp ./nfc/include/nfcManager.h ./nfc/include/apdu.h ./nfc/include/nfcUtils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/nfcUtils.o : ./nfc/src/nfcUtils.cpp ./nfc/include/nfcUtils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/main.o : ./src/main.cpp ./nfc/include/nfcManager.h ./network/include/network.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR) :
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

.PHONY : clean
clean :
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi
	if [ -f $(PROG) ]; then rm $(PROG); fi
