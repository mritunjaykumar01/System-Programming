if [ -d $1 ]
    then
    echo permissions:
    echo -n "is directory? print 'd' ":
    					ls -ld $1|cut -c1-1
    echo -n "user_permissions       " :
    					ls -ld $1|cut -c2-4
    echo -n "group_permissions      " :
    					ls -ld $1|cut -c5-7
    echo -n "others_permissions     " :
    					ls -ld $1|cut -c8-10

elif [ -f $1 ]
    then
    echo permissions:
    echo -n "is file ? print '-'     ":
    					ls -ld $1|cut -c1-1
    echo -n "user_permissions       "   :
    					ls -l $1|cut -c2-4
    echo -n "group_permissions      " :
    					ls -l $1|cut -c5-7
    echo -n "others_permissions     " :
    					ls -l $1|cut -c8-10
else
    echo "$1 doesn't exist"
fi
