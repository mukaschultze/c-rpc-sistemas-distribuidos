rpcgen date.x
gcc -c date_clnt.c
gcc -c date_svc.c
gcc -c cJSON.c dateproc.c
gcc -c rdate.c
gcc -o client date_clnt.o cJSON.o rdate.o
gcc -o server date_svc.o cJSON.o dateproc.o

# ./server &
# ./client localhost
