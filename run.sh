#/bin/bash
# check whether the result directory exists or not                                              
if ! [ -d result ]; then
    echo "#Create result directory..."
    echo `mkdir result`
fi
 
# check whether the program compiled
if ! [ -f SyncND.out ]; then
    if [ -f *.o ]; then
        echo "#make clean..."
        echo `make clean`
    fi
    echo "#Compile the code..."
    echo `make`
fi
 
# set values of variables
date=`date +%Y-%m-%d_%H%M`
simTime=604800000  # 7 days
# simTime=604800  # 7 days
dutyCycle=(0.01 0.02 0.05 0.1 0.2 0.5 1)
# dutyCycle=(0.01 0.5)
updateFreqency=(300000 600000 1800000 3600000 10800000 21600000 43200000 86400000 172800000)
# updateFreqency=(10 360)
# in minute: 5min, 10min, 30min, 1hr, 3hr, 6hr, 12hr, 24hr, 48hr)

 
resultPath="result/"$date
 
# start simulation
echo "start simulation at "$date"..."
echo `mkdir $resultPath`
echo $boundingProb
for i in ${updateFreqency[@]}
do
    for j in ${dutyCycle[@]}
    do
        echo $i"_"$j
        echo "updateFreqency: "$i", dutyCycle: "$j
        ./SyncND.out $simTime $j $i > $resultPath/"updateFreqency_"$i"-dutyCycle_"$j".raw"

    done
done

# for((i=10000,count=1; i<=100000;i=i+10000, count=count+1))
# do
#     echo "The "$count" time simulation with Nd = "$i
#     ./a.out $simTime $arrivalRate $backoffLimit $backoffIndicator $numOfArrivalTime $i $numOfGroup $zigbeeChannelSize $mtcPreambleSize > $resultPath/$count"-Proposed_Nd"$i".raw"
# done
