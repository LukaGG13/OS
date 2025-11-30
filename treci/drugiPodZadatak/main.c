#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");

MODULE_DESCRIPTION("Jednostavan modul");

MODULE_AUTHOR("SGG");

/* Ova funkcija se poziva prilikom učitavanja modula. */

int simple_init(void){

    printk(KERN_INFO "Ucitavam jezgreni modul svi procesi\n");
    struct task_struct *p;
    for_each_process(p){
        printk(KERN_INFO "Proces %s %d wakee: %s\n", p->comm, p->pid, p->last_wakee->comm);
    }

    return 0;

}

/* Ova funkcija se poziva prilikom uklanjanja modula. */

void simple_exit(void){
    printk(KERN_INFO "Uklanjanje jezgrenog modula svi procesi\n");

}

/* Makro za registraciju modula: ulazna i izlazna točka. */

module_init(simple_init);

module_exit(simple_exit);
