<h1>Estação Meteorológica</h1>

## 1. Introdução
Este projeto visa desenvolver uma solução integrada para o monitoramento de condições meteorológicas, utilizando tecnologias de ponta em hardware e comunicações. Neste repositório, focaremos exclusivamente na montagem do hardware e na integração do sistema embarcado com um servidor remoto, detalhando cada componente usado, sua configuração e a interconexão necessária para a transmissão eficiente de dados.


<h3>Diagrama de comunicação</h3> 


## 2. Materiais e métodos
Nota: Neste projeto, não foi utilizado o sensor de temperatura e pressão BMP280 por problemas na utilização do material. Porém, o hardware e o software permitem sua utilização para integração na estação meteorológica

Esta seção descreve detalhadamente os componentes e processos utilizados na construção e operação da estação meteorológica.

<h3>Caracterização do sistema embarcado</h3>

ESP32: Um módulo microcontrolador com Wi-Fi e Bluetooth integrados, ideal para aplicações IoT.
DHT11: Sensor de temperatura e umidade, usado para medições ambientais básicas.
Pluviômetro: Dispositivo utilizado para medir a quantidade de precipitação.
Anemômetro Arduino SV10: Sensor utilizado para medir a velocidade do vento.
Indicador de direção do vento Arduino DV10: Sensor utilizado para determinar a direção do vento.
Diagrama dos componentes
O diagrama abaixo define a configuração física utilizada e a interconexão dos componentes da estação meteorológica: Diagrama PI_Grande

Imagem do WhatsApp de 2024-06-15 à(s) 17 48 53_0760c21e

<h3>Configuração de Ambiente Local</h3>

Para configurar o ambiente local, siga os passos abaixo. Este arquivo deve conter informações sensíveis como SSID e senha da rede WiFi, além da URL do servidor:

Navegue até a pasta main do seu projeto e crie um arquivo chamado settings.h.

Adicione as seguintes linhas ao arquivo:

const char* ssid = "SeuSSID";  // Substitua pelo SSID da sua rede
const char* password = "SuaSenha";  // Substitua pela senha da sua rede
String serverURL = "URLDoSeuServidor"; // Substitua pela URL do seu servidor
Configuração do ESP32
Instalação do Driver para o ESP32
Baixe e Instale o Driver:

Antes de conectar o ESP32 ao seu computador, é necessário instalar o driver adequado para garantir que o dispositivo seja reconhecido corretamente. Você pode encontrar o driver específico para o ESP32 no seguinte link: Instalação do Driver para ESP32 - RoboCore
Siga as instruções no site para baixar e instalar o driver correspondente ao seu sistema operacional.
Conectar o ESP32 ao Computador:

Após a instalação do driver, conecte o ESP32 ao computador usando um cabo USB. Se tudo estiver correto, o dispositivo deverá ser reconhecido e uma nova porta COM será listada no seu sistema.
Configuração no Arduino IDE
Instale o Arduino IDE:

Se ainda não instalou, baixe e instale o Arduino IDE diretamente do site oficial: Arduino - Software
Adicione a URL de Gerenciamento de Placas do ESP32:

Abra o Arduino IDE.

Vá em Arquivo > Preferências.

No campo "URLs Adicionais de Gerenciadores de Placas", adicione a seguinte URL para permitir a instalação do pacote do ESP32:

 https://dl.espressif.com/dl/package_esp32_index.json
Instale o Pacote do ESP32:

Acesse Ferramentas > Placa: > Gerenciador de Placas.
Na barra de pesquisa, digite "ESP32".
Localize "esp32 by Espressif Systems" e clique em "Instalar".
Selecionar a Placa ESP32 e a Porta COM:

Após a instalação do pacote, vá em Ferramentas > Placa e selecione o modelo do seu ESP32 na lista sob o título "ESP32-WROOM-DA Module".
Vá em Ferramentas > Porta e selecione a porta COM que aparece (associada ao ESP32).
Instalação das bibliotecas necessárias no Arduino IDE
Para instalar todas as bibliotecas necessárias, abra o Arduino IDE, vá em Sketch > Incluir Biblioteca > Gerenciar Bibliotecas, e procure e instale as seguintes bibliotecas:

Adafruit BMP280 Library by Adafruit
Adafruit BusIO by Adafruit
Adafruit Unified Sensor by Adafruit
ArduinoJson by Benoit
DHT sensor library by Adafruit
Descrição dos Problemas e Soluções
Problemas com a memória flash do esp32
Descrição do Problema: Às vezes, pode ser necessário apagar a memória flash do ESP32 para resolver problemas de estabilidade ou falhas ao carregar novos programas. Esse procedimento torna-se essencial especialmente se o botão de reset físico (RST) não estiver funcionando, impedindo um reinício suave do dispositivo.

Solução:

Instalar a Biblioteca esptool: O esptool é uma ferramenta em linha de comando que permite a comunicação com o chipset ESP para apagar ou gravar a memória flash.

Instale o esptool usando o pip, o gerenciador de pacotes Python:

 pip install esptool
Apagar a Memória Flash: Para apagar completamente a memória flash do ESP32, siga os passos abaixo. Este processo é útil para limpar configurações antigas que podem estar causando conflitos.

Abra o terminal ou prompt de comando.

Execute o seguinte comando para apagar a memória flash:

 python -m esptool --chip esp32 erase_flash
Verificação de Sucesso:

Após apagar a memória flash, reconecte o ESP32 ao seu computador e tente carregar um novo programa. Se o programa carregar e executar corretamente, isso indica que a memória foi apagada com sucesso.
Foto da montagem física
IMG_2254

Vídeo do sistema funcionando
Este vídeo demonstra a operação da estação meteorológica, enfocando a coleta e o registro de dados em tempo real: https://youtu.be/Y84vYU7VSpE

Orçamento
O levantamento dos preços de cada componente foi realizado através de pesquisa na internet, consultando sites especializados na venda de componentes eletrônicos como: Amazon, Eletrogate e Usinainfo. Como referência, o orçamento foi levantado em junho/2024. Todos os componentes utilizados na construção da estação e descritos na subseção de caracterização do sistema embarcado estão compilados na tabela:
