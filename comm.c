#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("Akami");
MODULE_DESCRIPTION("rev");
MODULE_LICENSE("GPL");

void crypt_cesar(char * buffer, int n);
void crypt_rot13(char * buffer, int n);
void decrypt_cesar(char * buffer, int n);
void decrypt_rot13(char * buffer, int n);


static int _init(void){
 printk("<1>Module comm init\n");

 crypt_cesar("HELLO",3);
 crypt_rot13("HELLO",3);
 decrypt_cesar("HELLO",3);
 decrypt_rot13("HELLO",3);
 return 0;
}


static void _exit(void){
 printk("<1>Module comm exit\n");
}

module_init(_init);
module_exit(_exit);
