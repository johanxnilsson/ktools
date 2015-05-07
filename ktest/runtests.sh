#!/bin/sh

if [ ! -f ../src/eve/eve ]; then
    echo "Please run make all before make check"
    exit
fi
mkdir -p testout
CTRL=ctrl

if [ ! -f cwbld ]; then
	CTRL=wctrl
fi

if [ ! -f uwbld ]; then
	echo "Windows test  not supported in Linux"
	exit
fi

if [ ! -d $CTRL ]; then
	tar -xzf ../$CTRL.tar.gz
fi

cd ..
if [ ! -d examples ]; then
	tar -xzf examples.tar.gz
fi
cd examples
# test eve
../src/eve/eve 1 1 2 > ../ktest/testout/eveout1_1.bin
../src/eve/eve 1 2 2 > ../ktest/testout/eveout1_2.bin
../src/eve/eve 2 1 2 > ../ktest/testout/eveout2_1.bin
../src/eve/eve 2 2 2 > ../ktest/testout/eveout2_2.bin

diff ../ktest/$CTRL/eveout1_1.bin ../ktest/testout/eveout1_1.bin
diff ../ktest/$CTRL/eveout1_2.bin ../ktest/testout/eveout1_2.bin
diff ../ktest/$CTRL/eveout2_1.bin ../ktest/testout/eveout2_1.bin
diff ../ktest/$CTRL/eveout2_2.bin ../ktest/testout/eveout2_2.bin

# test getmodel
../src/eve/eve 1 1 2 | ../src/getmodel/getmodel 1  > ../ktest/testout/getmodelout1_1.bin
../src/eve/eve 1 2 2 | ../src/getmodel/getmodel 1  > ../ktest/testout/getmodelout1_2.bin
../src/eve/eve 2 1 2 | ../src/getmodel/getmodel 2  > ../ktest/testout/getmodelout2_1.bin
../src/eve/eve 2 2 2 | ../src/getmodel/getmodel 2  > ../ktest/testout/getmodelout2_2.bin

diff ../ktest/$CTRL/getmodelout1_1.bin ../ktest/testout/getmodelout1_1.bin
diff ../ktest/$CTRL/getmodelout1_2.bin ../ktest/testout/getmodelout1_2.bin
diff ../ktest/$CTRL/getmodelout2_1.bin ../ktest/testout/getmodelout2_1.bin
diff ../ktest/$CTRL/getmodelout2_2.bin ../ktest/testout/getmodelout2_2.bin

# test gulcalc
../src/eve/eve 1 1 2 | ../src/getmodel/getmodel 1 | ../src/gulcalc/gulcalc -C1 -S100 -R -r > ../ktest/testout/gulcalcout1_1.bin
../src/eve/eve 1 2 2 | ../src/getmodel/getmodel 1 | ../src/gulcalc/gulcalc -C1 -S100 -R -r > ../ktest/testout/gulcalcout1_2.bin
../src/eve/eve 2 1 2 | ../src/getmodel/getmodel 2 | ../src/gulcalc/gulcalc -C1 -S100 -R -r > ../ktest/testout/gulcalcout2_1.bin
../src/eve/eve 2 2 2 | ../src/getmodel/getmodel 2 | ../src/gulcalc/gulcalc -C1 -S100 -R -r > ../ktest/testout/gulcalcout2_2.bin

diff ../ktest/$CTRL/gulcalcout1_1.bin ../ktest/testout/gulcalcout1_1.bin
diff ../ktest/$CTRL/gulcalcout1_2.bin ../ktest/testout/gulcalcout1_2.bin
diff ../ktest/$CTRL/gulcalcout2_1.bin ../ktest/testout/gulcalcout2_1.bin
diff ../ktest/$CTRL/gulcalcout2_2.bin ../ktest/testout/gulcalcout2_2.bin

# test fmcalc
../src/eve/eve 1 1 2 | ../src/getmodel/getmodel 1 | ../src/gulcalc/gulcalc -C1 -S100 -R -r | ../src/fmcalc/fmcalc >  ../ktest/testout/fmcalcout1_1.bin

diff ../ktest/$CTRL/fmcalcout1_1.bin ../ktest/testout/fmcalcout1_1.bin

# test outputs
../src/eve/eve 1 1 1 | ../src/getmodel/getmodel 1 | ../src/gulcalc/gulcalc -C1 -S100 -R -r | ../src/outputcalc/outputcalc >  ../ktest/testout/gulout1.csv

diff ../ktest/$CTRL/gulout1.csv ../ktest/testout/gulout1.csv

../src/eve/eve 1 1 1 | ../src/getmodel/getmodel 1 | ../src/gulcalc/gulcalc -C1 -S100 -R -r | ../src/fmcalc/fmcalc | ../src/outputcalc/outputcalc >  ../ktest/testout/fmout1.csv

diff ../ktest/$CTRL/fmout1.csv ../ktest/testout/fmout1.csv

# test data conversion utilities
../src/cdftocsv/cdftocsv < ../ktest/testout/getmodelout1_1.bin > ../ktest/testout/getmodelout1_1.csv

diff ../ktest/$CTRL/getmodelout1_1.csv ../ktest/testout/getmodelout1_1.csv

../src/gultocsv/gultocsv < ../ktest/testout/gulcalcout1_1.bin > ../ktest/testout/gulcalcout1_1.csv

diff ../ktest/$CTRL/gulcalcout1_1.csv ../ktest/testout/gulcalcout1_1.csv

../src/fmtocsv/fmtocsv < ../ktest/testout/fmcalcout1_1.bin > ../ktest/testout/fmcalcout1_1.csv

diff ../ktest/$CTRL/fmcalcout1_1.csv ../ktest/testout/fmcalcout1_1.csv
