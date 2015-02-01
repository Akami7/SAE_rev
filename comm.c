#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h> // kmalloc
#include <asm/uaccess.h> // get_user et put_user

#ifndef min
# define min(a,b) (((a) < (b)) ? (a) : (b)
#endif

MODULE_AUTHOR("Akami");
MODULE_DESCRIPTION("rev");
MODULE_LICENSE("GPL");

// Periph ==============================
#define DEV_NAME "comm"
#define MAX_DEVICE 5
#define MAX_SIZE 256

void crypt_cesar(char *buffer,int n);
void crypt_rot13(char *buffer,int n);
void decrypt_cesar(char *buffer,int n);
void decrypt_rot13(char *buffer,int n);




static int _lwrite(struct file *f, char *buffer,size_t len, loff_t *ptr);
static int _lread(struct file *f, char * buffer , size_t len, loff_t *ptr);

struct file_operations fops = {
	owner: THIS_MODULE,
	read: _lread,
	write: _lwrite
};

//implementation low lvl


static int _lread(struct file *f , char * buffer , size_t len , loff_t *ptr){

 printk("<1>comm periph : read\n");

 int minor = MINOR(f->f_dentry->d_inode->i_rdev);

 char buf[len];


 if(copy_to_user(buffer, buf, len)!=0){
 printk("<1>Erreur copy to user\n");
}


 return 0;

}

static int _lwrite(struct file *f , char * buffer, size_t len, loff_t *ptr){


 printk("<1>comm periph : write\n");


 char buf[len];
 if(len > MAX_SIZE) {
 printk ("<1>error size flow\n");
 return  -EMSGSIZE;
 }

 int minor;
 minor= MINOR (f->f_dentry->d_inode->i_rdev);



 copy_from_user(buf + *ptr,buffer,len);
// printk("<1>Erreur de copie from user\n");
// return -EINVAL;
// }

if (minor == 0){
crypt_cesar(buf,len);
}else {
crypt_rot13(buf,len);
}

buf[len]='\0';

printk("<1>buf= %s",buf);



 return len;
}


//Crypto ================================



static int _init(void){
 printk("<1>Module comm init\n");
 int res; 

 if((res= register_chrdev(150,"comm",&fops))<0){
 printk("<1>Error Driver Load\n");
 }

// crypt_cesar("AB",2);
// crypt_rot13("AB",2);
// decrypt_cesar("HELLO",5);
// decrypt_rot13("HELLO",5);
 return 0;
}


static void _exit(void){
 printk("<1>Module comm exit\n");
 unregister_chrdev(150,"comm");
 
}

module_init(_init);
module_exit(_exit);
