#!/bin/bash
[ "$(whoami)" == "root" ] || {
    echo "$(basename $0) must be run with root permissions." 1>&2
    exit 1
}

pgids="$(ps -eopgid,ppid,pid,uid,comm | grep 'committer.sh' | awk '{print $1}' | sort -n | uniq)"
[ "$(echo "${pgids}" | wc -l)" == 1 ] || {
    echo "Committer is already running" 1>&2
    exit 1
}

exec 1> >(logger -t "$0 stdout")
exec 2> >(logger -t "$0 stderr")

set -x
source coliru_env.source

while true ; do

    (
        cd "${COLIRU_ARCHIVE2}"

        for d in $(ls) ; do 
            [ -d $d ] && {
                # Commit new
                svn ci $d -m "Update archive." || {
                    svn cleanup 
                    svn up 
                    svn ci $d -m "Update archive after cleaning and updating it."
                }
            } || {
                echo "$d is not a directory." 1>&2
            }
        done
    ) 

    # Repeat later. 
    sleep 3600
done
