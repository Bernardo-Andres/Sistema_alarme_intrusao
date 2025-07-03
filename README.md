# Montagem de Sistema de Alarme de Intrusão Doméstico baseado em ESP32


Este Manual te ensina a montar um sistema de alarme de intrusão que dispara a partir da interrupção de feixes de luz: quando alguém passa e interrompe os feixes de luz, isso aciona o sistema de alarme, que toca uma buzina e envia uma mensagem no seu celular pelo Telegram.

Este projeto está dimensionado para proteger uma via de acesso (mas pode ser ampliado para proteger mais de uma via).

**IMPORTANTE**: você não precisa saber programar ou entender eletrônica. Basta ler seguir os passos aqui descritos com calma e consultar, em caso de necessidade, as figuras do artigo deste projeto.


**Aquisição de Materiais**
Você vai precisar adquirir os seguintes materiais (alguns deles talvez você já possua)


| Nome do item                       | Pra que serve?                            | Quantidade |
| ---------------------------------- | ----------------------------------------- | ---------- |
| Microcontrolador ESP32             | É o "cérebro" do sistema                  | 1          |
| Laser 5V (vermelhinho)             | Cria os feixes de luz                     | 3          |
| Sensor LDR (com Potenciômetro)     | Detecta se a luz do laser está passando   | 3          |
| *Buzzer* passivo                   | Emite o som do alarme                     | 1          |
| Protoboard (840 pontos)            | Tabuleiro onde conectamos os fios         | 1          |
| Cabos CAT5e ou outro (0,5 a 0,6 mm)| Para fazer as ligações                    | a definir  |
| Fonte 5V ou cabo USB               | Para ligar tudo                           | 1          |
| Tubinhos PVC ou canudos opacos     | Para proteger os sensores da luz ambiente | 3          |
| Celular com Telegram               | Para receber os avisos                    | 1          |
| Notebook/PC com internet           | Para configurar tudo (apenas uma vez)     | 1          |

💡**OBSERVAÇÃO**: será necessário ter um ferro de solda ou adquirir conectores "Modu".

**Passos para a Instalação do Sistema de Alarme (incluindo medição de cabos CAT5e para aquisição e upload de código pela IDE no Microcontrolador ESP32)**


