#!/bin/bash
 
for i in *.xml
do
 
#cat <<EOT
value=`sed "s/'/\"/g" $i`
psql -c "INSERT INTO printers (name,description) VALUES( '$i', '$value');"
#EOT
 
done
