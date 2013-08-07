

function performAlterationForPresentDirectory {
for dir in *
do
    for file in "$dir"/*
    do
        if [[ -f $file ]]
        then
           cp "$file" "$SRC"
        fi
    done
if [[ -d $dir ]]
then
    rm -r $dir
fi
done
}
cd ..
cd Classes
SRC=`pwd`
performAlterationForPresentDirectory
cd ..
cd Resources
SRC=`pwd`
performAlterationForPresentDirectory