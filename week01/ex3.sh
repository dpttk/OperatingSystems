mkdir root 
date
sleep 3
cd root


ls -t  / >  root.txt 
date
sleep 3




cd ../

mkdir home
date 
sleep 3

cd home

ls -t ~ >  home.txt
date 
sleep 3

echo 
echo


ls 
cat home.txt

cd ../root 

echo 
echo


ls
cat root.txt
