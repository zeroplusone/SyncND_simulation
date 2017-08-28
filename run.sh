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
date=`date +%Y-%m-%d_%H%M%S`
# simTime=604800000  # 7 days
# simTime=1209600000  # 14 days
simTime=10000000 # count by cycle time
# dutyCycle=(0.01 0.02 0.05 0.1 0.2 0.5 1)
dutyCycle=(0.0001 0.0005 0.001 0.002 0.005 0.01 0.025 0.05 0.1 0.2 0.5 1)

# updateFreqency=(300000 600000 1800000 3600000 10800000 21600000 43200000 86400000 172800000)
# in minute: 5min, 10min, 30min, 1hr, 3hr, 6hr, 12hr, 24hr, 48hr)
# updateFreqency=(60000 300000 600000 1200000 1800000 2400000 3000000 3600000)
# in minute: 1min, 5min, 10min, 20min, 30min, 40min, 50min, 60min)
# updateFreqency=(60000 300000 600000 1800000 3600000 43200000 86400000)
# in minute: 1min, 5min, 10min, 30min, 60min, 12 hr, 1 day)
# updateFreqency=(172800000 259200000 345600000 432000000 518400000 604800000)
# in minute: 2day, 3day, 4day, 5day, 6day, 7day)
updateFreqency=(60000 3600000 43200000 86400000 172800000 345600000 691200000 864000000)
# in minute: 1min, 1hr, 12hr, 1day, 2day, 4day, 8day, 10day)

slotDuration=$1
 
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
        ./SyncND.out $simTime $j $i $slotDuration > $resultPath/"updateFreqency_"$i"-dutyCycle_"$j".raw"

    done
done

# for((i=10000,count=1; i<=100000;i=i+10000, count=count+1))
# do
#     echo "The "$count" time simulation with Nd = "$i
#     ./a.out $simTime $arrivalRate $backoffLimit $backoffIndicator $numOfArrivalTime $i $numOfGroup $zigbeeChannelSize $mtcPreambleSize > $resultPath/$count"-Proposed_Nd"$i".raw"
# done
