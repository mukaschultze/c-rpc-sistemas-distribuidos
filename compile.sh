rpcgen bands.x
gcc -c bands_clnt.c
gcc -c bands_svc.c
gcc -c cJSON.c bandsproc.c
gcc -c rbands.c
gcc -o client bands_clnt.o cJSON.o rbands.o
gcc -o server bands_svc.o cJSON.o bandsproc.o

# ./server &
# ./client localhost
