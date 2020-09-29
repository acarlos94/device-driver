<h1>Device Driver</h1>

<p>
  Driver de um pen drive para linux. Os arquivos que foram escritos foram o usb_driver.c e o Makefile. O Makefile consiste em um arquivo feito para compilar um módulo no kernel. Após a escrita do usb_driver.c e do Makefile, abra o terminal no diretório onde esses arquivos estão e rode o seguinte comando para compilar o módulo: <br><code>$ make</code>
</p>

<p>
  Ao executar esse comando, os demais arquivos vão ser criados e agora você pode inserir o seu módulo no kernel. Para isso, rode: <br><code>$ sudo insmod SEU_MODULO.ko</code>
</p>

<p>
  Para remover seu módulo do kernel, rode: <br><code>$ sudo rmmod SEU_MODULO</code>
</p>

<p>
  Voce consegue ver todos os modulos no kernel com o comando <br><code>$ lsmod</code>
</p>
