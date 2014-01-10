#!/bin/bash
 
for i in *.xml
do
 
#cat <<EOT
export value=`cat $i`
#export value
echo value
psql -c "INSERT INTO printers (name,description) VALUES( '$i', '$value');"
#EOT
 
done
