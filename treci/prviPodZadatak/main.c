#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

MODULE_DESCRIPTION("Jednostavan modul");

MODULE_AUTHOR("SGG");

/* Ova funkcija se poziva prilikom učitavanja modula. */

int simple_init(void){

    printk(KERN_INFO "Ucitavam jezgreni modul\n");
    printk(KERN_INFO "jiffies %lu\n", jiffies);
    printk(KERN_INFO "secunde %lu\n", jiffies/HZ);

    return 0;

}

/* Ova funkcija se poziva prilikom uklanjanja modula. */

void simple_exit(void){
    printk(KERN_INFO "Uklanjanje jezgrenog modula\n");
    printk(KERN_INFO "jiffies %lu\n", jiffies);
    printk(KERN_INFO "secunde %lu\n", jiffies/HZ);

}

/* Makro za registraciju modula: ulazna i izlazna točka. */

module_init(simple_init);

module_exit(simple_exit);
