#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/slab.h> // kmalloc
#include <asm/uaccess.h> // get_user et put_user

#ifndef min
# define min (a,b) (((a) < (b)) ? (a) : (b)
#endif

MODULE_AUTHOR("Akami");
MODULE_DESCRIPTION("rev");
MODULE_LICENSE("GPL");

// Periph ==============================
#define DEV_NAME "comm"
#define MAX_DEVICE 5

#define MAX_SIZE 256

char *buf;
int used;

void crypt_cesar(char *buffer,int n);
void crypt_rot13(char *buffer,int n);
void decrypt_cesar(char *buffer,int n);
void decrypt_rot13(char *buffer,int n);



static int _open(struct inode *inode,struct file *file);
static int _lwrite(struct file *f, char *buffer,size_t len, loff_t *ptr);
static int _lread(struct file *f, char * buffer , size_t len, loff_t *ptr);

struct file_operations fops = {
	owner: THIS_MODULE,
	read: _lread,
	write: _lwrite,
	open:_open
};

//implementation low lvl


static int _open(struct inode *inode, struct file *f){

if(f->f_mode==FMODE_WRITE)
used=0;

if(buf==NULL){
	if((buf=(char *) kmalloc(MAX_SIZE,GFP_KERNEL))==0){
	printk("<1>Probleme d'allocation buf\n");
	 return -ENOMEM;
	 }
	}
return 0;
}

static int _lread(struct file *f , char * buffer , size_t len , loff_t *ptr){


 int n;
 int minor = MINOR(f->f_dentry->d_inode->i_rdev);

 n= min((size_t)(used - *ptr),len);


 if(copy_to_user(buffer, buf + *ptr , n)!=0){
 printk("<1>Erreur copy to user\n");
 return -EINVAL;
}
*ptr += n;

if(minor == 0)
{decrypt_cesar(buffer,n);
}else {decrypt_rot13(buffer,n);}

 return n;

}

static int _lwrite(struct file *f , char * buffer, size_t len, loff_t *ptr){

 int minor = MINOR(f->f_dentry->d_inode->i_rdev);

 if(*ptr + len > MAX_SIZE) {
 printk ("<1>error size flow\n");
 return  -EMSGSIZE;
 }

 copy_from_user(buf + *ptr,buffer,len);
 *ptr+=len;


if (minor == 0){
crypt_cesar(buf,len);
}else {
crypt_rot13(buf,len);
}

buf[len]='\0';

printk("<1>buf= %s",buf);

 used= *ptr;
 return len;
}


//Crypto ================================



static int _init(void){
 printk("<1>Module comm init\n");
 int res; 

 if((res= register_chrdev(150,"comm",&fops))<0){
 printk("<1>Error Driver Load\n");
 }

 buf =NULL;
 return 0;
}


static void _exit(void){
 printk("<1>Module comm exit\n");
 unregister_chrdev(150,"comm");
 
}

module_init(_init);
module_exit(_exit);
