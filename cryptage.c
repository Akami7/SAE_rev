#include <linux/init.h>
#include <linux/module.h>

MODULE_AUTHOR("Akami");
MODULE_DESCRIPTION("rev");
MODULE_LICENSE("GPL");

extern void crypt_cesar(char * buffer, int n);
extern void crypt_rot13(char * buffer, int n);
extern void decrypt_cesar(char * buffer, int n);
extern void decrypt_rot13(char * buffer, int n);

void crypt_cesar(char * buffer, int n){
 
int i=0;

for (; i<n ; i++){
	if(buffer[i]>= 'A' && buffer[i]<='Z'){
	buffer[i]= ((buffer[i]-'A'+3)%26) + 'A';
		} else if(buffer[i]>='a' && buffer[i]<='z') {
	buffer[i]= ((buffer[i]- 'a'+3)%16) +'a';
		}
	}


 printk("<1>module cryptage : crypt_cesar\n");
}
void crypt_rot13(char * buffer, int n){

int i = 0;

for (; i<n ; i++){
        if(buffer[i]>= 'A' && buffer[i]<='Z'){
        buffer[i]= ((buffer[i]-'A'+13)%26) + 'A';
                } else if(buffer[i]>='a' && buffer[i]<='z') {
        buffer[i]= ((buffer[i]- 'a'+13)%16) +'a';
                }
        }





 printk("<1>module cryptage : crypt_rot13\n");
}

void decrypt_cesar(char * buffer, int n){

int i = 0;

for (; i<n ; i++){
        if(buffer[i]>= 'A' && buffer[i]<='Z'){
        buffer[i]= ((buffer[i]-'A'- 3)%26) + 'A';
                } else if(buffer[i]>='a' && buffer[i]<='z') {
        buffer[i]= ((buffer[i]- 'a'- 3)%16) +'a';
                }
        }





 printk("<1>module cryptage : decrypt_cesar\n");
}

void decrypt_rot13(char * buffer, int n){

int i = 0;

for (; i<n ; i++){
        if(buffer[i]>= 'A' && buffer[i]<='Z'){
        buffer[i]= ((buffer[i]-'A'-13)%26) + 'A';
                } else if(buffer[i]>='a' && buffer[i]<='z') {
        buffer[i]= ((buffer[i]- 'a'- 13)%16) +'a';
                }
        }





 printk("<1>module cryptage : decrypt_rot13\n");
}

static int _init(void){
 printk("<1>Module cryptage init\n");
 return 0;
}

static void _exit(void){
 printk("<1>Module cryptage exit\n");
}

EXPORT_SYMBOL(crypt_cesar);
EXPORT_SYMBOL(crypt_rot13);
EXPORT_SYMBOL(decrypt_cesar);
EXPORT_SYMBOL(decrypt_rot13);

module_init(_init);
module_exit(_exit);

