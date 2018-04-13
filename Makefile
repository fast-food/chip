CC = g++
ODIR = obj
PROG = main
CXXFLAG = -std=c++11 -lcurl -ljsoncpp -lnfc

$(PROG) : $(ODIR) $(ODIR)/network.o $(ODIR)/menuUtils.o $(ODIR)/food.o $(ODIR)/menu.o $(ODIR)/foodUtils.o $(ODIR)/nfcManager.o $(ODIR)/apduCmd.o $(ODIR)/apduResp.o $(ODIR)/nfcUtils.o $(ODIR)/main.o
	$(CC) -o $@ $(ODIR)/network.o $(ODIR)/menuUtils.o $(ODIR)/food.o $(ODIR)/menu.o $(ODIR)/foodUtils.o $(ODIR)/nfcManager.o $(ODIR)/apduCmd.o $(ODIR)/apduResp.o $(ODIR)/nfcUtils.o $(ODIR)/main.o $(CXXFLAG)

$(ODIR)/network.o : ./network/src/network.cpp ./network/include/network.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/menuUtils.o : ./food/src/menuUtils.cpp ./food/include/menuUtils.h ./food/include/menu.h ./food/include/food.h ./food/include/foodType.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/food.o : ./food/src/food.cpp ./food/include/food.h ./food/include/foodType.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/menu.o : ./food/src/menu.cpp ./food/include/menu.h ./food/include/food.h ./food/include/foodType.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/foodUtils.o : ./food/src/foodUtils.cpp ./food/include/foodUtils.h ./food/include/food.h ./food/include/foodType.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/nfcManager.o : ./nfc/src/nfcManager.cpp ./nfc/include/nfcManager.h ./nfc/include/nfcUtils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/apduCmd.o : ./nfc/src/apduCmd.cpp ./nfc/include/apduCmd.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/apduResp.o : ./nfc/src/apduResp.cpp ./nfc/include/apduResp.h ./nfc/include/apduCmd.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/nfcUtils.o : ./nfc/src/nfcUtils.cpp ./nfc/include/nfcUtils.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR)/main.o : ./src/main.cpp ./food/include/menuUtils.h ./food/include/foodUtils.h ./nfc/include/nfcManager.h ./network/include/network.h
	$(CC) -c $< -o $@ $(CXXFLAG)

$(ODIR) :
	if [ ! -d $(ODIR) ]; then mkdir $(ODIR); fi

.PHONY : clean
clean :
	if [ -d $(ODIR) ]; then rm $(ODIR) -r; fi
	if [ -f $(PROG) ]; then rm $(PROG); fi
