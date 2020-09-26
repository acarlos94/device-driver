#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h> // Esse arquivo contem a estrutura de dados exatas para especificação do USB

static struct usb_device *device;

/*
Funcao probe
Chamada sempre que um dispositivo e plugado ao PC.
Nao e chamada se um outro driver ja administra esse dispositivo.
*/
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    /*
    Identificadores de interface
    São ponteiros que apontam para a estrutura de usb_interface,
    pois os os drivers USB são escritos para interfaces de dispositivo e não para o dispositivo como um todo
    */
    struct usb_host_interface *iface_desc;
    struct usb_endpoint_descriptor *endpoint;

    int i;

    /*
    //Altsetting -> Matriz de estruturas de interface
    Contem todas as configurações alternativas que podem ser selecionadas para essa interface.
    Consiste em um conjuto de configurações do terminal.
    */
    iface_desc = interface->cur_altsetting;

    printk(KERN_INFO "[*] Pen drive de Antonio (%04X:%04X) plugado [*]\n", id->idVendor, id->idProduct);
    printk(KERN_INFO "ID->bNumEndpoints: %02X\n",
            iface_desc->desc.bNumEndpoints);
    printk(KERN_INFO "ID->bInterfaceClass: %02X\n",
            iface_desc->desc.bInterfaceClass); //codigo de classe

    //bNumEndpoint -> Número de endpoints usados por essa interface

    //Laço para mostrar as informações de cada endpoint da interface
    for (i = 0; i < iface_desc->desc.bNumEndpoints; i++)
    {
        endpoint = &iface_desc->endpoint[i].desc;

        //Endereco do endpoint
        printk(KERN_INFO "ED[%d]->bEndpointAddress: 0x%02X\n",
                i, endpoint->bEndpointAddress);

        /*
        Tipo de transferencia
        Control, isochronous, bulk ou interrupt
        */
        printk(KERN_INFO "ED[%d]->bmAttributes: 0x%02X\n",
                i, endpoint->bmAttributes);

        //Tamanho máximo do Pacote que este endpoint é capaz de enviar ou receber
        printk(KERN_INFO "ED[%d]->wMaxPacketSize: 0x%04X (%d)\n",
                i, endpoint->wMaxPacketSize,
                endpoint->wMaxPacketSize);

        //Tamanho do descritor
        printk(KERN_INFO "ED[%d]->bLength: 0x%02X\n",
        i, endpoint->bLength);

        /*
        Tipo de descritor
        0x01 = descritor de dispositivo
        0x02 = descritor de configuração
        0x03 = descritor de string
        0x04 = descritor de interface
        0x05 = descritor de endpoint
        */
        printk(KERN_INFO "ED[%d]->bDescriptorType: 0x%02X\n",
        i, endpoint->bDescriptorType);
    }

    //Obter o identificador do dispositivo
    device = interface_to_usbdev(interface);

    return 0; //indica que esse driver vai ser utilizado pra esse dispositivo
}

//disconnect
static void pen_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "[*] Pen drive de Antonio removido [*]\n");
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
    printk(KERN_INFO "[*] Desconstrutor do driver [*]\n");
    usb_deregister(&pen_drive);
    printk(KERN_INFO "\tdesregistro concluído\n");
}

module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Antonio Carlos");
MODULE_DESCRIPTION("USB driver para a disciplina de Principios Básicos de software");