1. Baixar o Arduino IDE do site oficial (siga intuitivamente). Após baixá-lo, execute-o. Aparecerá uma janela, na qual você deverá seguir este caminho: file/arquivo (Português)-> Preferences; uma nova janela se abrirá; nela você deve clicar em "Additional boards manager URLs:", o que fará com que se abra um espaço para você preencher; neste espaço, você colará o seguinte link: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package\_esp32\_index.json 💡**OBSERVAÇÃO**: caso já exista algo escrito neste espaço, coloque uma vírgula ao seu final e cole logo após esta vírgula o link aqui mencionado; em seguida, click em OK. Na janela que permanecerá aberta, no Menu ao alto você clicará em "Tools", logo em seguida em Board, e em seguida Boards Manager; abrirá um Menu lateral, à esquerda, no qual você deverá usar o campo de busca digitando "ESP32"; vão aparecer alguns itens e você deverá clique em "Install" no pacote chamado "esp32 by Espressif Systems". Aguarde a instalação. Uma vez instalado o programa, volte em "Tools", vá em Board e localize o item ESP32, passando o mouse por cima, de modo que aparecerão inúmeros modelos. Identifique o seu e clique em cima, para selecioná-la e preparar o IDE para que o upload do código seja devidamente realizado em sua ESP32.💡 **OBSERVAÇÃO**: se você não identificar o seu modelo, saiba que a maioria das ESP32 funciona com "ESP32 Dev Module", clique em cima dele neste caso.
2. Criação do *BotFather* no *Telegram*. Abra o Telegram e busque por @BotFather com selo de verificado (possui mais de 3.487.000 usuários), que é o Bot oficial para criaçáo de novos Bots no Telegram. Inicie uma conversa com *BotFather* digitando "/start", enviando esta mensagem. Aparecerá uma lista de comandos, e você deverá clicar sobre "/newbot"; em seguida, o *BotFather* perguntará qual o nome do seu *Bot* e você deve informá-lo, seguindo os demais passos requeridos pelo *Telegram/BotFather*, o qual criará um link na conversa.💡💡💡 **IMPORTANTE**: você deve guardar o Token de acesso ao API, pois você precisará dele para colar no código da ESP32 a fim de possibilitar o envio de mensagens para você. Clique no link da Conversa apresentado ao final. Após isto, você deverá voltar ao *Telegram* e buscar por "@UserInfotoBot", clicando nele e iniciando uma conversa que lhe dará sua ID, a qual também será usada no upload do Código Fonte para ESP32.
3. No mesmo PC que realizou as tarefas acima, conecte a sua ESP32 via cabo USB. Volte à janela que permaneceu aberta após a seleção do Modelo ESP32, indo novamente a "Tools", "Port" e selecione a porta USB que apareceu (exemplo: COM3, COM5); caso não apareça, pode ser necessário instalar um driver usb (geralmente TH340 ou CP2102). Feito isto, vá ao GitHub para obter o Código Fonte deste projeto, o qual foi disponibilizado juntamente com o artigo que o sustenta. O link é: https://github.com/Bernardo-Andres/Sistema\_alarme\_intrusao. Você deve clicar "main.cpp|", e, ao fazer isto, o código se abrirá, devendo você copiá-lo integralmente e colá-lo no Arduino IDE. Substitua as credenciais indicadas no Código Fonte pelas suas: nome do Wi-Fi, senha do Wi-Fi, seu Token e seu ID do chat do Telegram. Em seguida, clique no botão de upload (setinha para direita).💡**OBSERVAÇÃO**: caso dê erro no upload, clicar novamente em upload e segurar o botão de Boot físico da ESP32 (aí dará tudo certo).
4. Fixação do Microcontrolador ESP32 nos barramentos centrais da Protoboard (Plug and Play), por simples encaixe e pressão, o mais à direita possível (ocupando as colunas "b" a "j"), tendo cuidado de deixar livres a linha "a" e os barramentos laterais, positivo (+)/vermelho e negativo (-)/azul de ambos os lados.💡**OBSERVAÇÃO**: conectar o Microcontrolador ESP32 (identificar "V5" ou "5V") por meio de um pequeno pedaço de fio ao barramento positivo da Protoboard; da mesma forma, conectá-lo (identificar GND) no barramento negativo.
5. Fixação do *Buzzer* Passivo (buzina) na Protoboard (Plug and Play) na extremidade oposta à da ESP32, nos barramentos centrais, por simples encaixe e pressão (colunas "e" e "f").💡**OBSERVAÇÃO**: conectar o terminal indicado como positivo no *Buzzer* (pode ser o "maior", se não houver sinalização indicativa) por meio de um pequeno pedaço de fio ao ponto G33 (definido no código empregado neste projeto) na Protoboard; a linha onde está encaixado o terminal negativo do *Buzzer* deve ser conectada no barramento negativo geral da Protoboard usar pedaço de fio conectando a linha 1, na qual deve estar encaixado o *Buzzer*.
6. Identificação do ambiente a ser protegido e da via de acesso a ser protegida com o sistema de alarme, uma porta, por exemplo, com determinação dos pontos estratégicos para instalação dos Lasers 5V e dos Sensores LDR.💡**OBSERVAÇÃO**: os Sensores LDR devem ficar orientados de modo contrário à incidência de luz ambiente mais forte, devendo ser protegidos pelos tubinhos de PVC ou canudos totalmente opacos.
7. Identificação do ponto onde será fixada a Protoboard e a Fonte 5V ou cabo USB proveniente de algum equipamento, de modo a permitir o cálculo do comprimento dos cabos que serão usados para a conexão dos Lasers 5V e dos Sensores LDR que serão conectados à Protoboard;💡**OBSERVAÇÃO**: identificado o ponto, faça a fixação da Protoboard.
8. Medição e corte dos cabos CAT5e ou equivalente deve ser feita da seguinte maneira: meça o comprimento do cabo necessário para os Lasers 5V, partindo da Protoboard e indo até o Laser mais distante, passando por um trajeto que, ao mesmo tempo, permita esconder/preservar o cabo e passe por todos os pontos determinados para fixação dos Lasers 5V; repita esta operação tomando por referência os Sensores LDR.💡**OBSERVAÇÃO**: os cabos CAT5e são composto por 8 (oito) fios de 0.51 mm encapados. Cada Laser 5V usará 2 destes 8 fios, de modo que a metragem do Cabo CAT5e estabelecida para eles atenda a todos os 3, sobrando ainda 2 fios "mortos"; contudo, a metragem estabelecida para os Sensores LDR necessitará da aquisição de outra metragem igual de fio individual (0,5 a 0,6 mm) para completar toda a ligação, uma vez que cada sensor destes utiliza 3 fios para operar.
9. Preparo dos cabos CAT5e e fio individual (0,5 a 0,6 mm) que serão utilizados para a conexão de Lasers 5V e Sensores LDR à Protoboard:
   9.1 O preparo do cabo a ser utilizado para conectar os Lasers 5V deve se dar da seguinte forma: cortar o necessário da capa protetora dos fios para possibilitar sua conexão na Protoboard, e, a partir do Laser 5V mais próximo até sua extremidade, para possibilitar a ligação dos demais Lasers 5V;
   9.2 repetir o mesmo procedimento em relação aos Sensores LDR;
   9.3 cortar os fios na medida necessária à realização da conexão com os terminais de cada um dos componentes, deixando uma folga de 10 cm (para facilitar a soldagem);
   9.4 desencapar 1 cm dos fios para encaixá-los na Protoboard e possibilitar a realização da soldagem e/ou fixação de conectores "Modu" fêmea.
