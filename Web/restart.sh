#!/bin/bash
#set -x
if [ "$(whoami)" != "root" ] ; then
    echo "$(basename $0) must be run with root permissions." 1>&2
    exit 1
fi
cd $(dirname $0)
echo "Killing any previously running instances..."
./kill-all.sh >/dev/null 2>&1
echo "Starting new instance..."
./run.sh & disown

COMMITTER_PGID=$(ps -eopgid,comm | grep 'committer.sh' | sort | uniq | awk '{ print $1 }')
if [ "$COMMITTER_PGID" == "" ] ; then 
    echo "Starting committer.sh"
    ./committer.sh & disown
fi

{ 
    while true ; do 
        [ "$(ps -eocomm,args | grep '^ruby' | grep 'ruby webserver-sinatra' | wc -l)" == "1" ] || {
            echo "Restarting webserver."
            echo ./restart.sh
        }
        sleep 60
    done
} & disown

