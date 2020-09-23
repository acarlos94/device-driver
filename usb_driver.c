#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

/*
Funcao probe
Chamada sempre que um dispositivo e plugado ao PC.
Nao e chamada se um outro driver ja administra esse dispositivo.
*/
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    printk(KERN_INFO "[*] Pen drive de Antonio (%04X:%04X) plugado\n", id->idVendor, id->idProduct);
    return 0; //indica que esse driver vai ser utilizado pra esse dispositivo
}

//disconnect
static void pen_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "[*] Pen drive de Antonio removido\n");
}

//usb_device_id
static struct usb_device_id pen_table[] = {
    //vendor_id = 0781 e product_id = 5567, obtidos usando "lsusb" no terminal
    { USB_DEVICE(0x0781,0x5567) }, //obtidos com comando "lsusb -V" no terminal
    {},
};
MODULE_DEVICE_TABLE(usb_device_id, pen_table);

//USB driver
static struct usb_driver pen_drive =
{
    .name = "Driver de Antonio",
    .id_table = pen_table, // Tabela de identificacao. Tipo = usb_device_id
    .probe = pen_probe,
    .disconnect = pen_disconnect,
};

//Registrar o pen drive no USB core
static int __init pen_init(void){
    int ret = -1;
    printk(KERN_INFO "[*] Construtor do driver [*] \n");
    printk(KERN_INFO "\tRegistrando o driver no kernel\n");
    ret = usb_register(&pen_drive);
    printk(KERN_INFO "\tRegistro concluído\n");
    return ret;
}

//Retira o registro do pen drive do USB core
static void __exit pen_exit(void){
    printk(KERN_INFO "[*] Desconstrutor do driver[*]\n");
    usb_deregister(&pen_drive);
    printk(KERN_INFO "\tdesregistro concluído\n");
}

module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antonio Carlos");
MODULE_DESCRIPTION("Principios básicos de software");