10. Soldagem ou colocação de conectores na extremidade dos fios que serão conectadas nos componentes (Lasers 5V e Sensores LDR), ficando a outra preparada para ser encaixada na Protoboard (poderá ser usado também, caso se deseje, conector "Modu" macho).
    10.1 Nos Sensores LDR, os fios ligados no terminal VCC, deverão ter sua outra extremidade conectada na Protoboard no barramento positivo; os ligados no terminal DO deverão ter sua conexão na Protoboard nos pontos G32, G34 e G35 e o terminal central, GND (Terra), no barramento negativo da Protoboard.
    10.2 Nos Lasers 5V, os fios do terminal S, deverão ter sua outra extremidade conectada no barramento positivo da Protoboard; os ligados no terminal "-" serão ligados no terminal negativo da Protoboard.
11. Fixação dos Lasers 5V, com os fios já soldados ou conectados, nos pontos determinados (item 6), podendo utilizar, inclusive, fita autocolante dupla face de boa qualidade ou outro meio.
12. Fixação dos Sensores LDR, com os fios já soldados ou conectados, de modo a receberem diretamente a luz dos Lasers 5V, lembrando que devem ser protegidos pelos tubos PVC a fim de evitar ao máximo qualquer interferência ambiental em sua operação.

O funcionamento do sistema se dá da seguinte maneira: quando houver interrupção em feixe(s) de luz, o sistema enviará uma mensagem pelo Telegram informando; se a interrupção for total, ou seja, dos 3 feixes, o sistema enviará mensagem e acionará o Buzzer. Restaurados os feixes de luz, o sistema voltará ao normal.

💡💡💡Cuidados e dicas:

\* Verifique sempre se os lasers estão bem alinhados com os sensores.

\* Se o alarme tocar sozinho, talvez haja luz ambiente em excesso sobre o Sensor LDR: usar os tubos de PVC ajuda muito!

\* A alimentação pode ser feita com um cabo USB comum.

Pronto!

Seu alarme já está funcionando!

Ele é simples, barato, e eficaz. Pode proteger janelas, portas, corredores etc.