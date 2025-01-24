#include <iostream>
#include <cstdio>
#include "hashtable.h"

int main(int argc, char const* argv[]){ // ./main hs cs
    int type;
    char buffer[1000];int data;

    hashing_strategy* hs;
    collision_strategy* cs;

    if(atoi(argv[1]) == 1) hs = new bad_hashing();
    else if(atoi(argv[1]) == 2) hs = new good_hashing();
    else return -1;

    if(atoi(argv[2]) == 1) cs = new linear_probe();
    else if(atoi(argv[2]) == 2) cs = new quadratic_probe();
    else if(atoi(argv[2]) == 3) cs = new overflow_strategy();
    else return -1;

    hashtable table(TABLE_SIZE,hs,cs);
    while(true){
        scanf("%d", &type);
        if(type == 0){
            scanf("%s", buffer);scanf("%d",&data);
            table.insert(hash_entry(buffer, data));
        }else if(type == 1){
            scanf("%s",buffer);
            printf("%d\n", table.query(buffer));
        }else break;
    }
    return 0;
}