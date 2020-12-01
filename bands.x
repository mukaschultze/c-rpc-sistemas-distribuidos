typedef string json_result<65535>;

program BANDSPROG {	
version BANDSVERS { 
    void TEST(void) = 2; 

    string CREATE_BANDA(string) = 3;
    string READ_BANDA(string) = 4;
    string LIST_BANDA(void) = 5;
    string DELETE_BANDA(string) = 6;
} = 1;	
} = 0x3012225;	
